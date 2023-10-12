#define REDUX_ACTION_INCREMENT 1
#define REDUX_ACTION_DECREMENT 2


typedef struct Action {
    int type;
} Action;

typedef struct State {
    int count;
} State;

State state = {0};

void Redux_dispatch(Action* action) {
    Redux_reduce(action, &state);
    Redux_sideEffects(action, &state);
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