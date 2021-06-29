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

// initialization
void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "Quadtree Collisions",
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

    qt = qt_make((rectangle) {0, 0, WIDTH, HEIGHT});

    // create and insert 16 random points
    vec2 a_points[] = {
        VEC2(WIDTH/4,         HEIGHT/4), // top left
        VEC2(WIDTH/2+WIDTH/4, HEIGHT/4), // top right
        VEC2(WIDTH/4,         HEIGHT/2+HEIGHT/4), // bottom left
        VEC2(WIDTH/2+WIDTH/4, HEIGHT/2+HEIGHT/4), // bottom right
    };
    for (int i=0; i<4; qt_insert(qt, &a_points[i++]));
}

// rendering
void render() {
}

// processing
int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    return event.key.keysym.scancode == SDL_SCANCODE_Q;
}

void update() {
}

int main() {
    init();

    int close = 0;
    while (!close) {
        close = handleev();
        update();
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
