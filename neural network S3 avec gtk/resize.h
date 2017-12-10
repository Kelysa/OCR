#ifndef _RESIZE_H_
#define _RESIZE_H_

# include <stdlib.h>
# include <SDL.h>
#include <gtk/gtk.h>

typedef struct matrixsimple matrixsimple;
struct matrixsimple {
  int height, width;
  double *List;
};


typedef struct matrix matrix;

typedef struct network network;

void print_matrixsimple(matrixsimple mat);

void print_matrixx(double **mat, int lines, int cols);

matrix from_matrixsimple_to_matrix(matrixsimple mat);

matrixsimple from_matrix_to_matrixsimple(matrix mat);

matrixsimple resize_matrixsimple(matrixsimple src, int newH, int newW);

matrix resize_matrix(matrix src, int newH, int newW);


#endif /* _RESIZE_H_ */