/**
 * @file AP2-Fila.c
 * @author Deivid da Silva Galvao, 2408740
 * @brief atividade 2, sobre filas
 * @version 0.1
 * @date 2022-09-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define Tam 10
#define Total 21 //definindo total pq o if para verificar EOF nao estava funcionado

//-------Structs---------//
// Nofila * ptrNofila
typedef struct NoFila *PtrNoFila;
typedef struct NoFila2 *PtrNoFila2;

typedef struct obj{
    char chave[200];
}Objeto;

typedef struct{
    Objeto elemento[100];
    int inicio;
    int fim;
    int quantidadeElementos;

}FilaEstatica;

typedef struct NoFila{
    //informacoes
    char chave[200];
    PtrNoFila proximo;  //ptr (proximo)
}NoFila;

typedef struct{
    PtrNoFila inicio; // ptr para o primeiro elemento
    PtrNoFila fim; // ptr para o ultimo elemento
    int quantidadeElementos;
}FilaDinamica;

/*****************************************/
/*****************************************/
//------- Funcoes -------//

void inicializaEstatica();
void inicializaDinamica();
void desenfileiraEstatica();
void enfileiraFilaEstatica();
void enfileiraFilaDinamica();
bool estaCheia();
int verificaVisita();
int incrementaIndice();
bool estaVazia();
int recebeArq();
void imprimeFila();
void imprimeFilaDinamica();
bool estaVaziaDinamica();
int verificaAlerta ();
void destroiFilaDin();

/*****************************************/
/*****************************************/

 int main(int argc, char const *argv[])
 {
    FilaEstatica iniciais;
    FilaDinamica concretizadas;
    FilaDinamica naoConcretizadas;
    int i = 0, n = 1, j = 0; 
    int fimArq = 0;
    int escolha = 0;
    //inicializa as filas 
    inicializaEstatica(&iniciais);
    inicializaDinamica(&concretizadas);
    inicializaDinamica(&naoConcretizadas);

    //Funcao para manipular o arquivo de entrada e enfileirar as informacoes na fila
    recebeArq(argc, argv, &iniciais, n, fimArq);
    n++;// n para verificar se é a primeira vez que a funcao eh chamada

    for ( i = 0; i < Tam; i++)
    {
    printf("\n A visita na casa { %s foi concretizada?", iniciais.elemento[i].chave);
    //retorna a escolha do usuario por meio de funcao de verificacao
    escolha = verificaVisita();

        if (escolha == 1)
        {
         // caso tenha sido concretizada chama a funcao enfileiraFilaDinamica e enfileira na fila de concretizadas
         enfileiraFilaDinamica(&concretizadas, &iniciais, i); 
         //printf("\nConcretizada\n");teste
         }else{

        /* caso nao tenha sido concretizada chama a funcao enfileiraFilaDinamica e 
         enfileira na fila de nao concretizadas*/ 
        enfileiraFilaDinamica(&naoConcretizadas, &iniciais, i); 
       // printf("\nNão concretizada\n");teste
        }
    }

    while(concretizadas.quantidadeElementos != Tam && (concretizadas.quantidadeElementos+ naoConcretizadas.quantidadeElementos) != Total)
    {   
        if (j == (Tam)) j = 0;
       //printf("\n concretizadas : %i \n", concretizadas.quantidadeElementos); teste
       fimArq = concretizadas.quantidadeElementos + naoConcretizadas.quantidadeElementos;
       recebeArq(argc, argv, &iniciais, n, fimArq); 
       
    printf("\n A visita na casa { %s \n foi concretizada?", iniciais.elemento[j].chave);
//retorna a escolha do usuario por meio de funcao de verificacao
    escolha = verificaVisita();
    if (escolha == 1)
    {
// caso tenha sido concretizada chama a funcao enfileiraFilaDinamica e enfileira na fila de concretizadas
        enfileiraFilaDinamica(&concretizadas, &iniciais, j); 
    }else{
 // caso nao tenha sido concretizada chama a funcao enfileiraFilaDinamica e enfileira na fila de nao concretizadas 
        enfileiraFilaDinamica(&naoConcretizadas, &iniciais, j);    
    }  
    j++;

    }
    n=1;// restando o n para verificar se é a primeira chamada da funcao
    if (concretizadas.quantidadeElementos != Tam)
    {
        printf("!! Alerta[A meta de 10 casas não foi atingida]");
        //imprime as informacoes no arquivo
        imprimeFilaDinamica(argc, argv, &naoConcretizadas, n); 
        n++;//n++ para indicar que eh a segunda chamada da funcao
        imprimeFilaDinamica(argc, argv, &concretizadas, n);
    }else{
        //imprime as informacoes no arquivo
        imprimeFilaDinamica(argc, argv, &naoConcretizadas, n); 
        n++;//n++ para indicar que eh a segunda chamada da funcao
        imprimeFilaDinamica(argc, argv, &concretizadas, n);
    }
    destroiFilaDin(&concretizadas);
    destroiFilaDin(&naoConcretizadas);
    //printf("\n gg");teste
    return 0;
}

