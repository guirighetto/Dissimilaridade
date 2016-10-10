#include "libDiss.h"

int* createArray(int size)
{
	int* array = (int*)calloc(size+1,sizeof(int));

	int i;
	for(i=1;i<size;i++)
		array[i] = i;

	return array;

}

float Abs(float x)
{
	if(x < 0)
		x = x * -1;
	return x;
}


int next_comb(int comb[], int k, int n) 
{
	int i = k - 1;
	++comb[i];

	while ((i >= 0) && (comb[i] >= n - k + 1 + i)) 
	{
		--i;
		++comb[i];
	}

	if (comb[0] > n - k)
		return 0; 

	for (i = i + 1; i < k; ++i)
		comb[i] = comb[i - 1] + 1;

	return 1;
}

int** nchoosek(int* array, int nbRef, int nbComb)
{
	int** M = (int**)malloc(100*sizeof(int*));
	int i=0;
	for(i=1;i<100;i++)
		M[i] = (int*)malloc(3*sizeof(int));

	M[1][1] = array[0]+1;
	M[1][2] = array[1]+1;

	int l=2;
	while (next_comb(array, 2, nbRef))
	{
		M[l][1] = array[0]+1;
		M[l][2] = array[1]+1;
		l++;
	}

	return M;
}


int fatorial(int N)
{ 
    if(N <= 1)
         return 1;
    return N * fatorial(N - 1);
}

float** loadMatriz(char* nameFile, int nbAutoresTest, int nbAmotrasAutor, int nbFeat)
{

	float** matriz = (float**)malloc(((nbAutoresTest*nbAmotrasAutor)+1)*sizeof(float*));

	int i=1;
	for(i=1;i<(nbAutoresTest*nbAmotrasAutor)+1;i++)
		matriz[i] = (float*)calloc(nbFeat+1,sizeof(float));

	FILE *f;

	f = fopen(nameFile,"r");

	int j;
	for(i=1;i<(nbAutoresTest*nbAmotrasAutor)+1;i++)
		for(j=1;j<nbFeat+1;j++)
			fscanf(f,"%f",&matriz[i][j]);

	fclose(f);

	return matriz;

}

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

