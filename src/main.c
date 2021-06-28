#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "col.h"

#define WIDTH 800
#define HEIGHT 600
#define BG 15

#define SPD 10

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *red;
SDL_Texture *green;
SDL_Texture *blue;
SDL_Texture *outline;

quadtree *qt;

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

    red = IMG_LoadTexture(rend, "assets/red.png");
    green = IMG_LoadTexture(rend, "assets/green.png");
    blue = IMG_LoadTexture(rend, "assets/blue.png");
    outline = IMG_LoadTexture(rend, "assets/outline.png");

    qt = qt_make((rectangle) {
        (vec2) {0, 0},
        (vec2) {WIDTH, HEIGHT},
    });
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

void qt_render_quads(quadtree *t) {
    vec2 bl = t->boundary.bl;
    vec2 tr = t->boundary.tr;
    SDL_Rect r = (SDL_Rect) {bl.x, bl.y, tr.x-bl.x, tr.y-bl.y};
    SDL_RenderCopy(rend, outline, NULL, &r);
}

void qt_render_points(vec2 *point) {
    printf("> Drawing point\n");
    SDL_Rect r = (SDL_Rect) {point->x-5, point->y-5, 10, 10};
    SDL_RenderCopy(rend, red, NULL, &r);
}

void render() {
    qt_foreach(qt, qt_render_quads, qt_render_points);
}

int main() {
    init();

    // create and insert 16 random points
    vec2 a_points[8] = {
        (vec2) {WIDTH/4, HEIGHT/4}, // top left
        (vec2) {WIDTH/2+WIDTH/4, HEIGHT/4}, // top right
        (vec2) {WIDTH/4, HEIGHT/2+HEIGHT/4}, // bottom left
        (vec2) {WIDTH/2+WIDTH/4, HEIGHT/2+HEIGHT/4}, // bottom right
        (vec2) {WIDTH/2+WIDTH/4-20, HEIGHT/2+HEIGHT/4-40}, // bottom right
        (vec2) {WIDTH/2+WIDTH/4+20, HEIGHT/2+HEIGHT/4+15}, // bottom right
        (vec2) {WIDTH/2+WIDTH/4-40, HEIGHT/2+HEIGHT/4+20}, // bottom right
    };
    for (int i=0; i<8; i++)
        qt_insert(qt, &a_points[i]);

    float yv, xv;

    int close = 0;
    while (!close) {
        close = handleev();

        xv = -SPD * keys.a;
        xv += SPD * keys.d;

        yv = -SPD * keys.w;
        yv += SPD * keys.s;

        SDL_SetRenderDrawColor(rend, BG, BG, BG, 255);
        SDL_RenderClear(rend);
        render();
        SDL_RenderPresent(rend);
    }

    qt_free(qt);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
