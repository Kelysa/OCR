# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "decoupage.h"

struct Coords
{
    int beginposx;
    int endposx;
    int beginposy;
    int endposy;
};


int findendletters(SDL_Surface *surface, int posy)
{
    int n = 0;
    int posx =0;
    Uint8 r = 0, g = 0, b = 0;
    while (n != surface->h || posy<= surface->h)
    {
        if ((r & g & b) == 255  && r == g && g == b)
            n+=1;
        if (posx >= surface->w)
        {
            posx=0;
            posy+=1;

        }
        else
            posx+=1;
    }
    return posy;
}

void decoupage(char *path[])
{
   SDL_Surface *surface = IMG_Load(path[1]);
   Uint8 r = 0, g = 0, b = 0;
   int j=0;
   int i=0;
   struct Coords coord;
   while (j<= surface->h)
     {
       coord.beginposy=0;
       coord.beginposx=0;
       coord.endposy=0;
       coord.endposx=0;
       for (j = j ; j < surface->h; j++)
	 {
	   for (i = i ; i < surface->w; i++)
	     {
	       SDL_GetRGB(getpixel(surface, i, j), surface->format, &r, &g, &b);
	       if ((r & g & b) == 0  && r == g && g == b)
		 {
		   putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255));
		   coord.beginposy = i;
		   break;
		 }
	     }
	   if (b == 255 && (r & g) == 0 && r == g)
	     {
	       break;
	     }
	    
	 }
       if(j< surface->h)
	 {
	   return; 
	 }
     }
   coord.beginposy = i;
   coord.endposy = findendletters(surface,j);
   for (; i < surface->h; i++)
     {
       for (j = coord.beginposy; j<coord.endposy; j++)
	 {
	   if ((r & g & b) == 0  && r == g && g == b)
	     {
	       putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255));
	       coord.beginposx = i;
	       break;
	     }
	   
	 }
       if (b == 255 && (r & g) == 0 && r == g)
	 {
	   break;
	 }
       
       
     }
   for (i = surface->h ; i>0; i--)
     {
       for (j = coord.beginposx; j<coord.endposy; j++)
	 {
	   if ((r & g & b) == 0  && r == g && g == b)
	     {
	       coord.endposx = i;
	       putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255));
	       break;
	     }
	   
	 }
       if (b == 255 && (r & g) == 0 && r == g)
	 {
	   break;
	 }
     }
   drawLines(surface,coord.beginposx,coord.beginposy);
   drawBorders(surface,coord.endposx,coord.endposy);
   // la il faut creer une tableau [][] aloue et mettre la struc coord dedant
}



int main(int argc, char *path[])
{
  if (argc!=2)
    {
      return 1;
    }
  SDL_Surface *surface = IMG_Load(path[1]);
  display_image(surface);
  decoupage(path);
  SDL_FreeSurface(surface);
  return 0;
}
