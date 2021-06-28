#include "objects.h"

objects objs = {{}, 0};

void inittextures(SDL_Renderer *rend) {
    red = IMG_LoadTexture(rend, "assets/red.png");
    green = IMG_LoadTexture(rend, "assets/green.png");
    blue = IMG_LoadTexture(rend, "assets/blue.png");
}

object createobj(float x, float y, SDL_Texture *color) {
    return (object) {x, y, color};
}

void addobj(object obj) {
    if (objs.length > 32) return; // object limit reached
    objs.arr[objs.length] = obj;
    objs.length++;
}
