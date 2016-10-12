#include "DissTrain.h"

int execDissTrain(char* nameFileTrain, int nbAutoresTest, int nbRef, int nbAmostrasAutor, int nbFeat)
{
	int nbAmNeg;
	float** M = loadMatriz(nameFileTrain,nbAutoresTest,nbAmostrasAutor,nbFeat);
	int nbAutores = nbAutoresTest;
	int contLin=0;

	int contVN = 0;
	int contVP = 0;

	int nbCombPos = choose(nbRef,2);

    int t;
    int* vectorNbAmos = (int*)malloc(nbAmostrasAutor+1*sizeof(int));  
    for(t=0;t<nbAmostrasAutor;t++)
        vectorNbAmos[t] = t;

    int nbCombPosAlea = choose(nbAmostrasAutor,2);

    int** comb = nchoosek(vectorNbAmos,nbAmostrasAutor,nbCombPosAlea); 

    srand (time(NULL));

    int* fragAleatP2 = (int*)calloc(nbCombPosAlea+1,sizeof(int));
    int* AutorAleat = (int*)calloc((nbAutores*2)+1,sizeof(int));

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
    int* fragAleatP = (int*)calloc(nbCombPosAlea+1,sizeof(int));

    int i;
    for(i=1;i<nbAutores+1;i++)
    {
        for(t=0;t<nbCombPosAlea+1;t++)
            fragAleatP[t] = 0;
        
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
                fprintf(f1," %d:%f", b, Abs(M[frag1+(nbAmostrasAutor*(i-1))][b] - M[frag2+(nbAmostrasAutor*(i-1))][b]));  
            fprintf(f1,"\n");       
        }
        
        int y=0;
        for(y=0;y<nbCombPosAlea+1;y++)
            fragAleatP2[y] = 0;
        for(y=0;y<(nbAutores*2)+1;y++)
            AutorAleat[y] = 0;
        
        int nextAutor = i;

        int k;
        for(k=1;k<nbCombPos+1;k++)
        {
            int nbAleaAutor;
            while(1)
            {
                nbAleaAutor = rand() % (nbAutores*2) + 1;
                if(AutorAleat[nbAleaAutor] == 0 && AutorAleat[nbAleaAutor] != i)
                {
                    AutorAleat[nbAleaAutor] = 1;
                    break;
                }
            }

            int nbAleaPosNeg;
            while(1)
            {
                nbAleaPosNeg = rand() % nbCombPosAlea + 1;
                if(fragAleatP2[nbAleaPosNeg] == 0)
                {
                    fragAleatP2[nbAleaPosNeg] = 1;
                    break;
                }
            }

            int fragPos = comb[nbAleaPosNeg][1];
            int fragNeg = comb[nbAleaPosNeg][2];

            fprintf(f1,"%s ","-1");

            int m;
            for(m=1;m<nbFeat;m++)
                fprintf(f1," %d:%f",m, Abs(M[fragPos+(nbAmostrasAutor*(i-1))][m] - M[fragNeg+(nbAmostrasAutor*(negativeAuthors[nbAleaAutor]-1))][m]));
            fprintf(f1,"\n");

        }
            
    }
    fclose(f1);
    free(M);
    M = NULL;
    return 0;
	
}

