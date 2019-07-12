/*
** EPITECH PROJECT, 2019
** Task
** File description:
** Function my_print_com
*/

#include "sdlmandel.h"

void sdl_draw_mandelbrot(SDL_Surface *surface, complex double center, double zoom)
{
    int f,x,y,n;
    int maxiter = (WIDTH/2) * 0.049715909 * log10(zoom);
    complex double z, c;
    float C;

    static SDL_Rect rects[HEIGHT/FLIPS];

    fprintf(stderr, "zoom: %f\n", zoom);
    fprintf(stderr, "center point: %f %+fi\n", creal(center), 
                                              cimag(center) );
    fprintf(stderr, "iterations: %d\n", maxiter);

    for (f = 0; f < FLIPS; f++)
    {
        for  (y = f; y < HEIGHT; y += FLIPS)
        {
            for (x = 0; x < WIDTH; x++)
            {
                /* Get the complex poing on gauss space to be calculate */
                z = c = creal(center) + ((x - (WIDTH/2))/zoom) + 
                    ((cimag(center) + ((y - (HEIGHT/2))/zoom))*_Complex_I);


                /* Check if point lies within the main cardiod or 
                   in the period-2 buld */
                if ( (pow(X-.25,2) + pow(Y,2))*(pow(X,2) + (X/2) + pow(Y,2) - .1875) < pow(Y,2)/4 ||
                     pow(X+1,2) + pow(Y,2) < .0625 )
                    n = maxiter;
                else
                    /* Applies the actual mandelbrot formula on that point */
                    for (n = 0; n <= maxiter && cabs(z) < BAIL_OUT; n ++)
                        z = cpow(z, 2) + c;

                C = n - log2f(logf(cabs(z)) / M_LN2 );

                /* Paint the pixel calculated depending on the number 
                   of iterations found */
                ((Uint32*)surface->pixels)[(y*surface->w) + x] = (n >= maxiter)? 0 :
                    SDL_MapRGB( surface->format,
                    (1+sin(C*0.27 + 5))*127., (1+cos(C*0.85))*127., (1+sin(C*0.15))*127. );
            }
            rects[y/FLIPS].x = 0;
            rects[y/FLIPS].y = y;
            rects[y/FLIPS].w = WIDTH;
            rects[y/FLIPS].h = 1;
        }
        SDL_UpdateRects(surface, HEIGHT/FLIPS, rects);
    }
}

