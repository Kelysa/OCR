#ifndef _TOOL_LETTER_H_
#define _TOOL_LETTER_H_

#include "tools_network.h"

typedef struct network network;
typedef struct matrix matrix;


typedef struct tuple tuple;


int* charTobin(char letter);
char binTochar(int* L);


char** listOfLearning(char* dirName, int *sizeOfList);
char* concatenateString(char* string1, char* string2);
tuple initLearningByPath(char* myPath, char* dir);
tuple* make_list_tuple(char** listChar, int size);
double* reductMatrix(double* myMatrix);
double* matToList(matrix mat);

double* reductMatrix(double* myMatrix);
#endif //_TOOL_LETTER_H_