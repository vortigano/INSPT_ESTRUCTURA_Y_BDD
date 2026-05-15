/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-15
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 5:  Número elevado a una potencia
  Escriba un programa que calcule la potencia de un número base elevado a un exponente usando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>

double potencia(double base, int exp)
{
  // precondicion
  if(base == 0. && exp < 0)
  {
    fprintf(stderr, "\nERROR: no esta permitido base 0 exponente negativo\n");
    exit(1);
  }
  // precondicion
  if(base == 0. && exp == 0)
  {
    fprintf(stderr, "\nERROR: no esta permitido base 0 exponente 0\n");
    exit(2);
  }

  // caso base
  if(base != 0. && exp == 0)
  {
    return 1.;
  }

  // caso recursivo
  if(exp>0)
  {
    return base * potencia(base, exp - 1);
  }
  else
  {
    return (potencia(base, exp + 1) * (1. /base));
  }
}

int main(void)
{
  double  base    = 0.;
  int     exp     = 0;

  puts("Ingrese la base de un numero para calcular su potencia: ");
  scanf("%lg", &base);
  while(getchar()!='\n');

  puts("Ingrese el exponente entero para calcular su potencia: ");
  scanf("%d", &exp);
  while(getchar()!='\n');

  printf("----------------------------------------------------\n");
  printf("(%lg) ^ %d = ", base, exp);
  printf("%lg\n", potencia(base, exp));
  printf("----------------------------------------------------\n");

  return 0;
}
