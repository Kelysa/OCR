#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
#include "algebra.h"
#include "tools_network.h"
#include "correction.h"

double abso(double i)
{
  if(i < 0)
  {
    return -1 * i;
  }
  return i;
}

int main()
{
  srand(time(NULL));
  int size = 3;
  int nb = 1;

  int L[] = {2 ,15 , 1};
  matrix* lw  = makeLW(L, size);
  matrix* layer = makeLayer(L, size , nb);
  matrix* lz = makeLayer(L, size , nb);
  matrix* biais = makeLayer(L, size , nb);
  matrix* error = makeLayer(L, size , nb);
  
  double sortie[] = {0 , 1 , 1 , 0};
  double enter []  = {0,0,0,1,1,0,1,1};


  
  int j = 0;
  int s= 0;
  double val_abs;
  int la;
  int ha;
  while(s != 4)
  {
    s = 0;
    for(int i = 0; i < 4; i++)
    {
        putEnter(layer, enter, i);
        forward(size, lw, layer, biais, lz);
        puterror(error,layer,sortie,size, i);
        la = error[size-1].width -1;
        ha = error[size-1].height -1;
        val_abs = abso(error[size-1].List[ha][la]);
        if(val_abs< 0.05 )
        {
            s+=1;
        } 
        corr(layer, lz, lw, error, L, size);
      }
    j++;
  }
  printf("===================Neural Network======================\n");

  printf("nombre d'iteration : %d \n", j);
  double lay;
  for(int i = 0; i< 4; i++)
  {
    putEnter(layer, enter, i);
    forward(size, lw, layer, biais, lz);
    printf("  entrer           sortie\n");
    lay =  layer[size-1].List[layer[size-1].height-1][layer[size-1].width-1];
    printf("%4g    %4g       ", enter[(i*2)],enter[(i*2)+1]);
    printf("valeur:%4g  voulu:%4g \n",lay, sortie[i]);
  }

  printf("==========================================================\n");
  return 0; 
}