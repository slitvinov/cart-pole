#include <stdio.h>
#include <unistd.h>
#include "SDL.h"

int
main(void)
{
    unsigned int s;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Point window_position = {
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED
    };
    SDL_Point window_size = { 640, 480 };
    window = SDL_CreateWindow("Window",
                              window_position.x,
                              window_position.y,
                              window_size.x,
                              window_size.y, SDL_WINDOW_OPENGL);
    s = 5;
    printf("sleep for %d seconds\n", s);
    sleep(s);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
