/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-15
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 6:  Contar dígitos de un número
  Escriba un programa que cuente cuántos dígitos tiene un número entero utilizando una función recursiva.
*/
#include <stdio.h>
#include <stdlib.h>

int calcular_cantidad_de_digitos(int numero)
{
  if(abs(numero) < 10)
  {
    return 1;
  }
  else
  {
    return 1 + (calcular_cantidad_de_digitos(numero/10));
  }
}

int main(void)
{
  int numero = 0;

  puts("Ingrese un numero entero para contar su cantidad de digitos.");

  scanf("%d", &numero);
  while(getchar()!='\n');

  printf("----------------------------------------------------\n");
  printf("Numero ingresado:     %-8d \n", numero);
  printf("Candidad de digitos:  %-8d\n", calcular_cantidad_de_digitos(numero));
  printf("----------------------------------------------------\n");

  return 0;
}
