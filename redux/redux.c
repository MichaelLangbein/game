#include <stdlib.h>

#define REDUX_ACTION_INCREMENT 1
#define REDUX_ACTION_DECREMENT 2


typedef struct Action {
    int type;
    void* body;
} Action;


typedef struct ActionQueue {
    int capacity;
    int head;
    int tail;
    Action* actions;
} ActionQueue;

ActionQueue* createActionQueue(int capacity) {
    Action* actions = malloc(capacity * sizeof(Action));
    ActionQueue* queue = malloc(sizeof(ActionQueue));
    queue->actions = actions;
    queue->head = 0;
    queue->tail = 0;
    queue->capacity = capacity;
    return queue;
}

int addAction(ActionQueue* queue, int ActionType, void* body) {
    int newHead = (queue->head + 1) % queue->capacity;
    if (newHead == queue->tail) return -1;
    queue->head = newHead;
    Action m = (Action){ActionType, body};
    queue->actions[queue->head] = m;
    return 0;
}

Action* popAction(ActionQueue* queue) {
    if (queue->head == queue->tail) return NULL;
    Action a = queue->actions[queue->tail];
    int newTail = (queue->tail + 1) % queue->capacity;
    queue->tail = newTail;
    return &a;
}

void cleanActionQueue(ActionQueue* queue) {
    for (int i = 0; i < queue->capacity; i++) {
        free(queue->actions[i].body);
    }
    free(queue->actions);
    free(queue);
}



typedef struct State {
    int count;
} State;

State state;
ActionQueue* queue;

void Redux_init() {
    state = (State){0};
    queue = createActionQueue(50);
}

void Redux_clean() {
    cleanActionQueue(queue);
    // free(state);
}

void Redux_dispatch(int actionType, void* body) {
    addAction(&queue, actionType, body);
}

void Redux_handle(ActionQueue* queue) {
    Action* action;
    while (action = popAction(queue)) {
        Redux_reduce(action, &state);
        Redux_sideEffects(action, &state);
    }
}

void Redux_sideEffects(Action* action, State* state) {
    // @TODO
}

void Redux_reduce(Action* action, State* state) {
    switch (action->type) {
        case REDUX_ACTION_INCREMENT:
            state->count += 1;
            break;
        case REDUX_ACTION_DECREMENT:
            state->count -= 1;
            break;
        default:
            break;
    }
}