// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void decoupage(char *path[]);
void drawLines(SDL_Surface *surface, int x, int y);
void drawBorders(SDL_Surface *surface, int x, int y);
typedef struct Coordonnees Coordonnees;
int findendletters(SDL_Surface *surface, int posy);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed(void);
# endif
