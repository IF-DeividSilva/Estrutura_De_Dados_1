/*
 * @file hash.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define M 13 

typedef struct obj {
    int info;
    char nome[100];
    /* data */
}Objeto;

typedef struct tabelahash {
    Objeto elem[M];
    int qtdeElem;
}TabelaHash;

void inicializarTabelaHash(TabelaHash *t){
    t->qtdeElem=0;
    for(int i=0; i<M; i++){
        t->elem[i].info = -1;
        strcpy(t->elem[i].nome, "");
    }
}

bool estaCheio(TabelaHash *t){
    return(t->qtdeElem>=M);
}

bool estaVazio(TabelaHash *t){
    return(t->qtdeElem==0);
}

void imprimirTabelaHash(TabelaHash *t){
    printf("\n\n=================================");
    printf("\n=====Tabela Hash (total =%d)=====", t->qtdeElem);
    printf("\n=================================");
    for(int i=0; i<M; i++){
        printf("\n[%d] \tinfo=%d nome=%s", i, t->elem[i].info, t->elem[i].nome);
    }
    printf("\n=================================");
}

int funcaoHash(int x){
    return x%M;
}

void insereElem(TabelaHash *t, int info, char nome[100]){
    int pos = funcaoHash(info);

    if(estaCheio(t)==true){
        printf("\n---> Impossivel inserir info=%d. Estah cheia!", pos);
        return;
    }

    while(t->elem[pos].info!=-1){
        pos++;
        if(pos>=M) pos=0;
    }

    t->qtdeElem++;
    t->elem[pos].info=info;
    strcpy(t->elem[pos].nome, nome);
}

int pesquisarElem(TabelaHash *t, int info){
    int pos = funcaoHash(info);
    if(estaVazio(t)==true) return(-1);

    while(t->elem[pos].info!=info){
        pos++;
        if(pos>=M) pos=0;
        if(pos == funcaoHash(info)) return(-1);
    }

    return pos;
}

void deletarElem(TabelaHash *t, int info){
    int pos = pesquisarElem(t, info);
    if(pos < 0){
        printf("\nImpossivel deletar info=%d. Nao estah na Tabela Hash.", info);
        return;
    }
    t->qtdeElem--;
    t->elem[pos].info=-1;
    strcpy(t->elem[pos].nome,"");
}

int main(void){
    TabelaHash tab;
    int pos;

    inicializarTabelaHash(&tab);

    insereElem(&tab, 100, "Mantovas");
    insereElem(&tab, 40, "Daniel");
    insereElem(&tab, 6, "Wendel");
    insereElem(&tab, 0, "Maumau");
    insereElem(&tab, 17, "Luiz");
    insereElem(&tab, 15, "Tamara");
    insereElem(&tab, 4, "Andre");
    insereElem(&tab, 25, "Murielis");
    insereElem(&tab, 63, "Fabio");
    insereElem(&tab, 48, "Adalberto");
    insereElem(&tab, 96, "Fernando");
    insereElem(&tab, 2, "Ricardo");

    imprimirTabelaHash(&tab);
    
    pos=pesquisarElem(&tab, 2);
    if(pos < 0) printf("\n Elemento nao presente na tabela hash");
    else printf("\n [%d] - info =%d nome %s", pos, tab.elem[pos].info, tab.elem[pos].nome);

    deletarElem(&tab, 2);

    imprimirTabelaHash(&tab);

    return 0;
}
