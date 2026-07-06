#include "common.h"
#include "dynamicarray.h"
#include "value.h"
#pragma once

typedef enum {
    OP_RETURN,
    OP_CONSTANT,
} OpCode;

struct Chunk {
    // list of opcodes
    DynamicArray opcodeArray;
    // list of constants
    DynamicArray valueArray;
    // list of line numbers (to spam user with error messages)
    DynamicArray lineArray;
};

typedef struct Chunk Chunk;

Chunk createChunk();
void appendOpcode(Chunk *chunk, uint8_t opcode);
void freeChunk(Chunk *chunk);
uint8_t getOpcode(Chunk *chunk, int index);
int addConstant(Chunk *chunk, Value value);
Value getConstant(Chunk *chunk, int index);
