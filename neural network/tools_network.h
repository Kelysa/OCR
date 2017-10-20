#ifndef _TOOLSNET_H_
#define _TOOLSNET_H_

#include "algebra.h"

matrix* makeLW(int L[], int size);
double** matw(int hauteur, int largeur);
matrix* makeLayer(int L[], int size, int nb);
void forward(int sizeL, matrix* lw, matrix* layer );
void replace(matrix* layer);
#endif /* _TOOLSNET_H_ */
