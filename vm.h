#pragma once
#include "chunk.h"
#include <stdint.h>
#define STACK_MAX 256

struct VM {
    // Although we already have the ip, which points to the Chunk's
    // opcodeArray, we need the Chunk for the valueArray
    Chunk chunk;

    // Points to the instruction about to be executed
    // Program counter/Instruction Pointer
    uint8_t *ip;

    // VM's stack
    Value stack[STACK_MAX];

    // points to the value past the last value on the stack
    Value* stackTop;

    // tells free functions if the chunk has been freed or not
    bool liveChunk;
};

typedef struct VM VM;

enum InterpretResult {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
};

typedef enum InterpretResult InterpretResult;


void initVM();
// interprets a source code
InterpretResult interpret(char *source);
void freeVM();
