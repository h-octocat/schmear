#pragma once
#include <stdbool.h>

enum ValueType {
VAL_BOOL,
VAL_NIL,
VAL_NUMBER
};

typedef enum ValueType ValueType;

struct Value {
    ValueType type;
    union {
        double number;
        bool boolean;
    } as;
};

// turn c variables into values
#define BOOL_VAL(value)  ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL  ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})

// turn values into c variables
#define AS_BOOL(value) ((bool)value.as.boolean)
#define AS_NUMBER(value) ((double)value.as.number)

// check types of values
#define IS_BOOL(value) (value.type == VAL_BOOL)
#define IS_NIL(value) (value.type == VAL_NIL)
#define IS_NUMBER(value) (value.type == VAL_NUMBER)

typedef struct Value Value;

void printValue(Value value);
bool valuesEqual(Value a, Value b);
