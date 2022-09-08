/**
 * @file Atv_2-Fibonacci.c
 * @author your name (you@domain.com)
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

typedef struct fibo 
{
    int numero;
    struct fibo * proximo;
}Fibo;

typedef struct{  
    Fibo * topo;
}PilhaDin;

void inicializaPilha();

int main(int argc, char const *argv[])
{
    int N = 0;
    PilhaDin pilha;

    inicializaPilha(&pilha);

    do
    {

    printf(" Digite um numero entre 6 e 19: ");
    scanf("%d", &N);

    } while (N <= 5 || N >= 20 );

    empilha(N, pilha.topo);
    


    return 0;
}//main


void inicializaPilha(PilhaDin* p){
    p->topo=NULL;
}

    Fibo *empilha(int N, Fibo *topo){
     Fibo *aux;
     aux=(Fibo*) malloc(sizeof(Fibo));

    

     int i, fib1 = 1, fib2 = 1, soma;         
      for (i = 3; i <= N; i = i + 1)           
      {                                        
       soma = fib1 + fib2;                    
       fib1 = fib2;                           
       fib2 = soma;                           
     
       aux->numero = fib2;
     }         
     aux->proximo = topo;
    }