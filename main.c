#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./config.h"
#include "./datastructs/datastructs.h"







SDL_Window* window;
SDL_Renderer* renderer;
int running = 1;



#define TEXTURE_SHIP 1
SDL_Texture* shipTexture; 

void initTextureCache() {
    shipTexture = IMG_LoadTexture(renderer, "./assets/textures/ship.png");
}

void cleanTextureCache() {
    SDL_DestroyTexture(shipTexture);
}

SDL_Texture* textureCache(int textureId) {
    switch (textureId) {
    case TEXTURE_SHIP:
        return shipTexture;
    default:
        printf("No such texture %d \n", textureId);
        return NULL;
    }
}





typedef struct RenderComponent {
    int textureId;
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

Components* Components_create() {
    Components* c = malloc(sizeof(Components));
    c->motion = NULL;
    c->position = NULL;
    c->render = NULL;
}

void Components_clear(Components* c) {
    if (c->motion) free(c->motion);
    if (c->position) free(c->position);
    if (c->render) free(c->render);
    free(c);
}

typedef struct Entity {
    int id;
    Components* components;
} Entity;

int entityCount = 0;

Entity* Entity_create() {
    entityCount += 1;
    Entity* e = malloc(sizeof(Entity));
    e->id = entityCount;
    e->components = Components_create();
    return e;
}

void Entity_addPosition(Entity* e, int x, int y, int width, int height) {
    PositionComponent* pos = malloc(sizeof(PositionComponent));
    pos->pos_x = x;
    pos->pos_y = y;
    pos->width = width;
    pos->height = height;
    e->components->position = pos;
}

void Entity_addRender(Entity* e, int textureId) {
    RenderComponent* r = malloc(sizeof(RenderComponent));
    r->textureId = textureId;
    e->components->render = r;
}

void Entity_free(Entity* e) {
    Components_clear(e->components);
    free(e);
}

void physicsSystem(Entity* entity, float deltaSecs) {
    if (!entity->components->position || !entity->components->motion) return;
    entity->components->position->pos_x += deltaSecs * entity->components->motion->vel_x;
    entity->components->position->pos_y += deltaSecs * entity->components->motion->vel_y;
}

void renderSystem(Entity* entity, float deltaSecs) {
    if (!entity->components->render || !entity->components->position) return;

    SDL_Texture* texture = textureCache(entity->components->render->textureId);
    SDL_Rect textureRect = { 
        entity->components->position->pos_x,
        entity->components->position->pos_y,
        entity->components->position->width,
        entity->components->position->height,
    };
    SDL_RenderCopy(renderer, texture, &textureRect, NULL);
}



Entity* entities[1];
void initEntities() {
    Entity* player = Entity_create();
    Entity_addPosition(player, 100, 100, 100, 100);
    Entity_addRender(player, TEXTURE_SHIP);
    entities[0] = player;
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
    for (int i = 0; i < entityCount; i++) {
        physicsSystem(entities[i], deltaSecs);
    }
}

void render(float deltaSecs) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (int i = 0; i < entityCount; i++) {
        renderSystem(entities[i], deltaSecs);
    }

    // swaps front- and back-buffer
    SDL_RenderPresent(renderer); 
}

int main() {

    initSDL();
    initTextureCache();
    initEntities();

    int loopStart = 0;
    int loopEnd = 0;
    float deltaSecs = 0.0;
    while (running == 1) {
        deltaSecs = (SDL_GetTicks() - loopEnd) / 1000;
        loopStart = SDL_GetTicks();

        handleEvents();
        update(deltaSecs);
        render(deltaSecs);

        loopEnd = SDL_GetTicks();
        int waitTime = FRAME_TIME - (loopEnd - loopStart);
        if (waitTime > 0) SDL_Delay(waitTime);
    }

    cleanSDL();
    cleanTextureCache();

    return 0;
}