#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <math.h>

#include "fonctions.h"

void initPoint(struct Point *point)
{
  point->x = 0;
  point->y = 0;
}

void initLine(struct Line *line)
{
  initPoint(&line->origin);
  line->height = 0;
  line->width = 0;
}

void initSymbol(struct Symbol *symbol)
{
  initPoint(&symbol->origin);
  symbol->width = 0;
  symbol->height = 0;
}

void initBlock(struct Block *block)
{
  initPoint(&block->origin);
  block->width = 0;
  block->height = 0;
};
//Vector

/*double normalize(struct Vector *vect)
  {
  double a = pow(vect->x, 2);
  double b = pow(vect->y, 2);
  return sqrt(a + b);
  }*/

//*********************** VECTOR OPERATIONS **************************

struct Vector *make_vector()
{
  struct Vector *vect = malloc(sizeof(struct Vector));
  vect->capacity_b = 1;
  vect->size_b = 0;
  vect->block = malloc(sizeof(struct Block));
  vect->capacity_l = 1;
  vect->size_l = 0;
  vect->line = malloc(sizeof(struct Line));
  vect->capacity_s = 1;
  vect->size_s = 0;
  vect->symbol = malloc(sizeof(struct Symbol));
  return vect;
}

void vector_push_back_b(struct Vector *vect, struct Block *data)
{
  if (vect->size_b + 1 >= vect->capacity_b)
  {
    vect->block = realloc(vect->block, sizeof(struct Block) * vect->capacity_b * 2);
    vect->capacity_b *= 2;
  }

  vect->block[vect->size_b] = *data;
  vect->size_b++;
}

void vector_push_back_l(struct Vector *vect, struct Line *data)
{
  if (vect->size_l + 1 >= vect->capacity_l)
  {
    vect->line = realloc(vect->line, sizeof(struct Line) * vect->capacity_l * 2);
    vect->capacity_l *= 2;
  }

  vect->line[vect->size_l] = *data;
  vect->size_l++;
}

void vector_push_back_s(struct Vector *vect, struct Symbol *data)
{
  if (vect->size_s + 1 >= vect->capacity_s)
  {
    vect->symbol = realloc(vect->symbol, sizeof(struct Symbol) * vect->capacity_s * 2);
    vect->capacity_s *= 2;
  }

  vect->symbol[vect->size_s] = *data;
  vect->size_s++;
}


//*********************** PIXELS OPERATIONS **************************

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;
      break;

    case 2:
      return *(Uint16 *)p;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
      break;

    case 4:
      return *(Uint32 *)p;
      break;

    default:
      return 0;       /* shouldn't happen, but avoids warnings */
  }
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  int bpp = surface->format->BytesPerPixel;

  Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
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

//******************* DRAWING ************************

void drawLines(SDL_Surface *ecran, struct Line line)
{
  SDL_LockSurface(ecran);
  for (int i = 0; i < line.width; i++)
  {
    setPixel(ecran, i + line.origin.x, line.origin.y-1, SDL_MapRGB(ecran->format, 0, 50, 255));
    setPixel(ecran, i + line.origin.x, line.origin.y + line.height, SDL_MapRGB(ecran->format, 0, 50, 255));
  }
  SDL_UnlockSurface(ecran);
}