int recebeArq(int argc, char const *argv[],FilaEstatica* fe, int n, int eof){
    static FILE *arq1;
    char c;
    char linha[200];
    int contador = 0;
    
     if (n == 1)
    {
    //Abrir arquivo
    arq1 = fopen (argv[1], "r");
    
        //Verifica se abriu corretamente
        if (arq1 == NULL)
        {
        printf("Erro na abertura do arquivo...encerrando...");
        exit(1);
         }//if arqv

    while ((c = fgetc(arq1) == '{') && contador != 10 ) {
      //  printf("%s", linha); teste
        fgets(linha,200,arq1);//salva a linha
        enfileiraFilaEstatica(fe, linha);//enfileira a string na fila
        contador++;
    }//while
            if (contador == 10){
            fseek(arq1, -1, SEEK_CUR);
            return 0;
            }   

    }else{
         while ((c = fgetc(arq1) == '{') && contador != 10 ) {
         // if  para verificar se a fila esta cheia
        if (estaCheia(fe) == true){
          //printf("%s", linha);teste
          fgets(linha,200,arq1);//salva a linha
          desenfileiraEstatica(fe);    
          enfileiraFilaEstatica(fe, linha);//enfileira a string na fila
         }
               //  if (c == EOF){//tentei usar o EOF mais nao estva funcionado...
               /*
                 fclose(arq1);
                 printf("EOF\n");
                 return 1;
                 }*/ 
        contador++;
    }//while
    }if(contador == 10){
        fseek(arq1, -1, SEEK_CUR);//volta uma posicao 
        return 0;
    }
    if (eof == Total)
    {
    fclose(arq1);  //fecha o arquivo  
    return 0;
    }
    
  }//recebe arq1

 void inicializaEstatica(FilaEstatica* fila){
    //inicializa fila estatica
    fila->quantidadeElementos = 0;
    fila->inicio = 0;
    fila->fim = -1;

 }//inicializa

 void inicializaDinamica(FilaDinamica *fila){
    //inicializa fila dinamica
    fila->quantidadeElementos = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
 }
 
 bool estaCheia(FilaEstatica* fila){
    // contador == tamanho
    return(fila->quantidadeElementos ==  Tam);
 }

 void enfileiraFilaEstatica(FilaEstatica* fila, char x[]){
     // Só pode inserir se a fila nao estiver cheia
        if(estaVazia(fila) == true){
        //coloca os ponteiros de fim e inicio na posicao zero da fila
        fila->fim = 0;
        fila->inicio = 0;
        //atribui o elemento na posicao indicada pelo fim(array)
        strcpy(fila->elemento[0].chave, x);
        // incrementa a quantidade de elementos
        fila->quantidadeElementos++;
        return;
        }
    if (estaCheia(fila) == true){
       // printf("Erro, fila cheia");
        return;
    } else {
         //incrementa o fim
        fila->fim = incrementaIndice(fila->fim);
        //atribui o elemento na posicao indicada pelo fim(array)
        strcpy(fila->elemento[fila->fim].chave, x);
        // incrementa a quantidade de elementos
        fila->quantidadeElementos++;
        return;
    }
 }

void enfileiraFilaDinamica(FilaDinamica * fila, FilaEstatica * filaEstatica, int indice) {
//   criar uma variavel auxiliar (NoFila)
    PtrNoFila aux;
//   alocar a memoria para esse nó
    aux = (PtrNoFila)malloc(sizeof(NoFila));
//   copiar as informaçoes para o novo nó
     strcpy(aux->chave,filaEstatica->elemento[indice].chave);
//(case) -> primeira insercao (Atualiza tanto o inicio quanto o fim)
if (estaVaziaDinamica(fila) == true)
{
//   inicio e fim apontam para o novo nó
    fila->inicio = aux;
    fila->fim = aux;
//   proximo do novo nó aponta para nulo
    aux->proximo = NULL;
}else{
//(case) -> nao é primeira inserção (Atualiza somente o fim)
//   proximo do novo nó = NULL (proximo do fim)
    aux->proximo = fila->fim->proximo;
//   o proximo do fim aponta para o novo elemento (aux)
    fila->fim->proximo = aux;
//   o fim recebe o proximo de fim (fim-> aux)
    fila->fim = fila->fim->proximo;
}
//   incrementa quantidade de elementos
     fila->quantidadeElementos++;
}

