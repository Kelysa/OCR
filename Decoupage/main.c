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

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

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
    //while (posx>0)
    //{
    //   tableau[posx][posy] == 71;
    //   posx -=1 ;
    //}
    return posy;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}
void decoupage(char *path[])
{
   SDL_Surface *surface = IMG_Load(path[1]);
   Uint8 r = 0, g = 0, b = 0;
   int j=0;
   int i=0;
   
   while (j<= surface->h)
   {
     struct Coords coord;
     coord.beginposy=0;
     coord.beginposx=0;
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
        if( j < surface->h)
	     {
	       return; 
	     }
	     
        // findendletters demarque la fin d'une lettre en cherchant une ligne blanche
        // colonne verte pour separer la fin d'une lettre
        coord.endposy = findendletters(surface,j);
        for (; i < surface->h; i++)
        {
            for (j = coord.beginposy; j<coord.endposy; j++)
            {
	            if ((r & g & b) == 0  && r == g && g == b)
                {
                    putpixel(surface, i-1, j, SDL_MapRGB(surface->format,0, 0, 255));//point vert en haut
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


void drawLines(SDL_Surface *surface, int x, int y)
{
  SDL_LockSurface(surface);
  for (int i = x; i < surface -> w; i++)
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

int main(int argc, char *path[])
{
  if (argc!=2)
  {
    return 1;
  }
  SDL_Surface *surface = IMG_Load(path[1]);
  drawLines(surface,50,50);
  drawBorders(surface,50,50);
  display_image(surface);

  SDL_FreeSurface(surface);
  //decoupage(path);
  return 0;
}
