#include <stdlib.h>
#include <stdio.h>
#include "./datastructs.h"

void Ll_testWithInts() {

    // Ll is designed to hold arbitrary data.
    // For that, its data is stored as a void*.
    // The easiest way to provide data that'll be passed
    // as a void* is assigning an array.
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    LlNode* ll = Ll_create(&arr[0]);
    for (int i = 1; i < 9; i++) {
        Ll_append(ll, &arr[i]);
    }

    LlNode* current = ll;
    while (current->next != NULL) {
        int val = *(int*)(current->data);
        printf("Value: %d\n", val);
        current = current->next;
    }

    Ll_clean(ll, 0);
}


typedef struct Entity {
    char* name;
} Entity;

Entity* createEntity(char* name) {
    Entity* entity = malloc(sizeof(Entity));
    entity->name = name;
    return entity;
}

void Ll_testWithStructs() {
    Entity* player = createEntity("player");
    Entity* ball = createEntity("ball");
    LlNode* ll = Ll_create(player);
    Ll_append(ll, ball);
    Ll_clean(ll, 1);

    // No need to free data: already freed in Ll_clean.
    // free(player);
    // free(ball);
}

void Q_test() {
    Entity* a = createEntity("Andy");
    Entity* b = createEntity("Babs");
    Entity* c = createEntity("Charles");

    Queue* queue = Queue_create(a);
    Queue_push(queue, b);
    Queue_push(queue, c);

    Entity* retrieved = Queue_pop(queue);
    printf("Retrieved from queue: %s\n", retrieved->name);

    Entity* retrieved2 = Queue_pop(queue);
    printf("Retrieved from queue: %s\n", retrieved2->name);

    Queue_clean(queue, 1);
    // queue could only clean those items still known to it.
    // all others must be free'd here.
    free(retrieved2);
    free(retrieved);
    // free(a);
}

int main() {

    Ll_testWithInts();
    Ll_testWithStructs();
    Q_test();

    
    return 0;
}