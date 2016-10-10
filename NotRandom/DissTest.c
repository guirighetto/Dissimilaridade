#include "DissTest.h"

int execDissTest(char* nameFileTest, int nbAutoresTest, int nbRef, int nbAmostrasAutor, int nbFeat)
{
	int nbAmNeg;
	float** M2 = loadMatriz(nameFileTest,nbAutoresTest,nbAmostrasAutor,nbFeat);
	int nbAutores = nbAutoresTest;
	int contLin=0;

	int lin = 0;
	int contVN = 0;
	int contVP = 0;

	int* vectorNbRef = (int*)calloc(nbRef+1,sizeof(int));
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
    strcpy(name,nameFileTest);
    strcat(name,"_Diss_");
    char* s = itoa(nbRef,10);
    strcat(name,s);
    strcat(name,"Ref_Test.svm");

    FILE* f1 = fopen(name,"w");

    int i,l,c,a,b;
    for(i=1;i<nbAutores+1;i++)
    {
        int* fragAleatP = createArray(nbRef+1);

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
    			fprintf(f1," %d:%f", b, Abs(M2[frag1+(nbAmostrasAutor*(i-1))][b] - M2[frag2+(nbAmostrasAutor*(i-1))][b]));  
    		fprintf(f1,"\n"); 		
    	}

    	int k;
    	for(k=1;k<nbAutores+1;k++)
    	{
    		if(k != i)
    		{
	    		int ri;
	    		for(ri=1;ri<nbRef+1;ri++)
	    		{
	    			int* negFrag = createArray(nbRef+1);
	    			int* posFragN = createArray(nbRef+1);

	    			int tb;
	    			for(tb=1;tb<nbAmNeg+1;tb++)
	    			{
	    				int pFragPos = posFragN[tb];
                        int pFragNeg = negFrag[ri];

                        contLin++;

                        fprintf(f1,"%s","-1");

                        int m;
                        for (m=1;m<nbFeat;m++)
                        	fprintf(f1," %d:%f", m, Abs(M2[pFragPos+(nbAmostrasAutor*(i-1))][m] - M2[pFragNeg+(nbAmostrasAutor*(k-1))][m])); 
                        fprintf(f1,"\n");

	    			}
	    		}
    		}
    	}
    }
    fclose(f1);
    free(M2);
    free(vectorNbRef);

    return 0;

}