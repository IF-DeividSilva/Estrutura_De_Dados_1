/**
 * @file Atv_3-SistMercado.c
 * @author Eduardo Yuji Yoshida Yamada / Deivid da Silva Galvao (eduardoyuji@alunos.utfpr.edu.br/deivid.2002@alunos.utfpr.edu.br)
 * RAs 2320606/2408740
 * @brief 
 * Um supermercado precisa implementar um programa para auxiliar a administracao de seu
 * estoque, onde diversos paletes sao empilhados. O equipamento permite empilhar no maximo 4 paletes
 * em 5 locais. Elabore um programa em C implementando uma Pilha Estatica com o seguinte menu de
   programa:
   (a) Adicionar novo palete;
   (b) Remover palete;
   (c) Sair.
   
   Observacoes:
• Novos paletes devem ser colocados no local com a pilha mais baixa dispon ́ıvel;
• Ao se remover um palete, retirar do local com a pilha mais alta dispon ́ıvel;
• Em cada opera ̧c ̃ao (empilhar ou desempilhar) mostrar de qual local (pilha) esta manipulando.   

 * @version 0.1
 * @date 2022-09-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 20

typedef struct 
{
    int key;
    int quantidade;
    int topo;
    
}PilhaLocal;

typedef struct 
{
    int topo;
}PilhaEstoque;


int menu();
void inicializaPilha();
void empilhar();
bool EstoqueCheio();
bool EstoqueVazio();
int verificaPilhaMenor();
int verificaPilhaMaior();
int desempilha();
void imprimePilha();

int main(int argc, char const *argv[])
{
    PilhaLocal pilha[5];
    PilhaEstoque estoque;
   

    int escolha = 0;
    int indicePilha = 0;
    int n = 0 ;
    
    inicializaPilha(pilha, &estoque);   

// do while pra repetir caso o usuario digite um numero invalido
// switch case para verificar a escolha
    do
    {
        escolha = menu (n);

        switch (escolha)
        {
        case 1:
            indicePilha = verificaPilhaMenor(pilha);
            printf("O palete sera colocado no local [%d]", indicePilha);

            empilhar(pilha, indicePilha, &estoque);
            
            break;

        case 2:
            indicePilha = verificaPilhaMaior(pilha);  
            printf("O palete sera retirado do local [%d]", indicePilha);  
            desempilha(pilha, indicePilha, &estoque);

            break;

         case 3:
            printf("O programa sera encerrado...");

            break;     

        default:
            printf("Numero invalido digite novamente...");
            break;
        }
        
    } while (escolha != 3);
    
    
    return 0;
}//main

int menu(int esc){
    
    printf("\nBem vindo ao sistema\n");
    printf("Digite sua escolha: \n");
    printf(" [1] Adicionar novo palete\n [2] Remover palete \n [3] Sair\n");
    scanf("%d", &esc);
    fflush(stdin);

    return esc;
    
}

void inicializaPilha(PilhaLocal* p, PilhaEstoque* estoque){
    for (int i = 0; i < 5; i++)
    {
        p[i].topo = 0;
        p[i].quantidade = 0;
        estoque->topo = 0;
    }

}//inicializa

void empilhar(PilhaLocal p[], int i, PilhaEstoque* estoque){
    //verifica se esta cheia e exibe erro caso esteja
    if (EstoqueCheio(estoque) == false)
    {
    printf("\n Digite o codigo do palete: ");
    scanf("%d", &p[i].key);  
    fflush(stdin);

    p[i].topo++;    
    p[i].quantidade++;
    estoque->topo++;
    printf("%d",estoque->topo);
    }else{
        printf("\n O estoque esta cheio, nao eh possivel adicionar mais paletes...\n");
    }
}

bool EstoqueCheio (PilhaEstoque *estoque){
    return (estoque->topo == TAM);
}

int desempilha(PilhaLocal p[], int i, PilhaEstoque* estoque){
    int aux = -1;
    //se apilha nao estiver vazia
    printf("\n%d 1", estoque->topo);
    if(EstoqueVazio(estoque)==false){
    // variavel auxiliar recebe o elemento mais recente 
    aux = p[i].key;
    // decrementa o indice do topo
    p[i].topo--;
    // decrementa a quantidade de elementos
    p[i].quantidade--;  
    estoque->topo--; 
    }else{
        printf("Erro: nao eh possivel remover pois estah vazia..\n");
    }
    return(aux);
}

int verificaPilhaMenor(PilhaLocal p[]){
    // varios "for" para verificar o local com menos paletes e retornar o indice 
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 0)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 1)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 2)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 3)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 4)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 5)
        {
        return i;
        }
    }
     return-999;
}

bool EstoqueVazio (PilhaEstoque *e){
   // printf("\n %d 2", e->topo);
    return (e->topo == 0);
}

int verificaPilhaMaior(PilhaLocal p[]){
    // varios "for" para verificar o local com mais paletes e retornar o indice 
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 5)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 4)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 3)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 2)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 1)
        {
        return i;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (p[i].quantidade == 0)
        {
        return i;
        }
    }
    return-999; 
}

void imprimePilha(PilhaLocal p[], int j){
    printf("Pilha(Codigos dos paletes) = {");
    //for (percorre o vetor, imprimindo todas as posições ateh topo -1)
    int i;
    for ( i = 0; i < p[i].topo; i++)
    {
        printf(" %d ", p[i].key);
    }
    printf("}\n");
        printf("\nQuantidade: %d ", p[j].quantidade);
   
}