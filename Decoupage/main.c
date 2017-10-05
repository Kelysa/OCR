#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct Coords
{
    int beginposx;
    int endposx;
    int beginposy;
    int endposy;
};

typedef struct Coordonnees Coordonnees;

int main(int argc, char *argv[])
{
  //int tab[2][20] = {{0,5,0}, {0, 2},{0, 0}};
    //printf("%d\n",tab[0][1]);
    //int tab2[10] = {0,0,0,0};
    //printf("%d\n", contains(tab));
    //printf("taille de tab2 = %d\n",sizeof(tab2)/sizeof(int));
    //printf("taille de tab = %d\n",sizeof(tab[0])/sizeof(int));
    return 0;
}

//int contains(int *tableau[]);
//int contains(int *tableau[])
//{
//    int ligne = sizeof(tableau)/sizeof(int);
//    int column = sizeof(tableau[0])/ligne;
//    int i = 1;
//    if (i ==  ligne)
//    {
//        return 10;
//    }
//    if (i ==  column)
//    {
//        return 20;
//    }
//    return 0;
//}


void decoupage(int *tableau[], int x, int y)
{
    int i = 0;
    int j = 0;
    int beginposy =0;
    int endposy =0;
    int beginposx =0;
    int endposx =0;
    while (j<= y)
    {
        struct Coords coord;
        for (j; j<y; j++)
        {
            for (i; i<y; i++)
            {
                if (tableau[i][j] == 0)
                {
                    tableau[i-1][j] = 71; //point vert à gauche
		    coord.beginposy = i;
                    break;
                }
            }
	    if (tableau[i][j] == 71)
	    {
	      break;
	    }
	    
        }
	if (j == y)
	{
	  return; 
	}
	
        // findendletters demarque la fin d'une lettre en cherchant une ligne blanche
        // colonne verte pour separer la fin d'une lettre
        coord.endposy = findendletters(tableau,x,y,j);
        for (i; i<y; i++)
        {
            for (j = beginposx; j<endposy; j++)
            {
                if (tableau[i][j] == 0)
                {
                    tableau[i-1][j] = 71;//point vert en haut
                    coord.beginposx = i;
                    break;
                }
	
            }
	    if (tableau[i][j] == 71)
	    {
	      break;
	    }

        }
        for (i=x; i>0; i--)
        {
            for (j = beginposx; j<endposy; j++)
            {
                if (tableau[i][j] == 0)
                {
                    coord.endposx = i;
                    tableau[i+1][j] = 71; //point vert en bas
                    break;
                }

            }
	    if (tableau[i][j] == 71)
	    {
	      break;
	    }
         }
	// la il faut creer une tableau [][] aloue et mettre la struc coord dedant
    }


}

int findendletters(int *tableau[],int x ,int y, int posy)
{
    int n = 0;
    int posx =0;
    while (n != y || posy<= y)
    {
        if (tableau[posx][posy] == 255)
            n+=1;
        if (posx >= x)
        {
            posx=0;
            posy+=1;

        }
        else
            posx+=1;
    }
    //while (posx>0)
    //{
    //   tableau[posx][posy] == 71;
    //   posx -=1 ;
    //}
    return posy;
}
