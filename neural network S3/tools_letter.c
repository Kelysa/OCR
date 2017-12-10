#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <sys/types.h>
#include <dirent.h>

#include <gtk/gtk.h>

#include <SDL.h>
#include <SDL/SDL_image.h>

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"
#include "segmentation.h"
#include "resize.h"

int* charTobin(char letter)
{
    int* L = NULL;
    L = malloc(8 * sizeof(int));
    if(L == NULL){
        exit(0);
    }  
    int n;
    int intletter = (int)letter;
    for(int i = 7; i >= 0; i--)
    {
        n = pow(2,i);
        if(intletter-n >= 0)
        {
            L[i] = 1;
            intletter-=n;
        }
        else{
            L[i] = 0;
        }
    }
    return L;
}

char binTochar(int* L)
{
    int n=0;
    for(int i = 0; i< 8; i++)
    {
        n+= L[i] * pow(2,i);
    }
    return (char)n;
}

char** listOfLearning(char* dirName, int *sizeOfList){
        DIR *dp;
    struct dirent *ep;
    int mySize = 0;
    dp = opendir(dirName);
    if (dp != NULL)
      {
        while(readdir (dp)){
            mySize++;
        }
        (void) closedir (dp);
      }
    else{
        perror ("Couldn't open the directory");
        exit(0);
    }
    dp = opendir(dirName);

    //mySize = 100;
    int testSize = mySize;

    char** listOfName = NULL;
    if((listOfName = malloc(sizeof(char*) * mySize)) == NULL){
        exit(0);
    }
    *sizeOfList = mySize;
    mySize = 0;
    while((ep = readdir (dp)) !=  NULL && mySize != testSize){
        if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..")){
            listOfName[mySize] = NULL;
            if((listOfName[mySize] = malloc(sizeof(ep->d_name))) == NULL){
                exit(0);
            }
            for(unsigned int j = 0; j < sizeof(ep->d_name) / sizeof(char); j++){
                listOfName[mySize][j] = (ep->d_name)[j];
            }
            mySize++;
        }
        else{
            *sizeOfList = *sizeOfList - 1;
        }
    }
    (void) closedir (dp);
    return listOfName;
}

char* concatenateString(char* string1, char* string2){
    char* myNewString;
    size_t size1 = strlen(string1);
    size_t size2 = strlen(string2);
    if((myNewString = malloc(sizeof(char) * (size1 + size2 + 1))) == NULL){
        exit(0);
    }
    for(unsigned int i = 0; i < size1; i++){
        *(myNewString + i) = *(string1 + i);
    }
    for(unsigned int i = 0; i < size2; i++){
        *(myNewString + size1 + i) = *(string2 + i);
    }
    *(myNewString + size1 + size2) = 0;
    return myNewString;

}

tuple initLearningByPath(char* myPath, char* dir){
    tuple learning;
    learning.inputsChar = myPath[0];
    learning.mat =  give_matrix_im(concatenateString(dir, myPath));
    learning.list = matToList(learning.mat);
    return learning;
}

tuple* make_list_tuple(char** listChar, int size)
{
    tuple* res = NULL;
    res = malloc(sizeof(tuple)* size);
    if(res == NULL){
        exit(0);
    }
    for(int i =0; i<size; i++)
    {
        res[i] = initLearningByPath(listChar[i],"learning/");
    }
    return res;
}

double* matToList(matrix mat)
{
    double* res = NULL;
    res = malloc(sizeof(double)* (mat.height)*(mat.width));
    if(res == NULL){
        exit(0);
    }
    int v = 0;
    for(int i = 0; i< mat.height; i++)
    {
        for(int j = 0; j< mat.width; j++)
        {
            res[v] = mat.List[i][j];
            v++;
        }
    }
    return res;
}

double* reductMatrix(double* myMatrix){
    int xmin = 0;
    int xmax = 25;
    int ymin = 0;
    int ymax = 35;
    int found = 0;
    while(xmin < xmax && !found){
        for(int i = ymin; i <= ymax && !found; i++){
            if(myMatrix[i * 25 + xmin] == 1){
                found = 1;
            }
        }
        xmin++;
    }
    found = 0;
    while(xmin < xmax && !found){
        xmax--;
        for(int i = ymin; i <= ymax && !found; i++){
            if(myMatrix[i * 25 + xmax] == 1){
                found = 1;
            }
        }
    }
    found = 0;
    while(ymin < ymax && !found){
        for(int i = xmin; i <= xmax && !found; i++){
            if(myMatrix[25 * ymin + i] == 1){
                found = 1;
            }
        }
        ymin++;
    }
    found = 0;
    while(ymin < ymax && !found){
        ymax--;
        for(int i = xmin; i <= xmax && !found; i++){
            if(myMatrix[25 * ymax + i] == 1){
                found = 1;
            }
        }
    }
    
    double coefx = ((double)xmax - (double)xmin + 2) / 25;
    double coefy = ((double)ymax - (double)ymin + 2) / 35;
    double* newMatrix = calloc(25 * 35, sizeof(double));
    if(newMatrix == NULL)
        exit(1);
    for(int i = 0; i < 35; i++){
        for(int j = 0; j < 25; j++){
            newMatrix[25 * i + j] = myMatrix[(int)((double)i * coefy + (double)ymin - 1) * 25 + (int)((double)j * coefx + (double)xmin - 1)];
        }
    }
    free(myMatrix);
    return newMatrix;
}
