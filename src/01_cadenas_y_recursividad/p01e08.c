/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-16
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 8:  Verificar si un número es palíndromo
  Escriba un programa que determine si un número entero es palíndromo utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

//int numero_invertido(int num)
//{
//  num = abs(num);
//
//  if(num < 10)
//  {
//    return num;
//  }
//
//  return (num%10) * pow(10,(int)(log10(num))) + numero_invertido(num/10);
//}

static int _numero_invertido(int num, int acum)
{
  if(num < 10)
    return acum + num;
  else
  {
    acum += num % 10;
  }

  return _numero_invertido( num/10 , acum*10);
}

int numero_invertido(int num)
{
  int signo = (num >= 0) ?(1):(-1);
  num = abs(num);

  return signo * _numero_invertido(num, 0);
}

int es_palindromo(int num)
{
  return (num == numero_invertido(num));
}

int main(void)
{
  int numero = 0;

  puts("Ingrese un numero entero para saber si es palindromo:");
  scanf("%d", &numero);
  while(getchar()!='\n');

  printf("----------------------------------------------------\n");
  printf("Numero ingresado: %d\n", numero);
  printf("Numero invertido: %d\n", numero_invertido(numero));
  printf("Es palindromo: ");
  if(es_palindromo(numero))
  {
    printf("Si\n");
  }
  else
  {
    printf("No\n");
  }
  printf("----------------------------------------------------\n");

  return 0;
}
