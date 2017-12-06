# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include <math.h>
#include "../algebra.h"

int main ()
{
  double l [] = {2.0, 15.0 ,1.0,
                 2.0, 15.2, 1.8,
                 11 , 20 ,  100};
  int col = 3;
  int line = 3;
  matricefile(l,col,line);
}

void matricefile (double matrice[], int col, int line)
{
  FILE* fichier = NULL;
  fichier = fopen("poid.txt", "w+");
  for(int  i = 0; i < line*col;i++)
    {
      if ( i % col == 0)
	{
	  fprintf(fichier,"\n");
	}
      fprintf(fichier,"%4g,",matrice[i]);
    }
}

/* double* filetomatrice(FILE* fichier, int line, int col) */
/* { */
/*   double l [] = {-10,-10,-10 */
/*                  -10,-10,-10 */
/*                  -10,-10,-10}; */
/*   if (fichier) */
/*     { */
/*       fichier =fopen("poid.txt", "r"); */
/*       return NULL; */
/*     } */
/*   return l; */
/* } */
