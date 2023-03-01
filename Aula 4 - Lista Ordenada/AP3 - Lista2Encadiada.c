/*
 * @file AP3 - Lista2Encadiada.c
 * @author Deivid da Silva Galvao
 * @brief 
 * 
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

//-------Structs---------//
typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

// NoLista* -> PtrNoLista
typedef struct NoLista * PtrNoLista;

typedef struct NoLista{
    int x;
    char nome[200];
    char sexo[5];
    Data nascimento;
    Data ultima_consulta;
    PtrNoLista proximo;
    PtrNoLista anterior;
} NoLista;


typedef struct{
 PtrNoLista inicio;
 PtrNoLista fim;
 int quantidadeElementos;


} ListaOrdenada;
//**************************************************





/*****************************************/
/*****************************************/
//------- Funcoes -------//

void iniciaLista(ListaOrdenada *lista);
bool estaVazia(ListaOrdenada *lista);
void lerArquivo(FILE *arq, ListaOrdenada * lista);
void insereLista(ListaOrdenada *lista, char nome, char sexo, int dia, int mes, int ano , int diaConsulta, int mesConsulta, int anoConsulta);
void escolhaPesquisar(ListaOrdenada * lista, int dia, int mes, int ano);
void menuPesquisa(char * nome);
void pesquisarLista(ListaOrdenada *lista, char nome, int dia, int mes, int ano);

void imprimeLista();
int  verificaIdade();
//void imprimeListaArq();
void escolhaInserir();
void escolhaPesquisar();
void menu();
/******************************************/



int main(int argc, char const *argv[])
{
    ListaOrdenada lista;
    int dia = 0;
    int mes = 0;
    int ano = 0;
    
    //O tipo de dados time_t para representar a data 
    time_t dataAtual;
    //A função localtime() recebe o tempo em segundos de uma variável do tipo time_t, 
    //converte para o tempo local, armazena os dados na sua estrutura e retorna um ponteiro para uma struct do tipo 
    //tm com os dados locais.
    dataAtual = time(NULL);
    struct tm atual = *localtime(&dataAtual);
    printf("Data: %d/%d/%d\n", atual.tm_mday, atual.tm_mon + 1, atual.tm_year + 1900);
    dia = atual.tm_mday;
    mes = atual.tm_mon + 1;
    ano = atual.tm_year + 1900;

    //abrindo arquivo de entrada para leitura **utilizando argv**
    FILE *arq=fopen("pacientes.txt", "r"); 

    //verifica erro na abertura do arquivo
    if(arq==NULL){
        printf("Erro encerrando...");
    return 1;          
    } 

    //abrindo arquivo de saida para escrita utilizando arv
    FILE *arq1 = fopen("arquivo_ginecologista", "w");

    //verifica erro na abertura do arquivo
    if(arq1==NULL){
        printf("Erro encerrando...");
    return 1;          
    } 

     //abrindo arquivo de saida para escrita utilizando arv
    FILE *arq2 = fopen("arquivo_andrologista", "w");

    //verifica erro na abertura do arquivo
    if(arq2==NULL){
        printf("Erro encerrando...");
    return 1;          
    } 

    iniciaLista(&lista);
    lerArquivo(arq, &lista);
    imprimeLista(&lista);

    escolhaPesquisar(&lista, dia , mes, ano);
    
    escolhaInserir(&lista);

   // imprimeListaArq(&lista, arq1, arq2);

    fclose(arq);
    fclose(arq1);
    fclose(arq2);
    return 0;
}

// inicializa a lista
void iniciaLista(ListaOrdenada *lista) {
// inicio e fim aponta pra NULL
    lista->inicio = NULL;
    lista->fim = NULL;
// contador = 0
    lista->quantidadeElementos = 0;
}

