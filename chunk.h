#pragma once
#include "common.h"
#include "dynamicarray.h"
#include "value.h"


typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_NIL,
    OP_FALSE,
    OP_TRUE,
    OP_GREATER,
    OP_EQUAL,
    OP_LESS,
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_DIVIDE,
    OP_MULTIPLY,
    OP_NOT
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

// Create and free chunk

Chunk createChunk();
void freeChunk(Chunk *chunk);

// Append and get opcode

void appendChunk(Chunk *chunk, uint8_t opcode, int lineNumber);
uint8_t getOpcode(Chunk *chunk, int index);

// Add and get constants

int addConstant(Chunk *chunk, Value value);
Value getConstant(Chunk *chunk, int index);

// Add and get lineNumber

int getLineNumber(Chunk *chunk, int index);
void appendLineNumber(Chunk *chunk, int lineNumber);
