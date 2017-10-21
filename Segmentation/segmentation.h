// pixel_operations.h

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

# include <stdlib.h>
# include <SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void drawLines(SDL_Surface *surface, int x, int y, int* begin);
void drawBorders(SDL_Surface *surface, int* x, int y);
typedef struct Coordonnees Coordonnees;
int findendline(SDL_Surface *surface,int posy);
int findfirstline(SDL_Surface *surface,int posy);
int* cutline(SDL_Surface *surface);
SDL_Surface* display_image(SDL_Surface *img);
int findfirstletters(SDL_Surface *surface,int* begin,int posx);
int findendletters(SDL_Surface *surface,int* begin,int posx);
int* cutcolum(SDL_Surface *surface,int* begin);
void wait_for_keypressed(void);
void addcoord (SDL_Surface *surface,int* line, int*colum);
void print_matrix (SDL_Surface *surface,int beginposx, int endposx, 
int beginposy,int endposy);
# endif
