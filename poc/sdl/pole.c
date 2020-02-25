#include <stdio.h>
#include "SDL.h"
#include "gfxPrimitives.h"

static const char *me = "pole";
static void
usg(void)
{
    fprintf(stderr, "%s -o imag.png -x cartx -t angle[rad] \n", me);
    exit(2);
}

struct Points {
    double x[4];
    double y[4];
};
static int points_rotate(struct Points *p, double t);
static int points_translate(struct Points *p, double x, double y);

static int DrawRect(int x, int y, int w, int h);
static int Polygon(struct Points *);
static int Line(int x0, int y0, int x1, int y1);
static int Circle(int x0, int y0, int r);
static int SetColor(double r, double g, double b);
static int screen_height;
static int screen_width;
SDL_Renderer *renderer;

int
main(int argc, char **argv)
{
    char command[999];
    char *out;
    double length;
    double polelen;
    double polewidth;
    double scale;
    double t;
    double world_width;
    double x;
    double x_threshold;
    int axleoffset;
    int cartheight;
    int cartwidth;
    int cartx;
    int carty;
    SDL_Window *window;
    struct Points points;
    unsigned int seconds;

    x = 0;
    t = 0;
    out = NULL;
    while (*++argv != NULL && argv[0][0] == '-')
        switch (argv[0][1]) {
        case 'h':
            usg();
            break;
        case 'o':
            argv++;
            if (*argv == NULL) {
                fprintf(stderr, "%s: -o needs an argument\n", me);
                exit(2);
            }
            out = *argv;
            break;
        case 'x':
            argv++;
            if (*argv == NULL) {
                fprintf(stderr, "%s: -x needs an argument\n", me);
                exit(2);
            }
            x = atof(*argv);
            break;
        case 't':
            argv++;
            if (*argv == NULL) {
                fprintf(stderr, "%s: -t needs an argument\n", me);
                exit(2);
            }
            t = atof(*argv);
            break;
        default:
            fprintf(stderr, "%s: unknown option '%s'\n", me, argv[0]);
            exit(2);
        }

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
                         SDL_WINDOWPOS_CENTERED, screen_width,
                         screen_height, SDL_WINDOW_OPENGL);
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

    SetColor(1, 1, 1);
    SDL_RenderClear(renderer);

    SetColor(0, 0, 0);
    DrawRect(cartx, carty, cartwidth, cartheight);

    SetColor(0, 0, 0);
    Line(0, carty, screen_width, carty);

    points.x[0] = -polewidth / 2;
    points.y[0] = 0;
    points.x[1] = polewidth / 2;
    points.y[1] = 0;
    points.x[2] = polewidth / 2;
    points.y[2] = polelen;
    points.x[3] = -polewidth / 2;
    points.y[3] = polelen;
    points_translate(&points, 0, -axleoffset / 2);
    points_rotate(&points, -t);
    points_translate(&points, cartx, carty);
    SetColor(.8, .6, .4);
    Polygon(&points);
    SetColor(.5, .5, .8);
    Circle(cartx, carty, polewidth / 2);
    SDL_RenderPresent(renderer);
    if (out != NULL) {
        sprintf(command, "xwd -name Window | convert xwd:- png:'%s'", out);
        if (system(command) != 0) {
            fprintf(stderr, "%s: command '%s' failed\n", me, command);
            exit(2);
        }
    } else {
        seconds = 3;
        printf("sleep for %d seconds\n", seconds);
        SDL_Delay(seconds * 1000);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(NULL);
    SDL_Quit();
}

static int
DrawRect(int x, int y, int w, int h)
{
    SDL_Rect rectangle;

    rectangle.x = x - w / 2;
    rectangle.y = screen_height - (y + h / 2);
    rectangle.w = w;
    rectangle.h = h;
    SDL_RenderFillRect(renderer, &rectangle);
    return 0;
}

static int
Polygon(struct Points *p)
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    int n;
    int sh;

    sh = screen_height;
    Sint16 x[] = { p->x[0], p->x[1], p->x[2], p->x[3] };
    Sint16 y[] =
        { sh - p->y[0], sh - p->y[1], sh - p->y[2], sh - p->y[3] };
    n = sizeof(x) / sizeof(*x);
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    filledPolygonRGBA(renderer, x, y, n, r, g, b, a);

    return 0;
}


static int
Line(int x0, int y0, int x1, int y1)
{
    return SDL_RenderDrawLine(renderer, x0, screen_height - y0, x1,
                              screen_height - y1);
}

static int
Circle(int x, int y, int radius)
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    return filledCircleRGBA(renderer, x, screen_height - y, radius, r, g,
                            b, a);
}

static int
SetColor(double r, double g, double b)
{
    return
        SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255,
                               SDL_ALPHA_OPAQUE);
}

static int
points_translate(struct Points *p, double x, double y)
{
    int i;

    for (i = 0; i < 4; i++) {
        p->x[i] += x;
        p->y[i] += y;
    }
    return 0;
}

static int
points_rotate(struct Points *p, double t)
{
    int i;
    double c;
    double s;
    double x;
    double y;

    c = cos(t);
    s = sin(t);
    for (i = 0; i < 4; i++) {
        x = p->x[i];
        y = p->y[i];
        p->x[i] = x * c - y * s;
        p->y[i] = x * s + y * c;
    }
    return 0;
}
