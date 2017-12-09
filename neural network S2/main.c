#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
#include "segmentation.h"

 
#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"



int training(network* net,double** enter, double** sortie,int L[], int nbexemple)
{
  double s= 0;
  double val_abs;
  for(int i = 0; i < nbexemple; i++)
  {
    val_abs = neural_network_training(net, enter[i] , sortie[i] ,L);
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

  int taille;
  char** listchar = listOfLearning("learning/",&taille);
  printf("%s\n",listchar[2]);
  //matrix l =  initLearningByPath(listchar[2],"learning/").mat;
  //print_matrix(l.List, l.height, l.width);

  tuple* list_tuple =  make_list_tuple(listchar,taille);
  pprint(list_tuple[1].mat,1);
  
  /*srand(time(NULL));
  int size = 3;

  int L[] = {2 ,4 , 1};
  network* net = make_network(size, L);

  //creation des enter sortie###################
  
  double sorties[] = {0 , 1 , 1 , 0};

  double enters []  = {0,0,0,1,1,0,1,1};

  double** enter = malloc(sizeof(double*)*4);
  for(int i = 0; i < 4; i++)
  {
    enter[i] = malloc(sizeof(double)*2);
    enter[i][0] = enters[i*2];
    enter[i][1] = enters[(i*2)+1];
  }

  double** sortie = malloc(sizeof(double*)*4);
  for(int i = 0; i < 4; i++)
  {
    sortie[i] = malloc(sizeof(double));
    sortie[i][0] = sorties[i];
  }
  //###############################################
  
  int s= 0;
  while(s < 100)
  {
    s= training(net,enter, sortie, L,4);
    //printf("reussite : %d \n",s);
  }
  printf("\n===================Neural Network======================\n");

  double lay;
  for(int i = 0; i< 4; i++)
  {
    putEnter(net->layer, enter[i]);
    forward(net->size, net->lw, net->layer, net->biais, net->lz);
    printf("  entrer           sortie\n");
    lay =  net->layer[net->size-1].List[net->layer[net->size-1].height-1][net->layer[net->size-1].width-1];
    printf("%4g    %4g       ", enter[i][0],enter[i][1]);
    printf("valeur:%4g  voulu:%4g \n",lay, sortie[i][0]);
  }

  printf("==========================================================\n");*/
  return 0;
}