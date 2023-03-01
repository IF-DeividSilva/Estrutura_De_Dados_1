/**
 * @file Pilha_Estatica.c
 * @author your name (you@domain.com)
 * @brief Pilha Dinamica
 * @version 0.1
 * @date 2022-09-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//NoPilha (informação, ptr)
//PilhaDinamica (topo -> NoPilha)
typedef struct NoPilha* PtrNoPilha;

typedef struct NoPilha{
    int x;
    PtrNoPilha proximo;
}NoPilha;

typedef struct{
    PtrNoPilha topo;
    int quantidadeElementos;

}PilhaDinamica;

   void iniciaPilha(PilhaDinamica *p){
    p->topo = NULL;
    p->quantidadeElementos = 0;
   }

   bool estaVazia(PilhaDinamica *p){
    return (p->topo == NULL);
    //ou return (p->quantidadeElemento == 0);
    }

   int tamanhoPilha(PilhaDinamica *p){
    return (p->quantidadeElementos);
   } 

   void empilha(PilhaDinamica* p, int x){
    //1. primeira insercao em uma pilha vazia

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

    //2. insercao em uma pilha nao vazia
        // criar um nó, alocar memoria dele (malloc)
        // copiar o x para o novo nó
        // proximo do novo nó aponta para que, o topo aponta
        // topo apontar para o novo nó
        // incrementa a quantidade elementos    

   }

    void imprime(PilhaDinamica* p){
        printf("Pilha = { ");
        PtrNoPilha ptr;
        for (ptr = p->topo; ptr != NULL; ptr = ptr->proximo)
        {
            printf(" %d ", ptr->x);
        }
        printf(" }\n");
    }

   int desempilha(PilhaDinamica* p){
        int ret = -1;
        //so remove se nao estiver vazia
        if (estaVazia(p)== false)
        {
            // cria um ponteiro auxiliar
            PtrNoPilha aux = p->topo;
            // copia informacao para ret (retornar usuario)
            ret = aux->x;
            // topo apontar para o proximo do topo
            p->topo = p->topo->proximo;
            // desaloca memoria do aux (nó removido)
            free(aux);
            // decrementa a quantidade de elemento
            p->quantidadeElementos--;
        } else{
            printf("Warning: nao eh possivel remover...pois pilha esta vazia....");
        }
        return(ret);

   } 

/*
    destruição 
    inserção
    remoção 
    consulta
*/

int main(int argc, char const *argv[])
{
    PilhaDinamica pilha;
    iniciaPilha(&pilha);
     imprime(&pilha);

    //verifica se ta vazia
    if (estaVazia(&pilha))
    {
        printf("Estah vazia \n");
    }else{
        printf("Tem elementos na pilha");
    }

    int obj;

    for (int i = 0; i < 20; i++)
    {
        empilha(&pilha, i);
        imprime(&pilha);
    }
    

    for (int i = 0; i < 10; i++)
    {
      obj  =  desempilha(&pilha);
      printf("Elemento removido: %d \n", obj);
      imprime(&pilha);
    }
    
    printf("Tamanho = %d \n", tamanhoPilha(&pilha));
    return 0;
}//main
