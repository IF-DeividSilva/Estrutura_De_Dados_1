/**
 * @file FilaEstatica.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define tamanho 5

// Estrutra de fila estatica
// Tamanho fixo definido
// Q - array[tamanho]
// Inicio (int) variavel indexadora
// Fim (int) variavel indexadora
// Contador - quantidade de elementos dentro do arrey
typedef struct{
    
    int inicio; //controla o inicio da fila
    int fim; //controla o fim da fila
    int array[tamanho];
    int quantidadeElementos;

}FilaEstatica;


// Duas extremidades manipulaveis
// Inicio de fila (primeiro elemento)
// Fim de fila  (ultimo elemento)

// Inicializacao
void iniciaFila(FilaEstatica *fila){
    fila->quantidadeElementos = 0;
    fila->inicio = 0;
    fila->fim = -1;
}
// estrutura esta vazia
bool estaVazia(FilaEstatica *fila){
    // contador == 0
    return(fila->quantidadeElementos == 0);

}

// estrutura esta cheia
bool estaCheia(FilaEstatica *fila){
    // contador == tamanho
    return(fila->quantidadeElementos ==  tamanho);
}

// insercoes sao feitas no final da fila
void enfileirar(FilaEstatica *fila, int x){
    // Só pode inserir se a fila nao estiver cheia
    if (!estaCheia(fila)){
        //incrementa o fim
        //fila->fim++;
        fila->fim = incrementaIndice(fila->fim);
        //atribui o elemento na posicao indicada pelo fim(array)
        fila->array[fila->fim] = x;
        // incrementa a quantidade de elementos
        fila->quantidadeElementos++;

    } else {
        printf("Erro, fila cheia");
    }
} 

// remocoes saso feitas no inicio da fila
int desenfileirar(FilaEstatica *fila){
    int ret = -777;
    // Só pode remover se a fila nao estiver vazia
    if (! estaVazia(fila))
    {
    // 1 Salvar o dado que precisa ser retornado
        ret = fila->array[fila->inicio];

    // 2 Incrementa a posicao do inicio
        //fila->inicio++;
        fila->inicio = incrementaIndice(fila->inicio);

    // 3 Decrementa a quantidade de elementos
        fila->quantidadeElementos--;

    // 4 Retorna o valor para o usuario
        return (ret);
    }
    
}

// consultar o primeiro elemento

// tamanho da estrutura 
int tamanhoFila (FilaEstatica *fila){
    return(fila->quantidadeElementos);
}

void imprimeFila(FilaEstatica *fila){
    printf("Fila = {");
    //for 0 a tamanho -1
    int i;
    int n = tamanhoFila(fila);
    for ( i = 0; i < n; i++)
    {
        int indice = (fila->inicio + i) % tamanho;
        printf(" %d ", fila->array[indice]);
    }
    
    printf("}\n");
}

// indice == tamanho -1
// indice = 0
// se nao indice++

int incrementaIndice(int i){
    int newValue = (i+1) % tamanho;
    return newValue;

}



int main(int argc, char const *argv[])
{
    FilaEstatica f;
    iniciaFila(&f);
    printf(" Sucesso\n");
    
    if (estaVazia(&f))
    {
        printf("Esta vazia \n");
    }

    if (estaCheia(&f))
    {
        printf("Esta cheia \n");
    }

    enfileirar(&f, 10);
    imprimeFila(&f);
    enfileirar(&f, 50);
    imprimeFila(&f);
    enfileirar(&f, 20);
    imprimeFila(&f);
    enfileirar(&f, 30);
    imprimeFila(&f);
    enfileirar(&f, 26);
    imprimeFila(&f);
    enfileirar(&f, 27);
    imprimeFila(&f);


    printf("Tamanho = %d \n", tamanhoFila(&f));
    
    int removido;
    removido = desenfileirar(&f);
     imprimeFila(&f);
    removido = desenfileirar(&f);
     imprimeFila(&f);
    removido = desenfileirar(&f);
     imprimeFila(&f);

    enfileirar(&f, 15);
    imprimeFila(&f);
    enfileirar(&f, 507);
    imprimeFila(&f); 

    return 0;
}//main

