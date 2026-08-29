#pragma once
#include "common.h"
#include "chunk.h"

void disassembleChunk(Chunk chunk, char* name);
int disassembleInstruction(Chunk chunk, int index);
