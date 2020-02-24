#include <stdio.h>
#include "SDL.h"
#include "gfxPrimitives.h"

static const char *me = "circle";

int
main(void)
{
    unsigned int seconds;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Sint16 x;
    Sint16 y;
    Sint16 rad;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "%s: SDL_Init failed: %s\n", me, SDL_GetError());
        exit(2);
    }
    window =
        SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 640, 480,
                         SDL_WINDOW_OPENGL);
    if (window == NULL) {
        fprintf(stderr, "%s: SDL_CreateWindow failed: %s\n", me,
                SDL_GetError());
        exit(2);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "%s: SDL_CreateRenderer failed: %s\n", me,
                SDL_GetError());
        exit(2);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    x = 200;
    y = 200;
    rad = 100;
    filledCircleRGBA(renderer, x, y, rad, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);

    seconds = 3;
    printf("sleep for %d seconds\n", seconds);
    SDL_Delay(seconds * 1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(NULL);
    SDL_Quit();
}
