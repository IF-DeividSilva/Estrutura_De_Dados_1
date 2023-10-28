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
    char sexo[2];
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
void insereLista(ListaOrdenada* lista, PtrNoLista novo);
void pesquisarLista(ListaOrdenada *lista, int dia, int mes, int ano);
void menu(ListaOrdenada* lista,int dia, int mes, int ano);
int verificaIdade(int diaNascimento, int mesNascimento, int anoNascimento, int diaAtual, int mesAtual, int anoAtual);
void inserir(ListaOrdenada* lista);
void imprimeListaArq(ListaOrdenada *lista, FILE *arq1, FILE* arq2);
int verificaConsulta(int diaConsulta, int mesConsulta, int anoConsulta, int diaAtual, int mesAtual, int anoAtual);

/******************************************/

int main(int argc, char const *argv[]){
    // *************** TIRAR ********************** //
    argv[1] = "pacientes.txt";
    argv[2] = "arquivo_andrologista.txt";
    argv[3] = "arquivo_ginecologista.txt";
    /***********************************************/

    ListaOrdenada lista;
    int dia = 0;
    int mes = 0;
    int ano = 0;

   /* //O tipo de dados time_t para representar a data
    time_t dataAtual;
    //A função localtime() recebe o tempo em segundos de uma variável do tipo time_t,
    //converte para o tempo local, armazena os dados na sua estrutura e retorna um ponteiro para uma struct do tipo
    //tm com os dados locais.
    dataAtual = time(NULL);
    struct tm atual = *localtime(&dataAtual);
     //printf("Data: %d/%d/%d\n", atual.tm_mday, atual.tm_mon + 1, atual.tm_year + 1900);
 */
    dia = 25 ;//atual.tm_mday;
    mes = 10 ;//atual.tm_mon + 1;
    ano = 2022; //atual.tm_year + 1900;

    //abrindo arquivo de entrada para leitura utilizando arv
    FILE *arq=fopen (argv[1], "r");
 
    //verifica erro na abertura do arquivo
    if(arq==NULL){
        printf("Erro encerrando...");
    return 1;
    }
 
    //abrindo arquivo de saida para escrita utilizando arv
    FILE *arq1 = fopen(argv[2], "w");

    //verifica erro na abertura do arquivo
    if(arq1==NULL){
        printf("Erro encerrando...");
    return 1;
    }

     //abrindo arquivo de saida para escrita utilizando arv
    FILE *arq2 = fopen(argv[3], "w");
 
    //verifica erro na abertura do arquivo
    if(arq2==NULL){
        printf("Erro encerrando...");
    return 1;
    }
    iniciaLista(&lista);

    while(!feof (arq)){
    lerArquivo(arq, &lista);
    }
    menu(&lista, dia, mes, ano);

    imprimeListaArq(&lista, arq1, arq2);

    //fecha os arquivos
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

// verifica se a lista esta vazia
bool estaVazia(ListaOrdenada *lista){
    return(lista->quantidadeElementos==0);
}

// funcao para ler o arquivo e salvar nas variavels da estrutura
void lerArquivo(FILE *arq, ListaOrdenada * lista){ //lê uma linha a cada chamada
    char linha[100];
    char c;
    char nome[200];
    char sexo[2];
    int dia, mes, ano;
    int dia2, mes2, ano2;
    char * palavra;

   //Verifica se chegou no final do arquivo e se a leitura da linha foi feita com sucesso
   if (!feof(arq) && !fgets(linha, 100, arq))  {
        printf("\n\nNao foi possível ler a linha");
        return;
    }
     // criar um novo nó, alocar memoria para ele
    PtrNoLista novo = (PtrNoLista)malloc(sizeof(NoLista));

    //Como separador de informação temos os caracteres: "<>,/\n"

    //Salva nome
    palavra= strtok(linha,",");
    strcpy(novo->nome, palavra);
    //Salva sexo
    palavra= strtok(NULL,",");
    strcpy(novo->sexo, palavra);

    //Salva data nascimento (Dia)
    //***Converter para int//
    palavra= strtok(NULL,"/");
    novo->nascimento.dia = atol (palavra);

    //Salva data (Mes)
    palavra= strtok(NULL,"/");
    novo->nascimento.mes =atol (palavra);

    //Salva data (Ano)
    palavra= strtok(NULL,",");
    novo->nascimento.ano =atol (palavra);
    //printf("\n %d \n", novo->nascimento.ano );

    //Salva data consulta (Dia)
    //***Converter para int//
    palavra= strtok(NULL,"/");
    novo->ultima_consulta.dia = atol (palavra);

    //Salva data (Mes)
    palavra= strtok(NULL,"/");
    novo->ultima_consulta.mes = atol (palavra);

    //Salva data (Ano)
    palavra= strtok(NULL,">");
    novo->ultima_consulta.ano = atol (palavra);
    //printf("\n %d \n", novo->ultima_consulta.ano );

    insereLista(lista, novo);

}

// funcao para inserir o no de lista na lista
void insereLista(ListaOrdenada* lista, PtrNoLista novo)
{
    PtrNoLista aux = (PtrNoLista)malloc(sizeof(NoLista));
    PtrNoLista aux2;
    // caso esteja vazio
    if(estaVazia(lista)== true){
        // o novo proximo aponta para NULL
        novo->proximo= NULL;
        // o novo anterior aponta para NULL
        novo->anterior = NULL;
        // o inicio e o fim recebem o novo(pois tem apenas 1 elemento)
        lista->inicio = novo;
        //lista->fim = novo;
        lista->quantidadeElementos++;
        return;
    }
    //caso tenha que inserir o novo nome no inicio
    if(strcmp(lista->inicio->nome, novo->nome) > 0)
    {
        printf("%s \n", novo->nome);
        // o novo proximo aponta o inicio da lista
        novo->proximo=lista->inicio;
        // o novo anterior aponta para null
        novo->anterior = NULL;
        // o inicio anterior aponta para o novo
        lista->inicio->anterior = novo;
        // o inicio lista recebe o novo
        lista->inicio = novo;

        lista->quantidadeElementos++;
        return;

    // caso  tenha que percorrer a lista para inserir
    }else{
        // auxiliar para poder percorre a lista e encontrar a posicao de insersao
        PtrNoLista aux;
        aux = lista->inicio;
        //while somente para percorrer a lista
        while(aux->proximo!=NULL && strcmp(aux->proximo->nome, novo->nome) < 0){
        aux=aux->proximo;
        }
        aux2=aux->proximo;
        // como saiu do while significa que o ponto de insecao foi encontrado

        // caso nome seja repetido
      /*  char nome[100];
        if (strcmp(aux,nome)==0)
        {
            printf("Nome ja esta na lista tente novamente... \n");
            return;
        }*/

        //proximo do novo aponta o proximo do auxiliar
        novo->proximo = aux->proximo;
        novo->anterior=aux;
        //proximo do auxiliar aponta para o novo
        aux->proximo = novo;
        // o anterior do proximo do auxiliar aponta para o novo
        if(aux2!=NULL){
            aux2->anterior = novo;
        }
           // aux->proximo->anterior = aux;

       // novo->proximo->anterior = novo;
        // o novo anterior aponta para o aux
        //novo->anterior = aux;
        //** nesse caso esse else tambem funciona para caso a insersao seja no fim da lista
        lista->quantidadeElementos++;
    }
    return;

}

// funcao para realizar a pesquisa do nome digitado pelo usuario
void pesquisarLista(ListaOrdenada *lista, int dia, int mes, int ano){
  PtrNoLista aux;
  char nome[200];

  setbuf(stdin, NULL);
  printf("Digite o nome a ser pesquisado: ");
  fgets(nome, 200, stdin);
  nome[strcspn(nome,"\n")]='\0';
  setbuf(stdin, NULL);


  if (estaVazia(lista)) {
    printf("Erro... Lista a estah vazia... \n");
    return;
  }

  while (aux != NULL){
     printf("teste\n");
   if (strcmp(aux->nome, nome) == 0){
    break;
   }
   printf("%d\n", aux);
   aux = aux->proximo;
  }
  // posicao onde o elemento deveria existir
  // (aux)
  // nao existe
  if(aux == NULL || strcmp(aux->nome, nome) == -1 ){
   printf(" Nome não encontrado...\n");
 }else{

  printf("Nome: %s\n", nome);
  printf("Sexo: %s\n", aux->sexo);
  printf("Idade: %d anos\n", verificaIdade(aux->nascimento.dia, aux->nascimento.mes, aux->nascimento.ano, dia, mes, ano));
 // fazer funcao que calcula a quantos dias foi a ultima consulta
  printf("A ultima consulta foi a %d dias\n", verificaConsulta(aux->ultima_consulta.dia, aux->ultima_consulta.mes, aux->ultima_consulta.ano, dia, mes, ano));
 }
}

// funcao para verificar o que o usuario deseja fazer
void menu(ListaOrdenada* lista,int dia, int mes, int ano){
    int escolha = 0;
    do
    {
    printf("O que Deseja Fazer: \n");
    printf("[1] Inserir novo cadastro \n");
    printf("[2] Realizar uma Pesquisa \n");
    printf("[3] Sair do programa \n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        inserir(lista);
        break;

    case 2:
        pesquisarLista(lista, dia, mes, ano);
        break;
    case 3:
        break;
    default:
    printf(" Numero digitado eh invalido...tente novamente! \n");
        break;
     }
    } while (escolha != 3);
}

// Funcao que calcula a idade da pessoa
int verificaIdade(int diaNascimento, int mesNascimento, int anoNascimento, int diaAtual, int mesAtual, int anoAtual) {
  int idade = 0;
  printf("\n%d\n",anoNascimento );
  printf("\n%d\n",anoAtual );
  // verifica se o mes atual eh maior o igual ao mes de nascimento e se o dia atual eh maior ou igual o dia de nascimento
  if (mesAtual >= mesNascimento && diaAtual >= diaNascimento) {
    idade = anoAtual - anoNascimento;
  }
  else {
    idade = anoAtual - anoNascimento - 1;
  }

  return (idade);
}

// funcao para inserir um novo elemento (apartir do usuario) na lista em ordem alfabetica
void inserir(ListaOrdenada* lista){
    char nome[200];
    char sexo[5];
    int diaNascimento = 0;
    int mesNascimento = 0;
    int anoNascimento = 0;
    int diaUltima_consulta = 0;
    int mesUltima_consulta = 0;
    int anoUltima_consulta = 0;

    setbuf(stdin, NULL);
    printf("Digite o nome: ");
    fgets(nome, 200, stdin);
    nome[strcspn(nome,"\n")]='\0';
    setbuf(stdin, NULL);

    printf("Digite o sexo: ");
    fgets(sexo, 5, stdin);
    sexo[strcspn(sexo,"\n")]='\0';
    setbuf(stdin, NULL);

    printf("Digite a data de nascimento no formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &diaNascimento, &mesNascimento , &anoNascimento );

    printf("Digite a data da ultima consulta no formato DD/MM/AAAA: ");
    scanf("%d/%d/%d", &diaUltima_consulta, &mesUltima_consulta, &anoUltima_consulta);

    // criar um novo nó, alocar memoria para ele
    PtrNoLista novo = (PtrNoLista)malloc(sizeof(NoLista));


    // copiar informação para novo nó
    strcpy(novo->nome, nome);
    printf("pacientes.txt");
    strcpy(novo->sexo, sexo);
    novo->nascimento.dia = diaNascimento;
    novo->nascimento.mes = mesNascimento;
    novo->nascimento.ano = anoNascimento;
    novo->ultima_consulta.dia = diaUltima_consulta;
    novo->ultima_consulta.mes = mesUltima_consulta;
    novo->ultima_consulta.ano = anoUltima_consulta;

    insereLista(lista, novo);

}

// funcao para preencher os arquivos de saida dos dois medicos
void imprimeListaArq(ListaOrdenada *lista, FILE *arq1, FILE* arq2){
    PtrNoLista percorre;
    PtrNoLista percorre2;


    //percorre recebe o inicio e enquanto ele for diferente de NULL(fim da lista) ele recebe o proximo nó
    for(percorre = lista->inicio; percorre->proximo!= NULL; percorre = percorre->proximo)
    {// escrevendo o arquivo de saida do ginecologiste A-Z
    fprintf(arq2,"< %s , %s , nascimento: %d/%d/%d, ultima consulta: %d/%d/%d > \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );

    }
    
    if(percorre->proximo ==  NULL){
     fprintf(arq2,"< %s , %s , nascimento: %d/%d/%d, ultima consulta: %d/%d/%d > \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );
    }
   

    //for(percorre; percorre->anterior != NULL; percorre = percorre->anterior)
    while(percorre!=NULL)
    {// escrevendo o arquivo de saida do andrologista Z-A
    fprintf(arq1,"< %s , %s , nascimento: %d/%d/%d, ultima consulta: %d/%d/%d > \n", percorre->nome, percorre->sexo, percorre->nascimento.dia,percorre->nascimento.mes, percorre->nascimento.ano, percorre->ultima_consulta.dia, percorre->ultima_consulta.mes, percorre->ultima_consulta.ano );
        percorre=percorre->anterior; 
        printf("testeaaa");
    }
}

int verificaConsulta(int diaConsulta, int mesConsulta, int anoConsulta, int diaAtual, int mesAtual, int anoAtual){
    int meses[12] = {31, 28, 31, 30 ,31, 30, 31, 31 ,30,31,30,31};
    int ultimaConsulta = 0;
    int dia = 0;
    int mes = 0;
    int ano = 0;
    int aux1 = 0;
    int aux2 = 0;
    int aux3 = 0;

    aux1 = meses[mesConsulta - 1] - diaConsulta;
    for (size_t i = mesConsulta;i < 12 ; i++){
      aux1 += meses[i];
    }
    for (size_t i = mesAtual - 2 ; i < 0; i--) {
      aux2 += meses[i];
    }
      aux2 += diaAtual;

      aux3  = anoAtual - anoConsulta - 2;
      aux3 = 365 * aux3;

      ultimaConsulta = aux1 + aux2 + aux3;


    return (ultimaConsulta);
}