void drawBorders(SDL_Surface *ecran, struct Symbol symbol)
{
  SDL_LockSurface(ecran);

  for (int j = symbol.origin.y; j < symbol.origin.y + symbol.height; j++)
  {
    //To not go out of the screen
    if (j >= 0 && j < ecran->h)
    {
      if (symbol.origin.x - 1 >= 0)
      {
        setPixel(ecran, symbol.origin.x - 1, j, SDL_MapRGB(ecran->format, 200, 25, 25));
      }
      if (symbol.origin.x + symbol.width < ecran->w)
      {
        setPixel(ecran, symbol.origin.x + symbol.width, j, SDL_MapRGB(ecran->format, 200, 25, 25));
      }
    }
  }

  for (int i = symbol.origin.x; i < symbol.origin.x + symbol.width; i++)
  {
    //To not go out of the screen
    if (i >= 0 && i < ecran->w)
    {
      if (symbol.origin.y - 1 >= 0)
      {
        setPixel(ecran, i, symbol.origin.y - 1, SDL_MapRGB(ecran->format, 200, 25, 25));
      }
      if (symbol.origin.y + symbol.height < ecran->h)
      {
        setPixel(ecran, i, symbol.origin.y + symbol.height, SDL_MapRGB(ecran->format, 200, 25, 25));
      }
    }
  }
  SDL_UnlockSurface(ecran);
}

void drawBlockBorders(SDL_Surface *screen, struct Block *block)
{
  SDL_LockSurface(screen);

  for (int j = block->origin.y; j < block->origin.y + block->height; j++)
  {
    if (j >= 0 && j < screen->h)
    {
      if (block->origin.x - 1 >= 0)
        setPixel(screen, block->origin.x - 1, j, SDL_MapRGB(screen->format, 25, 200, 25));
      if (block->origin.x + block->width < screen->w)
        setPixel(screen, block->origin.x + block->width, j, SDL_MapRGB(screen->format, 25, 200, 25));
    }
  }

  for (int i = block->origin.x; i < block->origin.x + block->width; i++)
  {
    if (i >= 0 && i < screen->w)
    {
      if (block->origin.y - 1 >= 0)
        setPixel(screen, i, block->origin.y - 1, SDL_MapRGB(screen->format, 25, 200, 25));
      if (block->origin.y + block->height < screen->h)
        setPixel(screen, i, block->origin.y + block->height, SDL_MapRGB(screen->format, 25, 200, 25));
    }
  }

  SDL_UnlockSurface(screen);
}

//*************** To perfect image ************************

void blackNWhite(SDL_Surface *ecran)
{
  Uint8 r = 0, g = 0, b = 0;

  SDL_LockSurface(ecran);

  for (int j = 0; j < ecran->h; j++)
  {
    for (int i = 0; i < ecran->w; i++)
    {
      SDL_GetRGB(getPixel(ecran, i, j), ecran->format, &r, &g, &b);

      if ((r & g & b) < 120 && r == g && g == b) // Test du gris
      {
        setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 0, 0, 0));
      }
      else if((r & g & b) < 100 && fabs(r - g) < 100 && fabs(g - b) < 100 && fabs(b -r) < 100)
      {
        setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 0, 0, 0));
      }
      else
      {
        setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255, 255, 255));
      }
    }
  }
  SDL_UnlockSurface(ecran);
}

void eraseLonelyPoint(SDL_Surface *ecran)
{
  int caseAroundCenter = 1; //For future bigger matrix !
  int alone = 1;

  for (int j = 0; j < ecran->h; j++)
  {
    for (int i = 0; i < ecran->w; i++)
    {
      //If it's a black pixel
      if (getPixel(ecran, i, j) == SDL_MapRGB(ecran->format, 0, 0, 0))
      {
        //A pixel is alone while there are no other black pixel around it
        alone = 1;
        //The Matrice
        for (int y = j - caseAroundCenter; y <= j + caseAroundCenter; y++)
        {
          for (int x = i - caseAroundCenter; x <= i + caseAroundCenter; x++)
          {
            //Not to go out of the screen && not to test the pixel in the center
            if (y >= 0 && y < ecran->h && x >= 0 && x < ecran->w &&
                (y != j || x != i) && getPixel(ecran, x, y) == SDL_MapRGB(ecran->format, 0, 0, 0))
            {
              alone = 0;
            }
          }
        }

        if (alone) // If it's a lonely point, then it's erased
        {
          SDL_LockSurface(ecran);
          setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255, 255, 255));
          SDL_UnlockSurface(ecran);
        }

      }
    }
  }
}
