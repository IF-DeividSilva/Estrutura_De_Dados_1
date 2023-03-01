/**
 * @file BuscaBinaria.c
 * @author Deivid da Silva Galvao (you@domain.com)
 * @brief Busca de numeros inteiros estaticos de forma binaria com while
 * @version 0.1
 * @date 2022-08-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

busca_bin();

int main(int argc, char const *argv[])
{
    int vet [] = {2,3,9,17,19,23};
    int tam = 0;
    int elemento = 0;
    int pos = 0;

    printf("Digite o valor a ser pesquisado: ");
    scanf("%d", &elemento);

    if (pos= busca_bin(vet, tam, elemento) >= 0)
        printf("O numero digitado estah na posicao %d", pos);
    else
        printf("O numero digitado nao estah no vetor...");
    
    return 0;  
}//main

int busca_bin(int vet[], int tam, int elemento){
    int ini, fim, meio;
    ini=0; fim=tam; 
    while(ini<=fim){
        meio = (int) ((ini + fim)/2);
        if(vet[meio]==elemento){
            return meio;
        }
        else{
           if(vet[meio]>elemento){
            fim=meio-1;
           }
           else{
            ini = meio + 1;
            }//else
        }//else
    }//while  
    
    return(-1);
}//busca bin
