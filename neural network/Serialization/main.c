# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include <math.h>
# include <string.h>
#include "../algebra.h"

int main ()
{
  /* int width = 3; */
  /* int height = 3; */
  /* double** l  = malloc((height) * sizeof(double*)); */
  /* l[0] = malloc(sizeof(double) * width); */
  /* l[0][0] = 1.2; l[0][1] = 10; l[0][2] = 6.52;  */
  /* l[1] = malloc(sizeof(double) * width); */
  /* l[1][0] = -10; l[1][1] = 25; l[1][2] = -2;  */
  /* l[2] = malloc(sizeof(double) * width); */
  /* l[2][0] = 1.2; l[2][1] = 1.2; l[2][2] = 1.2; */


  //matricefile(l,width,height); */
  /* l = filetomatrice(height, width); */
  /* printf("\n"); */
  /* printf("%f",l[1][0]); */
  
}

void matricefile (double** matrice, int height, int width)
{
  FILE* fichier = NULL;
  fichier = fopen("poid.txt", "w+");
  for(int i = 0; i < height;i++)
    {
      for(int j = 0; j < width;j++)
	{
	  fprintf(fichier,"%4g",matrice[i][j]);
	  fprintf(fichier,"\n");
	}
    }
  fclose(fichier);
}

char* gline(FILE* f)
{
  size_t len = 0;
  ssize_t read;
  char* line = NULL;
  if ((read = getline(&line,&len,f))==-1)
    {
      exit(0);
    }
  line[read-1]=0;
  return line;
}


double** filetomatrice(int height, int width)  
 {
    double** l  = malloc((height) * sizeof(double*));
    for(int i =0; i< height ; i++)
      {
	l[i] = malloc(sizeof(double) * width); 
      }
    FILE *fichier =fopen("poid.txt", "r");
    
    int i =0;
    int j =0;
    int x = 1;
    double value;
    char* line = NULL;
    while (x <= height*width)
      {
	line = gline(fichier);
	sscanf(line,"%lf",&value);
	if (j == 3)
	  {
	    j=0;
	    i++;
	  }
	//printf("%d",i);
	l[i][j] = value;
	j++;
	x++;
	
      }
    return l;  
}  