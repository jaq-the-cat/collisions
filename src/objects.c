#include "objects.h"

objects objs = {{}, 0};
SDL_Texture* colors[3];

void inittextures(SDL_Renderer *rend) {
    colors[0] = IMG_LoadTexture(rend, "assets/red.png");
    colors[1] = IMG_LoadTexture(rend, "assets/green.png");
    colors[2] = IMG_LoadTexture(rend, "assets/blue.png");
}

object createobj(float x, float y, enum COLORS color) {
    return (object) {x, y, color};
}

void addobj(object obj) {
    if (objs.length > 32) return; // object limit reached
    objs.arr[objs.length] = obj;
    objs.length++;
}
