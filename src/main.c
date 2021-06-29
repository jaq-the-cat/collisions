#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "quadtree.h"

#define WIDTH 800
#define HEIGHT 800
#define BG 200

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *red;
SDL_Texture *green;
SDL_Texture *blue;
SDL_Texture *outline;

quadtree *qt;

vec2 a_points[] = {
    VEC2(WIDTH/4-50,      HEIGHT/4-50), // top left
    VEC2(WIDTH/4+50,      HEIGHT/4-50), // top left
    VEC2(WIDTH/4-50,      HEIGHT/4+50), // top left
    VEC2(WIDTH/4+50,      HEIGHT/4+50), // top left
    VEC2(WIDTH/2+WIDTH/4, HEIGHT/4), // top right
    VEC2(WIDTH/4,         HEIGHT/2+HEIGHT/4), // bottom left
    VEC2(WIDTH/2+WIDTH/4, HEIGHT/2+HEIGHT/4), // bottom right
};

// initialization
void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
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
    for (int i=0; i<7; i++)
        qt_insert(qt, &a_points[i]);
}

// rendering

void render_quadtree(quadtree *qt) {
    SDL_Rect r = (SDL_Rect) {
        qt->boundary.origin.x,
        qt->boundary.origin.y,
        qt->boundary.size.x,
        qt->boundary.size.y,
    };

    SDL_RenderCopy(rend, outline, NULL, &r);
}

void render_points(vec2 *point) {
    SDL_Rect r = (SDL_Rect) {
        point->x-5, point->y-5,
        10, 10
    };

    SDL_RenderCopy(rend, red, NULL, &r);
}

void render() {
    qt_foreach(qt, render_quadtree, render_points);
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
