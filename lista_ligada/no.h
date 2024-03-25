#include     <stdio.h>
#include     <stdlib.h>
#include     <string.h>

struct no {
  int info;
  struct no* proximo;
};

int         get_info(struct no*);
void        set_info(struct no*, int);
void        set_proximo(struct no*, struct no*);
void        liberar_no(struct no*);
char *      imprimir_no(struct no*);
char *      int_para_string(int);
struct no*  get_proximo(struct no*);
struct no*  criar_no(int);

struct no* criar_no(int info) {
  struct no* no = (struct no*)malloc(sizeof(struct no));
  no->info = info;
  no->proximo = NULL;

  return no;
}

int get_info(struct no* no) {
  return no->info;
}

struct no* get_proximo(struct no* no) {
  return no->proximo;
}

void set_info(struct no* no, int info) {
  no->info = info;
}

void set_proximo(struct no* no, struct no* proximo) {
  no->proximo = proximo;
}

void liberar_no(struct no* no) {
  free(no);
}

char *imprimir_no(struct no* no) {
  char *info_str = int_para_string(no->info);
  int tamanho = snprintf(NULL, 0, "%d", no->info);
  char *no_str = (char*)malloc(tamanho + 5);
  no_str = strcat(info_str, "| ->");
  return no_str;
}

char *int_para_string(int numero) {
  char *str = (char*)malloc(sizeof(char)*10);
  int i = 0;

  if (numero < 0) {
    str[i++] = '-';
  }

  while (numero != 0) {
    int digito = numero % 10;
    str[i++] = digito + '0';
    numero /= 10;
  }
  str[i] = '\0';

  int inicio = 0, fim = i - 1;
  while (inicio < fim) {
    char temp = str[inicio];
    str[inicio] = str[fim];
    str[fim] = temp;
    inicio++;
    fim--;
  }
  return str;
}

