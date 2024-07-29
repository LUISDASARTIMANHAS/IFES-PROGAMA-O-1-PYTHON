#include "functions.c"
#include <stdlib.h>
#include <stdio.h>
// Faça um programa com funções em C para ler a matrícula do aluno e suas três notas. Valide os dados de entrada. A matrícula deve ser maior que zero e as notas entre 0 e 10.
// Calcule a média final do aluno e imprima: “APROVADO” se a média for maior ou igual a 7;
// “REPROVADO” se a média for menor que 6; e “PROVA FINAL” se a média estiver entre 6 e 7.
// Faça uma função para cada operação: ler e validar a matrícula; ler e validar as notas; calcular a média e imprimir a mensagem.



int main(){
    head();
    int matricula = validMatricula();
    float nota1 = validNota();
    float nota2 = validNota();
    float nota3 = validNota();
    float media = calcMedia3(nota1,nota2,nota3);
    printf("\n=======SISTEMA=======\n");
    printf("Matricula: %d \n", matricula);
    printf("Media: %.2f \n", media);
    printf("=====================\n");

    copy();
    return 0;
}