#ifdef _MSC_VER
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif /* _MSC_VER */

#include <stdio.h>
#include <math.h>
#include <complex.h>

#define WIDTH 640
#define HEIGHT 480

#define START_POS   0
#define START_ZOOM  (WIDTH*0.125296875f)

#define BAIL_OUT        2.0
#define FLIPS           24

#define ZOOM_FACTOR     4

void sdl_draw_mandelbrot(SDL_Surface *surface, complex center, double zoom)
{
    int f,x,y,n;
    int maxiter = (WIDTH/10) * 0.049715909 * log10(zoom);
    complex z, c;

    static SDL_Rect rects[HEIGHT/FLIPS];

    for (f = 0; f < FLIPS; f++)
    {
        for  (y = f; y < HEIGHT; y += FLIPS)
        {
            for (x = 0; x < WIDTH; x++)
            {
                /* Get the complex poing on gauss space to be calculate */
                z = c = creal(center) + ((x - (WIDTH/2))/zoom) + 
                    ((cimag(center) + ((y - (HEIGHT/2))/zoom))*_Complex_I);

                /* Applies the actual mandelbrot formula on that point */
                for (n=0; n < maxiter && cabs(z) < BAIL_OUT; n ++)
                    z = cpow(cpow(cpow(cpow(z, 2) + c, 2) + c, 2) + c, 2) + c;

                /* Paint the pixel calculated depending on the number 
                   of iterations found */
                ((Uint32*)surface->pixels)[(y*surface->w) + x] = (n >= maxiter)? 0 :
                    SDL_MapRGB( surface->format,
                    (1.+sin(n*0.27 + 5))*127., (1+cos(n*0.85))*127., (1.+sin(n*0.15))*127. );
            }
            rects[y/FLIPS].x = 0;
            rects[y/FLIPS].y = y;
            rects[y/FLIPS].w = WIDTH;
            rects[y/FLIPS].h = 1;
        }
        SDL_UpdateRects(surface, HEIGHT/FLIPS, rects);
    }
}

int main(int argc, char **argv)
{
    /* SDL SEtup */
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    SDL_Surface *surface;

    surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, 
                               SDL_HWSURFACE | SDL_FULLSCREEN );
    if ( surface == NULL )
    {
        fprintf(stderr, "Could not setup screen to resolution %dx%d : %s\n", 
                WIDTH, HEIGHT, SDL_GetError());
        exit(1);
    }

    /* Initialize variables */
    double complex center = START_POS;
    double zoom = START_ZOOM;

    sdl_draw_mandelbrot(surface, center, zoom);

    SDL_Event event;
    while(1)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == ' ')
                {
                    center = START_POS;
                    zoom = START_ZOOM;
                    sdl_draw_mandelbrot(surface, center, zoom);
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    exit(0);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                center = creal(center) + ((event.button.x - (WIDTH/2))/zoom) +
                         ((cimag(center) + ((event.button.y - (HEIGHT/2))/zoom))
                          *_Complex_I);

                if (event.button.button == 1)
                    zoom *= ZOOM_FACTOR;
                else if (event.button.button == 3)
                    zoom /= ZOOM_FACTOR;

                sdl_draw_mandelbrot(surface, center, zoom);
                break;
        }
    }

    return 0;
}