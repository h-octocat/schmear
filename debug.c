#include "debug.h"
#include "value.h"
#include <stdio.h>

int printSimpleInstruction(char * name) {
    printf(" %s", name);
    return 1;
}

// takes index and chunk so it can lookup constant in the array
int printConstantInstruction(char *name, Chunk chunk, int index) {
    // index for the constant in the constant array
    int constantIndex = (int) getOpcode(&chunk, index+1);
    Value value = getConstant(&chunk, constantIndex);

    printf(" %s: ", name);
    printValue(value);
    return 2;
}

void disassembleChunk(Chunk chunk, char *name) {
    printf("-- %s --\n", name);
    for (int i = 0; i < chunk.opcodeArray.size;) {
        printf("%04d", i);
        switch (getOpcode(&chunk, i)) {
            case OP_RETURN:
                i += printSimpleInstruction("OP_RETURN");
                break;
            case OP_CONSTANT:
                i += printConstantInstruction("OP_CONSTANT", chunk, i);
                break;
            default:
                printf("Invalid opcode!");
                i++;
        }
        printf("\n");
    }
}
