#include "debug.h"
#include "chunk.h"
#include "value.h"
#include <stdint.h>
#include <stdio.h>

int printSimpleInstruction(char *name) {
	printf(" %s", name);
	return 1;
}

// takes index and chunk so it can lookup constant in the array
int printConstantInstruction(char *name, Chunk chunk, int index) {
	// index for the constant in the constant array
	int constantIndex = (int)getOpcode(&chunk, index + 1);
	Value value = getConstant(&chunk, constantIndex);

	printf(" %s: ", name);
	printValue(value);
	return 2;
}

int disassembleInstruction(Chunk chunk, int index) {
	switch (getOpcode(&chunk, index)) {
	case OP_RETURN:
		return printSimpleInstruction("OP_RETURN");
		break;
	case OP_CONSTANT:
		return printConstantInstruction("OP_CONSTANT", chunk, index);
		break;
	case OP_NEGATE:
		return printSimpleInstruction("OP_NEGATE");
		break;
	case OP_ADD:
		return printSimpleInstruction("OP_ADD");
		break;
	case OP_DIVIDE:
		return printSimpleInstruction("OP_DIVIDE");
		break;
	case OP_MULTIPLY:
		return printSimpleInstruction("OP_MULTIPLY");
		break;
	case OP_SUBTRACT:
		return printSimpleInstruction("OP_SUBTRACT");
		break;
	case OP_TRUE:
		return printSimpleInstruction("OP_TRUE");
		break;
	case OP_FALSE:
		return printSimpleInstruction("OP_FALSE");
		break;
	case OP_NIL:
		return printSimpleInstruction("OP_NIL");
		break;
	case OP_NOT:
		return printSimpleInstruction("OP_NOT");
		break;
	case OP_EQUAL:
		return printSimpleInstruction("OP_EQUAL");
		break;
	case OP_GREATER:
		return printSimpleInstruction("OP_GREATER");
		break;
	case OP_LESS:
		return printSimpleInstruction("OP_LESS");
		break;
	default:
		printf("Invalid opcode!");
		return 1;
	}
}

// prints each opcode in the chunk
void disassembleChunk(Chunk chunk, char *name) {
	printf("-- %s --\n", name);
	int pastLine;

	for (int i = 0; i < chunk.opcodeArray.size;) {
		int currentLine = getLineNumber(&chunk, i);
		printf("%04d", i);
		if (pastLine == currentLine) {
			printf("   |");
		} else {
			printf("   %d", currentLine);
		}
		i += disassembleInstruction(chunk, i);
		pastLine = currentLine;
		printf("\n");
	}
}
