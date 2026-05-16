/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-16
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 9:  Suma de dígitos de un número
  Escriba un programa que calcule la suma de los dígitos de un número entero utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>

int suma_sus_digitos(int numero)
{
  numero = abs(numero);
  if(numero < 10)
  {
    return numero;
  }
  return numero % 10 + suma_sus_digitos(numero / 10);
}

int main(void)
{
  int numero = 0;

  puts("Ingrese un numero entero para calcular la suma de sus digitos:");
  scanf("%d", &numero);
  while(getchar()!='\n');

  printf("----------------------------------------------------\n");
  printf("Numero ingresado:     %d\n", numero);
  printf("Suma de sus digitos:  %d\n", suma_sus_digitos(numero));
  printf("----------------------------------------------------\n");

  return 0;
}
