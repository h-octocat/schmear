#include <stdlib.h>
#include <stdio.h>
#include "dynamicarray.h"
#include <string.h>

// creates dynamic array
DynamicArray createDA(int capacity, int sizeof_element) {
    void *array = calloc(capacity, sizeof_element);
    if (array == NULL) {
        printf("Error allocating memory to create dynamic array.");
        exit(-1);
    }
    return (DynamicArray){
        capacity, 0, sizeof_element, array
    };
}

// returns a pointer to an element in the array
void* getValue(DynamicArray *dn, int index) {
    if (index > (dn -> size)-1) {
        printf("\nIndex out of range!");
        exit(-1);
    } else {
        // converts the array to a char pointer,
        // which allows it to be stepped through byte by byte until the desired memory address is reached,
        // where it is then casted to a void pointer to be casted into the proper type and dereferenced
        return (void*)(((char *)(dn -> array))+ index*dn -> sizeof_element);
    }
}

// appends element to end of array
void appendDA(DynamicArray *dn, void* element) {
    dn -> size++;
    if (dn -> size > dn -> capacity) {
        dn -> capacity *= 2;
        dn -> array = realloc(dn -> array, (dn -> capacity) * dn -> sizeof_element);
        if (dn -> array == NULL) {
            printf("Error allocating memory to resize dynamic array.");
            exit(-1);
        }
    }
    memcpy(getValue(dn, dn -> size - 1), element, dn -> sizeof_element);
}

// prints the dynamic array out in the form of [e, e] (requires a printer helper function like so:)
// void printInt(void* value) {
//    printf("%d", *(int *) value);
// }
void printDA(DynamicArray dn, void (*print_elem)(void*)) {
    printf("[");
    for (int i = 0; i < dn.size - 1; i++) {
        print_elem(getValue(&dn, i));
        printf(", ");
    }
    print_elem(getValue(&dn, dn.size -1));
    printf("]\n");
}


// removes the last element from the array
void popDA(DynamicArray *dn) {
    if (dn -> size > 0 ) {
        dn -> size--;
    } else {
        printf("Dynamic array is too small to shrink.");
        exit(-1);
    }
}

// frees the dynamic array from the heap
void freeDA(DynamicArray *dn) {
    free(dn -> array);
}
