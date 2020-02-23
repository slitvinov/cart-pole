/*  

SDL2_rotozoom.c: rotozoomer, zoomer and shrinker for 32bit or 8bit surfaces

Copyright (C) 2012-2014  Andreas Schiffler

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

Andreas Schiffler -- aschiffler at ferzkopp dot net

*/

#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif

    /* ---- Defines */

    /*!
       \brief Disable anti-aliasing (no smoothing).
     */
#define SMOOTHING_OFF		0

    /*!
       \brief Enable anti-aliasing (smoothing).
     */
#define SMOOTHING_ON		1

    /* ---- Function Prototypes */

SDL_Surface *rotozoomSurface(SDL_Surface * src, double angle, double zoom,
                             int smooth);

SDL_Surface *rotozoomSurfaceXY
    (SDL_Surface * src, double angle, double zoomx, double zoomy,
     int smooth);


void rotozoomSurfaceSize(int width, int height, double angle, double zoom,
                         int *dstwidth, int *dstheight);

void rotozoomSurfaceSizeXY
    (int width, int height, double angle, double zoomx, double zoomy,
     int *dstwidth, int *dstheight);

    /* 

       Zooming functions

     */

SDL_Surface *zoomSurface(SDL_Surface * src, double zoomx, double zoomy,
                         int smooth);

void zoomSurfaceSize(int width, int height, double zoomx, double zoomy,
                     int *dstwidth, int *dstheight);

    /* 

       Shrinking functions

     */

SDL_Surface *shrinkSurface(SDL_Surface * src, int factorx, int factory);

    /* 

       Specialized rotation functions

     */

SDL_Surface *rotateSurface90Degrees(SDL_Surface * src,
                                    int numClockwiseTurns);

    /* Ends C function definitions when using C++ */
