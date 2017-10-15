## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

OBJ= pixel_operations.o scaling.o
DEP= ${SRC:.o=.d}

all: scaling

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} scaling

-include ${DEP}

# END
