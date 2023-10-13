# Includes are header files without a concrete implementation.
INCLUDES = -I/usr/include/SDL2 -D_REENTRANT
# Libraries are object files. -L adds a directory of libraries, -l adds a single library. User -l:SDL2 (note the :) to link statically.
LIBS = -lSDL2
WARNINGS = -Wall -Wextra

# Compiling
#   -c: compile (nur compile, nicht link!)
#   -g: fuer debugger
# Linking
# 	-o: object-file: name der fertigen binary
# 	-g: fuer debugger

datastructs.o: datastructs/datastructs.c
	gcc -g -c $(WARNINGS) $(INCLUDES) datastructs/datastructs.c

datastructs.test: datastructs/datastructs.test.c datastructs.o
	gcc -g -c $(WARNINGS) $(INCLUDES) datastructs/datastructs.test.c
	gcc -g -o datastructs.test datastructs.test.o datastructs.o $(LIBS)
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=datastructs.test.log ./datastructs.test

main.o: main.c
	gcc -g -c $(WARNINGS) $(INCLUDES) main.c

main: main.o datastructs.o
	gcc -g -o main main.o datastructs.o $(LIBS)

clean:
	rm -r *.o
	rm -r *.test
	rm -r *.log

run: main
	./main

valgrind: main
	valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=val.log ./main

all: main clean run
