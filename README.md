# Dissimilaridade
Hanusiak et al. (2011) - Writer verification using texture-based features
#Param 
Need change main.c

execDissTrain or execDissTest: File, nbAuthor, nbRef, nbSamplesAuthor, nbFeatures+1
Ex: "/../File.train", 50, 9, 9, 255+1

#Compile
make or gcc *.c -o nameProg

#Execute
Args: 1 = TrainFile or 0 = TestFile 

./executeDiss 1 or ./executeDiss 0

