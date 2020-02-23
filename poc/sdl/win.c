#include <stdio.h>
#include "SDL.h"

static const char *me = "win";

int
main(void)
{
    unsigned int seconds;
    SDL_Window *window;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	fprintf(stderr, "%s: SDL_Init failed: %s\n", me, SDL_GetError());
	exit(2);
    }
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    if (window == NULL) {
	fprintf(stderr, "%s: SDL_CreateWindow failed: %s\n", me, SDL_GetError());
	exit(2);
    }
    seconds = 1;
    printf("sleep for %d seconds\n", seconds);
    SDL_Delay(seconds * 1000);
    SDL_DestroyWindow(NULL);
    SDL_Quit();
}
