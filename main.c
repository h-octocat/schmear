#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, char* argv[]) {
    Chunk chunk = createChunk();
    appendOpcode(&chunk, OP_RETURN);

    int constantIndex = addConstant(&chunk, 1.2);
    appendOpcode(&chunk, OP_CONSTANT);
    appendOpcode(&chunk, constantIndex);

    disassembleChunk(chunk, "chunk1");
    freeChunk(&chunk);
    return 0;
}
