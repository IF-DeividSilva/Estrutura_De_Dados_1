/**
 * @file test-g01.c
 * @author your name (you@domain.com)
 * @brief Projeto jogo da velha
 * @version 0.1
 * @date 2022-09-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int vez;

int menu();
void jogar();
void zera_jogo();
void exibe_jogo();
void jogada();

int main(int argc, char const *argv[])
{
    int matriz_jogo [3][3];//matriz das casas do jogo da velha "#"
    int continuar;
    

    do
    {
        vez = 1;
        continuar = menu();
        if (continuar == 1)
        {
          jogar(matriz_jogo);
        }

    } while (continuar);

    return 0;
}//main

/**
 * @brief menu do jogo
 * 
 * @return int 
 */
int menu(){
    int escolha = 0;

    printf("\n Jogo da velha test");
    printf("\n Digite 1 para jogar");
    printf("\n Digite 0 para sair");

    scanf("%d", &escolha);

    do
    {
        printf("Erro, valor invalido...digite novamente...");
        printf("\n Jogo da velha test");
        printf("\n Digite 1 para jogar");
        printf("\n Digite 0 para sair");
        
    } while (escolha != 1 || escolha != 0);
    
    return escolha;    

}//menu

/**
 * @brief funcao para exercutar o jogo
 * 
 * @param matriz_jogo 
 */
void jogar(int matriz_jogo[][3]){
    int continua;
    zera_jogo(matriz_jogo);

    do
    {
        exibe_jogo(matriz_jogo);
        jogada(matriz_jogo);

    } while (verifica_termino(matriz_jogo, vez) != 1);
    
}//jogar

/*
 * @brief funcao para zerar todas as casas do jogo
 * 
 * @param matriz_jogo 
 */
void zera_jogo(int matriz_jogo[][3]){
    
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            matriz_jogo[i][j] =0;
        }
    }
    

}//zera jogo

void exibe_jogo(int matriz_jogo[][3]){
    int linha;
    int coluna;

    for (linha = 0; linha < 3; linha++)
    {
        for (coluna = 0; coluna < 3; coluna++)
        {
            if (matriz_jogo[linha][coluna] == 0) printf("     ");
            else
                if (matriz_jogo[linha][coluna] == 1) printf("  X  ");
                else printf("  O  ");
            
            if (coluna != (3 - 1)) printf("|");
        }
        printf("\n");
    }
    printf("\n");
}//exibe jogo

void jogada(int matriz_jogo[][3]){
int linha;
int coluna;
vez++;
printf("\n Jogador %d", (vez % 2) + 1);

do
{
    printf("Linha: ");
    scanf("%d", &linha);
    linha--;

    printf("Coluna: ");
    scanf("%d", &coluna);
    coluna--;

    if (verifica_local(matriz_jogo, linha, coluna) == 0) printf("posicao ocupada ou invalida...tente novamente");
    
} while ((matriz_jogo, linha, coluna) == 0);


}//jogada

