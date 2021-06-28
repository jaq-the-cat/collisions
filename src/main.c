#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "objects.h"
#include "col.h"

#define WIDTH 800
#define HEIGHT 600
#define BG 15

#define SPD 10

SDL_Window *win;
SDL_Renderer *rend;

typedef struct keyboard {
    int w, a, s, d;
} keyboard;

keyboard keys = {0, 0, 0, 0};

void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "SDL Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);

    // Textures
    inittextures(rend);
}

int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q:
            return 1;
        case SDL_SCANCODE_W:
            keys.w = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_A:
            keys.a = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_S:
            keys.s = event.key.type == SDL_KEYDOWN;
            break;
        case SDL_SCANCODE_D:
            keys.d = event.key.type == SDL_KEYDOWN;
            break;
        default: break;
    }
    return 0;
}

void render() {
    SDL_Rect r;
    for (int i=0; i<objs.length; i++) {
        object obj = objs.arr[i];
        r = (SDL_Rect) {obj.x, obj.y, OW, OH};
        SDL_RenderCopy(rend, colors[obj.color], NULL, &r);
    }
}

int main() {
    init();
    quadtree *qt = qt_make((rectangle) {
        (vec2) {0, 0},
        (vec2) {WIDTH, HEIGHT},
    });

    vec2 a_points[16] = {0};
    for (int i=0; i<16; i++) {
        a_points[i] = (vec2) {rand() % WIDTH, rand() % HEIGHT};
        qt_insert(qt, &a_points[i]);
    }
    qt_remove(qt, &a_points[2]);

    // add objects
    addobj(createobj(10, 10, RED));
    addobj(createobj(WIDTH/2-OW/2, HEIGHT/2-OH*3, GREEN));
    addobj(createobj(WIDTH/2-OW/2, HEIGHT/2-OH/3, BLUE));

    float yv, xv;

    int close = 0;
    while (!close) {
        close = handleev();

        xv = -SPD * keys.a;
        xv += SPD * keys.d;

        yv = -SPD * keys.w;
        yv += SPD * keys.s;

        objs.arr[0].x += xv;
        objs.arr[0].y += yv;

        SDL_SetRenderDrawColor(rend, BG, BG, BG, 255);
        SDL_RenderClear(rend);
        render();
        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
