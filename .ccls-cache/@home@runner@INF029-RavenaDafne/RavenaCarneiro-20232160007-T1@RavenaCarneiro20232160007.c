#include <stdio.h>
#include <stdlib.h>
#include "RavenaCarneiro20232160007.h"


int somar(int x, int y){
  int soma = x + y;
  return soma;
}

//Iterativo
int fatorial(int x){
  int fat = 1;
  int i;
  for(i = x; i >1 ; i--){
     fat = fat * i;
   
  }
   return fat;
}

