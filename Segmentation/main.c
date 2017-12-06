# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "segmentation.h"




int main(int argc, char *path[])
{
  if (argc!=2)
    {
      return 1;
    }
  SDL_Surface *surface = IMG_Load(path[1]);
  int* line = cutline(surface);
  //findfirstletters(surface,begin);
  //findendletters(surface,begin,0);
  int *colum = cutcolum(surface,line);
  addcoord (surface,line,colum);
  SDL_Surface *newsurface = IMG_Load(path[1]);
  print_matrix (newsurface,line,colum);
  display_image(surface);
  SDL_FreeSurface(surface);
  return 0;

}
