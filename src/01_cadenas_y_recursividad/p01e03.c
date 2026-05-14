/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-14
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 3:  Suma de los primeros N números naturales
  Escriba un programa que calcule la suma de los primeros N números naturales utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>

/*
  para 1 -> 1
  para 2 -> 2+1     = 3
  para 3 -> 3+2+1   = 6
  para 4 -> 4+3+2+1 = 10
*/
int suma(int max_num)
{
  if(max_num==1)
  {
    return 1;
  }
  else
  {
    return max_num + suma(max_num-1);
  }
}

int main(void)
{
  int numero = -1;

  puts("Se indica la suma de los primeros números naturales hasta el indicado a continuación");
  puts("Ingrese el ultimo numero de la serie a sumar:");
  scanf("%d", &numero);
  while(getchar()!='\n');

  if(numero <= 0)
  {
    fprintf(stderr, "Error, se esperaba un numero natural\n");
    exit(1);
  }

  printf("----------------------------------------------------\n");
  printf("Suma de los primeros numeros natuales hasta %d\n", numero);
  printf("%d \n", suma(numero));
  printf("----------------------------------------------------\n");

  return 0;
}
