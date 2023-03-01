/**
 * @file Atv_4-Pilha_Bin.c
 * @author Eduardo Yuji Yoshida Yamada / Deivid da Silva Galvao (eduardoyuji@alunos.utfpr.edu.br/deivid.2002@alunos.utfpr.edu.br)
 * RAs 2320606/2408740
 * @brief Elabore um programa que realize a convers ̃ao de n ́umeros decimais (n ̃ao negativos) para
n ́umeros bin ́arios usando Pilhas Dinˆamicas. O programa deve:
• O usu ́ario digitar um n ́umero decimal (N ≥ 0);
• Efetuar sucessivas divis ̃oes por 2 e armazenar os restos destas divis ̃oes na pilha (veja o esbo ̧co da
ideia na Figura 1);
• Na  ́ultima divis ̃ao, armazenar tamb ́em o quociente que ser ́a o elemento do topo;
• Imprimir a pilha, pois ela conter ́a o valor de N em base bin ́aria.

 * @version 0.1
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoPilha{
  int chave;
  struct NoPilha* proximo; // = NoPilha*
} NoPilha;

typedef struct{
  NoPilha* topo;
  int qtde;
} PilhaDinamica;

void iniciaPilhaDinamica(PilhaDinamica *pilha){
  pilha->topo = NULL;
  pilha->qtde = 0;
}//inicia pilha

bool estaVaziaPilhaDinamica(PilhaDinamica *pilha){
  return(pilha->qtde == 0);
}//verififica se estah vazia

int tamanhoPilhaDinamica(PilhaDinamica *pilha){
  return(pilha->qtde);
}//retorna o tamanho da pilha

void empilhaPilhaDinamica(PilhaDinamica *pilha, int x){
  //Cria um nó e aloca memoria para ele  
  NoPilha *aux;
  aux = malloc(sizeof(NoPilha));
  //copia o x para o novo nó (aux)
  aux->chave = x;
  //proximo do nó aponta para o que o topo aponta
  aux->proximo = pilha->topo;
  // topo aponta para o novo nó
  pilha->topo = aux;
  //encrementa quantidade
  pilha->qtde++;
}//empilha

void destroiPilha(PilhaDinamica *pilha){
  while (pilha->qtde != 0){
    desempilhaPilhaDinamica(pilha);
  }
}

void imprimePilhaDinamica(PilhaDinamica *pilha){
  printf("Pilha:{ ");
  NoPilha* percorre;
  //for para percorrer a pilha enquanto a varivel auxiliar percorre, que inicialmente recebe o topo, for difente de NULL
  for(percorre = pilha->topo; percorre != NULL; percorre = percorre->proximo){
    printf("%d ",percorre->chave);
  }
  printf(" }\n");
}

int desempilhaPilhaDinamica(PilhaDinamica *pilha){
  int ret = -999;
  //verifica se esta vazia e decrementa o topo apartir da variavel auxiliar e ja libera a memoria retornando o valor retirado
  if(!estaVaziaPilhaDinamica(pilha)){
    NoPilha* aux;
    ret = pilha->topo->chave;
    aux = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(aux);
    pilha->qtde--;
  }else{
    printf("Não é possível remover. Pilha vazia.\n");
  }
  return(ret);
}

int main(){
  int i, num, binB[8], x;
    PilhaDinamica pd;
    iniciaPilhaDinamica(&pd);

    if(estaVaziaPilhaDinamica(&pd)){
        printf("Pilha vazia.\n");
    }else{
        printf("Não está vazia.\n");
    }

    printf("Digite um numero decimal maior que zero: ");
    scanf("%d", &num);
    fflush(stdin);
    //for ateh com i decrementando ate i ser maior -1
    for(i = 7; i > -1; i--){
      //divide por 2 e verifica se o numero tem resto 0 ou 1 e ja empilha o resto
      if(num % 2 == 0){
        binB[i] = 0;
        num = num / 2;
      }else{
        binB[i] = 1;
        num = num / 2;
      }
      x = binB[i];
      empilhaPilhaDinamica(&pd, x);   
    }

    imprimePilhaDinamica(&pd);

    destroiPilha(&pd);

    printf("\n");
    
    
    return 0;
}//main