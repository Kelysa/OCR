#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "fonctions.h"

void lineDetection(SDL_Surface *ecran, struct Block *block, struct Vector *vect)
{
  int charDetected = 0, lineBegin = 0;
  struct Line *new = NULL;

  for (int j = block->origin.y; j <= block->origin.y + block->height; j++)
  {
    charDetected = 0;
    for (int i = block->origin.x; i <= block->origin.x + block->width; i++)
    {
      //If a black pixel is detected, then there is a line
      if (getPixel(ecran, i, j) == SDL_MapRGB(ecran->format, 0, 0, 0))
      {
        //If we were not in a line, then it's the beginning of a new line
        if (!lineBegin)
        {
          new = malloc(sizeof(struct Line));
          initLine(new);
          new->origin.x = block->origin.x;
          new->origin.y = j;
          //vector_push_back_l(vect, new);
          lineBegin = 1;
        }
        charDetected = 1;
      }
    }

    //If no black pixel has been detected, and we were in a line, then we just got out
    if (charDetected == 0 && lineBegin == 1)
    {
      //Get the height of the line
      new->height = j - new->origin.y;
      new->width = block->width;
      vector_push_back_l(vect, new);
      lineBegin = 0;
    }
  }

  for (int i = 0; i < vect->size_l; i++)
  {
    drawLines(ecran, vect->line[i]);
  }
}
