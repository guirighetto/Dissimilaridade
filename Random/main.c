#include "DissTrain.h"
#include "DissTest.h"
#include <time.h>
#define bool int

int main(int argc, char const *argv[])
{
	/*Flag para executar separado, esta com algum problema de memoria que nao consegue executar em sequencia*/
	bool isTrain = atoi(argv[1]);
	
	time_t begin,end;
	begin= time(NULL);

	/*Param: File, nbAuthor, nbRef, nbSamplesAuthor, nbFeatures+1
	Ex: /../File.train, 50, 9, 9, 255+1*/

	if(isTrain)
		execDissTrain("/home/guilherme/Documentos/Projeto_Diego/Scripts/BFL_115_128_2048_Diss.Train",50,9,18,2049);
	else
		execDissTest("/home/guilherme/Documentos/Projeto_Diego/Scripts/BFL_115_128_2048_Diss.Test",50,9,9,2049);
	
	end= time(NULL);
	printf("Done. Time: %f\n",difftime(end, begin));

	return 0;
}