/**
 * @file Lista.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//**************************************************
// Tipos necessarios para a implementacao de lista estrategica(singularmente encadeada)
//**************************************************
// NoLista* -> PtrNoLista
typedef struct NoLista * PtrNoLista;
//1 NoLista(int, PtrNoLista)
typedef struct NoLista{
    int x;
    PtrNoLista proximo;
} NoLista;
//2 Lista(PtrNoLista -> inicio, quantidade de elementos)
typedef struct{
 PtrNoLista inicio;
 int quantidadeElementos;


} ListaOrdenada;
//**************************************************

// Metodos / Funcoes que manipulam a lista
//- inicializacao
void iniciaLista(ListaOrdenada *lista) {
// inicio -> NULL
    lista->inicio = NULL;
// contador = 0
    lista->quantidadeElementos = 0;
}

//- estaVazia
bool estaVazia(ListaOrdenada *lista) {
//return (inicio == NULL) OU return (contador  == 0)
return (lista->inicio == NULL);
}

//- retorna quantidade de elementos
int tamanhoLista(ListaOrdenada *lista){
//return(contador)
return (lista->quantidadeElementos);
}

bool pesquisarLista(ListaOrdenada *lista, int x){
  PtrNoLista aux;
  if (estaVazia(lista)) return false;
  while ( aux != NULL && x > aux->x){
  aux = aux->proximo;
  } 
  // posicao onde o elemento deveria existir
  // (aux)
  // nao existe
  if(aux == NULL || aux->x > x) return false;
  return true;
}

// impressao/ visualizacao ( estado interno)
void imprimeLista(ListaOrdenada *lista){
    PtrNoLista percorre;
    printf("Lista = {");
    for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo)
    {// imprimir o no corrente
    printf("%d ", percorre->x);
    }
    printf("}\n");
}

// insersao
void inserirLista(ListaOrdenada *lista, int x){
// criar um novo nó, aloca memoria para ele
PtrNoLista novo = (PtrNoLista)malloc(sizeof(NoLista));
// copiar informação para novo nó
novo->x = x;

if (estaVazia(lista) || x < lista->inicio->x)
{
// 1 - Primeira insersao ou x menor que o primeiro elemento
// proximo do novo nó aponta para nulo
printf("eh primeira insercao ou eh menor que o primeiro elemento\n");
novo->proximo = lista->inicio; //NULL ou primeiro elemento que ja existia
// inicio aponta para o novo nó
lista->inicio = novo;
    
}else{
// 2 - Segunda insersao
printf("Percorrendo e inserindo\n");
PtrNoLista aux;
// 2 ponteiros -> (novo) -> (aux)
// aux vai percorrer e encontrar a posicao de insercao
// aux = inicio
aux = lista->inicio;
while (aux->proximo != NULL && x > aux->proximo->x){
    aux = aux->proximo;
}
// achou o ponto de insercao(aux->proximo)

// Lista [ ...aux ,...] - antes
//proximo do novo aponta aux->proximo 
novo->proximo = aux->proximo;
//proximo do auxiliar aponta para o novo
aux->proximo = novo;
// lista [ ...aux , novo ...]
}
// incrementar contador em +1
lista->quantidadeElementos++;
}

// remover 
// revover(lista, numero)
// lista = {0 2 2 3 5 50}

bool removeLista(ListaOrdenada *lista, int numero){
// numero nao existe na lista

// caso 1 / a caso 2
// lista vazia
if (estaVazia(lista)){ 
    printf("\nNao pode remover, pois a lista estah vazia.\n");
    return false;
}if (numero < lista->inicio->x){
    printf("\nNao pode remover, pois o elemento eh menor que o inicial");
}

// caso 3 --> elemento for o primeiro
    if (numero == lista->inicio->x){
    // aux recebe o inicio
    PtrNoLista aux = lista->inicio;
    // inicio aponta para o inicio proxim
    lista->inicio = lista->inicio->proximo;
    // libera a memoria (free)
    free(aux);
    // decrementa a quantidade de elementos
    lista->quantidadeElementos--;
    return true;
    }

// caso 4 / 5 --> se nao for o primeiro elemento (intermediario/ ultimo)
    //percorrer a lista e verificar se ele existe parando uma posicao antes
    // encontrou (remover, return true)
    // nao encontrou ( nao remove, return false)
    PtrNoLista percorre;
    percorre = lista->inicio;

    //enquanto o proximo de percorre for diferente de nulo e a chave do proximo do percorre for menor que o numero
    while ( percorre->proximo != NULL && numero > percorre->proximo->x){
        percorre = percorre->proximo;
    }
    //premissa: ponto de remocao do elemento
    //percorre = NULL (xxxxxxxx)
    //percorre proximo chave > numero (xxxxxxxxx)
    if ( percorre->proximo == NULL || numero < percorre->proximo->x){
        printf("\nElemento nao existe na lista\n");
        return false;
    }

    /* Percorri a lista e encontrei por exclusao 
*/
  //  Ponteiro auxiliar
  PtrNoLista aux; 
  //  auxiliar apontar para o proximo do percorre
  aux = percorre->proximo;
  //  proximo do percorre recebe o proximo do aux
  percorre->proximo = aux->proximo;
  //  free(aux)
  free(aux);
  //  decrementar quantidade de elemento
  lista->quantidadeElementos--;
  return true;  
}

int main(int argc, char const *argv[])
{
    ListaOrdenada lista;
    iniciaLista(&lista);

    if (estaVazia(&lista)){
        printf("Informacional vaziazinha\n");
    }
    int tam = tamanhoLista(&lista);
    printf("tamanho = %d", tam);
    imprimeLista(&lista);
    inserirLista(&lista, 1);
    // lista = {1}; #vazia
    imprimeLista(&lista);
    inserirLista(&lista, 3);
    // lista {1,3}; percorrendo e inserindo
    imprimeLista(&lista);
    inserirLista(&lista, 2);
    // lista {1,2,3}; percorrendo e inserindo
    imprimeLista(&lista);
    inserirLista(&lista, 80);
    // lista {1,2,3,80}; percorrendo e inserindo
    imprimeLista(&lista);
    printf("tamanho = %d", tam = tamanhoLista(&lista));

    removeLista(&lista, 80);

    imprimeLista(&lista);
    printf("tamanho = %d", tam = tamanhoLista(&lista));

    if(pesquisarLista(&lista, 1 )) printf("Elemento encontrado\n");
    else{
        printf("Nao Elemento encontrado");
    }
     if(pesquisarLista(&lista, 99 )) printf("Elemento encontrado\n");
   else { 
    printf("Nao Elemento encontrado");
   }
    return 0;
}
