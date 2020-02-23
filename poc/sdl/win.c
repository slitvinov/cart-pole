#include <stdio.h>
#include "SDL.h"

static const char *me = "win";

int
main(void)
{
    unsigned int seconds;
    SDL_Window *window;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
exit(2);
    }
    seconds = 1;
    printf("sleep for %d seconds\n", seconds);
    SDL_Delay(seconds * 1000);
    SDL_DestroyWindow(NULL);
    SDL_Quit();
}
