#pragma once

// wrapper function for appendDA to simplify usage
#define DA_APPEND(dn, value) \
  do { \
    typeof(value) temp = value; \
    appendDA(dn, &temp); \
  } while (0)

struct DynamicArray {
    int capacity;
    int size;
    int sizeof_element;
    void *array;
};

typedef struct DynamicArray DynamicArray;

void popDA(DynamicArray *dn);
void printDA(DynamicArray dn, void (*print_func)(void *));
void appendDA(DynamicArray *dn, void* element);
void freeDA(DynamicArray *dn);
void* getValue(DynamicArray *dn, int index);
DynamicArray createDA(int capacity, int sizeof_element);
