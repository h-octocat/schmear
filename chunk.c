#include "chunk.h"
#include "common.h"
#include "dynamicarray.h"
#include "value.h"
#include <stdio.h>

Chunk createChunk() {
    return (Chunk) {createDA(10, sizeof(uint8_t)), createDA(10, sizeof(Value)), createDA(10, sizeof(int))};
}

void appendOpcode(Chunk *chunk, uint8_t opcode) {
    DA_APPEND(&chunk -> opcodeArray, opcode);
}

uint8_t getOpcode(Chunk *chunk, int index) {
    return *(uint8_t*) getValue(&chunk -> opcodeArray, index);
}

void freeChunk(Chunk *chunk) {
    freeDA(&chunk -> opcodeArray);
}

int addConstant(Chunk *chunk, Value value) {
   DA_APPEND(&chunk -> valueArray, value);
   return chunk -> valueArray.size - 1;
}

Value getConstant(Chunk *chunk, int index) {
    return *(Value*) getValue(&chunk -> valueArray, index);
}
