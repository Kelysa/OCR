#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

#include "resize.h"

void print_matrixsimple(matrixsimple mat)
{
  for(int i = 0; i < mat.height; i++) {
    printf("\n");
    for(int j = 0; j < mat.width; j++)
      if(mat.List[j+i*mat.width] != 0)
	printf("%s%.2f", KRED, mat.List[j + i * mat.width]);
      else
	printf("%s%.2f", KNRM, mat.List[j + i * mat.width]);
  }
  printf("\n");
}

void print_matrixx(double **mat, int lines, int cols)
{
  for(int i = 0; i < lines; i++) {
    printf("\n");
    for(int j = 0; j < cols; j++) {
      if(mat[i][j] != 0)
        printf("%s%4g",KRED, mat[i][j]);
      else
        printf("%s%4g",KNRM, mat[i][j]);
    }
  }
  printf("\n");

}

matrix from_matrixsimple_to_matrix(matrixsimple mat)
{
  matrix res;
  res.height = mat.height;
  res.width = mat.width;
  res.List = malloc(sizeof(double)*res.height);
  
  for(int i = 0; i < mat.height; i++) {
    res.List[i] = malloc(sizeof(double)*res.width);
    for(int j = 0; j < mat.width; j++) {
      //res.List[i][j] = malloc(sizeof(double));
      res.List[i][j] = mat.List[j+i*mat.width];
    }
  }

  free(mat.List);
  return res;
}

matrixsimple from_matrix_to_matrixsimple(matrix mat)
{
  matrixsimple res ;
  res.height = mat.height;
  res.width = mat.width;
  res.List = malloc(sizeof(double)*res.height*res.width);

  for(int i = 0; i < mat.height; i++) {
    for(int j = 0; j < mat.width; j++) {
      res.List[j+i*mat.width] = mat.List[i][j];
    }
    free(mat.List[i]);
  }
  
  free(mat.List);
  return res;
}

matrixsimple resize_matrixsimple(matrixsimple src, int newH, int newW)
{

  matrixsimple dst;
  dst.height = newH;
  dst.width = newW;
  dst.List = malloc(sizeof(double)*dst.height*dst.width);

  double *temp = malloc(sizeof(double)*src.height*dst.width);
  
  int coefH;
  int coefW;
  float restH;
  float restW;
  //float refH;
  //float refW;

  if(src.width > dst.width) {
 
    //coefW = src.width/dst.width;
    restW = (float)src.width/(float)dst.width; 
    if(restW != 0)
      coefW = (int)restW+1;
    else
      coefW = (int)restW;
    //restW = restW-coefW;
    //refW = restW;
    
    //printf("%f & %ld\n", refW, coefW);

    /*
    for(int i = 0; i < src.height; i++) {
      double buff = 0;
      for(int j = 0, k = 0; j < src.width; j++, k++) {
	buff += src.List[i*src.width+j];
	//printf("%5f\n", restW);
	if((k+1) == (coefW+(int)restW)) {
	  //printf("BUFF = %.f & RESTW = %.2f\n", buff, restW);
	  temp[i*dst.width+j/coefW] = (buff/((double)coefW+restW));
	  buff = 0;
	  k = 0;
	  if(restW >= 1)
	    restW -= 1;
	  restW += refW;
	}
      }
    }
    */
    for(int i = 0; i < src.height; i++) {
      double buff = 0;
      for(int j = 0; j < src.width; j++) {
	buff += src.List[i*src.width+j];
	if((j+1)%coefW == 0) {
 	  temp[i*dst.width+j/coefW] = buff/(double)coefW;
	  buff = 0;
	}
      }
    }
  }
  
  else {
    coefW = floor((double)dst.width/(double)src.width);

    for(int i = 0; i < src.height; i++) {
      for(int j = 0, k = 0; j < src.width  && k < dst.width; j++) {
	for(int l = 0; l < coefW; k++, l++) {
	  temp[i*dst.width+k] = src.List[i*src.width+j];
	}
      }
    }
  }

  if(src.height > dst.height) {
    
    restH = (float)src.height/(float)dst.height; 
    if(restH != 0)
      coefH = (int)restH+1;
    else
      coefH = (int)restH;
    //coefH = (int)/*floor*/((double)src.height/(double)dst.height);
    
    for(int i = 0; i < dst.width; i++) {
      double buff = 0;
      for(int j = 0; j < src.height; j++) {
	buff += temp[j*dst.width+i];
	
	if((j+1)%coefH == 0) {
	  dst.List[j/coefH*dst.width+i] = buff/(double)coefH;
	  buff = 0;
	}
      }
    } 
  }

  else {
    coefH = floor((double)dst.height/(double)src.height);

    for(int i = 0; i < dst.width; i++) {
      for(int j = 0, k = 0; j < src.height; j++) {
	for(int l = 0; l < coefH; k++, l++) {
	  dst.List[k*dst.width+i] = temp[j*dst.width+i];
	}
      }
    }
  }

  
  free(temp);

  return dst;
}

matrix resize_matrix(matrix src, int newH, int newW)
{
  matrixsimple temp = from_matrix_to_matrixsimple(src);
  return from_matrixsimple_to_matrix(resize_matrixsimple(temp, newH, newW));
}
