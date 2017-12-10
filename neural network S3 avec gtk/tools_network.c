#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
 
#include "function.h"
#include "tools_network.h"
#include "correction.h"

matrix* makeLW(int L[], int size)
{
  matrix* lw = NULL;
  lw = malloc((size-1) * sizeof(matrix));
  if(lw == NULL){
      exit(0);
}


  for( int i= 0 ; i < size-1; i++)
    {

      double** list = matw(L[i],L[i+1]);
      lw[i].width = L[i+1];
      lw[i].height = L[i] ;
      lw[i].List = list ;
    }
    return lw;
}

double** matw(int height, int width)
{
  double** w = NULL;
  w = malloc((height) * sizeof(double*));
  if(w == NULL){
      exit(0);
  }
  for(int i = 0; i < height;i++)
  {
    if((w[i] = malloc(sizeof(double) * width)) == NULL)
    {exit(0);}
    for(int j = 0; j < width;j++)
    {
      w[i][j]=((double)rand() /(double)RAND_MAX)*20 -10;
    }
  }

  return w;
}

matrix* makeLayer(int L[], int size, int nb)
{
  matrix* layer = NULL;
  layer = malloc((size) * sizeof(matrix));
  if(layer == NULL){
      exit(0);
  }


  for( int i= 0 ; i < size; i++)
    {
      double** list = NULL;
      list = malloc((nb) * sizeof(double*));
      if(list == NULL){
          exit(0);
      }
      for(int j = 0; j < nb;j++)
      {
        if((list[j] = malloc(sizeof(double) * L[i])) == NULL)
        {exit(0);}
      }
      
      layer[i].width = L[i];
      layer[i].height = nb ;
      layer[i].List = list ;
    }
    return layer;
}

void forward( int sizeL, matrix* lw, matrix* layer, matrix* biais, matrix* lz)
{
  double** l;
  double** l1;
  for(int i = 0; i < sizeL-1; i++)
  {
    l = layer[i].List;
    l1 = layer[i+1].List;
    mul(l, lw[i].List, layer[i].height, lw[i].height, lw[i].width, l1);
    add(l, biais[i].List, layer[i].height, layer[i].width ); // a revoir
    copy(l1, lz[i+1].List ,layer[i+1].height, layer[i+1].width);
    vector_apply(sigmoid, l1, layer[i+1].height, layer[i+1].width,l1);
    
  }
}

void copy(double** layer , double** lz , int height , int width)
{
  for(int i = 0; i < height;i++)
  {
    for(int j = 0; j < width;j++)
    {
      lz[i][j] = layer[i][j] ;
    }
  }
}

void putEnter(matrix* layer, double* enter)
{
    for(int j = 0; j < layer[0].width;j++)
    {
      layer[0].List[0][j] = enter[j];
    }
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
  recup[0].List = filetomatrice(750,200,0);
  recup[0].height = 750;
  recup[0].width = 200;
  for(int i =1; i < nbelement ; i++)
  {
    recup[i].List = filetomatrice(200,52
    ,200*52);
    recup[i].height = 200;
    recup[i].width = 52;
    
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
	if (j == width)
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


int findindex (network* net,int L[])
{
  matrix mat = net->layer[net->size-1];
  int index = 0;
  for(int i = 0; i<L[(net->size)-1];i++)
   {
      if (mat.List[0][index] < mat.List[0][i])
	{
 	   index = i;
	}
   }
  return index;
}

int verifline(matrix letter)
{
   for(int i = 0; i < (letter.height) ; i++)
    {
    for(int j = 0; j < (letter.width); j++)
	{
	   if (letter.List[i][j] ==1)
		return 0;
	}
    }
    return 1;
}
