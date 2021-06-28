#pragma once
#include <SDL2/SDL_image.h>

#define OW 64
#define OH 64

SDL_Texture *red;
SDL_Texture *green;
SDL_Texture *blue;

typedef struct object {
    float x, y;
    SDL_Texture *color;
} object;

typedef struct objects {
    object arr[32];
    int length;
} objects;

extern objects objs;
extern SDL_Texture* colors[3];

void inittextures();
object createobj(float x, float y, SDL_Texture *color);
void addobj(object obj);
