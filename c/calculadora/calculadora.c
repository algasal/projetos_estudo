#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXIMO 100

/* Calculadora simples, que executa uma ou mais equações, respeitando a prioridade das operações e parênteses */

float calculadora(float x, float y, char sinal);
float resolver_equacao(char equacao[]);
int precedencia_sinais(char sinal);
int sinal_valido(char sinal);
float soma(float x, float y) { return x + y; }
float subt(float x, float y) { return x - y; }
float mult(float x, float y) { return x * y; }
float divs(float x, float y) { return x / y; }
typedef float (*Func)(float, float);

/* struct que guarda a chave (ex '+') e um pointeiro pra uma função (ex 'soma'), simulando um dicionário */
struct OperacaoMatematica {
    char Sinal;
    Func Operacao;
};

int
main(int argc, char *argv[])
{
    char equacao[MAXIMO];

    printf("Bem vindo à calculadora v3!\n");
    printf("Digite a sua equacao: ");
    fgets(equacao, MAXIMO, stdin);
    
    printf("resultado: %.1f\n", resolver_equacao(equacao));

    return 0;
}

/* separa a equação em pedaços e transforma os números em float pra poder executar o cálculo */
float
resolver_equacao(char equacao[]) 
{
    float x, y, resultado, stack[MAXIMO];
    char sinal, stack_sinais[MAXIMO];
    int i, stack_top = -1, sinais_top = -1;
    
    for (i = 0; equacao[i]; i++) {
        if (equacao[i] == ' ') {    /* se o caracter for um espaço em branco, pula */
            continue;
        } else if (equacao[i] == '(') {
            int i_interno = i + 1;              /* contador interno pq eu me perdi usando só o i */
            int parentese_abertura = 1;         /* se o caracter for um parentese, guarda o número de parenteses de abertura */
            int parentese_fechamento = 0;       /* de modo a identificar em qual parentese de fechamento terminar a string */
            char equacao_interna[MAXIMO] = " "; /* pro caso de haver várias equações entre parenteses */
            
            while (equacao[i_interno] != '\0') {
                if (equacao[i_interno] == '(') {
                    parentese_abertura++;
                } else if (equacao[i_interno] == ')') {
                    parentese_fechamento++;
                    if (parentese_fechamento == parentese_abertura) break;
                }
                
                strncat(equacao_interna, &equacao[i_interno], 1); /* torna a equação entre parenteses numa string (sem os parenteses) */
                i_interno++;
            }
            i = i_interno;

            float num = resolver_equacao(equacao_interna); /* resolve recursivamente a nova equação */
            stack[++stack_top] = num;                      /* e coloca o resultado no topo do stack */ 

        } else if (isdigit(equacao[i])) {
            float num = 0;

            while (isdigit(equacao[i])) {       /* necessário p caso o número tenha + de 1 dígito */
                num = num * 10 + (equacao[i] - '0');        /* transforma o caracter equacao[i] em um número */
                i++;
            }
            i--;
            
            stack[++stack_top] = num;       /* coloca o número obtido no topo do stack */
        } else if (sinal_valido(equacao[i])) {
            while(sinais_top >= 0 && precedencia_sinais(stack_sinais[sinais_top]) >= precedencia_sinais(equacao[i])) {
                 x = stack[stack_top--];                            /* se a precedência do sinal no topo for maior que a do sinal lido, */
                 y = stack[stack_top--];                            /* realiza a operação no topo do stack com os dois números do topo */
                 sinal = stack_sinais[sinais_top--];                /* depois coloca o resultado da operação no topo do stack, e o sinal */
                 stack[++stack_top] = calculadora(x, y, sinal);     /* lido no topo do stack de sinais */
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

/* checa se o sinal é valido para uma operação */
int
sinal_valido(char sinal)
{
    return sinal == '+' || sinal == '-' || sinal == '*' || sinal == '/';
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
        if (operacoes[i].Sinal == sinal) {
            return operacoes[i].Operacao(x, y);
        }
    }
}
