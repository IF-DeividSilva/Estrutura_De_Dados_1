/**
 * @file Fila_Dinamica.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------STRUCTS----------------

// Nofila * ptrNofila
typedef struct NoFila *PtrNoFila;

//Nofila (informacao, ponteiros)
typedef struct NoFila{
    int x;  //informacao
    PtrNoFila proximo;  //ptr (proximo)
}NoFila;

// Fila dinamica
typedef struct{
    PtrNoFila inicio; // ptr para o primeiro elemento
    PtrNoFila fim; // ptr para o ultimo elemento
    int quantidadeElemento; //contador
}FilaDinamica;
//------------------------------------------------------
//------------------------------------------------------


//---------Funções------------------------
void iniciaFila();
bool estaVazia();
int tamanho();
void enfileirar();
void imprimeFila();
int remocao();
// primeiro();
// ultimo();
// destrutor;


//----------------------------------------
//----------------------------------------

int main(int argc, char const *argv[])
{
    FilaDinamica f;
    int r = 0;
    iniciaFila(&f);
    if (estaVazia(&f))
    {
        printf("Esta vazia \n");
    }
    imprimeFila(&f);
    enfileirar(&f, 10);
    imprimeFila(&f);
    enfileirar(&f, 112);
    imprimeFila(&f);
    enfileirar(&f, 122);
    imprimeFila(&f);
    printf("Tamanho = %d \n", tamanho(&f));

    r = remocao(&f);
    imprimeFila(&f);
    r = remocao(&f);
    imprimeFila(&f);
    r = remocao(&f);
    imprimeFila(&f);
    r = remocao(&f);
    imprimeFila(&f);
    


    return 0;
}//main


void iniciaFila(FilaDinamica* fila){
    fila->quantidadeElemento = 0;
    fila->inicio = NULL;
    fila->fim = NULL;

}

bool estaVazia(FilaDinamica* fila){
    // qtde == 0;
    // inicio == fim == NULL
    return(fila->inicio == NULL);

}

int tamanho(FilaDinamica * fila){
    return(fila->quantidadeElemento);
}

void enfileirar(FilaDinamica* fila, int x){
//   criar uma variavel auxiliar (NoFila)
    PtrNoFila aux;
//   alocar a memoria para esse nó
    aux = (PtrNoFila)malloc(sizeof(NoFila));
//   copiar a informação para o novo nó
    aux->x = x;
//insercao
//a) primeira insercao (Atualiza tanto o inicio quanto o fim)
if (estaVazia(fila))
{
//   inicio e fim apontam para o novo nó
    fila->inicio = aux;
    fila->fim = aux;
//   proximo do novo nó aponta para nulo
    aux->proximo = NULL;

}else{
//b) nao é primeira inserção (Atualiza somente o fim)

//   proximo do novo nó = NULL (proximo do fim)
    aux->proximo = fila->fim->proximo;

//   o proximo do fim aponta para o novo elemento (aux)
    fila->fim->proximo = aux;

//   o fim recebe o proximo de fim (fim-> aux)
    fila->fim = fila->fim->proximo;
}

//   incrementa quantidade de elementos
fila->quantidadeElemento++;
//   incrementa contador
}

void imprimeFila(FilaDinamica *fila){
    printf("Fila = {");
    PtrNoFila ptr;
    ptr = fila->inicio;
    while (ptr != NULL)
    {
        printf("%d ", ptr->x);
        ptr = ptr->proximo;
    }
    printf("}\n");
}

//remocao (altera o inicio da fila)
int remocao(FilaDinamica * fila){
    int ret = -77;
    // nao pode remover se a fila estiver vazia
    if (!estaVazia(fila))
    {
    // ptr auxiliar(aux)
    PtrNoFila aux;
    // aux recebe o inicio da fila
    aux = fila->inicio;
    // copiar a informacao para o usuario
    ret = aux->x;
    // atualizar o inicio para proximo dele
    fila->inicio = fila->inicio->proximo;
    // desalocar memoria aux
    free(aux);
    // decrementar a quantidade de elemento
    fila->quantidadeElemento--;

    }else{
        printf("ErrO... fila ja estah vazia");
    }

  return(ret);  
}