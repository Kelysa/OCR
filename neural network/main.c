#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

 
#include "algebra.h"
#include "tools_network.h"

 

int main()
{
  srand(time(NULL));
  int size = 3;
  int nb = 4;

  int L[] = {2 ,2 , 1};
  matrix* lw  = makeLW(L, size);
  matrix* layer = makeLayer(L, size , nb);
  //print_matrix( layer[1].List,layer[1].hauteur ,layer[1].largeur);
  
  replace(layer);

  forward(size, lw, layer);
  print_matrix( layer[2].List,layer[2].hauteur ,layer[2].largeur);
  
  
  return 0; 
}


 
