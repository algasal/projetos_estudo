#include       <stdio.h>
#include       <stdlib.h>
#include       "no.h"

struct lista {
    struct no* primeiro;
    struct no* ultimo;
};

int           esta_vazia(struct lista*);
int           remover_inicio(struct lista*);
int           remover_fim(struct lista*);
void          inserir_inicio(struct lista*, int);
void          inserir_fim(struct lista*, int);
void          set_primeiro(struct lista*, struct no*);
void          set_ultimo(struct lista*, struct no*);
char *        imprimir_lista(struct lista*);
struct lista* criar_lista();
struct no*    get_primeiro(struct lista*);
struct no*    get_ultimo(struct lista*);

struct lista* criar_lista() {
    struct lista* lista = (struct lista*)malloc(sizeof(struct lista));
    if (lista == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    set_primeiro(lista, NULL);
    set_ultimo(lista, NULL);
    return lista;
}

void liberar_lista(struct lista* lista) {
    while (lista->primeiro != NULL) {
        struct no* temp = lista->primeiro;
        lista->primeiro = get_proximo(lista->primeiro);
        liberar_no(temp);
    }
    free(lista);
}

struct no* get_primeiro(struct lista* lista) {
    return lista->primeiro;
}

struct no* get_ultimo(struct lista* lista) {
    return lista->ultimo;
}

void set_primeiro(struct lista* lista, struct no* no) {
    lista->primeiro = no;
}

void set_ultimo(struct lista* lista, struct no* no) {
    lista->ultimo = no;
}

int esta_vazia(struct lista* lista) {
    return get_primeiro(lista) == NULL;
}

void inserir_inicio(struct lista* lista, int i) {
    struct no* novo = criar_no(i);
    if (!esta_vazia(lista)) {
        set_proximo(novo, lista->primeiro);
    }
    else {
        set_ultimo(lista, novo);
    }
    set_primeiro(lista, novo);
}

void inserir_fim(struct lista* lista, int i) {
    struct no* novo = criar_no(i);
    if (esta_vazia(lista)) {
        set_primeiro(lista, novo);
    }
    else {
        //struct no* aux = lista->primeiro;
        //while (get_proximo(aux) != NULL) {
        //    aux = get_proximo(aux);
        //}
        //set_proximo(aux, novo);
        set_proximo(lista->ultimo, novo);
  }
    lista->ultimo = novo;
}

int remover_inicio(struct lista* lista) {
    if (esta_vazia(lista)) {
        fprintf(stderr, "Lista vazia.\n");
        exit(EXIT_FAILURE);
    }
    int info = get_info(lista->primeiro);
    struct no* temp = lista->primeiro;
    lista->primeiro = get_proximo(lista->primeiro);
    liberar_no(temp);
    if (lista->primeiro == NULL)
        lista->ultimo == NULL;
    return info;
}

int remover_fim(struct lista* lista) {
    if (esta_vazia(lista)) {
        fprintf(stderr, "Lista vazia.\n");
        exit(EXIT_FAILURE);
    }
    int temp;

    if(get_proximo(lista->primeiro) == NULL) {
        temp = get_info(lista->primeiro);
        liberar_no(lista->primeiro);
        lista->primeiro = NULL;
        lista->ultimo = NULL;
    }
    else {
        struct no* aux = lista->primeiro;
        while (get_proximo(get_proximo(aux)) != NULL) {
            aux = get_proximo(aux);
        }
        temp = get_info(get_proximo(aux));
        liberar_no(get_proximo(aux));
        set_proximo(aux, NULL);
        lista->ultimo = aux;
    }
    return temp;
}

char *imprimir_lista(struct lista* lista) {

    int tamanho = 10;
    if (!esta_vazia(lista)) {
        struct no* aux = lista->primeiro;
        while (aux != NULL) {
            tamanho += strlen(imprimir_no(aux));
            aux = get_proximo(aux);
        }
    }
    tamanho += 3;

    char *lista_str = (char*)malloc(sizeof(char)*tamanho);
    if (lista_str == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(EXIT_FAILURE);
    }

    lista_str = strcat(lista_str, "Lista: ");
    if (esta_vazia(lista))
        strcat(lista_str, "está vazia\n");
    else {
        struct no* aux = lista->primeiro;
        while (aux != NULL) {
            strcat(lista_str, imprimir_no(aux));
            aux = get_proximo(aux);
        }
        strcat(lista_str, "\\\n");
    }
    return lista_str;
}
