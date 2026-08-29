#pragma once
#include <stddef.h>

// wrapper function for appendDA to simplify usage
#define DA_APPEND(dn, value) \
  do { \
    typeof(value) temp = value; \
    appendDA(dn, &temp); \
  } while (0)

struct DynamicArray {
    // size of underlying buffer
    int capacity;

    // size of array
    int size;

    // size of the element in bytes
    size_t sizeof_element;

    // pointer to the first address of raw buffer
    void *array;
};

typedef struct DynamicArray DynamicArray;

void popDA(DynamicArray *dn);
void printDA(DynamicArray dn, void (*print_func)(void *));
void appendDA(DynamicArray *dn, void* element);
void freeDA(DynamicArray *dn);
void* getValue(DynamicArray *dn, int index);
DynamicArray createDA(int capacity, int sizeof_element);
