#pragma once
#include <SDL2/SDL_image.h>

#define OW 64
#define OH 64

enum COLORS {
    RED, GREEN, BLUE,
};

typedef struct object {
    float x, y;
    enum COLORS color;
} object;

typedef struct objects {
    object arr[32];
    int length;
} objects;

extern objects objs;
extern SDL_Texture* colors[3];

void inittextures();
object createobj(float x, float y, enum COLORS color);
void addobj(object obj);
