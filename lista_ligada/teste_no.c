#include     <stdio.h>
#include     "no.h"

int main() {
  struct no* no1 = criar_no(10);
  struct no* no2 = criar_no(20);

  printf("No1: %s\n", imprimir_no(no1));
  printf("No2: %s\n", imprimir_no(no2));

  set_proximo(no1, no2);

  printf("Proximo do no1: %d\n", get_info(get_proximo(no1)));
}
