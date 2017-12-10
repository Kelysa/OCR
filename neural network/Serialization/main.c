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
   int width = 3; 
   int height = 3; 
   double** l  = malloc((height) * sizeof(double*)); 
   l[0] = malloc(sizeof(double) * width); 
   l[0][0] = 1.2; l[0][1] = 10; l[0][2] = 6.52;  
   l[1] = malloc(sizeof(double) * width); 
   l[1][0] = -10; l[1][1] = 25; l[1][2] = -2;  
   l[2] = malloc(sizeof(double) * width); 
   l[2][0] = 1.2; l[2][1] = 1.2; l[2][2] = 1.2; 

   int width2 = 3; 
   int height2 = 3; 
   double** l2  = malloc((height) * sizeof(double*)); 
   l2[0] = malloc(sizeof(double) * width); 
   l2[0][0] = -5; l2[0][1] = -5; l2[0][2] = -5;  
   l2[1] = malloc(sizeof(double) * width); 
   l2[1][0] = -5; l2[1][1] = -5; l2[1][2] = -5;  
   l2[2] = malloc(sizeof(double) * width); 
   l2[2][0] = -5; l2[2][1] = -5; l2[2][2] = -5; 

   matrix* lw = malloc(1024 * sizeof(matrix));
   lw[0].width = width; 
   lw[0].height = height;
   lw[0].List = l;

   lw[1].width = width2; 
   lw[1].height = height2;
   lw[1].List = l2;
  /* a prendre */
  //FILE* fichier = fopen("poid.txt", "w+");
  //matricefile(l,width,height,fichier);
  //matricefile(l2,width2,height2,fichier); 
  //fclose(fichier); 
  //l = filetomatrice(height2, width2,0); 
  //l2 = filetomatrice(height2, width2,height*width); 
  //printf("\n");
  //print_matrix(l, height, width);
  //printf("\n");
  //print_matrix(l2, height, width);
 /*les fonctions sont déjà dans la .h , copie juste ce main*/
 /*( et tu remplace l par ta 1ere matrice)*/
 /*( et l2 par ta 2eme matrice) , bref tu enregistres autant de matrice que tu veux*/
 /*tu remplaces aussi width et height par la taille de la hauteur et largeur de ta matrice */
  savealltofile(lw,2);
  matrix* recup = alltomatrice(2);
  pprint(recup, 2);

 
}
void savealltofile(matrix* l, int nbelement)
{ 
  FILE* fichier = fopen("poid.txt", "w+");
  for(int i =0; i < nbelement ; i++)
  {
    matricefile(l[i].List,l[i].height ,l[i].width,fichier);
  } 
  fclose(fichier); 
}


matrix* alltomatrice(int nbelement)
{ 
  matrix* recup = malloc(2 * sizeof(matrix));
  recup[0].List = filetomatrice(3,3,0);
  recup[0].height = 3;
  recup[0].width = 3;
  for(int i =1; i < nbelement ; i++)
  {
    recup[i].List = filetomatrice(recup[i-1].height ,recup[i-1].width
    ,recup[i-1].width*recup[i-1].height);
    recup[i].height = recup[i-1].height;
    recup[i].width = recup[i-1].width;
    
  }
  return recup;
}


void matricefile (double** matrice, int height, int width, FILE* fichier)
{
  for(int i = 0; i < height;i++)
    {
      for(int j = 0; j < width;j++)
	{
	  fprintf(fichier,"%4g",matrice[i][j]);
	  fprintf(fichier,"\n");
	}
    }
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


double** filetomatrice(int height, int width,int delta)  
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
    while (delta--)
      {
        line = gline(fichier);
	sscanf(line,"%lf",&value);
      }
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
    fclose(fichier);
    return l;  
}  
void print_matrix(double** mat, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {
          printf("%4g ",mat[i][j]);
        }
      
      printf("\n");
    }
}
void pprint(matrix* l, int size)
{
  for(int i =0; i < size ; i++)
  {
    print_matrix( l[i].List,l[i].height ,l[i].width);
    printf("\n");
  }
}
