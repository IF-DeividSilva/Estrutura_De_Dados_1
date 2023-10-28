/**
 * @file Rev_Arq.c
 * @author Deivid da Silva Galvao (you@domain.com)
 * @brief Arquivo: Faca um programa que receba, por argumento na main, o nome de um arquivo texto. 
//  Crie outro arquivo texto de sa ́ıda contendo o texto do arquivo de entrada original, porem 
//  substituindo todas as vogais ‘a’ pelo caractere ‘*’ e as demais vogais por ‘+’. Alem disso, 
//  mostre na tela quantas linhas esse arquivo possui. Dentro do programa faca o controle de 
//  erros, isto  ́e, insira comandos que mostre se os arquivos foram abertos com sucesso e, 
//  caso contrario, imprima uma mensagem de erro encerrando o programa.
 * @version 0.1
 * @date 2022-08-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>


 int main(int argc, char const *argv[])
 {
   FILE *arq1 = NULL;
   FILE *arq2 = NULL;
   int linha = 1;
   char c;
   
   arq1 = fopen ("arquivo1.txt", "r+");//abrindo o arquivo de texto para leitura e escrita
   if (arq1 == NULL)
   {
      printf("Ocorreu um erro inesp1erado...fechando programa");
      return 1;
   }//teste de erro
   
   arq2 = fopen ("arquivo2.txt", "w");//abrindo o arquivo2  de texto para escrita 
   
   if (arq2 == NULL)
   {
     printf("Ocorreu um erro inesperado...fechando o programa");
     return 1;
   }//teste de erro

   while (!feof(arq1))//while para percorrer o arquivo ate chegar no final dele 
   {
   fscanf(arq1, "%c", &c);

   switch(tolower(c)){//verificando se os caracteres do arquivo sao vogais e subsitituindo pelos simbolos propostos//
      case 'a':
      c = '*'; break;
      case 'e':
      c = '+'; break;
      case 'i':
      c = '+'; break;
      case 'o':
      c = '+'; break;
      case 'u':
      c = '+'; break;
      case '\n':
      linha++; break;
      default:;
      
   }//switch
   fprintf(arq2, "%c", c);
}//while
   printf("\n O arquivo tem %d linhas \n", linha);//printando os dados obitidos 
   fclose(arq1);//fechando os arquivos
   fclose(arq2);
   return 0;
    
 }//main
