# Includes are header files without a concrete implementation.
INCLUDES = -I/usr/include/SDL2 -D_REENTRANT
# Libraries are object files. -L adds a directory of libraries, -l adds a single library. 
LIBS = -lSDL2
WARNINGS = -Wall -Wextra

# Compiling
#   -c: compile (nur compile, nicht link!)
#   -g: fuer debugger
main.o: main.c
	gcc -g -c $(WARNINGS) $(INCLUDES) main.c

# Linking
# 	-o: object-file: name der fertigen binary
# 	-g: fuer debugger
main: main.o
	gcc -g -o main main.o $(LIBS)

clean:
	rm *.o

run: main
	./main

valgrind: main
	valgrind -v --leak-check=full --show-leak-kinds=all --log-file=val.log ./main

all: main clean
