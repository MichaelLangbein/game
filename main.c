#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "./config.h"


SDL_Window* window;
SDL_Renderer* renderer;
int running = 1;

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Failed to init SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
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

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // SDL_SetRenderDrawColor(renderer, 125, 76, 76, SDL_ALPHA_OPAQUE);
    SDL_Rect rect = { 100, 100, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 125, 50, 50, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    // swaps front- and back-buffer
    SDL_RenderPresent(renderer); 
}

int main() {
    initSDL();

    while (running == 1) {
        handleEvents();
        render();       
    }

    cleanSDL();

    return 0;
}