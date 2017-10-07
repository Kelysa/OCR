# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "pixel_operations.h"
#include <math.h>



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
    {
      errx(3, "can't load %s: %s", path, IMG_GetError());
    }
  return img;
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
int main(int arg, char *path[])
{
  if (arg == 1)
  {
    return 1;
  }
  else if (arg > 2)
  {
    return 1;
  }
  SDL_Surface *surface = load_image(path[1]);

  Uint8 r = 0, g = 0, b = 0;

  for (int j = 0; j < surface->h; j++)
  {
    for (int i = 0; i < surface->w; i++)
    {
      SDL_GetRGB(getpixel(surface, i, j), surface->format, &r, &g, &b);

      if ((r & g & b) < 127 && r == g && g == b)
      {
        putpixel(surface, i, j, SDL_MapRGB(surface->format, 0, 0, 0));
      }
      else if((r & g & b) < 100 && fabs(r - g) < 100 && fabs(g - b) < 100 && fabs(b -r) < 100)
      {
        putpixel(surface, i, j, SDL_MapRGB(surface->format, 0, 0, 0));
      }
      else
      {
        putpixel(surface, i, j, SDL_MapRGB(surface->format, 255, 255, 255));
      }
    }
  }
  display_image(surface);
  SDL_FreeSurface(surface);
  
}
