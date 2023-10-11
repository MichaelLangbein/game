# Includes are header files without a concrete implementation.
INCLUDES = -I/usr/include/SDL2 -D_REENTRANT
# Libraries are object files. -L adds a directory of libraries, -l adds a single library. 
LIBS = -lSDL2
WARNINGS = -Wall -Wextra

# Compiling
#   -c: compile (nur compile, nicht link!)
#   -g: fuer debugger
# Linking
# 	-o: object-file: name der fertigen binary
# 	-g: fuer debugger

utils.o: utils/utils.c
	gcc -g -c $(WARNINGS) $(INCLUDES) utils/utils.c

utils.test: utils/utils.test.c utils.o
	gcc -g -c $(WARNINGS) $(INCLUDES) utils/utils.test.c
	gcc -g -o utils.test utils.test.o utils.o $(LIBS)
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=utils.test.log ./utils.test

main.o: main.c
	gcc -g -c $(WARNINGS) $(INCLUDES) main.c

main: main.o utils.o
	gcc -g -o main main.o utils.o $(LIBS)

clean:
	rm *.o

run: main
	./main

valgrind: main
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=val.log ./main

all: main clean
