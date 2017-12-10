#ifndef _TOOLSNET_H_
#define _TOOLSNET_H_

#include "function.h"
#include "correction.h"

typedef struct matrix matrix;
struct matrix
{
  int width;
  int height;
  double** List;
};

typedef struct tuple tuple;
struct tuple
{
  matrix mat;
  double* list;
  char inputsChar;
};

typedef struct network network;
struct network
{
    int size;
    matrix* lw;
    matrix* layer;
    matrix* lz;
    matrix* biais;
    matrix* error;
  
};

matrix* makeLW(int L[], int size);
double** matw(int height, int width);
matrix* makeLayer(int L[], int size, int nb);
void forward(int sizeL, matrix* lw, matrix* layer, matrix* biais, matrix* lz);
void putEnter(matrix* layer, double* enter);
void copy(double** layer , double** lz , int height , int width);
void serialisation ( char *file, int L[], matrix* lw, int size);

#endif /* _TOOLSNET_H_ */
