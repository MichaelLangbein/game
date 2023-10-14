#include "./ecs.h"


SDL_Texture* shipTexture; 

void initTextures(SDL_Renderer* renderer) {
    shipTexture = IMG_LoadTexture(renderer, "assets/textures/ship.png");
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

void renderSystem(int id, float deltaSecs, SDL_Renderer* renderer) {
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
