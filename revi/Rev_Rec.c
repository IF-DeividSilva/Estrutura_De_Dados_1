/**
 * @file Rev_Rec.c
 * @author your name (you@domain.com)
 * @brief Recurs˜ao] Escreva e programe uma fun¸c˜ao recursiva para calcular o valor de 
 * um n´umero inteiro de base x elevada a um expoente inteiro y, sendo os valores de x>0 e y>0 fornecidos pelo usu´ario.
 * @version 0.1
 * @date 2022-08-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

rec();
dados();

int main(int argc, char const *argv[])
{
    int x = 2;
    int y = 2;
    int *ptr_x;
    int *ptr_y;
    int resultado = 0;

    dados(x , y, &ptr_x, &ptr_y);

   resultado =  rec(&x, &y);
   // printf("%d", ptr_x);
   printf("O resultado eh: %i ", resultado);

    return 0;
}//main

dados(int x , int y, int* ptr_x, int*ptr_y){

    printf("Digite o valor da base x: ");
    scanf("%d", &x); 
    fflush(stdin);

    printf("Digite o valor do expoente y: ");
    scanf("%d", &y); 
    fflush(stdin);

    printf("%d elevado a %d eh = %d", x, y, rec(x,y));

return 0;
}//dados

rec(int x, int y){
    static int i = 1;
    if (y == 0) return 1;
    if (y >= i++) {return rec(x, y) * x;}
    
}//rec


