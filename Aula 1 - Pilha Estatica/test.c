#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXTAM 30

typedef struct{
  int topo;
  int vetorPE[MAXTAM];
} PilhaEstatica;

void iniciaPilhaEstatica(PilhaEstatica *pilha){
  pilha->topo = 0;
}


bool estaVaziaPilhaEstatica(PilhaEstatica *pilha){
  return(pilha->topo == 0);
}


bool estaCheiaPilhaEstatica(PilhaEstatica *pilha){
  return(pilha->topo == MAXTAM);
}


int tamanhoPilhaEstatica(PilhaEstatica *pilha){
    return(pilha->topo);
}

void empilhaPilhaEstatica(PilhaEstatica *pilha, int x){
  if(estaCheiaPilhaEstatica(pilha) == false){
    pilha->vetorPE[pilha->topo] = x;
    printf("tst");
    pilha->topo++;
  }else{
    printf("Atenção! Não é possível inserir.\n");
  }
}

void imprimePilhaEstatica(PilhaEstatica *pilha){
  printf("Pilha:{ ");
  for(int i=0; i < pilha->topo; i++){
    printf("%d ", pilha->vetorPE[i]);
  }
  printf("}\n\n");
}

int desempilhaPilhaEstatica(PilhaEstatica *pilha){
  int aux = -999;
  if(estaVaziaPilhaEstatica(pilha) == false){
    aux = pilha->vetorPE[pilha->topo-1];
    pilha->topo--;
  }else{
    printf("A pilha está vazia.\n");
  }
  return aux;
}

// ------------------------------------------- MAIN -------------------------------------------

int main(){
  int i, verificaPilha, tamPE;
  //conversor de decimal para binário
  int num, binB[7], auxB;

  PilhaEstatica pe;

  printf("Digite um numero decimal maior que 0: ");
  scanf("%d", &num);
  fflush(stdin);
      for(auxB = 7; auxB >= 0; auxB--){
          if(num % 2 == 0){
              binB[auxB] = 0;
              num = num / 2;
          }
          else{
              binB[auxB] = 1;
              num = num / 2;
          }
      }
        printf("passou");
        for(auxB = 0; auxB <= num; auxB++){
        int aux = binB[auxB];
        printf("%d", binB[auxB]);
        empilhaPilhaEstatica(&pe, aux);
      }

    imprimePilhaEstatica(&pe);

  for(int i = 0; i < 8; i++){
    desempilhaPilhaEstatica(&pe);
  }

  printf("\n\n");

  return 0;
}