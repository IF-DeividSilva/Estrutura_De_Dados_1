/*
 * @file AP4
 * @author @author Deivid da Silva Galvao RA:2408740 // Joao Vitor Nakahodo Yoshida RA:2419904
 * @brief Atividade Pratica 4 [AVL]
 * @version 0.1
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/***************** STRUCTS ****************************/
typedef struct  noArvore
{
    char termo[200];
    char pagina[200];
    struct  noArvore* dir;
    struct  noArvore* esq;
    int altura;
}NoArvore;

/******************************************************/
/******************************************************/
//------- Funcoes -------/
NoArvore* incializaAvl();
bool estadoVazia(NoArvore** no);
void recebeArq(FILE *f, NoArvore** no);
void destroiAvl(NoArvore **no);
void menu(NoArvore **no);
void insereArvore(NoArvore **no, char termo[], char pagina[]);
int maxAlturaFilhos(NoArvore **no);
int altura(NoArvore **no);
void rotacaoEsq(NoArvore **no);
void rotacaoDir(NoArvore **no);
NoArvore* PesquisaTermo(NoArvore** no, char termo[]);
void imprimeEmOrdem(NoArvore **no);
/****************************************************/

int main(int argc, char const *argv[])
{
    // *************** TIRAR ********************** //
     argv[1] = "remissivo.xlsx";
    /***********************************************/

    //abrindo arquivo de entrada para leitura utilizando arv
    FILE *arq=fopen (argv[1], "r");

    //verifica erro na abertura do arquivo
    if(arq==NULL){
        printf("Erro encerrando...");
    return 1;
    }

    NoArvore * raiz = incializaAvl();

    while (!feof (arq))
    {
    recebeArq(arq, &raiz);
    }

    menu(&raiz);

    //fecha aquivo e libera a memoria alocada para a arvore
    fclose(arq);
    destroiAvl(&raiz);
    return 0;
}
// funcao que retorna null para inicializar a aarvore
NoArvore* incializaAvl(){
    return NULL;
}

// retorna se a arvore esta vazia
bool estaVazia(NoArvore** no){
    return((*no)==NULL);
}

//funcao para ler o arquivo de entrada e salvar nas respectivas variaveis
void recebeArq(FILE *arq, NoArvore** no){
    char termo[200];
    char pagina[200];
    
    fscanf(arq, "%s \t %s\n", termo, pagina);
    insereArvore(no, termo, pagina);
    
}
// funcao para fazer as insercoes
void insereArvore(NoArvore **no, char termo[], char pagina[]){
    // *NoArvore == Nulo (Ponto de inserir encontrado)
    if((*no)==NULL){
        // aloca memoria
        (*no)=(NoArvore*) malloc(sizeof(NoArvore));
        // copia a string da variavel pro no
        strcpy((*no)->termo,termo);
        strcpy((*no)->pagina,pagina);
        // o no direita e esquerda recebe null
        (*no)->dir=(*no)->esq=NULL;
        (*no)->altura=0;
        return;
    }
    // *NoArvore == termo retorna falso (pois ? um elemento repetido)
    if(strcasecmp((*no)->termo, termo) == 0){
        printf("\nElemento repetido");
        return;
    }

    // Casos recusirvos
    strcasecmp((*no)->termo, termo) > 0 ? insereArvore(&((*no)->esq),termo, pagina): insereArvore(&((*no)->dir), termo, pagina);
    (*no)->altura = maxAlturaFilhos(no) + 1;
    // se a subitracao das alturas for igual a 2 faz a rotacao para esquerda
    if(altura(&(*no)->dir) - altura(&(*no)->esq) == 2){
       rotacaoEsq(no);
    }
    // se a subitracao das alturas for igual a -2 faz a rotacao para direita
    else if(altura(&(*no)->dir) - altura(&(*no)->esq) == -2){
       rotacaoDir(no);
    }
}

//funcao recursiva para liberar memoria da AVL
void destroiAvl(NoArvore **no){
    if((*no)==NULL) return;
    destroiAvl(&((*no)->esq));
    destroiAvl(&((*no)->dir));
    free(*no);
    (*no)=NULL;
}

