#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXIMO 100

/* Calculadora simples, que executa uma ou mais equações sem respeitar prioridade de operações */

float calculadora(float x, float y, char sinal);
float resolver_equacao(char equacao[]);
float soma(float x, float y) { return x + y; }
float subt(float x, float y) { return x - y; }
float mult(float x, float y) { return x * y; }
float divs(float x, float y) { return x / y; }
typedef float (*Operacao)(float, float);

/* struct que guarda a chave (ex '+') e um pointeiro pra uma função (ex 'soma'), simulando um dicionário */
struct OperacaoMatematica {
    char Key;
    Operacao Func;
};

int
main(int argc, char *argv[])
{
    char equacao[MAXIMO];

    printf("Bem vindo à calculadora v1!\n");
    printf("Digite a sua equacao: ");
    fgets(equacao, MAXIMO, stdin);
    
    float resultado = resolver_equacao(equacao);

    printf("resultado: %.1f\n", resultado);

    return 0;
}

/* separa a equação em pedaços e transforma os números em float pra poder executar o cálculo */
float
resolver_equacao(char equacao[]) 
{
    float x, y, resultado;
    char *sinal;

    /* token usado pra quebrar a equação em pedaços menores de 'num', 'sinal', 'num' */
    char *token = strtok(equacao, " \n");
    x = atoi(token);

    while (token != NULL) {
        sinal = strtok(NULL, " \n");
        token = strtok(NULL, " \n");
        
        if (token != NULL) {
            y = atoi(token);

            resultado = calculadora(x, y, sinal[0]);
            printf("x: %.1f, y: %.1f, op: %c\n", x, y, sinal[0]);

            x = resultado;
        }
    }

    return resultado;
}

/* realiza o cálculo em si */
float
calculadora(float x, float y, char sinal)
{
    struct OperacaoMatematica operacoes[] = {
        {'+', soma},
        {'-', subt},
        {'*', mult},
        {'/', divs},
    };

    float resultado;

    /* loopa pela array operacoes[] pra encontrar a operação correspondente ao sinal */
    for (int i = 0; i < sizeof(operacoes) / sizeof(operacoes[0]); i++) {
        if (operacoes[i].Key == sinal) {
            resultado = operacoes[i].Func(x, y);
            break;
        }
    }

    return resultado;
}

 
