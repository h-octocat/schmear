#include "vm.h"
#include "chunk.h"
#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "dynamicarray.h"
#include "value.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// there is always one vm
VM vm;

static void resetStack() {
	// resets the stack pointer to the beginning of the stack
	vm.stackTop = vm.stack;
}

void initVM() { resetStack(); }

Value popStack() {
	// decrement pointer and then dereference it
	return *(--vm.stackTop);
}

// gives the value distance values deep into the stack (0 is the top, 1 is 1 in, etc.)
Value peekStack(int distance) { return vm.stackTop[-1 - distance]; }

void pushStack(Value value) {

	if (vm.stackTop == &vm.stack[STACK_MAX]) {
		printf("Stack overflow at line %d!",
		       *(int *)getValue(&vm.chunk.lineArray,
					(int)(vm.ip - (uint8_t *)vm.chunk.opcodeArray.array)));
		exit(-1);
	}
	*vm.stackTop = value;
	vm.stackTop++;
}

static void runtimeError(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);

	size_t instruction = vm.ip - ((uint8_t *)vm.chunk.opcodeArray.array) - 1;
	int line = getLineNumber(&vm.chunk, instruction);
	fprintf(stderr, "[line %d] in code\n", line);
	resetStack();
}

static bool isFalsey(Value value) { return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value)); }

InterpretResult run() {
	// gets the next opcode and constant and increments the instruction pointer
#define GET_OPCODE() (*vm.ip++)
#define GET_CONSTANT() (getConstant(&vm.chunk, GET_OPCODE()))

// instead of popping two values, just get the values and move the pointer seperately
#define BINARY_OP(val_function, op) \
	do { \
		if (!IS_NUMBER(peekStack(0)) || !IS_NUMBER(peekStack(0))) { \
			runtimeError("Operands must be numbers."); \
			return INTERPRET_RUNTIME_ERROR; \
		} \
		double b = AS_NUMBER(popStack()); \
		double a = AS_NUMBER(popStack()); \
		pushStack(val_function(a op b)); \
	} while (0)

	for (;;) {
// prints out a trace
#ifdef DEBUG_TRACE_EXECUTION
		printf("Instruction: ");
		// vm.ip - (uint8_t *)vm.chunk.opcodeArray.array is the index of the current
		// opcode in the chunk's opcodearray because it is: the address of the
		// instruction pointer which points to the element of the opcodeArray we are
		// on minus the first index (what dynamicarray.array points to) and we cast
		// it to a byte pointer because the DynamicArray uses generic void pointers
		disassembleInstruction(vm.chunk, vm.ip - (uint8_t *)vm.chunk.opcodeArray.array);
		printf(" Stack: ");
		for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
			printf("[");
			printValue(*slot);
			printf("]");
			printf(" ");
		}
		printf("\n");
#endif
		uint8_t instruction;
		switch (instruction = GET_OPCODE()) {
		case OP_RETURN:
			printValue(popStack());
			printf("\n");
			return INTERPRET_OK;
		case OP_CONSTANT: {
			Value constant = GET_CONSTANT();
			// printValue(constant);
			// printf("\n");
			pushStack(constant);
			break;
		}
		case OP_NEGATE:
			if (!IS_NUMBER(peekStack(0))) {
				runtimeError("Only numbers can be negated.");
				return INTERPRET_RUNTIME_ERROR;
			}
			pushStack(NUMBER_VAL(-AS_NUMBER(popStack())));
			break;
		case OP_ADD:
			BINARY_OP(NUMBER_VAL, +);
			break;
		case OP_DIVIDE:
			BINARY_OP(NUMBER_VAL, /);
			break;
		case OP_MULTIPLY:
			BINARY_OP(NUMBER_VAL, *);
			break;
		case OP_SUBTRACT:
			BINARY_OP(NUMBER_VAL, -);
			break;
		case OP_FALSE:
			pushStack(BOOL_VAL(false));
			break;
		case OP_TRUE:
			pushStack(BOOL_VAL(true));
			break;
		case OP_NIL:
			pushStack(NIL_VAL);
			break;
		case OP_NOT:
			pushStack(BOOL_VAL(isFalsey(popStack())));
			break;
		case OP_EQUAL: {
			Value b = popStack();
			Value a = popStack();
			pushStack(BOOL_VAL(valuesEqual(a, b)));
			break;
		}
		case OP_GREATER:
			BINARY_OP(BOOL_VAL, >);
			break;
		case OP_LESS:
			BINARY_OP(BOOL_VAL, <);
			break;
		}
	}

#undef GET_CONSTANT
#undef GET_OPCODE
#undef BINARY_OP
}

// InterpretResult interpret(Chunk chunk) {
// 	vm.ip = (uint8_t *)chunk.opcodeArray.array;
// 	vm.chunk = chunk;
// 	return run();
// }

InterpretResult interpret(char *source) {
	Chunk chunk = createChunk();
	if (!compile(source, &chunk)) {
		freeChunk(&chunk);
		vm.liveChunk = false;
		return INTERPRET_COMPILE_ERROR;
	}

	vm.chunk = chunk;
	vm.liveChunk = true;
	vm.ip = chunk.opcodeArray.array;

	InterpretResult result = run();

	freeChunk(&chunk);
	vm.liveChunk = false;
	return result;
}

void freeVM() {
	if (vm.liveChunk) {
		freeChunk(&vm.chunk);
	};
}
