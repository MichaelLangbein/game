#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "./config.h"
#include "./datastructs/datastructs.h"


typedef struct RenderComponent {
    char* texture;
} RenderComponent;

typedef struct PositionComponent {
    int pos_x;
    int pos_y;
    int width;
    int height;
} PositionComponent;

typedef struct MotionComponent {
    int vel_x;
    int vel_y;
} MotionComponent;

typedef struct Components {
    PositionComponent* position;
    MotionComponent* motion;
    RenderComponent* render;
} Components;

typedef struct Entity {
    int id;
    Components* components;
} Entity;

void physicsSystem(Entity* entity, float deltaSecs) {
    if (!entity->components->position || !entity->components->motion) return;
    entity->components->position->pos_x += deltaSecs * entity->components->motion->vel_x;
    entity->components->position->pos_y += deltaSecs * entity->components->motion->vel_y;
}

void renderSystem(Entity* entity, float deltaSecs) {
    if (!entity->components->render || !entity->components->position) return;

    SLD_Texture* texture = textureCache(entity->components->render);
    SLD_Rect textureRect = { 
        entity->components->position->pos_x,
        entity->components->position->pos_y,
        entity->components->position->width,
        entity->components->position->height,
    };
    SDL_RenderCopy(renderer, texture, &textureRect, NULL);
}




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

void render(float deltaSecs) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // for (const entity of entities) {
    //     renderSystem(entity, deltaSecs);
    // }
    // SDL_Rect rect = { 100, 100, 50, 50 };
    // SDL_SetRenderDrawColor(renderer, 125, 50, 50, SDL_ALPHA_OPAQUE);
    // SDL_RenderFillRect(renderer, &rect);

    // swaps front- and back-buffer
    SDL_RenderPresent(renderer); 
}

int main() {

    initSDL();

    int loopStart = 0;
    int loopEnd = 0;
    float deltaSecs = 0.0;
    while (running == 1) {
        deltaSecs = (SDL_GetTicks() - loopEnd) / 1000;
        loopStart = SDL_GetTicks();

        handleEvents();
        render(deltaSecs);

        loopEnd = SDL_GetTicks();
        int waitTime = FRAME_TIME - (loopEnd - loopStart);
        if (waitTime > 0) SDL_Delay(waitTime);
    }

    cleanSDL();

    return 0;
}