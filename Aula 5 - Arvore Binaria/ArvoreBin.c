/**
 * @file ArvoreBin.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoArvore * PtrNoArvore;

// NoArvore (2 conexoes - filhos)
typedef struct NoArvore{
// int chave (informação)
    int chave;
// filho direita (PtrNoArvore)
    PtrNoArvore esquerda;
// filho esquerda (PtrNoArvore) 
    PtrNoArvore direita;
}NoArvore;

/*********************************/
// --- FUNCOES --- //
// 1. Inicializar
void inicializaArvore();
// 2. Inserir
bool inserir();
// 3. Consultar
bool consultar();
// 4. estaVazia
bool estaVazia();
// 5. Impressao
void impressaoPreOrdem();
void impressaoPosOrdem();
// 6. Destrutor
void destroiArvore();

bool removerElemento();

PtrNoArvore valorMaximoEsquerda();

/*********************************/
int main(){
    PtrNoArvore raiz; //NoArvore*
    //inicializa a estrutura
    inicializaArvore(&raiz);
    if(estaVazia(&raiz)){
        printf("Vazia\n");
    }
    inserir(&raiz, 5);
    inserir(&raiz, 4);
    inserir(&raiz, 3);
    inserir(&raiz, 2);
    inserir(&raiz, 7);
    inserir(&raiz, 6);
    inserir(&raiz, 8);
    inserir(&raiz, 9);

    //PreOrdem impressao [5, 4, 3, 2, 7, 6, 8, 9]
    printf("Percurso pre ordem: ");
    impressaoPreOrdem(&raiz);
    printf("\n");

    //PosOrdem impressao [2, 3, 4, 6, 9, 8, 7, 5]
    printf("Percurso pos ordem: ");
    impressaoPosOrdem(&raiz);
    printf("\n");

    //Ordem impressao [2, 3, 4, 5, 6, 7, 8, 9]
    printf("Percurso ordem: ");
    impressaoOrdem(&raiz);
    printf("\n");

    if(!estaVazia(&raiz)){
        printf("Not Vazia\n");
    }
    int consulta[5] = {15,3,7,9,4};

    //consulta -> verificar se existem elementos dentro da arvore
    for (size_t i = 0; i < 5; i++)
    {
        printf("Verificando: %d --> ");
        if(consultar(&raiz, consulta[i])){
            printf("Achou \n");
    }else{
        printf("Nao encontrado \n");
    }
    }
    removerElemento(&raiz, 7);
    //PreOrdem impressao [5, 4, 3, 2, 7, 6, 8, 9]
    printf("Percurso pre ordem: ");
    impressaoPreOrdem(&raiz);
    printf("\n");

    destroiArvore(&raiz);
     if(estaVazia(&raiz)){
        printf("Tudo cortado...\n");
    }
}

/*********************************/
void inicializaArvore(PtrNoArvore *arvore){
    (*arvore) = NULL;
}

bool estaVazia(PtrNoArvore *arvore){
    return ((*arvore) == NULL);
}

bool inserir(PtrNoArvore *arvore, int x){
    // 1 - quando for inserir (ptr == NULL) // chegou na folha
    if((*arvore) == NULL){
    // Criar um novo no de arvore
    // Alocar memoria para ele
        (*arvore) = malloc (sizeof (NoArvore));
    // Copiar valor dentro do no
        (*arvore)->chave = x;
    // Filho direita && filho esquerda = NULL
        (*arvore)->esquerda = NULL;
        (*arvore)->direita = NULL;
    
    return true;
    }
    // 2 chaves duplicadas
    if ((*arvore)->chave == x){
        printf("erro chave ja inserida");
        return false;
    }

    //---Recursao------//
    // 3 if x maior que o valor do no corrente
    if (x > (*arvore)-> chave){
    // vai para direita -> chama recursivamente a funcao insercao (subarvore direita)
    //  subarvore direita -> filho direita
    return (inserir(&(*arvore)->direita, x));
    }else{
    // 4 if x menor que o valor do no corrente
    // vai para esquerda -> chama recursivamente a funcao insercao (subarvore esquerda)
    // subarvore esquerda -> filho esquerda   
    return (inserir(&(*arvore)->esquerda, x)); 
    }
}

