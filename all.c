#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
//#include"all.h"


void segmentation(char *path[])
{
    char path_fi[] = "Segmentation/main ";
    strcat(path_fi,path[1]);
    system(path_fi);
}
void preprocessing(char *path[])
{
    char path_fi[] = "Preprocessing/main ";
    strcat(path_fi,path[1]);
    system(path_fi);
}

void neural_network(char *path[])
{
    char path_fi[] = "neural?network/main ";
    strcat(path_fi,path[1]);
    system(path_fi);
}


int main(int argc, char *path[])
{
   
    if(argc == 3)
    {
        preprocessing(path);
    }
    if(argc == 4)
    {
        segmentation(path);
    }
    if(argc == 5)
    {
        neural_network(path);
    }
    
   // 
    
}

