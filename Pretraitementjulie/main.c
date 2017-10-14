# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "pixel_operations.h"
#include <math.h>

int main(int arg, char *path[])
{
  if (arg != 2)
  {
    return 1;
  }
  SDL_Surface *surface = load_image(path[1]);
  blackandwhite(surface);
  eraseLonelyPoint(surface);
  display_image(surface);
  SDL_FreeSurface(surface);

}