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
    newNode->prev = lastNode;
    return newNode;
}


// Removes one (potentially middle) entry from list,
// connects left and right again.
// Returns the node to the *right* of the removed node.
// The LlNode is free'd in the process.
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
    LlNode* next = node->next;
    free(node);
    return next;
}

// Removes start-entry from list,
// returns ref to new start.
// The LlNode is free'd in the process.
LlNode* Ll_shift(LlNode* startNode) {
    LlNode* first = Ll_first(startNode);
    LlNode* startAfterShift = Ll_splice(first);
    return startAfterShift;
}







Queue* Queue_create(void* datum) {
    Queue* queue = malloc(sizeof(Queue));
    queue->data = Ll_create(datum);
    return queue;
}

void Queue_push(Queue* queue, void* datum) {
    Ll_append(queue->data, datum);
}

void* Queue_pop(Queue* queue) {
    LlNode* node = queue->data;
    void* datum = node->data;
    void* newStart = Ll_shift(node);
    queue->data = newStart;
    return datum;
}

void Queue_clean(Queue* queue, int includeData) {
    Ll_clean(queue->data, includeData);
    free(queue);
}