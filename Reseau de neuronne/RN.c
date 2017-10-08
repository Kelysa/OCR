# include <assert.h>
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct str_neurone
{
	unsigned int *val;
	char *child[];
	unsigned int *poid;
}neurone;
typedef struct  str_reseau
{
	char *nEnter[];
	char *nSortie[];
}reseau;

neurone __init__(int *val,char *child[],unsigned int *poid)
{
	
	neurone n;
	n.val = val;
	if(child == NULL)
	{
		n.child=[];
	}
	else
	{
		n.child=child;
	}
	n.poid=poid;
	return n;
	
}

reseau __init__(char *nEnter[],char *nSortie[])
{
	reseau r;
	if(r.nEnter==NULL)
	{
		r.nEnter=[];
	}
	else
	{
		r.nEnter=nEnter;
	}
	if(r.nSortie==NULL)
	{
		r.nSortie=[];
	}
	else
	{
		r.nSortie=nSortie;
	}
	return r;
}

unsigned int value(neurone n)
{
	return n.poid *n.val;
}
unsigned int sum(neurone n)
{
	unsigned int s =0;
	for (int i = 0; i < sizeof(n.child)/sizeof(char *); ++i)
	{
		s=s+value(n.child[i]);
	}
	return s;
}
unsigned int func(neurone n)
{
	if (sum(n)>=1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



int Main()
{
	return 0;
}