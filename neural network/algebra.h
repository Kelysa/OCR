/*
 * algebra.h: some useful linear algebra operations
 *
 * 2017 Marwan Burelle / EPITA
 */
 
#ifndef _SOMEALGEBRA_ALGEBRA_H_
#define _SOMEALGEBRA_ALGEBRA_H_
 
/*
 * func_t: function pointer type
 */
typedef double (*func_t)(double);

typedef struct matrix matrix;
struct matrix
{
  int largeur;
  int hauteur;
  double** List;
};



 
/*
 * vector_apply(f, vect, size, res)
 * applies a function to all element on a vector of size n
 * for i in 0..size, res[i] = f[vect[i]]
 */
void vector_apply(func_t f, double** vect, int hauteur, int largeur, double** res);


double sigmoid(double x);

void mul(double** m1, double** m2, int n, int m, int p, double** res);

void print_matrix(double** mat, size_t cols, size_t lines);
 
#endif /* _SOMEALGEBRA_ALGEBRA_H_ */
 