// funcao para ler o arquivo e salvar nas variavels da estrutura
void lerArquivo(FILE *fp, ListaOrdenada * lista){ //lê uma linha a cada chamada
    char linha[100];
    char* palavra;
    char nome[100];
    char sexo[5];
    int dia, mes, ano;
    int dia2, mes2, ano2;
    static int i=0;

    
    //Verifica se chegou no final do arquivo e se a leitura da linha foi feita com sucesso
   if (!feof(fp) && !fgets(linha, 100, fp))  {  
        printf("\n\nNao foi possível ler a linha");
        return;
    }
    
    //Como separador de informação temos os caracteres: "<>,/\n"
    
    //Salva nome
    palavra= strtok(linha,"<,"); 
    strcpy(nome, palavra);
    //Salva sexo
    palavra= strtok(linha,",");  
    strcpy(sexo, palavra);

    //Salva data nascimento (Dia)
    //***Converter para int//
    palavra= strtok(linha,",/");
    dia = atol (palavra);

    //Salva data (Mes)
    palavra= strtok(linha,"/");
    mes =atol (palavra);

    //Salva data (Ano)
    palavra= strtok(linha,"/,");
    ano =atol (palavra);

    //Salva data consulta (Dia)
    //***Converter para int//
    palavra= strtok(linha,",/");
    dia2 = atol (palavra);

    //Salva data (Mes)
    palavra= strtok(linha,"/");
    mes2 =atol (palavra);

    //Salva data (Ano)
    palavra= strtok(linha,">/");
    ano2 =atol (palavra);
    
    insereLista(lista, nome, sexo, dia, mes, ano, dia2, mes2, ano2);
    printf("pacientes.txt");

}

// verifica se a lista esta vazia
bool estaVazia(ListaOrdenada *lista){
    return(lista->quantidadeElementos==0);
}

// funcao para inserir um novo elemento na lista em ordem alfabetica
void insereLista(ListaOrdenada *lista, char nome, char sexo, int dia, int mes, int ano , int diaConsulta, int mesConsulta, int anoConsulta){
    // criar um novo nó, alocar memoria para ele
    PtrNoLista novo = (PtrNoLista)malloc(sizeof(NoLista));
    PtrNoLista aux=lista->inicio;

    // copiar informação para novo nó
    strcpy(novo->nome, nome);
    printf("pacientes.txt");
    strcpy(novo->sexo, sexo);
    novo->nascimento.dia = dia;
    novo->nascimento.mes = mes;
    novo->nascimento.ano = ano;

    // caso esteja vazio
    if(estaVazia(lista)==true){
        // o novo proximo aponta para o inicio 
        novo->proximo=lista->inicio;
        // o novo anterior aponta para o fim (NULL no caso) 
        novo->anterior = lista->fim;
        // o inicio e o fim recebem o novo(pois tem apenas 1 elemento)
        lista->inicio = novo;
        lista->fim = novo;

    //caso tenha que inserir o novo nome no inicio
    if(strcmp(lista->inicio->nome, novo->nome)==-1){
        // o novo proximo aponta o inicio da lista
        novo->proximo=lista->inicio;
        // o novo anterior aponta para null 
        novo->anterior = NULL;
        // o inicio lista recebe o novo
        lista->inicio = novo;
        // o inicio anterior aponta para o novo
        lista->inicio->anterior = novo;
    }
    // caso  tenha que percorrer a lista para inserir
    }else{
        // auxiliar para poder percorre a lista e encontrar a posicao de insersao
        PtrNoLista aux;
        aux = lista->inicio;
        //while somente para percorrer a lista
        while(aux->proximo!=NULL && strcmp(aux->proximo->nome, novo->nome) > 0) 
        aux=aux->proximo;
    }   
    // como saiu do while significa que o ponto de insecao foi encontrado
    //proximo do novo aponta o proximo do auxiliar
    novo->proximo = aux->proximo;
    //proximo do auxiliar aponta para o novo
    aux->proximo = novo;
    // o anterior do proximo do auxiliar aponta para o novo
    aux->proximo->anterior = novo;
    // o novo anterior aponta para o aux
    novo->anterior = aux;
    //** nesse caso esse else tambem funciona para caso a insersao seja no fim da lista
    lista->quantidadeElementos++;
}

// impressao/ visualizacao ( estado interno)
void imprimeLista(ListaOrdenada *lista){
    PtrNoLista percorre;
    for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo)
    {// imprimir o no corrente
    printf("%s , %s , nascimento: %d/%d/%d, consulta: %d/%d/%d  \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );
    }
    
}

// funcao para realizar a pesquisa do nome digitado pelo usuario 
void pesquisarLista(ListaOrdenada *lista, char nome, int dia, int mes, int ano){
  PtrNoLista aux;
  if (estaVazia(lista)) {
    printf("Erro... Lista a estah vazia... \n");
  }
  while ( aux != NULL && strcmp(lista->inicio->nome, nome)!=-1){
  aux = aux->proximo;
  } 
  // posicao onde o elemento deveria existir
  // (aux)
  // nao existe
  if(aux == NULL || strcmp(lista->inicio->nome, nome) > -1 ) printf(" Nome não encontrado...\n");
  printf("Nome: %s\n", nome);
  printf("Sexo: %s\n", aux->sexo);
  printf("Idade: %d anos\n", idade(aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano, dia, mes, ano));
 // fazer funcao que calcula a quantos dias foi a ultima consulta
 //printf("A ultima consulta foi a %d dias\n");
}

