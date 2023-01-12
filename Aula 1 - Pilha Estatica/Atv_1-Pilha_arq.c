/**
 * @file Atv_1-Pilha_arq.c
 * @author Eduardo Yuji Yoshida Yamada / Deivid da Silva Galvao (eduardoyuji@alunos.utfpr.edu.br/deivid.2002@alunos.utfpr.edu.br)
 * RAs 2320606/2408740
 * @brief Implemente um programa com duas Pilhas Est ́aticas, uma que ter ́a apenas n ́umeros pares,
e a outra apenas com n ́umeros  ́ımpares. O programa dever ́a ler um arquivo de entrada contendo 10
n ́umeros, e empilha-los corretamente. Ao final, imprima cada pilha em um arquivo de sa ́ıda pr ́oprio.
 * @version 0.1
 * @date 2022-09-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXTAM 10

typedef struct pilhaEstatica{
    int topo;
    int vetor[MAXTAM];
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
    pilha->vetor[pilha->topo] = x;
    pilha->topo++;
  }else{
    printf("Atenção! Não é possível inserir.\n");
  }
}

void imprimePilhaEstatica(PilhaEstatica *pilha){
    printf("Pilha:{ ");
    for(int i=0; i < pilha->topo; i++){
        printf("%d ", pilha->vetor[i]);
    }
    printf("}\n\n");
}


int desempilhaPilhaEstatica(PilhaEstatica *pilha){
  int aux = -999;
  if(estaVaziaPilhaEstatica(pilha) == false){
    aux = pilha->vetor[pilha->topo-1];
    pilha->topo--;
  }else{
    printf("A pilha está vazia.\n");
  }
  return aux;
}
int main(int argc, const char* argv[]){
    FILE *arq1, *arq2, *arq3;
    PilhaEstatica pe;
    int recebe;

//Abre os arquivos
    arq1 = fopen(argv[1],"r");
    arq2 = fopen(argv[2],"w+");
    arq3 = fopen(argv[3],"w+");

//verifica a integridade dos arquivos
    if(arq1 == NULL){
        printf("Erro Na abertura do arquivo 1.\n");
    }
    if(arq2 == NULL){
        printf("Erro Na abertura do arquivo 2.\n");
    }
    if(arq3 == NULL){
        printf("Erro Na abertura do arquivo 3.\n");
    }

//inicia a pilha
    iniciaPilhaEstatica(&pe);

//recebe os valores e empilha
      while(fscanf(arq1, "%d", &recebe) != EOF){
    if(recebe == (int)recebe){
      empilhaPilhaEstatica(&pe, recebe);
    }else{
      printf("Erro!---Erro!---Erro!---Erro!\n\n");
      return 0;
    }
  }

//imprime a pilha 
    imprimePilhaEstatica(&pe);

    int tamPE = tamanhoPilhaEstatica(&pe); //recebe o tamanho da pilha
    int verificaNum;

    //desempilha a pilha
    for(int i = 0; i < tamPE; i++){
        verificaNum = desempilhaPilhaEstatica(&pe);
        printf("\n%d", verificaNum);//verifica a paridade do número
        if (verificaNum % 2 == 0) {
            fprintf(arq2,"%d\n",verificaNum);//escreve os números pares no arquivo
        }
        else {
            fprintf(arq3,"%d\n",verificaNum);//escreve os números ímpares no arquivo
        }
    }

//Fecha os arquivos
  fclose(arq1);
  fclose(arq2);
  fclose(arq3);

  return 0;
}