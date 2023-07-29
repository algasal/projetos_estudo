#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXIMO 100

/* Calculadora simples, que executa uma ou mais equação, respeitando a prioridade das operações, mas sem respeitar parênteses */

float calculadora(float x, float y, char sinal);
float resolver_equacao(char equacao[]);
int precedencia_sinais(char sinal);
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

    printf("Bem vindo à calculadora v2!\n");
    printf("Digite a sua equacao: ");
    fgets(equacao, MAXIMO, stdin);
    
    printf("resultado: %.1f\n", resolver_equacao(equacao));

    return 0;
}

/* separa a equação em pedaços e transforma os números em float pra poder executar o cálculo */
float
resolver_equacao(char equacao[]) 
{
    float x, y, resultado, stack[100];
    char sinal, stack_sinais[100];
    int i, stack_top = -1, sinais_top = -1;

    for (i = 0; equacao[i]; i++) {
        /* se o caracter for um espaço em branco, pula */
        if (equacao[i] == ' ') {
            continue;
        } else if (isdigit(equacao[i])) {
            float num = 0;
            /* while necessário p caso o número tenha + de 1 dígito */           
            while (isdigit(equacao[i])) {
                /* transforma o caracter equacao[i] em um número */
                num = num * 10 + (equacao[i] - '0');
                i++;
            }
            i--;
            
            /* coloca o número obtido no topo do stack */
            stack[++stack_top] = num;
        } else if (equacao[i] == '+' || equacao[i] == '-' || equacao[i] == '*' || equacao[i] == '/') {
            /* se a precedencia do sinal no topo for maior que a do sinal lido, 
             * realiza a operação no topo do stack com os dois números do topo
             * depois coloca o resultado da operação no topo do stack, e o sinal lido no topo do stack de sinais */
            while(sinais_top >= 0 && precedencia_sinais(stack_sinais[sinais_top]) >= precedencia_sinais(equacao[i])) {
                 x = stack[stack_top--];
                 y = stack[stack_top--];
                 sinal = stack_sinais[sinais_top--];
                 stack[++stack_top] = calculadora(x, y, sinal);
            }
            stack_sinais[++sinais_top] = equacao[i];
        }
    }

    /* faz os cálculos das equações que sobrarem */
    while (sinais_top >= 0) {
        y = stack[stack_top--];
        x = stack[stack_top--];
        sinal = stack_sinais[sinais_top--];
        stack[++stack_top] = calculadora(x, y, sinal);
    }

    resultado = stack[0];
    return resultado;
}

/* checa a precedência das equações */
int
precedencia_sinais(char sinal)
{
    if (sinal == '+' || sinal == '-') return 1;
    else if (sinal == '*' || sinal == '/') return 2;
    
    return 0;
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

    /* loopa pela array operacoes[] pra encontrar a operação correspondente ao sinal */
    for (int i = 0; i < sizeof(operacoes) / sizeof(operacoes[0]); i++) {
        if (operacoes[i].Key == sinal) {
            return operacoes[i].Func(x, y);
        }
    }
}
