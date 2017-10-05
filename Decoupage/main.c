# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "pixel_operations.h"

struct Coords
{
    int beginposx;
    int endposx;
    int beginposy;
    int endposy;
};

typedef struct Coordonnees Coordonnees;

int main(int argc, char *path[])
{
  decoupage(path);
  return 0;
}

void decoupage(char *path[])
{
   SDL_Surface *surface = load_image(path[1]);
   Uint8 r = 0, g = 0, b = 0;
   int j=0;
   int i=0;
   
   while (j<= surface->h)
   {
     struct Coords coord;
     for (j = j ; j < surface->h; j++)
     {
       for (i = i ; i < surface->w; i++)
       {
	 SDL_GetRGB(getpixel(surface, i, j), surface->format, &r, &g, &b);
         if ((r & g & b) == 0  && r == g && g == b))
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
        if( j < surface->h)
	{
	  return; 
	}
	
        // findendletters demarque la fin d'une lettre en cherchant une ligne blanche
        // colonne verte pour separer la fin d'une lettre
        coord.endposy = findendletters(surface,j);
        for (i; i < surface->h; i++)
        {
            for (j = coord.beginposx; j<coord.endposy; j++)
            {
	      if ((r & g & b) == 0  && r == g && g == b))
                {
                    putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255));//point vert en haut
                    coord.beginposy = i;
                    break;
                }
	
            }
	    if (b == 255 && (r & g) == 0 && r == g))
	    {
	      break;
	    }

        }
        for (i = surface->h ; i>0; i--)
        {
            for (j = beginposx; j<endposy; j++)
            {
                if ((r & g & b) == 0  && r == g && g == b))
                {
                    coord.endposx = i;
                    putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255)); //point vert en bas
                    break;
                }

            }
	    if (b == 255 && (r & g) == 0 && r == g)
	    {
	      break;
	    }
         }
	// la il faut creer une tableau [][] aloue et mettre la struc coord dedant
    }
}

int findendletters(SDL_Surface *surface, int posy)
{
    int n = 0;
    int posx =0;
    Uint8 r = 0, g = 0, b = 0;
    while (n != surface->h || posy<= surface->h)
    {
        if ((r & g & b) == 255  && r == g && g == b))
            n+=1;
        if (posx >= surface->w)
        {
            posx=0;
            posy+=1;

        }
        else
            posx+=1;
    }
    //while (posx>0)
    //{
    //   tableau[posx][posy] == 71;
    //   posx -=1 ;
    //}
    return posy;
}
void drawLines(SDL_Surface *surface, int x, int y)
{
  SDL_LockSurface(surface);
  for (int i = 0; i < surface -> w; i++)
  {
    putpixel(surface, i + x ,y-1, SDL_MapRGB(surface->format, 0, 0, 255));
  }
  SDL_UnlockSurface(surface);
}
void drawBorders(SDL_Surface *surface, int x, int y)
{
  SDL_LockSurface(surface);
  
  for (int j = y; j < surface -> h; j++)
  {
     putpixel(surface, x - 1, j, SDL_MapRGB(surface->format, 0, 0, 255));
  }
  
  SDL_UnlockSurface(surface);
}
