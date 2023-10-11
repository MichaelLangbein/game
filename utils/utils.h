#ifndef UTILS_HEADER
#define UTILS_HEADER


typedef struct LlNode LlNode;
struct LlNode {
    LlNode* next;
    void* data;
};

LlNode* Ll_create(void* val);

void Ll_clean(LlNode* startNode);

LlNode* Ll_last(LlNode* startNode);

LlNode* Ll_append(LlNode* startNode, void* newVal);


#endif