#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
#include "segmentation.h"
#include <gtk/gtk.h>
 
#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"

#include "resize.h"



int training(network* net,tuple* enter,int L[], int nbexemple)
{
  double s= 0;
  double val_abs;
  for(int i = 0; i < nbexemple; i++)
  {
    val_abs = neural_network_training(net, enter[i] ,L);
    if(val_abs< 0.005 )
    {
        s+=1;
    } 
  }
  return s/((double)(nbexemple))*100 ;
}


int main(int argc, char *path[])
{
  if (argc==2)
    {
      give_matrix(path[1]);
      return 1;
    }
  else
  {
    int taille;
    char** listchar = listOfLearning("learning/",&taille);

    tuple* list_tuple =  make_list_tuple(listchar,taille);
    /*for(int i = 0; i < taille; i++)
    {
      int* b = charTobin(list_tuple[i].inputsChar);
      for(int j = 0; j< 8; j++)
        printf("%d",b[j]);
      printf("%c\n",list_tuple[i].inputsChar);
      matrix l = list_tuple[i].mat;
      print_matrix(l.List, l.height, l.width);
      printf("\n");
    }*/
    printf("%c\n",list_tuple[2].inputsChar);
    matrix mm = list_tuple[2].mat;
    print_matrix(mm.List, mm.height, mm.width);
    mm = resize_matrix(mm, 30, 25);
    printf("\n");
    print_matrix(mm.List, mm.height, mm.width);
    
  
    srand(time(NULL));
  /*int size = 3;

  int L[] = {600 ,200 , 8};
  network* net = make_network(size, L);

  
  //############################################### 
  int s= 0;
  while(s < 70)
  {
    s= training(net,list_tuple, L,taille);
    //printf("reussite : %d \n",s);
  }*/
  }
  return 0;
}
