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

    int nbCombPos = fatorial(nbRef) / (fatorial(2) * fatorial(nbRef - 2));

    int t;
    int* vectorNbAmos = (int*)malloc(nbAmostrasAutor+1*sizeof(int));  
    for(t=0;t<nbAmostrasAutor;t++)
        vectorNbAmos[t] = t;

    int nbCombPosAlea = fatorial(nbAmostrasAutor) / (fatorial(2) * fatorial(nbAmostrasAutor - 2));

    int** comb = nchoosek(vectorNbAmos,nbAmostrasAutor,nbCombPosAlea); 

    srand (time(NULL));
	
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
        int* fragAleatP = (int*)calloc(nbCombPosAlea+1,sizeof(int));

        int n;
        for(n=1;n<nbCombPos+1;n++)
        {                                        
            int nbAlea;
            while(1)
            {
                nbAlea = rand() % nbCombPosAlea + 1;
                if(fragAleatP[nbAlea] == 0)
                {
                    fragAleatP[nbAlea] = 1;
                    break;
                }
            }

            int frag1 = comb[nbAlea][1];
            int frag2 = comb[nbAlea][2];

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
                int y;
                for(y=0;y<nbCombPosAlea+1;y++)
                    fragAleatP[y] = 0;

                int ri;
                for(ri=1;ri<nbCombPos+1;ri++)
                {
                    int nbAlea;
                    while(1)
                    {
                        nbAlea = rand() % nbCombPosAlea + 1;
                        if(fragAleatP[nbAlea] == 0)
                        {
                            fragAleatP[nbAlea] = 1;
                            break;
                        }
                    }

                    int pFragPos = comb[nbAlea][1];
                    int pFragNeg = comb[nbAlea][2];

                    fprintf(f1,"%s","-1");

                    int m;
                    for (m=1;m<nbFeat;m++)
                        fprintf(f1," %d:%f", m, Abs(M2[pFragPos+(nbAmostrasAutor*(i-1))][m] - M2[pFragNeg+(nbAmostrasAutor*(k-1))][m])); 
                    fprintf(f1,"\n");
                }
            }
        }
    }
    fclose(f1);
    free(M2);

    return 0;

}