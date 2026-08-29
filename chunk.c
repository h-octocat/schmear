#include "chunk.h"
#include "dynamicarray.h"
#include "value.h"
#include <stdio.h>

// initializes the chunk's dynamic arrays (opcodes, constants, and line numbers)
Chunk createChunk() {
	return (Chunk){createDA(10, sizeof(uint8_t)), createDA(10, sizeof(Value)),
		       createDA(10, sizeof(int))};
}

// appends an opcode to the chunk
void appendChunk(Chunk *chunk, uint8_t opcode, int lineNumber) {
	DA_APPEND(&chunk->opcodeArray, opcode);
	DA_APPEND(&chunk->lineArray, lineNumber);
}

// wrapper for getValue
uint8_t getOpcode(Chunk *chunk, int index) {
	return *(uint8_t *)getValue(&chunk->opcodeArray, index);
}

// frees the chunk
void freeChunk(Chunk *chunk) {
	freeDA(&chunk->opcodeArray);
	freeDA(&chunk->lineArray);
	freeDA(&chunk->valueArray);
}

// wrapper for DA_APPEND
int addConstant(Chunk *chunk, Value value) {
	DA_APPEND(&chunk->valueArray, value);
	return chunk->valueArray.size - 1;
}

// wrapper for getValue
Value getConstant(Chunk *chunk, int index) { return *(Value *)getValue(&chunk->valueArray, index); }

// wrapper for DA_APPEND
void appendLineNumber(Chunk *chunk, int lineNumber) { DA_APPEND(&chunk->lineArray, lineNumber); }

// wrapper for getValue
int getLineNumber(Chunk *chunk, int index) { return *(int *)getValue(&chunk->lineArray, index); }
