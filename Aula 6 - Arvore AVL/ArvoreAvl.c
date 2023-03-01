/*
 * @file ArvoreAvl.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***************** STRUCTS ****************************/


/******************************************************/
/******************************************************/


typedef struct NoArvore* PtrNoArvore;

typedef struct NoArvore{
    int x;
    PtrNoArvore esquerda;
    PtrNoArvore direita;

    //fator de balanceamento
    int altura;// altura do no
}NoArvore;

/*
    Fator de balanceamento (bf)
    bf =  altura(subarvore direita) - altura(subarvore esquerda
    bf = {-1,0,+1}
    bf > +1 -> desbalanceamento
        * lado direito eh maior (direita > esquerda)
        * rotações para esquerda
    bf < -1 -> desbalanceamento
        * lado esquerdo eh maior (esquerda > direita)
        rotações para direita
*/
void inicializaAvl(PtrNoArvore *NoArvore){
    (*NoArvore) = NULL;
}

int alturaArvore(PtrNoArvore NoArvore){
    if(NoArvore == NULL) return 0;
    else return(NoArvore->altura);
} 

int atualizaAltura(PtrNoArvore esq, PtrNoArvore dir){
    int altEsq = alturaArvore(esq);
    int altDir = alturaArvore(dir);
    if (altEsq > altDir) return (altEsq +1);
    else return (altdir +1);   
}

bool estaVazia(PtrNoArvore * NoArvore){
    return((*NoArvore) == NULL);
}

void rotacaoSimplesDireita(PtrNoArvore * NoArvore){
    PtrNoArvore aux1 = (*NoArvore)->esquerda;
    // filho esquerda de aux1 sera o alpha(direita do aux1)
    (*NoArvore)->esquerda = aux1->direita;
    // no direito de aux1 se torna o NoArvore
    aux1->direita = (*NoArvore);

    // atualiza a altura do No de arvore
    (*NoArvore)->altura = atualizaAltura((*NoArvore)->esquerda, (*NoArvore)->direita);
    // atualiza a altura do aux1
    aux1 = atualizaAltura(aux->esquerda, aux->direita);

    (*NoArvore) = aux1;// controle de recursao
}

void rotacaoDuplaEsquerda(){

}
void imprimePreOrden(PtrNoArvore * NoArvore){
    if((*NoArvore) == NULL) return;
    // imprime
    printf("%d ", (*NoArvore)->x);
    //vai para esquerda -> chama recursivamente a funcao impressao (subarvore esquerda)
    imprimePreOrden(&(*NoArvore)->esquerda);
    //vai para direita -> chama recursivamente a funcao impressao (subarvore direita)
    imprimePreOrden(&(*NoArvore)->direita);
}

bool inserirAvl(PtrNoArvore *NoArvore, int x){
    // *NoArvore == Nulo (Ponto de inserir encontrado)
    if((*NoArvore) == NULL){
     (*NoArvore) = (PtrNoArvore)malloc(sizeof(NoArvore));
     (*NoArvore)->direita = (*NoArvore)->esquerda = NULL;
     (*NoArvore)->x = x;
     (*NoArvore)->altura = 1;
     return true;
    }

    // *NoArvore == chave retorna falso
    if((*NoArvore)->x == x)
    return false;

    // recursivas
    bool insere;
    if(x > (*NoArvore)->x){
      insere = inserirAvl(&(*NoArvore)->direita, x);
    // direita -> chave > NoArvore->chave
    }else{
    // esquerda -> chave < NoArvore->chave
      insere = inserirAvl(&(*NoArvore)->esquerda, x);
    }
    if(insere == false) return false;
    
    //precisa verificar o balanceamento
    int alturaEsquerda = 0;
    int alturaDireita = 0;

    alturaDireita = alturaArvore((*NoArvore)->direita);
    alturaEsquerda = alturaArvore((*NoArvore)->esquerda);

    // identifica o desbalanceamento
    if((alturaDireita - alturaEsquerda) == 2 || (alturaDireita - alturaEsquerda) == -2)
    {
        rotacionarArvore(&(*NoArvore));
    }
        
    // ajuste de altura do no corrente
    (*NoArvore)->altura = atualizaAltura((*NoArvore)->esquerda,(*NoArvore)->direita);
    return true;

}

int main(int argc, char const *argv[])
{
    PtrNoArvore raiz;
    inicializaAvl(&raiz);
    if (estaVazia(&raiz))
    {
        printf("Avl criada e vazia \n");
    }else{
    printf("zooou");
    }

    printf("PreOrdem: { ");
    imprimePreOrden(&raiz);
    printf("}\n");



    return 0;
}
