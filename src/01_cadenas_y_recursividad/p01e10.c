/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-16
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 10: Imprimir números del 1 al N
  Escriba un programa que imprima los números del 1 hasta N utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>

void print_serie(int inicio, int fin)
{
  // caso base
  if(abs(inicio) > abs(fin))
  {
    printf("\n");
    return;
  }

  // caso recursivo
  printf("[%4d]", inicio);

  if(fin>0)
  {
    if(inicio % 10 == 0)
      printf("\n");
    print_serie(inicio+1, fin);
  }
  else
  {
    if(abs(inicio) % 10 == 0)
      printf("\n");
    print_serie(inicio-1, fin);
  }
}

int main(void)
{
  int numero = 0;

  puts("Ingrese hasta que numero entero desea imprimir desde el 1:");
  scanf("%d", &numero);
  while(getchar()!='\n');

  printf("-----------------------------------------------------------\n");
  printf("Numero ingresado:     %d\n", numero);
  print_serie(1, numero);
  printf("-----------------------------------------------------------\n");

  return 0;
}
