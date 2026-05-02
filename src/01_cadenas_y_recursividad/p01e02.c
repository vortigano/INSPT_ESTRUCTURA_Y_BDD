/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-02
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 2:  Serie de Fibonacci
  Escriba un programa que imprima los primeros N términos de la serie de Fibonacci utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>

/*
  Para la serie 0, 1, 1, 2, 3, 5, 8, ...
  término 1: 0
  término 2: 1
  término 3: 1
  término 4: 2
  término 5: 3
  término 6: 5
*/
int fibo_term(int n_termino)
{
  // precondición
  if (n_termino <= 0)
  {
    fprintf(stderr, "Error, se esperaba un numero entero mayor a cero para fibonacci\n");
    exit(1);
  }

  // caso base
  if (n_termino == 1) return 0;
  if (n_termino == 2) return 1;

  // caso recursivo
  return fibo_term((n_termino) - 1) + fibo_term((n_termino) - 2);
}

// imprime fibonacci
void print_fibonacci(int terminos)
{
  if(terminos == 0) return;
  print_fibonacci(terminos - 1);
  printf("%d ", fibo_term(terminos));
}


int main(void)
{
  int numero = -1;

  puts("Ingrese cuantos terminos de la serie de fibonacci desea imprimir");
  scanf("%d", &numero);
  while(getchar()!='\n');

  if(numero <= 0)
  {
    fprintf(stderr, "Error, se esperaba un numero entero mayor a cero para fibonacci\n");
    exit(2);
  }

  printf("--------------------\n");
  printf("Numero:     %d\n", numero);

  //soporte iterativo
  for(int i=1; i<=numero; i++)
    printf("%d ", fibo_term(i));
  printf("\n");

  //full recursivo
  print_fibonacci(numero);

  printf("\n--------------------\n");

  return 0;
}
