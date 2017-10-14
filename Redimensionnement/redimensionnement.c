#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

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

SDL_Surface *LoadImage(char path[])
{
  SDL_Surface *res = IMG_Load(path);
  if (!res)
    warnx("Wrong path");
  return res;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
    warnx("Missing path");
  SDL_Surface *img = LoadImage(argv[1]);
  SDL_Window *screen = SDL_CreateWindow("Affichage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  img->w, img->h, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
  
  SDL_Rect source;
  source.x = 0;
  source.y = 0;
  source.w = img->w;
  source.h = img->h;

  SDL_Rect desti;
  desti.x = 0;
  desti.y = 0;
  desti.w = 200;
  desti.h = 200;

  printf("%d %d \n", source.h, source.w);
  printf("%d %d \n", desti.h, desti.w);
  
  SDL_FreeSurface(img);
  
  //display_image(img);
  return 0;
}
