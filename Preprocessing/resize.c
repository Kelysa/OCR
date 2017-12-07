#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct matrix {
  size_t h, w;
  double *tab;
};

void print_matrix(double mat[], size_t lines, size_t cols)
{  
  for(size_t i = 0; i < lines; i++)
    {
    printf("\n");
    for(size_t j = 0; j < cols; j++)
      printf("%4f   ", mat[j + i * cols]);
    }
  printf("\n");
}

void resize_matrix(struct matrix *src, struct matrix *dst)
{
  size_t coefH = floor((double)src->h/(double)dst->h);
  size_t coefW = floor((double)src->w/(double)dst->w);
  
  double *temp = malloc(sizeof(double)*src->h*dst->w);
  
  for(size_t i = 0; i < src->h; i++) {
    double buff = 0;
    for(size_t j = 0; j < dst->w; j++) {
      buff += src->tab[i*dst->w+j];
      if((j+1)%coefW == 0) {
	temp[i*dst->w+j/coefW] = /*(double)floor*/(buff/(double)coefW);
	buff = 0;
      }
    }
  }

  for(size_t i = 0; i < dst->w; i++) {
    double buff = 0;
    for(size_t j = 0; j < src->h; j++) {
      buff += temp[j*dst->w+i];
      if((j+1)%coefH == 0) {
	dst->tab[j/coefH*dst->w+i] = buff/(double)coefH;
	buff = 0;
      }
    }
  }
  free(temp); 
}

int main()
{  
  struct matrix *m = malloc(sizeof(struct matrix));
  m->h = 10;
  m->w = 10;
  m->tab = malloc(sizeof(double)*m->h*m->w);
  m->tab[0] = 1;
  m->tab[1] = 1;
  m->tab[2] = 1;
  m->tab[10] = 1;
  
  struct matrix *m_resize = malloc(sizeof(struct matrix));
  m_resize->h = 5;
  m_resize->w = 5;
  m_resize->tab = malloc(sizeof(double)*m_resize->h*m_resize->w);

  resize_matrix(m, m_resize);
  
  print_matrix(m->tab, m->h, m->w);
  print_matrix(m_resize->tab, m_resize->h, m_resize->w);
  
  free(m->tab);
  free(m);
  free(m_resize->tab);
  free(m_resize);
}
