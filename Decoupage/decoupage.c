# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "decoupage.h"
# include <math.h>
 
static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
      p[0] = pixel & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = (pixel >> 16) & 0xff;
    }
    break;
  case 4:
    *(Uint32 *)p = pixel;
    break;
  }
}SDL_Surface* display_image(SDL_Surface *img) {
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
void drawLines(SDL_Surface *surface, int x, int y)
{
  SDL_LockSurface(surface);
  for (int i = x; i < (surface -> w)-x; i++)
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
     putpixel(surface, x-1
	      , j, SDL_MapRGB(surface->format, 0, 0, 255));
  }
  
  SDL_UnlockSurface(surface);
}
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

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

void decoupage(SDL_Surface *surface)
{
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

