#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
 
#include "algebra.h"
#include "tools_network.h"

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
      w[i][j]=((double)rand() /(double)RAND_MAX)*20 -10 ; 
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

void forward( int sizeL, matrix* lw, matrix* layer, matrix* biais, matrix* lz )
{
  for(int i = 0; i < sizeL-1; i++)
  {
    mul(layer[i].List, lw[i].List, layer[i].height, lw[i].height, lw[i].width, layer[i+1].List );
    add(layer[i].List, biais[i].List, layer[i].height, layer[i].width ); // a revoir
    copy(layer[i+1].List, lz[i+1].List ,layer[i+1].height, layer[i+1].width);
    vector_apply(sigmoid, layer[i+1].List, layer[i+1].height, layer[i+1].width,layer[i+1].List);
    
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

void putEnter(matrix* layer, double enter[], int i)
{
    for(int j = 0; j < layer[0].width;j++)
    {
      layer[0].List[0][j] = enter[j+(i*layer[0].width)];
    }
}