#ifndef datastructs_HEADER
#define datastructs_HEADER


typedef struct LlNode LlNode;
struct LlNode {
    LlNode* next;
    LlNode* prev;
    void* data;
};

LlNode* Ll_create(void* val);

void Ll_clean(LlNode* startNode, int includeData);

LlNode* Ll_last(LlNode* startNode);

LlNode* Ll_first(LlNode* startNode);

LlNode* Ll_append(LlNode* startNode, void* newVal);


#endif