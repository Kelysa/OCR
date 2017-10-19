# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "decoupage.h"




int main(int argc, char *path[])
{
  if (argc!=2)
    {
      return 1;
    }
  SDL_Surface *surface = IMG_Load(path[1]);
  int* line = decoupline(surface);
  //findfirstletters(surface,begin);
  //findendletters(surface,begin,0);
  int *colum = decoupcolum(surface,line);
  addcoord (surface,line,colum);
  display_image(surface);
  SDL_FreeSurface(surface);
  return 0;
  
}
