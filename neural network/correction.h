#ifndef _CORRECTION_H_
#define _CORRECTION_H_

#include "algebra.h"
double deriver_sigmoid(double x);
void corr(matrix* layer,matrix* lz,matrix* lw,matrix* error,int L[],int size);
void puterror(matrix* error, matrix* layer, double val[], int size, int j);

#endif /* _CORRECTION_H_ */