/*
** EPITECH PROJECT, 2019
** Task
** File description:
** Function my_print_com
*/

#include "sdlmandel.h"

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

    surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE);
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
