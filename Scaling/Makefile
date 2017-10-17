## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` 

OBJ= resize.o
DEP= ${SRC:.o=.d}

all: resize

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} resize resize.d

-include ${DEP}

# END
