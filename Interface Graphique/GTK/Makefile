## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` 

OBJ= learn.o
DEP= ${SRC:.o=.d}

all: learn

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ .o .d
	${RM} learn learn.d

-include ${DEP}

# END
