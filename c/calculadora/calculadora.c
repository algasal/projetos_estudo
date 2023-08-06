#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXIMO 100

/* Calculadora simples */

float calculadora(float x, float y, char sinal);
float resolver_equacao(const char *equacao);
int precedencia_sinais(char sinal);
int sinal_valido(char sinal);

int
main(int argc, char *argv[])
{
    int i = 0;
    char c, *equacao = (char *)malloc(sizeof(char));

    printf("Bem vindo à calculadora v5!\n");
    printf("Digite a sua equacao: ");
    while ((c = getc(stdin)) != '\n') {
        equacao[i++] = c;
        if ((equacao = realloc(equacao, (i+1) * sizeof(char))) == NULL) {
            fprintf(stderr, "Falha na alocação de memória.\n");
            exit(EXIT_FAILURE);
        }
    }
    equacao[i] = '\0';
    printf("resultado: %.1f\n", resolver_equacao(equacao));
    
    free(equacao);
    return 0;
}

/* separa a equação em pedaços e transforma os números em float pra poder executar o cálculo */
float
resolver_equacao(const char *equacao) 
{
    int j = 0, k = 0, stack_top = -1, sinais_top = -1;
    float x, y, resultado, *stack = (float *)malloc(j * sizeof(float));
    char sinal, *stack_sinais = (char *)malloc(sizeof(char));
    
    for (int i = 0; equacao[i]; i++) {
        if (equacao[i] == ' ') {
            continue;
        }
        else if (equacao[i] == '(') {
            int i_interno = i + 1;              /* contador interno pq eu me perdi usando só o i */
            int parentese_abertura = 1;         /* se o caracter for um parentese, guarda o número de parenteses de abertura */
            int parentese_fechamento = 0;       /* de modo a identificar em qual parentese de fechamento terminar a string */
            char equacao_interna[sizeof(equacao) / sizeof(float)] = " "; /* pro caso de haver várias equações entre parenteses */

            if ((stack = realloc(stack, (j+1) * sizeof(float))) == NULL) {
                fprintf(stderr, "Erro na alocação de memória.\n");
                exit(EXIT_FAILURE);
            }
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
            j++;
        } else if (isdigit(equacao[i])) {
            float num = 0;
            char num_string[MAXIMO] = " ";

            if ((stack = realloc(stack, (j+1) * sizeof(float))) == NULL) {
                fprintf(stderr, "Erro na alocação de memória.\n");
                exit(EXIT_FAILURE);
            }

            while (isdigit(equacao[i]) || equacao[i] == '.') {       /* checa se o caracter é um dígito ou um ponto (pra nums quebrados) */
                strncat(num_string, &equacao[i], 1);                 /* coloca o número numa string */
                i++;
            }
            i--;
            num = atof(num_string);                                 /* transforma a string em float, p realizar operação c/ nums quebrados */
            
            stack[++stack_top] = num;                               /* coloca o número obtido no topo do stack */
            j++;
        } else if (sinal_valido(equacao[i])) {
            while(sinais_top >= 0 && precedencia_sinais(stack_sinais[sinais_top]) >= precedencia_sinais(equacao[i])) {
                 x = stack[stack_top--];                            /* se a precedência do sinal no topo for maior que a do sinal lido, */
                 y = stack[stack_top--];                            /* realiza a operação no topo do stack com os dois números do topo */
                 sinal = stack_sinais[sinais_top--];                /* depois coloca o resultado da operação no topo do stack, e o sinal */
                 stack[++stack_top] = calculadora(x, y, sinal);     /* lido no topo do stack de sinais */
            }
            stack_sinais[++sinais_top] = equacao[i];
            k++;

            if ((stack_sinais = realloc(stack_sinais, (k+1) * sizeof(char))) == NULL) {
                fprintf(stderr, "Erro na alocação de memória.\n");
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Operação inválida.\n");
            exit(EXIT_FAILURE);
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
    free(stack);
    free(stack_sinais);
    return resultado;
}

/* checa se o sinal é valido para uma operação */
int
sinal_valido(char sinal)
{
    return sinal == '+' || sinal == '-' || sinal == '*' || sinal == '/' || sinal == '%' || sinal == '^';
}

/* checa a precedência das equações */
int
precedencia_sinais(char sinal)
{
    if (sinal == '+' || sinal == '-') return 1;
    else if (sinal == '*' || sinal == '/' || sinal == '%') return 2;
    else if (sinal == '^') return 3;
    
    return 0;
}

/* realiza o cálculo em si */
float
calculadora(float x, float y, char sinal)
{
    switch(sinal) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        case '%':
            int res = (x == (int) x && y == (int) y) ? (int) x % (int) y : 0;
            if (res == 0) goto erro_potencia;
            else return res;
        case '^':
            return pow(x,y); 
        default:
            fprintf(stderr, "Operação inexistente: %c\n", sinal);
            exit(EXIT_FAILURE);

        erro_potencia:
            fprintf(stderr, "Operação de módulo permitida somente com inteiros.\n");
            exit(EXIT_FAILURE);
    }
}


