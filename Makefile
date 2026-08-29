all:
	clang chunk.c debug.c dynamicarray.c value.c vm.c main.c compiler.c scanner.c -o bin/schmear

debug:
	clang -fsanitize=address -g chunk.c debug.c dynamicarray.c value.c vm.c main.c compiler.c scanner.c -o bin/schmear

run:
	./bin/schmear
