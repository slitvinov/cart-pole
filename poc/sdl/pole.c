#include <stdio.h>
#include "SDL.h"
#include "gfxPrimitives.h"

static const char *me = "pole";

static int DrawRect(int x, int y, int w, int h);
static int Line(int x0, int y0, int x1, int y1);
static int Circle(int x0, int y0, int r);
static int SetColor(float r, float g, float b);
static int screen_height;
static int screen_width;
SDL_Renderer *renderer;

int
main(void)
{
    float length;
    float polelen;
    float polewidth;
    float scale;
    float world_width;
    float x_threshold;
    int axleoffset;
    int cartheight;
    int cartwidth;
    int cartx;
    int carty;
    SDL_Window *window;
    unsigned int seconds;

    float x;

    length = 0.5;
    x_threshold = 2.4;

    screen_width = 600;
    screen_height = 400;

    world_width = x_threshold * 2;
    scale = screen_width / world_width;
    carty = 100;
    polewidth = 10.0;
    polelen = scale * (2 * length);
    cartwidth = 50;
    cartheight = 30;
    axleoffset = cartheight / 4;
    cartx = x * scale + screen_width / 2.0;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "%s: SDL_Init failed: %s\n", me, SDL_GetError());
        exit(2);
    }
    window =
        SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, screen_width, screen_height,
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

    SetColor(1,1,1);
    SDL_RenderClear(renderer);

    SetColor(0,0,0);
    DrawRect(cartx, carty, cartwidth, cartheight);

    SetColor(0,0,0);
    Line(0, carty, screen_width, carty);

    //SetColor(.8,.6,.4);
    //DrawRect(cartx, carty, cartwidth, cartheight);

    SetColor(.5,.5,.8);
    Circle(cartx, carty, polewidth/2);
    
    SDL_RenderPresent(renderer);

    seconds = 3;
    printf("sleep for %d seconds\n", seconds);
    SDL_Delay(seconds * 1000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(NULL);
    SDL_Quit();
}

static int
DrawRect(int x, int y, int w, int h)
{
   SDL_Rect rectangle;

   rectangle.x = x - w/2;
   rectangle.y = screen_height - (y + h/2);
   rectangle.w = w;
   rectangle.h = h;
   SDL_RenderFillRect(renderer, &rectangle);
   return 0;
}

static int
Line(int x0, int y0, int x1, int y1)
{
    return SDL_RenderDrawLine(renderer, x0, screen_height - y0, x1, screen_height - y1);
}

static int
Circle(int x, int y, int radius)
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    return filledCircleRGBA(renderer, x, screen_height - y, radius, r, g, b, a);
}


static int
SetColor(float r, float g, float b)
{
    SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, SDL_ALPHA_OPAQUE);
}
