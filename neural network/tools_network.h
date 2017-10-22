#ifndef _TOOLSNET_H_
#define _TOOLSNET_H_

#include "algebra.h"

matrix* makeLW(int L[], int size);
double** matw(int height, int width);
matrix* makeLayer(int L[], int size, int nb);
void forward(int sizeL, matrix* lw, matrix* layer, matrix* biais, matrix* lz );
void putEnter(matrix* layer, double enter[], int i);
void copy(double** layer , double** lz , int height , int width);
#endif /* _TOOLSNET_H_ */
