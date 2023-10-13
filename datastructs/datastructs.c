#include <stdlib.h>
#include "./datastructs.h"


LlNode* Ll_create(void* val) {
    LlNode* node = malloc(sizeof(LlNode));
    node->next = NULL;
    node->prev = NULL;
    node->data = val;
    return node;
}

/**
 * Cleans only from the current node downstream,
 * not upstream.
*/
void Ll_clean(LlNode* startNode, int includeData) {
    if (startNode->next != NULL) {
        Ll_clean(startNode->next, includeData);
    }
    if (includeData > 0) {
        free(startNode->data);
    }
    free(startNode);
}

LlNode* Ll_last(LlNode* startNode) {
    LlNode* currentNode = startNode;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

LlNode* Ll_first(LlNode* startNode) {
    LlNode* currentNode = startNode;
    while (currentNode->prev != NULL) {
        currentNode = currentNode->next;
    }
    return currentNode;
}

LlNode* Ll_append(LlNode* startNode, void* newVal) {
    LlNode* newNode = Ll_create(newVal);
    LlNode* lastNode = Ll_last(startNode);
    lastNode->next = newNode;
    return newNode;
}


typedef struct Queue {
    int capacity;
    int start;
    int end;
    void* data;
} Queue;

Queue* Queue_create(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->start = 0;
    queue->end = 0;
    queue->data = malloc(capacity * sizeof(void*));
    return queue;
}

int Queue_push(Queue* queue, void* datum) {
    queue->end += 1;
    queue->data[queue->end] = datum;
    return queue->end;
}

void* Queue_pop(Queue* queue) {
    void* datum = queue->data[queue->start];
    queue->start += 1;
    return datum;
}

void Queue_clean(Queue* queue, int includeData) {
    if (includeData > 0) {
        for (int i = 0; i < queue->capacity; i++) {
            free(queue->data[i]);
        }
    }
    free(queue->data);
    free(queue);
}