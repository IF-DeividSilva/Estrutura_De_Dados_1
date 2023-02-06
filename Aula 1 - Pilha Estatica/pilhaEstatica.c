/**
 * @file pilhaEstatica.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
TAD - Tipo abstrato de dados
    - Pilha estatica
     * objetos /struct
     * funcoes/ operações

----------------------- Pilha  ------------------------
    inicialização
    inserção(push) 
    remoção (pop)
    topo (top)
    estaVazia
    estaCheia
    tamanho
    impressão(estado, valores contidos)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define tamanho 10

typedef struct 
{
    //vetor de inteiros
    int array[tamanho];
    //controlar o topo 
    int topo;
    //contador (inteiro) quantidade
    int quantidadeElementos;

} PilhaEstatica;

void iniciaPilhaEstatica (PilhaEstatica* p){
    p->topo = 0;
    p->quantidadeElementos = 0;
}//inicializa

bool estaVazia (PilhaEstatica *p){
    return (p->topo ==0);
}

bool estaCheia (PilhaEstatica *p){
    return (p->topo == tamanho);
}

int tamanhoPilha(PilhaEstatica *p){
    return(p->quantidadeElementos);
}

void empilha(PilhaEstatica* p, int x){
    //se não estah cheia 
    if (estaCheia(p) == false)
    {
    //insere elemento
        p->array[p->topo] = x;
    //incrementa o elemento
        p->topo++;
    //incrementa a quantidade de elementos   
        p->quantidadeElementos++;
        
    }else {
        printf("\n Warning...pilha cheia... \n");
    }
 
}

void imprimePilha(PilhaEstatica*p){
    printf("Pilha = {");
    //for (percorre o vetor, imprimindo todas as posições ateh topo -1)
    int i;
    for ( i = 0; i < p->topo; i++)
    {
        printf(" %d ", p->array[i]);
    }
    
    printf("}\n");

}

//remoção (desempilhar)
// retorna o tipo de dado contido no array
int desempilha(PilhaEstatica *p){
    int aux = -1;
    //se apilha nao estiver vazia
    if(estaVazia(p)==false){
    // variavel auxiliar recebe o elemento mais recente 
    aux = p->array[p->topo-1];
    // decrementa o indice do topo
    p->topo--;
    // decrementa a quantidade de elementos
    p->quantidadeElementos--;    

    }else{
        //senao --> warning( nao faz nada)
        printf("Warning: nao eh possivel remover pois estah vazia..\n");
    }
    return(aux);
}


int main(int argc, char const *argv[])
{
    PilhaEstatica pilha;
    iniciaPilhaEstatica(&pilha);
    imprimePilha(&pilha);

    //verifica se estah vazia
    if(estaVazia(&pilha))
      printf("Estah vazia...\n");
    else{
      printf("Tem elementos na pilha...\n");
    }

    //verifica se estah cheia
    if (estaCheia(&pilha))
    {
        printf("Estah cheia...\n");
    }else{
        printf("Nao estah cheia...\n");
    }

    empilha(&pilha, 10);
    imprimePilha(&pilha);
    empilha(&pilha, 100);
    imprimePilha(&pilha);
    empilha(&pilha, 10000);

    int retorno = desempilha(&pilha);
    printf("elemento retornado: %d\n", retorno);
    imprimePilha(&pilha);

    
    printf("Tamanho = %d\n" , tamanhoPilha(&pilha));

     //verifica se estah vazia
    if(estaVazia(&pilha))
      printf("Estah vazia...\n");
    else{
      printf("Tem elementos na pilha...\n");
    }

    imprimePilha(&pilha);


    return 0;
}//main
