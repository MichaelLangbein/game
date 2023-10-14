#include <stdio.h>
#include "./ecs.h"

/**
 * Including an array here to see if valgrind picks it up as a memory leak.
 * Turns out it doesn't: this array is placed on the stack, not the heap,
 * and goes out of scope once main does.
*/
int data[] = {1, 2, 3};

int main() {
    return 0;
}