/*
  MATERIA:    Estructura y base de datos
  TITULO:     Práctica de recursividad
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-15
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 4:  Inversión de una cadena de caracteres
  Escriba un programa que invierta una cadena de texto utilizando recursividad.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_reverse(char* cadena);
void leer_cadena(char* buffer, size_t buffer_size);

int main(void)
{
  #define CADENA_BUFFER 12
  char cadena[CADENA_BUFFER] = {0};

  printf("Ingrese cadena a revertir, hasta %d caracteres:\n", CADENA_BUFFER - 1);
  leer_cadena(cadena, CADENA_BUFFER);

  printf("----------------------------------------------------\n");
  printf("cadena original: [%s]\n", cadena);
  printf("cadena revertida:[%s]\n", string_reverse(cadena));
  printf("----------------------------------------------------\n");

  return 0;
}

static char *str_rev(char* cadena, long pos)
{
  long len = strlen(cadena) - 1;

  //caso base
  if(pos > len/2)
  {
    return cadena;
  }
  //caso recursivo
  char c = cadena[len - pos];
  cadena[len - pos] = cadena [pos];
  cadena[pos] = c;
  //printf("cadena %s\n", cadena);
  return str_rev(cadena, pos + 1);
}

char *string_reverse(char* cadena)
{
  return str_rev(cadena, 0);
}

void leer_cadena(char* buffer, size_t buffer_size)
{
  char c      = 0;
  int  index  = 0;

  while( index < buffer_size - 1 && (c = getchar()) != '\n')
  {
    buffer[index++] = c;
  }

  buffer[index] = '\0';
}