// Funcao que calcula a idade da pessoa
int verificaIdade(int diaNascimento, int mesNascimento, int anoNascimento, int diaAtual, int mesAtual, int anoAtual) {
  int idade = 0;
  // verifica se o mes atual eh maior o igual ao mes de nascimento e se o dia atual eh maior ou igual o dia de nascimento
  if (mesAtual >= mesNascimento && diaAtual >= diaNascimento) {
    idade = anoAtual - anoNascimento;
  }
  else {
    idade = anoAtual - anoNascimento - 1;
  }

  return;
}

/*// funcao para preencher os arquivos de saida dos dois medicos
void imprimeListaArq(ListaOrdenada *lista, FILE *arq1, FILE* arq2){
    PtrNoLista percorre;
    //percorre recebe o inicio e enquanto ele for diferente de NULL(fim da lista) ele recebe o proximo nó
    for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo)
    {// escrevendo o arquivo de saida do ginecologiste A-Z
    fprintf(arq1,"< %s , %s , nascimento: %d/%d/%d, ultima consulta: %d/%d/%d > \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );
    }

    for(percorre = lista->fim; percorre != NULL; percorre = percorre->anterior)
    {// escrevendo o arquivo de saida do andrologista Z-A
    printf(arq2,"< %s , %s , nascimento: %d/%d/%d, ultima consulta: %d/%d/%d > \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );
    }
}
*/
// Funcao para pegar do usuario o nome para ser feita a pesquisa
void menuPesquisa(char * nome){
    printf("Digite o nome a ser pesquisado: ");
    fgets(nome, 200, stdin);
    nome[strcspn(nome,"\n")]='\0';
    setbuf(stdin, NULL);
    return;
}

void escolhaInserir(ListaOrdenada* lista){
    int escolha = 0;
    char nome[200];
    char sexo[1];
    int diaNascimento = 0;
    int mesNascimento = 0;
    int anoNascimento = 0;
    int diaUltima_consulta = 0;
    int mesUltima_consulta = 0;
    int anoUltima_consulta = 0;

    do
    {
        printf("Deseja inserir manualmente um novo cadastro?");
        printf("[1] Sim");
        printf("[0] Nao");
        scanf("%d", &escolha);
         if(escolha < 1)
        {
            printf("Escolha invalida digite novemente... \n");
        }
        if(escolha == 1){
            printf("Digite o nome: ");
            fgets(nome, 200, stdin);
            nome[strcspn(nome,"\n")]='\0';
            setbuf(stdin, NULL);
            printf("Digite o sexo: ");
            fgets(sexo, 1, stdin);
            sexo[strcspn(sexo,"\n")]='\0';
            setbuf(stdin, NULL);
            printf("Digite o dia de nascimento");
            scanf("%d", &diaNascimento);
            printf("Digite o mes de nascimento");
            scanf("%d", &mesNascimento);
            printf("Digite o ano de nascimento");
            scanf("%d", &anoNascimento);
            printf("Digite o dia da ultima consulta");
            scanf("%d", &diaUltima_consulta);
            printf("Digite o mes da ultima consulta");
            scanf("%d", &mesUltima_consulta);
            printf("Digite o ano da ultima consulta");
            scanf("%d", &anoUltima_consulta);

            insereLista(lista, nome, sexo, diaNascimento, mesNascimento, anoNascimento, diaUltima_consulta, mesUltima_consulta, anoUltima_consulta);
        }

    } while (escolha != 0); 
}

void escolhaPesquisar(ListaOrdenada * lista, int dia, int mes, int ano){
    char nome[200];
    int escolha = 0;
    do
    {   
        printf("Deseja realizar uma pesquisa? \n");
        printf("[1] Sim");
        printf("[0] Nao");
        scanf("%d", &escolha);
        menuPesquisa(&nome);
        pesquisarLista(&lista, nome, dia, mes, ano);
        if(escolha < 1)
        {
            printf("Escolha invalida digite novemente... \n");
        }
    } while (escolha != 0);

}

