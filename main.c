
#include "common.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

static char *readFile(const char *path) {
	// open the file
	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("Could not open file %s!", path);
		exit(74);
	}

	// seek to the end, where you can get the
	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char *buffer = (char *)malloc(fileSize + 1);

	if (buffer == NULL) {
		printf("Error allocating memory for file read for %s.", path);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	buffer[bytesRead] = '\0';
	if (bytesRead < fileSize) {
		printf("Error reading file %s!", path);
	}

	fclose(file);
	return buffer;
}

static void runFile(char *path) {
	char *contents = readFile(path);
	InterpretResult result = interpret(contents);
	free(contents);

	if (result == INTERPRET_COMPILE_ERROR)
		exit(65);
	if (result == INTERPRET_RUNTIME_ERROR)
		exit(70);
}

static void repl() {
	char line[1024];
	for (;;) {
		printf("schmear> ");

		if (!fgets(line, sizeof(line), stdin)) {
			printf("\n");
			break;
		}

		interpret(line);
	}
}

int main(int argc, char *argv[]) {
	initVM();

	if (argc == 1) {
		repl();
	} else if (argc == 2) {
		runFile(argv[1]);
	} else {
		fprintf(
		    stderr,
		    "Usage: 'schmear [path]' to execute a schmear file or 'schmear' for a REPL.");
		exit(64);
	}

	freeVM();
	return 0;
}
