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


// removes one (potentially middle) entry from list,
// connects left and right again.
// returns the node to the *right* of the removed node.
LlNode* Ll_splice(LlNode* node) {
    if (node->prev) {
        node->prev->next = NULL;
    }
    if (node->next) {
        node->next->prev = NULL;
    }
    if (node->prev && node->next) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    return node->next;
}

// removes start-entry from list,
// returns ref to new start
LlNode* Ll_shift(LlNode* startNode) {
    LlNode* first = Ll_first(startNode);
    LlNode* startAfterShift = Ll_splice(first);
    return startAfterShift;
}







Queue* Queue_create(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->start = 0;
    queue->end = 0;
    queue->data = malloc(capacity * sizeof(void*));
    return queue;
}

int Queue_push(Queue* queue, void* datum) {
    int newEnd = (queue->end + 1) % queue->capacity;
    if (newEnd == queue->start) return -1;
    queue->end = newEnd;
    queue->data[queue->end] = datum;
    return queue->end;
}

void* Queue_pop(Queue* queue) {
    void* datum = queue->data[queue->start];
    int newStart = (queue->start + 1) % queue->capacity;
    queue->start += newStart;
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