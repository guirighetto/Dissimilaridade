#pragma once
#include <stdio.h>
#include <stdlib.h>

int** nchoosek(int* array, int nbRef, int nbComb);
int next_comb(int comb[], int k, int n);
long long int fatorial(long long int N);
unsigned long long choose(unsigned long long n, unsigned long long k);
float** loadMatriz(char* nameFile, int nbAutoresTest, int nbAmotrasAutor, int nbFeat);
float Abs(float x);
int* createArray(int size);
char* itoa(int val, int base);
