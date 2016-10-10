#include "DissTrain.h"

int execDissTrain(char* nameFileTrain, int nbAutoresTest, int nbRef, int nbAmostrasAutor, int nbFeat)
{
	int nbAmNeg;
	float** M = loadMatriz(nameFileTrain,nbAutoresTest,nbAmostrasAutor,nbFeat);
	int nbAutores = nbAutoresTest;
	int contLin=0;

	int contVN = 0;
	int contVP = 0;

	int* vectorNbRef = (int*)malloc(nbRef+1*sizeof(int));
	int t;
	for(t=0;t<nbRef;t++)
	    vectorNbRef[t] = t;

	int nbCombPos = fatorial(nbRef) / (fatorial(2) * fatorial(nbRef - 2));

	int** comb = nchoosek(vectorNbRef,nbRef,nbCombPos); 

	if(nbAutores == 1)
    	nbAmNeg = 1;
	else
    	nbAmNeg = nbCombPos / nbRef;

    char name[1000];
    strcpy(name,nameFileTrain);
    strcat(name,"_Diss_");
    char* s = itoa(nbRef,10);
    strcat(name,s);
    strcat(name,"Ref_Train.svm");

    FILE* f1 = fopen(name,"w");

    int* negativeAuthors = (int*)calloc((nbAutores*2)+1,sizeof(int));
    int flagRealloc = 0;

    for (t = 1; t < (nbAutores*2)+1;t++)
    {
        if(t < nbAutores+1)
            negativeAuthors[t] = t;
        else
            negativeAuthors[t] = t-nbAutores;
    }    

    int* negFrag = createArray(nbAmNeg+1);
    int* posFragN = createArray(nbAmNeg+1);

    int i;
    for(i=1;i<nbAutores+1;i++)
    {
	    int* fragAleatP = (int*)malloc(nbRef+1*sizeof(int));
	    for(t=1;t<nbRef+1;t++)
	    	fragAleatP[t] = t;
        
	    int n;
    	for(n=1;n<nbCombPos+1;n++)
    	{
    		contVP++;
    		contLin++;
                                        
            int posFrag1 = comb[n][1];
            int posFrag2 = comb[n][2];

            int frag1 = fragAleatP[posFrag1];
            int frag2 = fragAleatP[posFrag2];

            fprintf(f1,"%s ","+1");

            int b;
            for(b=1;b<nbFeat;b++)
    			fprintf(f1," %d:%f", b, Abs(M[frag1+(nbAmostrasAutor*(i-1))][b] - M[frag2+(nbAmostrasAutor*(i-1))][b]));  
    		fprintf(f1,"\n"); 		
    	}
        
    	int nextAutor = i;

	    int k;
	    for(k=1;k<nbRef+1;k++)
	    {
	    	nextAutor++;

	    	int tb;
	    	for(tb=1;tb<nbAmNeg+1;tb++)
	    	{
	    		contVN++;
                contLin++;

                int pFragPos = posFragN[tb];
                int pFragNeg = negFrag[tb];

                fprintf(f1,"%s ","-1");

                int m;
                for(m=1;m<nbFeat;m++)
                    fprintf(f1," %d:%f",m, Abs(M[pFragPos+(nbAmostrasAutor*(i-1))][m] - M[pFragNeg+(nbAmostrasAutor*(negativeAuthors[nextAutor]-1))][m]));
                fprintf(f1,"\n");

            }
             
	    }
            
    }
    fclose(f1);
    free(M);
    M = NULL;
	return 0;
}

