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
  int r;
  for(int i = 0; i < nbexemple; i++)
  {
    r = random_index(nbexemple-1);
    val_abs = neural_network_training(net, enter[r] ,L);
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
      int size = 3;
      int L[] = {750 ,200 , 52};
      network* net = make_network(size, L);
      net-> lw = alltomatrice(2);
      print_matrix(net->lw[0].List,net->lw[0].height,net->lw[0].width);
      int nbimage = 0;
      matrix * texte = give_matrix(path[1],&nbimage);
      for(int i =0; i<nbimage;i++)
	{  
  	   if (verifline(texte[i]))
		{
	           printf("\n");
		   continue;
		}
           double* a = matToList(texte[i]);
           putEnter(net->layer, a);
           forward(net->size,net->lw, net->layer, net->biais, net->lz);
	   int index = findindex (net,L);
	   char lettre = inttochar(index);
	   printf("%c",lettre);
	}
      printf("\n");
      return 1;
    }
  else
  {
    int taille;
    char** listchar = listOfLearning("newlearn/",&taille);

    tuple* list_tuple =  make_list_tuple(listchar,taille);
    for(int i = 0; i < taille; i++)
    {
      printf("%c\n",list_tuple[i].inputsChar);
      matrix l = resize_matrix(list_tuple[i].mat, 30 ,25);
      print_matrixx(l.List, l.height, l.width);
      printf("\n");
    }
    /*printf("%c\n",list_tuple[12].inputsChar);  // cahnge le numero pour essayer avec des lettre differente
    matrix mm = list_tuple[12].mat;                  // ici aussi
    print_matrixx(mm.List, mm.height, mm.width);
    mm = resize_matrix(mm, 30, 25);
    printf("\n");
    print_matrixx(mm.List, mm.height, mm.width);*/
    
  
    srand(time(NULL));
    int size = 3;

    int L[] = {750 ,200 , 52};
    network* net = make_network(size, L);

  
  //############################################### 
    int s= 0;
    //int nb = 1;
    while(s < 60)
    {
      s= training(net,list_tuple, L,taille);
      printf("reussite : %d \n",s);
      /*if(nb%5 == 0)
	    {
	      savealltofile(net->lw,2);
	    }
      nb++;*/
    }
    savealltofile(net->lw,2);
  }
  return 0;
}
