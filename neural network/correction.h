#ifndef _CORRECTION_H_
#define _CORRECTION_H_

#include "algebra.h"
double deriver_sigmoid(double x);
void corr(matrix* layer, matrix* lz, matrix* lw, matrix* error, int L[], int size);
void puterror(matrix* error, matrix* layer, double val[], int size, int j);
//int training (int L[], int size, matrix* layer, matrix* lw, matrix* lz, matrix* error, matrix* biais, double sortie[], double enter[]);

#endif /* _CORRECTION_H_ */