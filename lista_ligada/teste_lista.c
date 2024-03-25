#include     <stdio.h>
#include     "lista.h"

int main() {
    struct lista* lista = criar_lista();
    printf("%s\n", imprimir_lista(lista));

    for (int i = 0; i < 5; i++) {
        inserir_inicio(lista, i+1);
    }

    printf("%s\n", imprimir_lista(lista));

    for (int i = 5; i < 10; i++) {
        inserir_fim(lista, i+1);
    }
    
    printf("%s\n", imprimir_lista(lista));

    printf("Item removido do inicio: %d\n", remover_inicio(lista));
    printf("%s\n", imprimir_lista(lista));

    printf("Item removido do fim: %d\n", remover_fim(lista));
    printf("%s\n", imprimir_lista(lista));
}
