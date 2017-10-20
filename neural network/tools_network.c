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
      lw[i].largeur = L[i+1];
      lw[i].hauteur = L[i] ;
      lw[i].List = list ;
    }
    return lw;
}

double** matw(int hauteur, int largeur)
{
  double** w = NULL;
  w = malloc((hauteur) * sizeof(double*));
  if(w == NULL){
      exit(0);
  }
  for(int i = 0; i < hauteur;i++)
  {
    if((w[i] = malloc(sizeof(double) * largeur)) == NULL)
    {exit(0);}
    for(int j = 0; j < largeur;j++)
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
        if((list[j] = calloc(0, sizeof(double) * L[i])) == NULL)
        {exit(0);}
      }
      layer[i].largeur = L[i];
      layer[i].hauteur = nb ;
      layer[i].List = list ;
    }
    return layer;
}

void forward( int sizeL, matrix* lw, matrix* layer )
{
  int l = lw[0].largeur;
  l +=1;
  for(int i = 0; i < sizeL-1; i++)
  {
    mul(layer[i].List, lw[i].List, layer[i].hauteur, lw[i].hauteur, lw[i].largeur, layer[i+1].List );
    vector_apply(sigmoid, layer[i+1].List, layer[i+1].hauteur, layer[i+1].largeur,layer[i+1].List);
  }
}

/*void propagation(int L[], int size, int nb)
{
  matrix* lw  = makeLW(L, size);
  matrix* layer = makeLayer(L, size , nb);
  forward(size, lw, layer);
}*/

void replace(matrix* layer)
{
  double m2[][2] = {{0,0},{0,1},{1,0},{1,1}};
  for(int i = 0; i < layer[0].hauteur;i++)
  {
    for(int j = 0; j < layer[0].largeur;j++)
    {
      layer[0].List[i][j] = m2[i][j];
    }
  }
}