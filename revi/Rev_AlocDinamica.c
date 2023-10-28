/**
 * @file Rev_AlocDinamica.c
 * @author your name (you@domain.com)
 * @brief Alocação Dinâmica: Faca um programa que leia um valor N e crie dinamicamente um vetor 
//  com essa quantidade de elementos. Em seguida, passe esse vetor para um procedimento que 
//  vai preencher os elementos desse vetor com numeros aleat ́orios de 0 at ́e N. Depois, 
//  no programa principal, imprima os valores do vetor preenchido. Alem disso, antes de 
//  finalizar o programa, lembre-se de liberar a  area de memoria alocada
 * @version 0.1
 * @date 2022-08-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

void preencher_vetor();

int main(int argc, char const *argv[])
{
    int N;
    int* vetor = NULL;
    

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &N); fflush(stdin);

    if (N <= 0)
    {
       printf("Valor invalido...encerrando");
       return 1;
    }//if

    vetor = (int*) malloc(N * sizeof(int));//alocando o vetor dinamicamente com malloc
    if(vetor == NULL){
    printf("Ocorreu um erro na alocaçao do vetor...encerrando");
    return 1;    

    }//verifica se a alocação foi ocorreu sem erros

    preencher_vetor(vetor, N);

    for(int i = 0; i < N; i++){
        printf("Valor[%d] = %d \n", i,vetor[i]);
    }
    free(vetor);//libera memoria alocada 

    return 0;
}//main
    /**
     * @brief funcao pra preencher o vetor alocado dinamicamente de forma aleatoria.
     * 
     * @param vetor 
     * @param N 
     */
   void preencher_vetor(int* vetor, int N){
    for (int i = 0; i < N; i++){
        vetor[i] = rand() % N;
    }
}

