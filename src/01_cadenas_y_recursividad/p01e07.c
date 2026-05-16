/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-16
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 7:  MCD (Máximo Común Divisor)
  Escribir un programa que calcule el MCD de dos números utilizando el algoritmo de Euclides de forma recursiva.
*/
#include <stdio.h>
#include <stdlib.h>

/*
  A=84 B=32
  84/32 =2R20
  84/20 =4R4
  84/4  =21R0
  MCD: 4

  A=120 B=72
  120/72  = 1R48
  120/48  = 2R24
  120/24  = 5R0
  MCD: 24
*/
int calcular_mcd(int num_a, int num_b)
{
  num_a = abs(num_a);
  num_b = abs(num_b);

  // caso base
  if(num_b == 0)
  {
    return num_a;
  }

  // caso recursivo
  return calcular_mcd(num_b, num_a%num_b);
}

int main(void)
{
  int numero_a = 0, numero_b = 0;

  puts("Ingrese dos numeros enteros para calcular su MCD (no pueden ser ambos numeros cero)");
  scanf("%d %d", &numero_a, &numero_b);
  while(getchar()!='\n');

  if(numero_a == 0 && numero_b == 0)
  {
    fprintf(stderr, "ERROR: no pueden ser ambos numeros cero\n");
    exit(1);
  }

  printf("----------------------------------------------------\n");
  printf("Numeros ingresados: %d , %d\n", numero_a, numero_b);
  printf("MDC: %d\n", calcular_mcd(numero_a, numero_b));
  printf("----------------------------------------------------\n");

  return 0;
}