int verificaVisita(){
    int escolha = 0;
    //do while pra enquanto o usuario nao digitar um numero valido (diacordo com o menu) ele repetir o menu
    do
    {
        
    printf("\n[1] Se a visita foi concretizada.\n");
    printf("\n[2] Se a visita foi nao foi concretizada.\n");
    scanf("%d", &escolha);
    if (escolha != 1 && escolha != 2)
        printf(" Erro de digitacao...tente novamente...");
    } while (escolha != 1 && escolha != 2);

    return escolha;
}// verificaVisita

int incrementaIndice(int i){
    int valor = (i+1) % Tam;
    return valor;
}

bool estaVazia(FilaEstatica *fila){
    // contador == 0
    return(fila->quantidadeElementos == 0);
}

bool estaVaziaDinamica(FilaDinamica *fila){
    // contador == 0
    return(fila->quantidadeElementos == 0);
}
 
void imprimeFila(FilaEstatica *fila){
// ----So pra testes------
    printf("Fila = {");
    //for 0 a tamanho -1
    int i;
    int n = Tam;
    for ( i = 0; i < n; i++)
    {
        printf("\n");
        int indice = (fila->inicio + i) % Tam;
        printf(" %s ", fila->elemento[indice].chave);
    }
    
    printf("}\n");
}

void desenfileiraEstatica(FilaEstatica *fila){
    // Só pode remover se a fila nao estiver vazia
    if (estaVazia(fila) == false)
    {
    // Incrementa a posicao do inicio
        fila->inicio = incrementaIndice(fila->inicio);
    // Decrementa a quantidade de elementos
        fila->quantidadeElementos--;
    }
}

void imprimeFilaDinamica(int argc, char const *argv[],FilaDinamica *fila, int n){
    static FILE *arq2;
    PtrNoFila ptr;
    ptr = fila->inicio;
    int verifica = 0;
    // verifica se eh a primeira chamada da funcao
     if (n == 1)
    {
    //Abrir arquivo
    arq2 = fopen (argv[2], "w");
    
        //Verifica se abriu corretamente
        if (arq2 == NULL)
        {
        printf("Erro na abertura do arquivo...encerrando...");
        exit(1);
            }
    fprintf(arq2 ,"---- Não Concretizadas ----\n");    
    //enquanto o ponteiro nao for nulo
    while (ptr != NULL)
    {
    // salvar a string no arq2
        fprintf(arq2 ,"{ %s", ptr->chave);
    // ponteiro aponta para o proximo
        ptr = ptr->proximo;
    }
     }
    if (n == 2){//else
    fprintf(arq2 ,"\n---- Concretizadas ----\n");    
    //enquanto o ponteiro nao for nulo
      while (ptr != NULL)
    {
        // salvar a string no arq2
        fprintf(arq2 ,"{ %s", ptr->chave);
        // ponteiro aponta para o proximo
        ptr = ptr->proximo;
    }
        // verifica qual messagen deve ser impressa na ultima linha
        if (verificaAlerta(fila) == 0)
        {
        fprintf(arq2,"\n!! Alerta [A meta de 10 casas não foi atingida!] ");
        }else{
        fprintf(arq2,"\n!! Alerta [A meta de 10 casas foi atingida com sucesso!] ");
        }
        fclose(arq2);//fecha arq2
    }
}

int verificaAlerta(FilaDinamica *fila){
    //funcao para verificar qual alerta deve ser exibido
    if (fila->quantidadeElementos == Tam)
    {
        return 1;
    }else return 0;   
}

void desenfileiraDinamica(FilaDinamica *fila){
    // nao pode remover se a fila estiver vazia
    if (estaVazia(fila)== false)
    {
    // ptr auxiliar(aux)
    PtrNoFila aux;
    // aux recebe o inicio da fila
    aux = fila->inicio;
    // atualizar o inicio para proximo dele
    fila->inicio = fila->inicio->proximo;
    // desalocar memoria aux
    free(aux);
    // decrementar a quantidade de elemento
    fila->quantidadeElementos--;

    }
}

void destroiFilaDin(FilaDinamica *fila){
    // funcao para destroir fila dinamica
    while (estaVaziaDinamica(fila) != true)
    {
        desenfileiraDinamica(fila);
    }      
}






