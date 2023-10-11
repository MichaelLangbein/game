#include <stdlib.h>
#include "./utils.h"

int main() {

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

    Ll_clean(ll);
    
    return 0;
}