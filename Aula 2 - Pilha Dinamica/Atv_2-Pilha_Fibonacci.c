/**
 * @file Atv_2-Fibonacci.c
 * @author Eduardo Yuji Yoshida Yamada / Deivid da Silva Galvao (eduardoyuji@alunos.utfpr.edu.br/deivid.2002@alunos.utfpr.edu.br)
 * RAs 2320606/2408740
 * @brief Elabore um programa em C implementando uma Pilha Dinˆamica que armazene N n ́umeros
 *  da sequˆencia de Fibonacci, onde N se ́ra um valor recebido pelo usu ́ario e dever ́a estar contido entre
 *  5 < N < 20.
 * 
 * • Usu ́ario fornece um valor (entre 5 < N < 20), por exemplo, N = 10
 * • Elementos da Pilha (nesta ordem) { 34, 21, 13, 8, 5, 3, 2, 1, 1, 0 }
 * 
 * @version 0.1
 * @date 2022-09-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoPilha* PtrNoPilha;

typedef struct NoPilha 
{
    int x;
    PtrNoPilha proximo;
}NoPilha;

typedef struct{  
    PtrNoPilha * topo;
    int quantidadeElementos;
}PilhaDin;

void inicializaPilha();
void fibonacci();
void empilha();
void imprime();
void destroi();
bool estaVaziaPilhaDinamica();

int main()
{
    int N = 0;
    PilhaDin pilha;

    inicializaPilha(&pilha);
    // do while para repetir enquanto o N for invalido
    do
    {

    printf("\n Digite um numero entre 6 e 19: ");
    scanf("%d", &N);
    if (N < 6 || N > 19)
    {
        printf("\n Numero digitado eh invalido...Digite novamente...");
    }
    

    } while (N <= 5 || N >= 20 );

    fibonacci(N, &pilha);

    imprime(&pilha);

    destroi(&pilha);
    

    return 0;
}//main

void inicializaPilha(PilhaDin* p){
    p->topo=NULL;
    p->quantidadeElementos = 0;
}

void fibonacci(int N, PilhaDin*p){
    // faz o calculo da sequencia de fibonacci e vai empilhando os numeros da sequencia
     int i, fib1 = 1, fib2 = 1, soma;         
      for (i = 3; i < N; i = i + 1)           
      {   
       if (i == 3)
       {
        empilha(p, 0);
        empilha(p, fib1);
        empilha(p, fib2);
       }                                         
       soma = fib1 + fib2;                    
       fib1 = fib2;                           
       fib2 = soma;                           
       empilha(p, fib2); 
     }     
}
void empilha(PilhaDin *p, int x){
        // criar um nó, alocar a memoria dele (malloc)
        PtrNoPilha aux;
        aux = (PtrNoPilha)malloc(sizeof(NoPilha));
        // copiar o x para o novo nó (aux)
        aux->x = x;
        // o proximo do novo nó aponta para NULO (topo -> NULO)
        aux->proximo = p->topo;
        // topo apontar para novo nó
        p->topo = aux;
        // incrementa a quantidade de elemento 
        p->quantidadeElementos++;

}      

void imprime(PilhaDin *p){
     printf("Pilha = { ");
        PtrNoPilha ptr;
        for (ptr = p->topo; ptr != NULL; ptr = ptr->proximo)
        {
            printf(" %d ", ptr->x);
        }
        printf(" }\n");
}

int desempilhaPilhaDinamica(PilhaDin *p){
  int ret = -999;
  //verifica se esta vazia e decrementa o topo apartir da variavel auxiliar e ja libera a memoria retornando o valor retirado
  if(!estaVaziaPilhaDinamica(p)){
    PtrNoPilha aux;
    //ret = aux->x;
    aux = p->topo;
    p->topo = aux->proximo;
    free(aux);
    p->quantidadeElementos--;
  }else{
    printf("Não é possível remover. Pilha vazia.\n");
  }
  return(ret);
}

void destroi(PilhaDin *p){
        //enquanto a pilha nao for nula o while percorre a pilha desalocando a memoria e por fim desaloca o topo
        while (p->quantidadeElementos != 0){
            desempilhaPilhaDinamica(p);
        }   
}

bool estaVaziaPilhaDinamica(PilhaDin *p){
  return(p->quantidadeElementos == 0);
}//verififica se estah vazia

    

   