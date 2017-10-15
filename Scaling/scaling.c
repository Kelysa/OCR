#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

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
}

void wait_for_keypressed()
{
  SDL_Event event;

  for(;;)
    {
      SDL_PollEvent(&event);
      switch (event.type)
	{
	case SDL_KEYDOWN:
	  return;
	default:
	  break;
	}
    }
}

SDL_Surface *load(char path[])
{
  SDL_Surface *res = IMG_Load(path);
  if (!res)
    warnx("Path incorrect");
  return res;
}

void display_image(SDL_Surface *img)
{
  SDL_Surface *screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);

  if (!screen)
    {
      warnx("Issue");
    }
   
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error");

  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  
  wait_for_keypressed();

  SDL_FreeSurface(screen);

}

void Scaling(SDL_Surface *src, SDL_Surface *dest)
{
  int stepx = (int)round(src->w/dest->w), stepy = (int)round(src->h/dest->h);
  int cpt = 0;
  Uint8 r, g, b;
  int tempR = 0, tempG = 0, tempB = 0;


  
  for (int i = 0; i < src->h; i++)
    {
      for (int j = 0; j < src->w; j++)
	{
	  if (cpt >= stepx)
	    {
	      putpixel(dest,i,j,SDL_MapRGB(dest->format, tempR/stepx, tempG/stepx, tempB/stepx));
	      cpt = 0;
	      tempR = 0;
	      tempG = 0;
	      tempB = 0;
	    }
	  else
	    {
	      SDL_GetRGB(getpixel(src,i,j), src->format, &r, &g, &b);
	      tempR += r;
	      tempG += g;
	      tempB += b;
	      r = 0;
	      g = 0;
	      b = 0;
	    }
	}
      cpt = 0;
    }   
}


int main(int argc, char *argv[])
{
  if(argc > 1)
    {
      SDL_Surface *img = load(argv[1]);
      SDL_Surface *res = SDL_CreateRGBSurface(0, 200, img->h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

      Scaling(img, res);

      display_image(res);
      return 1;
    }
  else
    warnx("Path is required");
  return 0;
}
