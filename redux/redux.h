#ifndef redux_HEADER
#define redux_HEADER

#define REDUX_ACTION_UP 1;
#define REDUX_ACTION_RIGHT 2;
#define REDUX_ACTION_DOWN 3;
#define REDUX_ACTION_LEFT 4;

void Redux_init();

void Redux_dispatch(int actionType, void* body);

void Redux_handle();

void Redux_clean();

#endif