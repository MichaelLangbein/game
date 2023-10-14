#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./config.h"
#include "./ecs/ecs.h"



SDL_Window* window;
SDL_Renderer* renderer;
int running = 1;



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
        renderSystem(i, deltaSecs, renderer);
    }

    SDL_RenderPresent(renderer); 
}

int main() {

    initSDL();
    initTextures(renderer);
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