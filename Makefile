#! /bin/make
# :vim: set noexpandtab:

CFLAGS = `sdl-config --cflags --libs` -lm

SRC	=	src/main.c\
		src/sdlmandel.c

INCLUDE	=	include/

CPPFLAGS	=	-I$(INCLUDE)

OUTPUT	=	sdl_mandel

OBJ	=	$(SRC:.c=.o)

$(OUTPUT): $(OBJ)
	gcc  $(OBJ) $(CFLAGS) -o $(OUTPUT) -I$(INCLUDE)

