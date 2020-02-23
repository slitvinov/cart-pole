/* 

SDL2_gfxPrimitives.c: graphics primitives for SDL2 renderers

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
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL.h>
    
#include "gfxPrimitives.h"
#include "rotozoom.h"
#include "gfxPrimitives_font.h"
    
/* ---- Structures */ 
    
/*!
\brief The structure passed to the internal Bresenham iterator.
*/ 
    typedef struct {
    
    
    



/*!
\brief The structure passed to the internal Murphy iterator.
*/ 
    typedef struct {
    
    
    
    
    
    
        first2y, tempx, tempy;



/* ---- Pixel */ 
    
/*!
\brief Draw pixel  in currently set color.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pixel(SDL_Renderer * renderer, Sint16 x, Sint16 y) 
    { 



/*!
\brief Draw pixel with blending enabled if a<255.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param color The color value of the pixel to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pixelColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint32 color) 
    { 
    



/*!
\brief Draw pixel with blending enabled if a<255.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the pixel.
\param y Y (vertical) coordinate of the pixel.
\param r The red color value of the pixel to draw. 
\param g The green color value of the pixel to draw.
\param b The blue color value of the pixel to draw.
\param a The alpha value of the pixel to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pixelRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r, Uint8 g,
          Uint8 b, Uint8 a) 
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/*!
\brief Draw pixel with blending enabled and using alpha weight on color.

\param renderer The renderer to draw on.
\param x The horizontal coordinate of the pixel.
\param y The vertical position of the pixel.
\param r The red color value of the pixel to draw. 
\param g The green color value of the pixel to draw.
\param b The blue color value of the pixel to draw.
\param a The alpha value of the pixel to draw.
\param weight The weight multiplied into the alpha value of the pixel.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pixelRGBAWeight(SDL_Renderer * renderer, Sint16 x, Sint16 y, Uint8 r,
                Uint8 g, Uint8 b, Uint8 a, Uint32 weight) 
        /*
         * Modify Alpha by weight 
         */ 
        Uint32 ax = a;
    
    
        
    
        
    
    



/* ---- Hline */ 
    
/*!
\brief Draw horizontal line in currently set color

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
hline(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y) 
    { 



/*!
\brief Draw horizontal line with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
hlineColor(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y,
           Uint32 color) 
    



/*!
\brief Draw horizontal line with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param a The alpha value of the line to draw. 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
hlineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y, Uint8 r,
          Uint8 g, Uint8 b, Uint8 a) 
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/* ---- Vline */ 
    
/*!
\brief Draw vertical line in currently set color

\param renderer The renderer to draw on.
\param x X coordinate of points of the line.
\param y1 Y coordinate of the first point (i.e. top) of the line.
\param y2 Y coordinate of the second point (i.e. bottom) of the line.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
vline(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2) 
    { 



/*!
\brief Draw vertical line with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the points of the line.
\param y1 Y coordinate of the first point (i.e. top) of the line.
\param y2 Y coordinate of the second point (i.e. bottom) of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
vlineColor(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2,
           Uint32 color) 
    



/*!
\brief Draw vertical line with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the points of the line.
\param y1 Y coordinate of the first point (i.e. top) of the line.
\param y2 Y coordinate of the second point (i.e. bottom) of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param a The alpha value of the line to draw. 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
vlineRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y1, Sint16 y2, Uint8 r,
          Uint8 g, Uint8 b, Uint8 a) 
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/* ---- Rectangle */ 
    
/*!
\brief Draw rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param color The color value of the rectangle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
rectangleColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
               Sint16 y2, Uint32 color) 
    
                          c[3]);



/*!
\brief Draw rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param r The red value of the rectangle to draw. 
\param g The green value of the rectangle to draw. 
\param b The blue value of the rectangle to draw. 
\param a The alpha value of the rectangle to draw. 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
rectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
              Sint16 y2, Uint8 r, Uint8 g, Uint8 b,
              Uint8 a) 
    
    
    
        /*
         * Test for special cases of straight lines or single point 
         */ 
        if (x1 == x2) {
        
            
        
            
        
    
        
            
        
    
    
        /*
         * Swap x1, x2 if required 
         */ 
        if (x1 > x2) {
        
        
        
    
    
        /*
         * Swap y1, y2 if required 
         */ 
        if (y1 > y2) {
        
        
        
    
    
        /* 
         * Create destination rect
         */ 
        rect.x = x1;
    
    
    
    
        /*
         * Draw
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/* ---- Rounded Rectangle */ 
    
/*!
\brief Draw rounded-corner rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param rad The radius of the corner arc.
\param color The color value of the rectangle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
roundedRectangleColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1,
                      Sint16 x2, Sint16 y2, Sint16 rad,
                      Uint32 color) 
    
                                 c[2], c[3]);



/*!
\brief Draw rounded-corner rectangle with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the rectangle.
\param y1 Y coordinate of the first point (i.e. top right) of the rectangle.
\param x2 X coordinate of the second point (i.e. bottom left) of the rectangle.
\param y2 Y coordinate of the second point (i.e. bottom left) of the rectangle.
\param rad The radius of the corner arc.
\param r The red value of the rectangle to draw. 
\param g The green value of the rectangle to draw. 
\param b The blue value of the rectangle to draw. 
\param a The alpha value of the rectangle to draw. 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
roundedRectangleRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1,
                     Sint16 x2, Sint16 y2, Sint16 rad, Uint8 r, Uint8 g,
                     Uint8 b, Uint8 a) 
    
    
    
    
    
        /*
         * Check renderer
         */ 
        if (renderer == NULL)
        
        
        
    
        /*
         * Check radius vor valid range
         */ 
        if (rad < 0) {
        
    
    
        /*
         * Special case - no rounding
         */ 
        if (rad <= 1) {
        
    
    
        /*
         * Test for special cases of straight lines or single point 
         */ 
        if (x1 == x2) {
        
            
        
            
        
    
        
            
        
    
    
        /*
         * Swap x1, x2 if required 
         */ 
        if (x1 > x2) {
        
        
        
    
    
        /*
         * Swap y1, y2 if required 
         */ 
        if (y1 > y2) {
        
        
        
    
    
        /*
         * Calculate width&height 
         */ 
        w = x2 - x1;
    
    
        /*
         * Maybe adjust radius
         */ 
        if ((rad * 2) > w)
        
        
        
    
        
        
        
    
        /*
         * Draw corners
         */ 
        xx1 = x1 + rad;
    
    
    
    
    
    
    
    
        /*
         * Draw lines
         */ 
        if (xx1 <= xx2) {
        
        
    
    
        
        
    
    



/* ---- Rounded Box */ 
    
/*!
\brief Draw rounded-corner box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param rad The radius of the corner arcs of the box.
\param color The color value of the box to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
roundedBoxColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
                Sint16 y2, Sint16 rad, Uint32 color) 
        (Uint8 *) & color;
    
                           c[3]);



/*!
\brief Draw rounded-corner box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param rad The radius of the corner arcs of the box.
\param r The red value of the box to draw. 
\param g The green value of the box to draw. 
\param b The blue value of the box to draw. 
\param a The alpha value of the box to draw. 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
roundedBoxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
               
               Uint8 a) 
    
    
    
    
    
    
    
    
    
    
    
    
        /* 
         * Check destination renderer 
         */ 
        if (renderer == NULL)
        
        
        
    
        /*
         * Check radius vor valid range
         */ 
        if (rad < 0) {
        
    
    
        /*
         * Special case - no rounding
         */ 
        if (rad <= 1) {
        
    
    
        /*
         * Test for special cases of straight lines or single point 
         */ 
        if (x1 == x2) {
        
            
        
            
        
    
        
            
        
    
    
        /*
         * Swap x1, x2 if required 
         */ 
        if (x1 > x2) {
        
        
        
    
    
        /*
         * Swap y1, y2 if required 
         */ 
        if (y1 > y2) {
        
        
        
    
    
        /*
         * Calculate width&height 
         */ 
        w = x2 - x1 + 1;
    
    
        /*
         * Maybe adjust radius
         */ 
        r2 = rad + rad;
    
        
        
        
        
    
        
        
        
    
        /* Setup filled circle drawing for corners */ 
        x = x1 + rad;
    
    
    
    
        /*
         * Set color
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
        /*
         * Draw corners
         */ 
        do {
        
        
        
        
        
            
                
                
                
                
            
                
            
            
        
        
            
                
                    
                    
                    
                    
                
                    
                
            
            
        
        
            /*
             * Update 
             */ 
            if (df < 0) {
            
            
            
        
            
            
            
            
        
        
    
    
        /* Inside */ 
        if (dx > 0 && dy > 0) {
        
            boxRGBA(renderer, x1, y1 + rad + 1, x2, y2 - rad, r, g, b, a);
    
    



/* ---- Box */ 
    
/*!
\brief Draw box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param color The color value of the box to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
boxColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
         Sint16 y2, Uint32 color) 
    



/*!
\brief Draw box (filled rectangle) with blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. top right) of the box.
\param y1 Y coordinate of the first point (i.e. top right) of the box.
\param x2 X coordinate of the second point (i.e. bottom left) of the box.
\param y2 Y coordinate of the second point (i.e. bottom left) of the box.
\param r The red value of the box to draw. 
\param g The green value of the box to draw. 
\param b The blue value of the box to draw. 
\param a The alpha value of the box to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
boxRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
        Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) 
    
    
    
        /*
         * Test for special cases of straight lines or single point 
         */ 
        if (x1 == x2) {
        
            
        
            
        
    
        
            
        
    
    
        /*
         * Swap x1, x2 if required 
         */ 
        if (x1 > x2) {
        
        
        
    
    
        /*
         * Swap y1, y2 if required 
         */ 
        if (y1 > y2) {
        
        
        
    
    
        /* 
         * Create destination rect
         */ 
        rect.x = x1;
    
    
    
    
        /*
         * Draw
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/* ----- Line */ 
    
/*!
\brief Draw line with alpha blending using the currently set color.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
line(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2) 
        /*
         * Draw
         */ 
        return SDL_RenderDrawLine(renderer, x1, y1, x2, y2);



/*!
\brief Draw line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the seond point of the line.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
lineColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
          Sint16 y2, Uint32 color) 
    



/*!
\brief Draw line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param r The red value of the line to draw. 
\param g The green value of the line to draw. 
\param b The blue value of the line to draw. 
\param a The alpha value of the line to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
lineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
         Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a) 
        /*
         * Draw
         */ 
        int result = 0;

    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
    



/* ---- AA Line */ 
    
#define AAlevels 256
#define AAbits 8
    
/*!
\brief Internal function to draw anti-aliased line with alpha blending and endpoint control.

This implementation of the Wu antialiasing code is based on Mike Abrash's
DDJ article which was reprinted as Chapter 42 of his Graphics Programming
Black Book, but has been optimized to work with SDL and utilizes 32-bit
fixed-point arithmetic by A. Schiffler. The endpoint control allows the
supression to draw the last pixel useful for rendering continous aa-lines
with alpha<255.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param r The red value of the aa-line to draw. 
\param g The green value of the aa-line to draw. 
\param b The blue value of the aa-line to draw. 
\param a The alpha value of the aa-line to draw.
\param draw_endpoint Flag indicating if the endpoint should be drawn; draw if non-zero.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
_aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
            Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
            int draw_endpoint) 
    

    
    
    

    
        /*
         * Keep on working with 32bit numbers 
         */ 
        xx0 = x1;
    
    
    
    
        /*
         * Reorder points to make dy positive 
         */ 
        if (yy0 > yy1) {
        
        
        
        
        
        
    
    
        /*
         * Calculate distance 
         */ 
        dx = xx1 - xx0;
    
    
        /*
         * Adjust for negative dx and set xdir 
         */ 
        if (dx >= 0) {
        
    
        
        
    
    
        /*
         * Check for special cases 
         */ 
        if (dx == 0) {
        
            /*
             * Vertical line 
             */ 
            if (draw_endpoint)
            
            
        
            
                
                         (renderer, x1, yy0, yy0 + dy, r, g, b, a));
            
                
            
        
    
        
            /*
             * Horizontal line 
             */ 
            if (draw_endpoint)
            
            
        
            
                
                         (renderer, xx0, xx0 + (xdir * dx), y1, r, g, b,
                          a));
            
                
            
        
    
        
            /*
             * Diagonal line (with endpoint)
             */ 
            return (lineRGBA(renderer, x1, y1, x2, y2, r, g, b, a));
    
    
        /*
         * Line is not horizontal, vertical or diagonal (with endpoint)
         */ 
        result = 0;
    
        /*
         * Zero accumulator 
         */ 
        erracc = 0;
    
        /*
         * # of bits by which to shift erracc to get intensity level 
         */ 
        intshift = 32 - AAbits;
    
        /*
         * Mask used to flip all bits in an intensity weighting 
         */ 
        wgtcompmask = AAlevels - 1;
    
        /*
         * Draw the initial pixel in the foreground color 
         */ 
        result |= pixelRGBA(renderer, x1, y1, r, g, b, a);
    
        /*
         * x-major or y-major? 
         */ 
        if (dy > dx) {
        
            /*
             * y-major.  Calculate 16-bit fixed point fractional part of a pixel that
             * X advances every time Y advances 1 pixel, truncating the result so that
             * we won't overrun the endpoint along the X axis 
             */ 
            /*
             * Not-so-portable version: erradj = ((Uint64)dx << 32) / (Uint64)dy; 
             */ 
            erradj = ((dx << 16) / dy) << 16;
        
            /*
             * draw all pixels other than the first and last 
             */ 
            x0pxdir = xx0 + xdir;
        
            
            
            
                
                    /*
                     * rollover in error accumulator, x coord advances 
                     */ 
                    xx0 = x0pxdir;
                
            
            
            
                /*
                 * the AAbits most significant bits of erracc give us the intensity
                 * weighting for this pixel, and the complement of the weighting for
                 * the paired pixel. 
                 */ 
                wgt = (erracc >> intshift) & 255;
            
                pixelRGBAWeight(renderer, xx0, yy0, r, g, b, a, 255 - wgt);
            
                pixelRGBAWeight(renderer, x0pxdir, yy0, r, g, b, a, wgt);
        
    
        
            /*
             * x-major line.  Calculate 16-bit fixed-point fractional part of a pixel
             * that Y advances each time X advances 1 pixel, truncating the result so
             * that we won't overrun the endpoint along the X axis. 
             */ 
            /*
             * Not-so-portable version: erradj = ((Uint64)dy << 32) / (Uint64)dx; 
             */ 
            erradj = ((dy << 16) / dx) << 16;
        
            /*
             * draw all pixels other than the first and last 
             */ 
            y0p1 = yy0 + 1;
        
            
            
            
                
                    /*
                     * Accumulator turned over, advance y 
                     */ 
                    yy0 = y0p1;
                
            
            
            
                /*
                 * the AAbits most significant bits of erracc give us the intensity
                 * weighting for this pixel, and the complement of the weighting for
                 * the paired pixel. 
                 */ 
                wgt = (erracc >> intshift) & 255;
            
                pixelRGBAWeight(renderer, xx0, yy0, r, g, b, a, 255 - wgt);
            
                pixelRGBAWeight(renderer, xx0, y0p1, r, g, b, a, wgt);
        
    
    
        /*
         * Do we have to draw the endpoint 
         */ 
        if (draw_endpoint) {
        
            /*
             * Draw final pixel, always exactly intersected by the line and doesn't
             * need to be weighted. 
             */ 
            result |= pixelRGBA(renderer, x2, y2, r, g, b, a);
    
    



/*!
\brief Draw anti-aliased line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param color The color value of the aa-line to draw (0xRRGGBBAA).

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aalineColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
            Sint16 y2, Uint32 color) 
    
                        1);



/*!
\brief Draw anti-aliased line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-line.
\param y1 Y coordinate of the first point of the aa-line.
\param x2 X coordinate of the second point of the aa-line.
\param y2 Y coordinate of the second point of the aa-line.
\param r The red value of the aa-line to draw. 
\param g The green value of the aa-line to draw. 
\param b The blue value of the aa-line to draw. 
\param a The alpha value of the aa-line to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aalineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
           Sint16 y2, Uint8 r, Uint8 g, Uint8 b,
           Uint8 a) 
                                            b, a, 1);



/* ----- Circle */ 
    
/*!
\brief Draw circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the circle.
\param y Y coordinate of the center of the circle.
\param rad Radius in pixels of the circle.
\param color The color value of the circle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
circleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
            Uint32 color) 
    



/*!
\brief Draw circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the circle.
\param y Y coordinate of the center of the circle.
\param rad Radius in pixels of the circle.
\param r The red value of the circle to draw. 
\param g The green value of the circle to draw. 
\param b The blue value of the circle to draw. 
\param a The alpha value of the circle to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
circleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
           Uint8 r, Uint8 g, Uint8 b,
           Uint8 a) 
                                            b, a);



/* ----- Arc */ 
    
/*!
\brief Arc with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the arc.
\param y Y coordinate of the center of the arc.
\param rad Radius in pixels of the arc.
\param start Starting radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param end Ending radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param color The color value of the arc to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
arcColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
         Sint16 start, Sint16 end, Uint32 color) 
        (Uint8 *) & color;
    
                    c[3]);



/*!
\brief Arc with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the arc.
\param y Y coordinate of the center of the arc.
\param rad Radius in pixels of the arc.
\param start Starting radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param end Ending radius in degrees of the arc. 0 degrees is down, increasing counterclockwise.
\param r The red value of the arc to draw. 
\param g The green value of the arc to draw. 
\param b The blue value of the arc to draw. 
\param a The alpha value of the arc to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
/* TODO: rewrite algorithm; arc endpoints are not always drawn */ 
    int
arcRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
        Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b,
        Uint8 a) 
    
    
    
    
    
    
    
    
    
    

    
        /*
         * Sanity check radius 
         */ 
        if (rad < 0) {
        
    
    
        /*
         * Special case for rad=0 - draw a point 
         */ 
        if (rad == 0) {
        
    
    
        /*
           Octant labeling
           
           \ 5 | 6 /
           \  |  /
           4 \ | / 7
           \|/
           ------+------ +x
           /|\
           3 / | \ 0
           /  |  \
           / 2 | 1 \
           +y
           
           Initially reset bitmask to 0x00000000
           the set whether or not to keep drawing a given octant.
           For example: 0x00111100 means we're drawing in octants 2-5
         */ 
        drawoct = 0;
    
        /*
         * Fixup angles
         */ 
        start %= 360;
    
    
        /* 0 <= start & end < 360; note that sometimes start > end - if so, arc goes back through 0. */ 
        while (start < 0)
        start += 360;
    
        end += 360;
    
    
    
        /* now, we find which octants we're drawing in. */ 
        startoct = start / 45;
    
    
    
        /* stopval_start, stopval_end; what values of cx to stop at. */ 
        do {
        
        
            
                /* need to compute stopval_start for this octant.  Look at picture above if this is unclear */ 
                dstart = (double) start;
            
                
            
            
                
                
            
            
                
                
            
            
                
                
            
            
                
                
                
            
            
            
                /* 
                   This isn't arbitrary, but requires graph paper to explain well.
                   The basic idea is that we're always changing drawoct after we draw, so we
                   stop immediately after we render the last sensible pixel at x = ((int)temp).
                   and whether to draw in this octant initially
                 */ 
                if (oct % 2)
                drawoct |= (1 << oct);  /* this is basically like saying drawoct[oct] = true, if drawoct were a bool array */
            
            else
                drawoct &= 255 - (1 << oct);    /* this is basically like saying drawoct[oct] = false */
        
        
            
                /* need to compute stopval_end for this octant */ 
                dend = (double) end;
            
                
            
            
                
                
            
            
                
                
            
            
                
                
            
            
                
                
                
            
            
            
                /* and whether to draw in this octant initially */ 
                if (startoct == endoct) {
                
                    /* note:      we start drawing, stop, then start again in this case */ 
                    /* otherwise: we only draw in this octant, so initialize it to false, it will get set back to true */ 
                    if (start > end) {
                    
                        /* unfortunately, if we're in the same octant and need to draw over the whole circle, */ 
                        /* we need to set the rest to true, because the while loop will end at the bottom. */ 
                        drawoct = 255;
                
                    
                
            
            
            else if (oct % 2)
                drawoct &= 255 - (1 << oct);
            
            else
                drawoct |= (1 << oct);
        
            
        
    
    
        /* so now we have what octants to draw and when to draw them. all that's left is the actual raster code. */ 
        
        /*
         * Set color 
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
        /*
         * Draw arc 
         */ 
        do {
        
        
        
            
            
            
                /* always check if we're drawing a certain octant before adding a pixel to that octant. */ 
                if (drawoct & 4)
                result |= pixel(renderer, xmcx, ypcy);
            
                result |= pixel(renderer, xpcx, ypcy);
            
                result |= pixel(renderer, xmcx, ymcy);
            
                result |= pixel(renderer, xpcx, ymcy);
        
            
                result |= pixel(renderer, x, ymcy);
            
                result |= pixel(renderer, x, ypcy);
        
        
        
        
            
            
            
                result |= pixel(renderer, xmcy, ypcx);
            
                result |= pixel(renderer, xpcy, ypcx);
            
                result |= pixel(renderer, xmcy, ymcx);
            
                result |= pixel(renderer, xpcy, ymcx);
        
            
                result |= pixel(renderer, xmcy, y);
            
                result |= pixel(renderer, xpcy, y);
        
        
            /*
             * Update whether we're drawing an octant
             */ 
            if (stopval_start == cx) {
            
                /* works like an on-off switch. */ 
                /* This is just in case start & end are in the same octant. */ 
                if (drawoct & (1 << startoct))
                drawoct &= 255 - (1 << startoct);
            
            else
                drawoct |= (1 << startoct);
        
        
            
                drawoct &= 255 - (1 << endoct);
            
            else
                drawoct |= (1 << endoct);
        
        
            /*
             * Update pixels
             */ 
            if (df < 0) {
            
            
            
        
            
            
            
            
        
        
    
    



/* ----- AA Circle */ 
    
/*!
\brief Draw anti-aliased circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-circle.
\param y Y coordinate of the center of the aa-circle.
\param rad Radius in pixels of the aa-circle.
\param color The color value of the aa-circle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aacircleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
              Uint32 color) 
    
                          c[3]);



/*!
\brief Draw anti-aliased circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-circle.
\param y Y coordinate of the center of the aa-circle.
\param rad Radius in pixels of the aa-circle.
\param r The red value of the aa-circle to draw. 
\param g The green value of the aa-circle to draw. 
\param b The blue value of the aa-circle to draw. 
\param a The alpha value of the aa-circle to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aacircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
             Uint8 r, Uint8 g, Uint8 b, Uint8 a) 
        /*
         * Draw 
         */ 
        return aaellipseRGBA(renderer, x, y, rad, rad, r, g, b, a);



/* ----- Ellipse */ 
    
/*!
\brief Internal function to draw pixels or lines in 4 quadrants.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the quadrant.
\param y Y coordinate of the center of the quadrant.
\param dx X offset in pixels of the corners of the quadrant.
\param dy Y offset in pixels of the corners of the quadrant.
\param f Flag indicating if the quadrant should be filled (1) or not (0).

\returns Returns 0 on success, -1 on failure.
*/ 
    int
_drawQuadrants(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 dx,
               Sint16 dy, Sint32 f) 
    
    
    
        
            
        
            
            
            
                
            
                
                
            
        
    
        
        
        
        
        
            
            
        
            
            
            
            
        
    
    



/*!
\brief Internal function to draw ellipse or filled ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param r The red value of the ellipse to draw. 
\param g The green value of the ellipse to draw. 
\param b The blue value of the ellipse to draw. 
\param a The alpha value of the ellipse to draw.
\param f Flag indicating if the ellipse should be filled (1) or not (0).

\returns Returns 0 on success, -1 on failure.
*/ 
#define DEFAULT_ELLIPSE_OVERSCAN	4
    int
_ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
             Sint16 ry, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
             Sint32 f) 
    
    
    
    
    
    
    
    
        /*
         * Sanity check radii 
         */ 
        if ((rx < 0) || (ry < 0)) {
        
    
    
        /*
         * Set color
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
        /*
         * Special cases for rx=0 and/or ry=0: draw a hline/vline/pixel 
         */ 
        if (rx == 0) {
        
            
        
            
        
    
        
            
        
    
    
        /*
         * Adjust overscan 
         */ 
        rxi = rx;
    
    
        
        
        
    
    else if (rxi >= 256 || ryi >= 256)
        
        
        
    
    else
        
        
        
    
        /*
         * Top/bottom center points.
         */ 
        oldX = scrX = 0;
    
    
    
        /* Midpoint ellipse algorithm with overdraw */ 
        rxi *= ellipseOverscan;
    
    
    
    
    
    
    
    
    
    
        /* Points in segment 1 */ 
        error = ry2 - rx2 * ryi + rx2 / 4;
    
        
        
        
        
        
            
            
            
            
            
        
        
        
             || (scrX != oldX && scrY != oldY)) {
            
            
            
        
        
    
        /* Points in segment 2 */ 
        if (curY > 0)
        
        
        
        
            ry2 * curX * curXp1 + ((ry2 + 3) / 4) + rx2 * curYm1 * curYm1 -
            rx2 * ry2;
        
            
            
            
            
            
            
                
                
                
                
                
            
            
            
                 || (scrX != oldX && scrY != oldY)) {
                
                
                    
                        _drawQuadrants(renderer, x, y, scrX, oldY, f);
                    
                        /* prevent overdraw */ 
                        if (f) {
                        
                    
                
                
                
            
            
        
            /* Remaining points in vertical */ 
            if (!f) {
            
            
                
            
        
        
    



/*!
\brief Draw ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param color The color value of the ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
ellipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
             Sint16 ry, Uint32 color) 
    
                         0);



/*!
\brief Draw ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the ellipse.
\param y Y coordinate of the center of the ellipse.
\param rx Horizontal radius in pixels of the ellipse.
\param ry Vertical radius in pixels of the ellipse.
\param r The red value of the ellipse to draw. 
\param g The green value of the ellipse to draw. 
\param b The blue value of the ellipse to draw. 
\param a The alpha value of the ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
ellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
            Sint16 ry, Uint8 r, Uint8 g, Uint8 b,
            Uint8 a) 
                                              b, a, 0);



/* ----- Filled Circle */ 
    
/*!
\brief Draw filled circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled circle.
\param y Y coordinate of the center of the filled circle.
\param rad Radius in pixels of the filled circle.
\param color The color value of the filled circle to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledCircleColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
                  Uint32 color) 
    
                              c[3]);



/*!
\brief Draw filled circle with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled circle.
\param y Y coordinate of the center of the filled circle.
\param rad Radius in pixels of the filled circle.
\param r The red value of the filled circle to draw. 
\param g The green value of the filled circle to draw. 
\param b The blue value of the filled circle to draw. 
\param a The alpha value of the filled circle to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledCircleRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
                 Uint8 r, Uint8 g, Uint8 b,
                 Uint8 a) 
                                                   rad, r, g, b, a, 1);



/* ----- AA Ellipse */ 
    
/*!
\brief Draw anti-aliased ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-ellipse.
\param y Y coordinate of the center of the aa-ellipse.
\param rx Horizontal radius in pixels of the aa-ellipse.
\param ry Vertical radius in pixels of the aa-ellipse.
\param color The color value of the aa-ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aaellipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
               Sint16 ry, Uint32 color) 
    



/*!
\brief Draw anti-aliased ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the aa-ellipse.
\param y Y coordinate of the center of the aa-ellipse.
\param rx Horizontal radius in pixels of the aa-ellipse.
\param ry Vertical radius in pixels of the aa-ellipse.
\param r The red value of the aa-ellipse to draw. 
\param g The green value of the aa-ellipse to draw. 
\param b The blue value of the aa-ellipse to draw. 
\param a The alpha value of the aa-ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aaellipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
              Sint16 ry, Uint8 r, Uint8 g, Uint8 b,
              Uint8 a) 
    
    

    
    
    

    
    
        /*
         * Sanity check radii 
         */ 
        if ((rx < 0) || (ry < 0)) {
        
    
    
        /*
         * Special cases for rx=0 and/or ry=0: draw a hline/vline/pixel 
         */ 
        if (rx == 0) {
        
            
        
            
        
    
        
            
        
    
    
        /* Variable setup */ 
        a2 = rx * rx;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
        /* Draw */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
        /* "End points" */ 
        result |= pixelRGBA(renderer, xp, yp, r, g, b, a);
    
    
    
    
        
        
        
            
        
        else if ((d - s - a2) > 0) {
            
                
            
            else {
                
                
                
                
            
        
            
            
            
            
        
        
        
            /* Calculate alpha */ 
            if (s != 0) {
            
            
                
            
        
            
        
        
            /* Calculate weights */ 
            weight = (Uint8) (cp * 255);
        
        
            /* Upper half */ 
            xx = xc2 - xp;
        
        
        
        
        
            /* Lower half */ 
            yy = yc2 - yp;
        
        
        
        
        
    
    
        /* Replaces original approximation code dyt = abs(yp - yc); */ 
        dyt = (Sint16) lrint((double) b2 / sab) + od;
    
        
        
        
            
        
        else if ((d + t - b2) < 0) {
            
                
            
            else {
                
                
                
                
            
        
            
            
            
            
        
        
        
            /* Calculate alpha */ 
            if (t != 0) {
            
            
                
            
        
            
        
        
            /* Calculate weight */ 
            weight = (Uint8) (cp * 255);
        
        
            /* Left half */ 
            xx = xc2 - xp;
        
        
        
        
            pixelRGBAWeight(renderer, xp, yy, r, g, b, a, iweight);
        
        
            /* Right half */ 
            xx = xc2 - xs;
        
        
        
        
    
    



/* ---- Filled Ellipse */ 
    
/*!
\brief Draw filled ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled ellipse.
\param y Y coordinate of the center of the filled ellipse.
\param rx Horizontal radius in pixels of the filled ellipse.
\param ry Vertical radius in pixels of the filled ellipse.
\param color The color value of the filled ellipse to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledEllipseColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
                   Sint16 ry, Uint32 color) 
        (Uint8 *) & color;
    
                         1);



/*!
\brief Draw filled ellipse with blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled ellipse.
\param y Y coordinate of the center of the filled ellipse.
\param rx Horizontal radius in pixels of the filled ellipse.
\param ry Vertical radius in pixels of the filled ellipse.
\param r The red value of the filled ellipse to draw. 
\param g The green value of the filled ellipse to draw. 
\param b The blue value of the filled ellipse to draw. 
\param a The alpha value of the filled ellipse to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledEllipseRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rx,
                  Sint16 ry, Uint8 r, Uint8 g, Uint8 b,
                  Uint8 a) 
                                                    r, g, b, a, 1);



/* ----- Pie */ 
    
/*!
\brief Internal float (low-speed) pie-calc implementation by drawing polygons.

Note: Determines vertex array and uses polygon or filledPolygon drawing routines to render.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param r The red value of the pie to draw. 
\param g The green value of the pie to draw. 
\param b The blue value of the pie to draw. 
\param a The alpha value of the pie to draw.
\param filled Flag indicating if the pie should be filled (=1) or not (=0).

\returns Returns 0 on success, -1 on failure.
*/ 
/* TODO: rewrite algorithm; pie is not always accurate */ 
    int
_pieRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
         Sint16 start, Sint16 end, Uint8 r, Uint8 g, Uint8 b, Uint8 a,
         Uint8 filled) 
    
    
    
    

    
    
        /*
         * Sanity check radii 
         */ 
        if (rad < 0) {
        
    
    
        /*
         * Fixup angles
         */ 
        start = start % 360;
    
    
        /*
         * Special case for rad=0 - draw a point 
         */ 
        if (rad == 0) {
        
    
    
        /*
         * Variable setup 
         */ 
        dr = (double) rad;
    
    
    

    
        
    
    
        /* We will always have at least 2 points */ 
        numpoints = 2;
    
        /* Count points (rather than calculating it) */ 
        angle = start_angle;
    
        
        
    
    
        /* Allocate combined vertex array */ 
        vx = vy = (Sint16 *) malloc(2 * sizeof(Uint16) * numpoints);
    
        
    
    
        /* Update point to start of vy */ 
        vy += numpoints;
    
        /* Center */ 
        vx[0] = x;
    
    
        /* First vertex */ 
        angle = start_angle;
    
    
    
        
        
            lineRGBA(renderer, vx[0], vy[0], vx[1], vy[1], r, g, b, a);
        
    
    else
        
        
            /* Calculate other vertices */ 
            i = 2;
        
        
            
            
                
                
                
            
            
            
        
            /* Draw */ 
            if (filled) {
            
                filledPolygonRGBA(renderer, vx, vy, numpoints, r, g, b, a);
        
            
        
        
    
        /* Free combined vertex array */ 
        free(vx);
    



/*!
\brief Draw pie (outline) with alpha blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param color The color value of the pie to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pieColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
         
        (Uint8 *) & color;
    
                     c[3], 0);



/*!
\brief Draw pie (outline) with alpha blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the pie.
\param y Y coordinate of the center of the pie.
\param rad Radius in pixels of the pie.
\param start Starting radius in degrees of the pie.
\param end Ending radius in degrees of the pie.
\param r The red value of the pie to draw. 
\param g The green value of the pie to draw. 
\param b The blue value of the pie to draw. 
\param a The alpha value of the pie to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
pieRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
        
        Uint8 a) 
                                      g, b, a, 0);



/*!
\brief Draw filled pie with alpha blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled pie.
\param y Y coordinate of the center of the filled pie.
\param rad Radius in pixels of the filled pie.
\param start Starting radius in degrees of the filled pie.
\param end Ending radius in degrees of the filled pie.
\param color The color value of the filled pie to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledPieColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
               Sint16 start, Sint16 end, Uint32 color) 
        (Uint8 *) & color;
    
                     c[3], 1);



/*!
\brief Draw filled pie with alpha blending.

\param renderer The renderer to draw on.
\param x X coordinate of the center of the filled pie.
\param y Y coordinate of the center of the filled pie.
\param rad Radius in pixels of the filled pie.
\param start Starting radius in degrees of the filled pie.
\param end Ending radius in degrees of the filled pie.
\param r The red value of the filled pie to draw. 
\param g The green value of the filled pie to draw. 
\param b The blue value of the filled pie to draw. 
\param a The alpha value of the filled pie to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledPieRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, Sint16 rad,
              
              Uint8 a) 
                                            end, r, g, b, a, 1);



/* ------ Trigon */ 
    
/*!
\brief Draw trigon (triangle outline) with alpha blending.

Note: Creates vertex array and uses polygon routine to render.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the trigon.
\param y1 Y coordinate of the first point of the trigon.
\param x2 X coordinate of the second point of the trigon.
\param y2 Y coordinate of the second point of the trigon.
\param x3 X coordinate of the third point of the trigon.
\param y3 Y coordinate of the third point of the trigon.
\param color The color value of the trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
trigonColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
            Sint16 y2, Sint16 x3, Sint16 y3,
            Uint32 color) 
    
    
    
    
    
    
    
    



/*!
\brief Draw trigon (triangle outline) with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the trigon.
\param y1 Y coordinate of the first point of the trigon.
\param x2 X coordinate of the second point of the trigon.
\param y2 Y coordinate of the second point of the trigon.
\param x3 X coordinate of the third point of the trigon.
\param y3 Y coordinate of the third point of the trigon.
\param r The red value of the trigon to draw. 
\param g The green value of the trigon to draw. 
\param b The blue value of the trigon to draw. 
\param a The alpha value of the trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
trigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
           Sint16 y2, Sint16 x3, Sint16 y3, 
           Uint8 a) 
    
    
    
    
    
    
    
    



/* ------ AA-Trigon */ 
    
/*!
\brief Draw anti-aliased trigon (triangle outline) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-trigon.
\param y1 Y coordinate of the first point of the aa-trigon.
\param x2 X coordinate of the second point of the aa-trigon.
\param y2 Y coordinate of the second point of the aa-trigon.
\param x3 X coordinate of the third point of the aa-trigon.
\param y3 Y coordinate of the third point of the aa-trigon.
\param color The color value of the aa-trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aatrigonColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
              Sint16 y2, Sint16 x3, Sint16 y3,
              Uint32 color) 
    
    
    
    
    
    
    
    



/*!
\brief Draw anti-aliased trigon (triangle outline) with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the aa-trigon.
\param y1 Y coordinate of the first point of the aa-trigon.
\param x2 X coordinate of the second point of the aa-trigon.
\param y2 Y coordinate of the second point of the aa-trigon.
\param x3 X coordinate of the third point of the aa-trigon.
\param y3 Y coordinate of the third point of the aa-trigon.
\param r The red value of the aa-trigon to draw. 
\param g The green value of the aa-trigon to draw. 
\param b The blue value of the aa-trigon to draw. 
\param a The alpha value of the aa-trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aatrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
             Sint16 y2, Sint16 x3, Sint16 y3, 
             Uint8 a) 
    
    
    
    
    
    
    
    



/* ------ Filled Trigon */ 
    
/*!
\brief Draw filled trigon (triangle) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the filled trigon.
\param y1 Y coordinate of the first point of the filled trigon.
\param x2 X coordinate of the second point of the filled trigon.
\param y2 Y coordinate of the second point of the filled trigon.
\param x3 X coordinate of the third point of the filled trigon.
\param y3 Y coordinate of the third point of the filled trigon.
\param color The color value of the filled trigon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledTrigonColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
                  Sint16 y2, Sint16 x3, Sint16 y3,
                  Uint32 color) 
    
    
    
    
    
    
    
    



/*!
\brief Draw filled trigon (triangle) with alpha blending.

Note: Creates vertex array and uses aapolygon routine to render.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the filled trigon.
\param y1 Y coordinate of the first point of the filled trigon.
\param x2 X coordinate of the second point of the filled trigon.
\param y2 Y coordinate of the second point of the filled trigon.
\param x3 X coordinate of the third point of the filled trigon.
\param y3 Y coordinate of the third point of the filled trigon.
\param r The red value of the filled trigon to draw. 
\param g The green value of the filled trigon to draw. 
\param b The blue value of the filled trigon to draw. 
\param a The alpha value of the filled trigon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledTrigonRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
                 Sint16 y2, Sint16 x3, Sint16 y3, 
                 Uint8 b, Uint8 a) 
    
    
    
    
    
    
    
    



/* ---- Polygon */ 
    
/*!
\brief Draw polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
polygonColor(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy,
             int n, Uint32 color) 
    



/*!
\brief Draw polygon with the currently set color and blend mode.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
polygon(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy,
        int n) 
        /*
         * Draw 
         */ 
        int result = 0;
    

    
    
        /*
         * Vertex array NULL check 
         */ 
        if (vx == NULL) {
        
    
    
        
    
    
        /*
         * Sanity check 
         */ 
        if (n < 3) {
        
    
    
        /*
         * Create array of points
         */ 
        nn = n + 1;
    
    
        
        
        
    
        
        
        
        
    
    
    
        /*
         * Draw 
         */ 
        result |= SDL_RenderDrawLines(renderer, points, nn);
    
    



/*!
\brief Draw polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the polygon.
\param vy Vertex array containing Y coordinates of the points of the polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the polygon to draw. 
\param g The green value of the polygon to draw. 
\param b The blue value of the polygon to draw. 
\param a The alpha value of the polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
polygonRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy,
            int n, Uint8 r, Uint8 g, Uint8 b, Uint8 a) 
        /*
         * Draw 
         */ 
        int result;
    

    
        /*
         * Vertex array NULL check 
         */ 
        if (vx == NULL) {
        
    
    
        
    
    
        /*
         * Sanity check 
         */ 
        if (n < 3) {
        
    
    
        /*
         * Pointer setup 
         */ 
        x1 = x2 = vx;
    
    
    
    
        /*
         * Set color 
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
        /*
         * Draw 
         */ 
        result |= polygon(renderer, vx, vy, n);
    



/* ---- AA-Polygon */ 
    
/*!
\brief Draw anti-aliased polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the aa-polygon.
\param vy Vertex array containing Y coordinates of the points of the aa-polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the aa-polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aapolygonColor(SDL_Renderer * renderer, const Sint16 * vx,
               const Sint16 * vy, int n, Uint32 color) 
        (Uint8 *) & color;
    



/*!
\brief Draw anti-aliased polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the aa-polygon.
\param vy Vertex array containing Y coordinates of the points of the aa-polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the aa-polygon to draw. 
\param g The green value of the aa-polygon to draw. 
\param b The blue value of the aa-polygon to draw. 
\param a The alpha value of the aa-polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
aapolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx,
              const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b,
              Uint8 a) 
    
    

    
        /*
         * Vertex array NULL check 
         */ 
        if (vx == NULL) {
        
    
    
        
    
    
        /*
         * Sanity check 
         */ 
        if (n < 3) {
        
    
    
        /*
         * Pointer setup 
         */ 
        x1 = x2 = vx;
    
    
    
    
        /*
         * Draw 
         */ 
        result = 0;
    
        
            _aalineRGBA(renderer, *x1, *y1, *x2, *y2, r, g, b, a, 0);
        
        
        
        
    
    
    



/* ---- Filled Polygon */ 
    
/*!
\brief Internal helper qsort callback functions used in filled polygon drawing.

\param a The surface to draw on.
\param b Vertex array containing X coordinates of the points of the polygon.

\returns Returns 0 if a==b, a negative number if a<b or a positive number if a>b.
*/ 
    int
_gfxPrimitivesCompareInt(const void *a, const void *b) 
    { 


/*!
\brief Global vertex array to use if optional parameters are not given in filledPolygonMT calls.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/ 
static int *gfxPrimitivesPolyIntsGlobal = NULL;


/*!
\brief Flag indicating if global vertex array was already allocated.

Note: Used for non-multithreaded (default) operation of filledPolygonMT.
*/ 
static int gfxPrimitivesPolyAllocatedGlobal = 0;


/*!
\brief Draw filled polygon with alpha blending (multi-threaded capable).

Note: The last two parameters are optional; but are required for multithreaded operation.  

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw. 
\param g The green value of the filled polygon to draw. 
\param b The blue value of the filled polygon to draw. 
\param a The alpha value of the filled polygon to draw.
\param polyInts Preallocated, temporary vertex array used for sorting vertices. Required for multithreaded operation; set to NULL otherwise.
\param polyAllocated Flag indicating if temporary vertex array was allocated. Required for multithreaded operation; set to NULL otherwise.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledPolygonRGBAMT(SDL_Renderer * renderer, const Sint16 * vx,
                    const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b,
                    Uint8 a, int **polyInts,
                    int *polyAllocated) 
    
    
    
    
    
    
    
    
    
    

    
        /*
         * Vertex array NULL check 
         */ 
        if (vx == NULL) {
        
    
    
        
    
    
        /*
         * Sanity check number of edges
         */ 
        if (n < 3) {
        
    
    
        /*
         * Map polygon cache  
         */ 
        if ((polyInts == NULL) || (polyAllocated == NULL)) {
        
            /* Use global cache */ 
            gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
        
    
        
            /* Use local cache */ 
            gfxPrimitivesPolyInts = *polyInts;
        
    
    
        /*
         * Allocate temp array, only grow array 
         */ 
        if (!gfxPrimitivesPolyAllocated) {
        
        
    
        
            
                (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
            
                
                    
                    
                
                
            
                
                
            
        
    
    
        /*
         * Check temp array
         */ 
        if (gfxPrimitivesPolyInts == NULL) {
        
    
    
        /*
         * Update cache variables
         */ 
        if ((polyInts == NULL) || (polyAllocated == NULL)) {
        
        
    
        
        
    
    
        /*
         * Check temp array again
         */ 
        if (gfxPrimitivesPolyInts == NULL) {
        
    
    
        /*
         * Determine Y maxima 
         */ 
        miny = vy[0];
    
    
        
            
        
            
        
    
    
        /*
         * Draw, scanning y 
         */ 
        result = 0;
    
        
        
            
                
                
            
                
                
            
            
            
            
                
                
            
                
                
                
                
            
                
            
            
                 || ((y == maxy) && (y > y1) && (y <= y2))) {
                
                    ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) +
                    (65536 * x1);
            
        
        
                 _gfxPrimitivesCompareInt);
        
            /*
             * Set color 
             */ 
            result = 0;
        
            SDL_SetRenderDrawBlendMode(renderer,
                                       (a ==
                                        255) ? SDL_BLENDMODE_NONE :
                                       SDL_BLENDMODE_BLEND);
        
        
            
            
            
            
            
        
    
    



/*!
\brief Draw filled polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param color The color value of the filled polygon to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledPolygonColor(SDL_Renderer * renderer, const Sint16 * vx,
                   const Sint16 * vy, int n, Uint32 color) 
        (Uint8 *) & color;
    
                                c[3], NULL, NULL);



/*!
\brief Draw filled polygon with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the filled polygon.
\param vy Vertex array containing Y coordinates of the points of the filled polygon.
\param n Number of points in the vertex array. Minimum number is 3.
\param r The red value of the filled polygon to draw. 
\param g The green value of the filled polygon to draw. 
\param b The blue value of the filed polygon to draw. 
\param a The alpha value of the filled polygon to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
filledPolygonRGBA(SDL_Renderer * renderer, const Sint16 * vx,
                  const Sint16 * vy, int n, Uint8 r, Uint8 g, Uint8 b,
                  Uint8 a) 
                                                           vy, n, r, g, b,
                                                           a, NULL, NULL);



/* ---- Textured Polygon */ 
    
/*!
\brief Internal function to draw a textured horizontal line.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point (i.e. left) of the line.
\param x2 X coordinate of the second point (i.e. right) of the line.
\param y Y coordinate of the points of the line.
\param texture The texture to retrieve color information from.
\param texture_w The width of the texture.
\param texture_h The height of the texture.
\param texture_dx The X offset for the texture lookup.
\param texture_dy The Y offset for the textured lookup.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
_HLineTextured(SDL_Renderer * renderer, Sint16 x1, Sint16 x2, Sint16 y,
               SDL_Texture * texture, int texture_w, int texture_h,
               int texture_dx, int texture_dy) 
    
    
    
    

    
    

    
        /*
         * Swap x1, x2 if required to ensure x1<=x2
         */ 
        if (x1 > x2) {
        
        
        
    
    
        /*
         * Calculate width to draw
         */ 
        w = x2 - x1 + 1;
    
        /*
         * Determine where in the texture we start drawing
         */ 
        texture_x_walker = (x1 - texture_dx) % texture_w;
    
        
    
    
    
        
    
    
        /* setup the source rectangle; we are only drawing one horizontal line */ 
        source_rect.y = texture_y_start;
    
    
    
        /* we will draw to the current y */ 
        dst_rect.y = y;
    
    
        /* if there are enough pixels left in the current row of the texture */ 
        /* draw it all at once */ 
        if (w <= texture_w - texture_x_walker) {
        
        
        
        
        
            (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect) ==
             0);
    
        
            /* we need to draw multiple times */ 
            /* draw the first segment */ 
            pixels_written = texture_w - texture_x_walker;
        
        
        
        
        
            (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect) ==
             0);
        
        
            /* now draw the rest */ 
            /* set the source x to 0 */ 
            source_rect.x = 0;
        
            
                
            
            
            
            
            
                (SDL_RenderCopy(renderer, texture, &source_rect, &dst_rect)
                 == 0);
            
        
    
    



/*!
\brief Draws a polygon filled with the given texture (Multi-Threading Capable). 

\param renderer The renderer to draw on.
\param vx array of x vector components
\param vy array of x vector components
\param n the amount of vectors in the vx and vy array
\param texture the sdl surface to use to fill the polygon
\param texture_dx the offset of the texture relative to the screeen. If you move the polygon 10 pixels 
to the left and want the texture to apear the same you need to increase the texture_dx value
\param texture_dy see texture_dx
\param polyInts Preallocated temp array storage for vertex sorting (used for multi-threaded operation)
\param polyAllocated Flag indicating oif the temp array was allocated (used for multi-threaded operation)

\returns Returns 0 on success, -1 on failure.
*/ 
    int
texturedPolygonMT(SDL_Renderer * renderer, const Sint16 * vx,
                  const Sint16 * vy, int n, 
                  int texture_dx, int texture_dy, int **polyInts,
                  int *polyAllocated) 
    
    
    
    
    
    
    
    
    
    

    
    
        /*
         * Sanity check number of edges
         */ 
        if (n < 3) {
        
    
    
        /*
         * Map polygon cache  
         */ 
        if ((polyInts == NULL) || (polyAllocated == NULL)) {
        
            /* Use global cache */ 
            gfxPrimitivesPolyInts = gfxPrimitivesPolyIntsGlobal;
        
    
        
            /* Use local cache */ 
            gfxPrimitivesPolyInts = *polyInts;
        
    
    
        /*
         * Allocate temp array, only grow array 
         */ 
        if (!gfxPrimitivesPolyAllocated) {
        
        
    
        
            
                (int *) realloc(gfxPrimitivesPolyInts, sizeof(int) * n);
            
                
                    /* Realloc failed - keeps original memory block, but fails this operation */ 
                    return (-1);
            
            
            
        
    
    
        /*
         * Check temp array
         */ 
        if (gfxPrimitivesPolyInts == NULL) {
        
    
    
        /*
         * Update cache variables
         */ 
        if ((polyInts == NULL) || (polyAllocated == NULL)) {
        
        
    
        
        
    
    
        /*
         * Check temp array again
         */ 
        if (gfxPrimitivesPolyInts == NULL) {
        
    
    
        /*
         * Determine X,Y minima,maxima 
         */ 
        miny = vy[0];
    
    
    
    
        
            
        
            
        
        
            
        
            
        
    
    
        /* Create texture for drawing */ 
        textureAsTexture = SDL_CreateTextureFromSurface(renderer, texture);
    
        
        
        
    
    
        /*
         * Draw, scanning y 
         */ 
        result = 0;
    
        
        
            
                
                
            
                
                
            
            
            
            
                
                
            
                
                
                
                
            
                
            
            
                 || ((y == maxy) && (y > y1) && (y <= y2))) {
                
                    ((65536 * (y - y1)) / (y2 - y1)) * (x2 - x1) +
                    (65536 * x1);
            
        
        
                 _gfxPrimitivesCompareInt);
        
            
            
            
            
            
                _HLineTextured(renderer, xa, xb, y, textureAsTexture,
                               texture->w, texture->h, texture_dx,
                               texture_dy);
        
    
    
    
    



/*!
\brief Draws a polygon filled with the given texture. 

This standard version is calling multithreaded versions with NULL cache parameters.

\param renderer The renderer to draw on.
\param vx array of x vector components
\param vy array of x vector components
\param n the amount of vectors in the vx and vy array
\param texture the sdl surface to use to fill the polygon
\param texture_dx the offset of the texture relative to the screeen. if you move the polygon 10 pixels 
to the left and want the texture to apear the same you need to increase the texture_dx value
\param texture_dy see texture_dx

\returns Returns 0 on success, -1 on failure.
*/ 
    int
texturedPolygon(SDL_Renderer * renderer, const Sint16 * vx,
                const Sint16 * vy, int n, SDL_Surface * texture,
                int texture_dx, int texture_dy) 
        /*
         * Draw
         */ 
        return (texturedPolygonMT
                (renderer, vx, vy, n, texture, texture_dx, texture_dy,
                 NULL, NULL));



/* ---- Character */ 
    
/*!
\brief Global cache for NxM pixel font textures created at runtime.
*/ 
static SDL_Texture *gfxPrimitivesFont[256];


/*!
\brief Pointer to the current font data. Default is a 8x8 pixel internal font. 
*/ 
static const unsigned char *currentFontdata = gfxPrimitivesFontdata;


/*!
\brief Width of the current font. Default is 8. 
*/ 
static Uint32 charWidth = 8;


/*!
\brief Height of the current font. Default is 8. 
*/ 
static Uint32 charHeight = 8;


/*!
\brief Width for rendering. Autocalculated.
*/ 
static Uint32 charWidthLocal = 8;


/*!
\brief Height for rendering. Autocalculated.
*/ 
static Uint32 charHeightLocal = 8;


/*!
\brief Pitch of the current font in bytes. Default is 1. 
*/ 
static Uint32 charPitch = 1;


/*!
\brief Characters 90deg clockwise rotations. Default is 0. Max is 3. 
*/ 
static Uint32 charRotation = 0;


/*!
\brief Character data size in bytes of the current font. Default is 8. 
*/ 
static Uint32 charSize = 8;


/*!
\brief Sets or resets the current global font data.

The font data array is organized in follows: 
[fontdata] = [character 0][character 1]...[character 255] where
[character n] = [byte 1 row 1][byte 2 row 1]...[byte {pitch} row 1][byte 1 row 2] ...[byte {pitch} row height] where
[byte n] = [bit 0]...[bit 7] where 
[bit n] = [0 for transparent pixel|1 for colored pixel]

\param fontdata Pointer to array of font data. Set to NULL, to reset global font to the default 8x8 font.
\param cw Width of character in bytes. Ignored if fontdata==NULL.
\param ch Height of character in bytes. Ignored if fontdata==NULL.
*/ 
    void
gfxPrimitivesSetFont(const void *fontdata, Uint32 cw, Uint32 ch) 
    { 
    
        
        
        
    
        
        
        
    
    
    
    
        /* Maybe flip width/height for rendering */ 
        if ((charRotation == 1) || (charRotation == 3))
        
        
        
        
    
    else
        
        
        
        
    
        /* Clear character cache */ 
        for (i = 0; i < 256; i++) {
        
            
            
        
    



/*!
\brief Sets current global font character rotation steps. 

Default is 0 (no rotation). 1 = 90deg clockwise. 2 = 180deg clockwise. 3 = 270deg clockwise.
Changing the rotation, will reset the character cache.

\param rotation Number of 90deg clockwise steps to rotate
*/ 
    void
gfxPrimitivesSetFontRotation(Uint32 rotation) 

    
    
        
        
            /* Store rotation */ 
            charRotation = rotation;
        
            /* Maybe flip width/height for rendering */ 
            if ((charRotation == 1) || (charRotation == 3))
            
            
            
            
        
        else
            
            
            
            
        
            /* Clear character cache */ 
            for (i = 0; i < 256; i++) {
            
                
                
            
        
        



/*!
\brief Draw a character of the currently set font.

\param renderer The Renderer to draw on.
\param x X (horizontal) coordinate of the upper left corner of the character.
\param y Y (vertical) coordinate of the upper left corner of the character.
\param c The character to draw.
\param r The red value of the character to draw. 
\param g The green value of the character to draw. 
\param b The blue value of the character to draw. 
\param a The alpha value of the character to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
characterRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, char c, Uint8 r,
              Uint8 g, Uint8 b, Uint8 a) 
    
    

    
    

    
    
    
    
    
    
    
    
        /*
         * Setup source rectangle
         */ 
        srect.x = 0;
    
    
    
    
        /*
         * Setup destination rectangle
         */ 
        drect.x = x;
    
    
    
    
        /* Character index in cache */ 
        ci = (unsigned char) c;
    
        /*
         * Create new charWidth x charHeight bitmap surface if not already present.
         * Might get rotated later.
         */ 
        if (gfxPrimitivesFont[ci] == NULL) {
        
            /*
             * Redraw character into surface
             */ 
            character =
            SDL_CreateRGBSurface(SDL_SWSURFACE, 
                                 
                                 0x000000FF);
        
            
        
        
        
        
        
            /*
             * Drawing loop 
             */ 
            patt = 0;
        
            
            
            
                
                    
                    
                
                
                    
                
                    
                
                
            
            
        
        
            /* Maybe rotate and replace cached image */ 
            if (charRotation > 0)
            
            
                rotateSurface90Degrees(character, charRotation);
            
            
            
        
            /* Convert temp surface into texture */ 
            gfxPrimitivesFont[ci] =
            SDL_CreateTextureFromSurface(renderer, character);
        
        
            /*
             * Check pointer 
             */ 
            if (gfxPrimitivesFont[ci] == NULL) {
            
        
    
    
        /*
         * Set color 
         */ 
        result = 0;
    
    
    
        /*
         * Draw texture onto destination 
         */ 
        result |=
        SDL_RenderCopy(renderer, gfxPrimitivesFont[ci], &srect, &drect);
    



/*!
\brief Draw a character of the currently set font.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the upper left corner of the character.
\param y Y (vertical) coordinate of the upper left corner of the character.
\param c The character to draw.
\param color The color value of the character to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
characterColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, char c,
               Uint32 color) 
    



/*!
\brief Draw a string in the currently set font.

The spacing between consequtive characters in the string is the fixed number of pixels 
of the character width of the current global font.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the upper left corner of the string.
\param y Y (vertical) coordinate of the upper left corner of the string.
\param s The string to draw.
\param color The color value of the string to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
stringColor(SDL_Renderer * renderer, Sint16 x, Sint16 y, const char *s,
            Uint32 color) 
    



/*!
\brief Draw a string in the currently set font.

\param renderer The renderer to draw on.
\param x X (horizontal) coordinate of the upper left corner of the string.
\param y Y (vertical) coordinate of the upper left corner of the string.
\param s The string to draw.
\param r The red value of the string to draw. 
\param g The green value of the string to draw. 
\param b The blue value of the string to draw. 
\param a The alpha value of the string to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
stringRGBA(SDL_Renderer * renderer, Sint16 x, Sint16 y, const char *s,
           Uint8 r, Uint8 g, Uint8 b, Uint8 a) 
    
    
    

    
        
            characterRGBA(renderer, curx, cury, *curchar, r, g, b, a);
        
            
        
            
            
        
            
            
        
            
            
        
            
            
            
        
    
    



/* ---- Bezier curve */ 
    
/*!
\brief Internal function to calculate bezier interpolator of data array with ndata values at position 't'.

\param data Array of values.
\param ndata Size of array.
\param t Position for which to calculate interpolated value. t should be between [0, ndata].

\returns Interpolated value at position t, value[0] when t<0, value[n-1] when t>n.
*/ 
    double
_evaluateBezier(double *data, int ndata, double t) 
    
    

    
        /* Sanity check bounds */ 
        if (t < 0.0) {
        
    
    
        
    
    
        /* Adjust t to the range 0.0 to 1.0 */ 
        mu = t / (double) ndata;
    
        /* Calculate interpolate */ 
        n = ndata - 1;
    
    
    
    
        
        
        
        
        
        
        
            
            
            
                
                
            
            
                
                
            
        
    



/*!
\brief Draw a bezier curve with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the bezier curve.
\param vy Vertex array containing Y coordinates of the points of the bezier curve.
\param n Number of points in the vertex array. Minimum number is 3.
\param s Number of steps for the interpolation. Minimum number is 2.
\param color The color value of the bezier curve to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
bezierColor(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy,
            int n, int s, Uint32 color) 
    



/*!
\brief Draw a bezier curve with alpha blending.

\param renderer The renderer to draw on.
\param vx Vertex array containing X coordinates of the points of the bezier curve.
\param vy Vertex array containing Y coordinates of the points of the bezier curve.
\param n Number of points in the vertex array. Minimum number is 3.
\param s Number of steps for the interpolation. Minimum number is 2.
\param r The red value of the bezier curve to draw. 
\param g The green value of the bezier curve to draw. 
\param b The blue value of the bezier curve to draw. 
\param a The alpha value of the bezier curve to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
bezierRGBA(SDL_Renderer * renderer, const Sint16 * vx, const Sint16 * vy,
           int n, int s, Uint8 r, Uint8 g, Uint8 b,
           Uint8 a) 
    
    

    
    
        /*
         * Sanity check 
         */ 
        if (n < 3) {
        
    
    
        
    
    
        /*
         * Variable setup 
         */ 
        stepsize = (double) 1.0 / (double) s;
    
        /* Transfer vertices into float arrays */ 
        if ((x = (double *) malloc(sizeof(double) * (n + 1))) == NULL) {
        
    
    
        
        
    
    
        
        
    
    
    
        /*
         * Set color 
         */ 
        result = 0;
    
        SDL_SetRenderDrawBlendMode(renderer,
                                   (a ==
                                    255) ? SDL_BLENDMODE_NONE :
                                   SDL_BLENDMODE_BLEND);
    
    
        /*
         * Draw 
         */ 
        t = 0.0;
    
    
    
        
        
        
        
        
        
    
    
        /* Clean up temporary array */ 
        free(x);
    
    



/*!
\brief Draw a thick line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param width Width of the line in pixels. Must be >0.
\param color The color value of the line to draw (0xRRGGBBAA). 

\returns Returns 0 on success, -1 on failure.
*/ 
    int
thickLineColor(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
               Sint16 y2, Uint8 width, Uint32 color) 
        (Uint8 *) & color;
    
                          c[2], c[3]);



/*!
\brief Draw a thick line with alpha blending.

\param renderer The renderer to draw on.
\param x1 X coordinate of the first point of the line.
\param y1 Y coordinate of the first point of the line.
\param x2 X coordinate of the second point of the line.
\param y2 Y coordinate of the second point of the line.
\param width Width of the line in pixels. Must be >0.
\param r The red value of the character to draw. 
\param g The green value of the character to draw. 
\param b The blue value of the character to draw. 
\param a The alpha value of the character to draw.

\returns Returns 0 on success, -1 on failure.
*/ 
    int
thickLineRGBA(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2,
              Sint16 y2, Uint8 width, Uint8 r, Uint8 g, Uint8 b,
              Uint8 a) 
    
    

    
    
        
    
    
        
    
    
        /* Special case: thick "point" */ 
        if ((x1 == x2) && (y1 == y2)) {
        
        
                        r, g, b, a);
    
    
        /* Special case: width == 1 */ 
        if (width == 1) {
        
    
    
        /* Calculate offsets for sides */ 
        dx = (double) (x2 - x1);
    
    
    
    
    
    
    
    
        /* Build polygon */ 
        dx1 = (double) x1;
    
    
    
    
    
    
    
    
    
    
    
    
        /* Draw polygon */ 
        return filledPolygonRGBA(renderer, px, py, 4, r, g, b, a);