void impressaoPreOrdem(PtrNoArvore *arvore){
    if ((*arvore) == NULL) return;
    // Imprime
    printf("%d ", (*arvore)->chave);
    // Esquerda
    impressaoPreOrdem(&(*arvore)->esquerda);
    // Direita
    impressaoPreOrdem(&(*arvore)->direita);
}

void impressaoPosOrdem(PtrNoArvore *arvore){
    if ((*arvore) == NULL) return;
    // Esquerda
    impressaoPosOrdem(&(*arvore)->esquerda);
    // Direita
    impressaoPosOrdem(&(*arvore)->direita);
    // Imprime
    printf("%d ", (*arvore)->chave);
}

void impressaoOrdem(PtrNoArvore *arvore){
    if ((*arvore) == NULL) return;
    // Esquerda
    impressaoOrdem(&(*arvore)->esquerda);
    // Imprime
    printf("%d ", (*arvore)->chave);
    // Direita
    impressaoOrdem(&(*arvore)->direita);
}

bool consultar(PtrNoArvore *arvore, int x){
    
    // se arvore filho == null retorna falso
    if ((*arvore) == NULL) return false;

    //elemento encontrado
    // se arvore filho == x retorna verdadeiro
    if ((*arvore)->chave == x) return true;
    
    // recursao
    // chamar o filho da direita
    if(x > (*arvore)->chave) return (consultar(&(*arvore)->direita, x));
    // chamar o filho da esquerda
    else
     return (consultar(&(*arvore)->esquerda, x));    

}

void destroiArvore(PtrNoArvore *arvore){
    if((*arvore) != NULL){
        destroiArvore(&(*arvore)->esquerda);
        destroiArvore(&(*arvore)->direita);
        free(*arvore);
        *arvore = NULL;
    }
}
//---------------------------//
// Remocao arvore binaria
//---------------------------//
bool removerElemento(PtrNoArvore *arvore, int x) {
    PtrNoArvore aux =  (*arvore);
// criterio de parada de recursao (fracasso)
// chegou aonde o elemento deveria existir
// mas ele nao existe,  logo nao tem o que remover
    if ((*arvore) == NULL)
        return false;

// criterio de parada de sucesso (achou)
    if ((*arvore)->chave == x){
    // caso 1 -> nao tem subarvore esquerda e tem subarvore direita
        if((*arvore)->esquerda == NULL && (*arvore)->direita != NULL){
            // no recebe o filho da direita do no
            (*arvore) = (*arvore)->direita;
        }
        if( (*arvore)->esquerda == NULL && (*arvore)->direita == NULL){
        // caso 2 -> folha (nao tem subarvore esquerda e nao tem subarvore direita)
        // no recebe null 
        (*arvore) = NULL;
        // ou no recebe filho da direita ou esquerda (pq sao null)
}
       if((*arvore)->direita == NULL && (*arvore)->esquerda != NULL){
       // caso 3 -> nao tem subarvore direita e tem subarvore esquerda
       // no recebe o filho esquerda do no
       (*arvore) = (*arvore)->esquerda;
     }
       else{
        // caso 4 -> tem subarvore direita e tem subarvore esquerda
        //  a) menor numero da subarvore direita
        //   getMinimumAux(&(*arvore)->direita)
        //  b) maior numero da subarvore esquerda 
        //   getMaximumAux(&(*arvore)->esquerda)
        // aux recebe a referncia do no que sera apagado

        aux = valorMaximoEsquerda(&(*arvore)->esquerda);
        (*arvore) = aux->chave;
       }
printf("Elemento %d removido com sucesso\n ", x);
free (aux);
return true;
} 

}

PtrNoArvore valorMaximoEsquerda(PtrNoArvore *arvore){
    PtrNoArvore ret;


    if ((*arvore) ->direita == NULL){
        ret = (*arvore);
        (*arvore) = (*arvore) -> esquerda;
        return ret;
    }
    return(valorMaximoEsquerda(&(*arvore)->direita));
}




