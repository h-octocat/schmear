#pragma once
#include "chunk.h"
#include "scanner.h"
#include <stdbool.h>

struct Parser {
	Token current;
	Token previous;

	// so the compile function knows if compilation was a sucess and what to return
	bool hadError;

	// we stop execution
	bool panicMode;
};

enum Precedence {
    PREC_NONE,
    PREC_ASSIGNMENT, // =
    PREC_OR, // or
    PREC_AND, // and
    PREC_EQUALITY, // == !=
    PREC_COMPARISON, // < > <= >=
    PREC_TERM, // + -
    PREC_FACTOR, // * /
    PREC_UNARY, // ! -
    PREC_CALL, // . ()
    PREC_PRIMARY
};

typedef enum Precedence Precedence;

typedef void (*ParseFn) ();

struct ParseRule {
    ParseFn prefix;
    ParseFn infix;
    Precedence precedence;
};


typedef struct Parser Parser;
typedef struct ParseRule ParseRule;


bool compile (char * source, Chunk * chunk);
