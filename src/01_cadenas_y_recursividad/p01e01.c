/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-02
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1:  Factorial de un número
  Escriba un programa en C que calcule el factorial de un número entero positivo utilizando una función recursiva.
*/
#include <stdio.h>
#include <stdlib.h>

int fact(int numero)
{
  // precondición
  if(numero < 0)
  {
    fprintf(stderr, "Error, se esperaba un numero entero positivo para factorial\n");
    exit(1);
  }

  // precondición
  if(numero > 12)
  {
    fprintf(stderr, "Error, el numero entero para factorial debe ser menor o igual a 12\n");
    exit(2);
  }

  // caso base
  if(numero == 0 || numero == 1)
    return 1;

  // caso recursivo
  return fact(numero - 1) * numero;
}

int main(void)
{
  int numero = -1;

  puts("Ingrese un numero entero positivo hasta 12:");
  scanf("%d", &numero);
  while(getchar()!='\n');

  printf("--------------------\n");
  printf("Numero:     %d\n", numero);
  printf("Factorial:  %d\n", fact(numero));
  printf("--------------------\n");
  return 0;
}
