#ifndef SDL_MANDEL 
#define SDL_MANDEL
#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif /* _MSC_VER */

#include <stdio.h>
#include <math.h>
#include <complex.h>

#define X creal(z)
#define Y cimag(z)
#define WIDTH 800
#define HEIGHT 600

#define START_POS   -0.5
#define START_ZOOM  (WIDTH * 0.25296875f)

#define BAIL_OUT        2.0
#define FLIPS           24

#define ZOOM_FACTOR     4

void sdl_draw_mandelbrot(SDL_Surface *surface, complex double center, double zoom);
#endif /* SDL_MANDEL */
