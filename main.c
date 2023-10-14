#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./config.h"
#include "./datastructs/datastructs.h"







SDL_Window* window;
SDL_Renderer* renderer;
int running = 1;



SDL_Texture* shipTexture; 

void initTextures() {
    shipTexture = IMG_LoadTexture(renderer, "/home/michael/Desktop/code/game/assets/textures/ship.png");
}

void cleanTextures() {
    SDL_DestroyTexture(shipTexture);
}



typedef struct PositionComponent {
    float pos_x;
    float pos_y;
    int width;
    int height;
} PositionComponent;

typedef struct MotionComponent {
    int vel_x;
    int vel_y;
} MotionComponent;

typedef struct RenderComponent {
    SDL_Texture* texture;
} RenderComponent;



#define NR_ENTITIES 1
#define ID_PLAYER 0

PositionComponent positionComponents[NR_ENTITIES];
MotionComponent motionComponents[NR_ENTITIES];
RenderComponent renderComponents[NR_ENTITIES];


void initComponents() {
    for (int i = 0; i < NR_ENTITIES; i++) {
        positionComponents[i] = (PositionComponent) { 0, 0, 0, 0 };
        motionComponents[i]   = (MotionComponent)   { 0, 0 };
        renderComponents[i]   = (RenderComponent)   { NULL };
    }

    positionComponents[ID_PLAYER] = (PositionComponent) { 100, 100, 100, 100 };
    motionComponents[ID_PLAYER]   = (MotionComponent)   { 10, 10 };
    renderComponents[ID_PLAYER]   = (RenderComponent)   { shipTexture };
}

void physicsSystem(int id, float deltaSecs) {
    positionComponents[id].pos_x += deltaSecs * motionComponents[id].vel_x;
    positionComponents[id].pos_y += deltaSecs * motionComponents[id].vel_y;
}

void renderSystem(int id, float deltaSecs) {
    if (renderComponents[id].texture == NULL) return;

    SDL_Texture* texture = renderComponents[id].texture;
    SDL_Rect destinationRect = { 
        positionComponents[id].pos_x,
        positionComponents[id].pos_y,
        positionComponents[id].width,
        positionComponents[id].height,
    };
    SDL_RenderCopy(renderer, texture, NULL, &destinationRect);
}




void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Failed to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!window) {
        printf("Failed to init window: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    // or SDL_GL_CreateContext if you want to do OpenGl
    if (!renderer) {
        printf("Failed to init renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void cleanSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_UP) printf("You pressed the up key. \n");
            break;
        default:
            break;
        }
    }
}

void update(float deltaSecs) {
    for (int i = 0; i < NR_ENTITIES; i++) {
        physicsSystem(i, deltaSecs);
    }
}

void render(float deltaSecs) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < NR_ENTITIES; i++) {
        renderSystem(i, deltaSecs);
    }

    SDL_RenderPresent(renderer); 
}

int main() {

    initSDL();
    initTextures();
    initComponents();

    int loopStart = 0;
    int processingEnd = 0;
    int loopEnd = 0;
    float lastLoopSecs = 0.0;
    while (running == 1) {
        lastLoopSecs = (loopEnd - loopStart) / 1000.0;
        loopStart = SDL_GetTicks();

        handleEvents();
        update(lastLoopSecs);
        render(lastLoopSecs);

        processingEnd = SDL_GetTicks();

        int waitTime = FRAME_TIME - (processingEnd - loopStart);
        if (waitTime > 0) SDL_Delay(waitTime);
        loopEnd = SDL_GetTicks();
    }

    cleanTextures();
    cleanSDL();

    return 0;
}