// funcao para retornar a altura maxima dos filhos
int maxAlturaFilhos(NoArvore **no){
    if((*no)->esq==NULL && (*no)->dir==NULL) return -1;
    if((*no)->esq==NULL) return (*no)->dir->altura;
    if((*no)->dir==NULL) return (*no)->esq->altura;
    return (*no)->dir->altura > (*no)->esq->altura ? (*no)->dir->altura : (*no)->esq->altura;
}
//funcao para retornar  a altura
int altura(NoArvore **no){
    if((*no)==NULL) return -1;
    return((*no)->altura);
}
// funcao para balancear a arvore para esquerda
void rotacaoEsq(NoArvore **no){
    NoArvore *aux = (*no)->dir;
    // filho direita de aux sera o alpha(esquerda do aux)
    (*no)->dir = aux->esq;
    // no esquerdo de aux se torna o NoArvore
    aux->esq = (*no);
    // controle de recursao
    (*no)=aux;
    // atualiza as alturas dos Nos de arvore
    (*no)->esq->altura = maxAlturaFilhos(&(*no)->esq) + 1;
    (*no)->altura = maxAlturaFilhos(no) + 1;
}
// funcao para balancear a arvore para direita
void rotacaoDir(NoArvore **no){
    NoArvore *aux = (*no)->esq;
    // filho esquerda de aux sera o alpha(direita do aux)
    (*no)->esq=aux->dir;
    // no direito de aux se torna o NoArvore
    aux->dir=(*no);
    // controle de recursao
    (*no)=aux;
    // atualiza as alturas dos Nos de arvore
    (*no)->dir->altura = maxAlturaFilhos(&(*no)->dir) + 1;
    (*no)->altura = maxAlturaFilhos(no) + 1;
}
// funcao para o menu
void menu(NoArvore **no){
    int escolha = 0;
    char novoTermo[200];
    char novaPagina[200];
    char pesquisa[200];
    NoArvore* aux1;

   printf("\n---- Bem Vindo ao sistema ----\n");
   do
   {
        printf("\n----- Menu  ----- \n");
        printf("\n[1] Inserir um novo termo \n");
        printf("[2] Pesquisar um termo \n");
        printf("[3] Mostrar todos os termos cadastrados \n");
        printf("[4] Sair \n");
        printf("\n----------------- \n");
        printf("Sua escolha: ");
        scanf("%d", &escolha);
        setbuf(stdin, NULL);
        if (escolha < 1 || escolha > 4)
            {
            printf("Numero digitado eh invalido...Digite novamente");
            }
        //switch para verificar a escolha do usuario    
        switch (escolha)
        {
            case 1:

                setbuf(stdin, NULL);
                printf("Digite o novo termo para ser inserido: ");
                fgets(novoTermo, 200, stdin);
                novoTermo[strcspn(novoTermo,"\n")]='\0';
                setbuf(stdin, NULL);

                printf("Digite a pagina: ");
                fgets(novaPagina, 200, stdin);
                novaPagina[strcspn(novaPagina,"\n")]='\0';
                setbuf(stdin, NULL);


                insereArvore(no, novoTermo, novaPagina);
                break;

            case 2:
        
                setbuf(stdin, NULL);
                printf("Digite o termo a ser pesquisado: ");
                fgets(pesquisa, 200, stdin);
                pesquisa[strcspn(pesquisa,"\n")]='\0';
                setbuf(stdin, NULL);

                PesquisaTermo(no, pesquisa);


                break;

            case 3:
                imprimeEmOrdem(no);
                break;

            case 4:
                printf("Encerrando...Adeus...");
                break;

            default:
                break;
        }
   } while (escolha != 4);
}
// funcao para a pesquisa de termos 
NoArvore* PesquisaTermo(NoArvore** no, char termo[]){
    //funcao recursiva para buscar um termo
    // se o no for nulo significa que o termo nao esta contido na arvore
    if(*no==NULL){
        printf("\nTermo nao encontrado...\n");
        return NULL;
    }
    // se o termo foi encontrado
    if(strcasecmp((*no)->termo, termo) == 0) {
        printf("---- Termo encontrado ----\n");
        printf("Termo = %s \n", (*no)->termo);
        printf("Pagina = %s\n", (*no)->pagina);
        return (*no);
    }
    // if para fazer a busca recursivamente at? entrar em algum dos ifs a cima
    if(strcasecmp((*no)->termo, termo) > 0) return PesquisaTermo(&(*no)->esq, termo);
    else return PesquisaTermo(&(*no)->dir, termo);
}

//funcao recursiva para imprimir os termos da arvore em ordem alfabetica
void imprimeEmOrdem(NoArvore **no){
    // se for o fim da arvore retorna 
    if(*no==NULL) return;
    //chama recursivamente a funcao de impressao passando o filho da esquerda
    imprimeEmOrdem(&((*no)->esq));
    //printa o elemento para o usuario
    printf("\n Termo {%s}, Pagina {%s}  ", (*no)->termo,(*no)->pagina);
    //chama recursivamente a funcao de impressao passando o filho da direita 
    imprimeEmOrdem(&((*no)->dir));
}