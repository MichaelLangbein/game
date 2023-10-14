#ifndef ecs_HEADER
#define ecs_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void initTextures(SDL_Renderer* renderer);

void cleanTextures();


#define NR_ENTITIES 1
#define ID_PLAYER 0

void initComponents();

void physicsSystem(int id, float deltaSecs);

void renderSystem(int id, float deltaSecs, SDL_Renderer* renderer);


#endif