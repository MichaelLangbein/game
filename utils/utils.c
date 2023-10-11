#include <stdlib.h>
#include "./utils.h"


LlNode* Ll_create(void* val) {
    LlNode* node = malloc(sizeof(LlNode));
    node->data = val;
    return node;
}

void Ll_clean(LlNode* startNode) {
    if (startNode->next != NULL) {
        Ll_clean(startNode->next);
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

LlNode* Ll_append(LlNode* startNode, void* newVal) {
    LlNode* newNode = Ll_create(newVal);
    LlNode* lastNode = Ll_last(startNode);
    lastNode->next = newNode;
    return newNode;
}


