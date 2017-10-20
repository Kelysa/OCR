#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
 
#include "algebra.h"
#include "tools_network.h"



/*
 * vector_apply(f, vect, size, res)
 * applies a function to all element on a vector of size n
 * for i in 0..size, res[i] = f[vect[i]]
 */
void vector_apply(func_t f, double** vect, int hauteur, int largeur, double** res)
{
  for(int i = 0; i < hauteur;i++)
    {
      for(int j = 0; j < largeur;j++)
      {
      res[i][j] = f(vect[i][j]);
      }
    }
}


double sigmoid(double x)
{
  return 1 / (1 + exp(-x));
}
//
void mul(double** m1, double** m2, int n, int m, int p, double** res)
{
  for(int i =0; i < n ;i++)//lines
    {
      for(int j =0; j < p ;j++) // cols
	      {
	        for(int h =0; h < m ;h++)
	         {
	          res[i][j]+= m1[i][h]*m2[h][j];
	         }
        }       
    }
}
void print_matrix(double** mat, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {
          printf("%4g ",mat[i][j]);
        }
      
      printf("\n");
    }
}
