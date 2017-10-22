#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "algebra.h"
#include "tools_network.h"

double deriver_sigmoid(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

void corr(matrix* layer, matrix* lz, matrix* lw, matrix* error, int L[], int size)
{
    int l = lz[0].width;
    l++;
    for(int i =0; i< size-1; i++) // pour chaque couche 
    {
        for(int x =0; x< L[size - 2 - i]; x++) // neurone x d'une couche i
            {
                double s = 0;

                for(int h =0; h < layer[size - 2 - i].width; h++)
                {
                     s += error[size - 1 - i].List[0][h] * lw[size - 2 - i].List[x][h]; 
                }

                error[size - 2 - i].List[0][x] = deriver_sigmoid(lz[size - 2 - i].List[0][x]) * s ;
                
                
            }
        for(int y =0; y< lw[size-2 - i].height; y++) // nb test
        {
            for(int x =0; x< lw[size-2 - i].width; x++) // neurone x d'une couche i
            {
                
                lw[size-2 - i].List[y][x] -= layer[size-2 - i].List[0][y] * error[size -1 -i].List[0][x];
                
            }
        }
        
    }
}

void puterror(matrix* error, matrix* layer, double val[], int size, int j)
{
    for(int i = 0; i < layer[size-1].width; i++)
    {
        error[size-1].List[0][i] =  layer[size-1].List[0][i] - val[j] ;
    }
}

/*int training (int L[], int size, matrix* layer, matrix* lw, matrix* lz, matrix* error, matrix* biais, double sortie[], double enter[])
{
    int s = 0;
    for(int i = 0; i < 4; i++)
    {
        putEnter(layer, enter, i);
        forward(size, lw, layer, biais, lz);
        puterror(error,layer,sortie,size, i);
        if(abs(error[size-1].List[error[size-1].height][error[size-1].width]) < 0.05)
        {
            s+=1;
        }
        corr(layer, lz, lw, error, L, size);
    }
    if(s == 4)
    {
        return 0;
    }
    return 1;
}*/