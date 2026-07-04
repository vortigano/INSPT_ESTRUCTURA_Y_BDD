/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de arcihvos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-26
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1.2:  Contar la cantidad de palabras por renglón que tiene un archivo de texto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARCHIVO_FUENTE  "texto_de_prueba.txt"

int main(void)
{
  FILE *src;

  if( (src = fopen(ARCHIVO_FUENTE, "r"))==NULL)
  {
    perror(ARCHIVO_FUENTE);
    exit(1);
  }

  int count_palabra = 0;
  int count_renglon = 1;
  int c;
  int c_last;

  // lectura adelantada
  c = fgetc(src);
  if(c=='\n')
  {
    printf("Renglon %d palabras %d\n", count_renglon, count_palabra);
    count_renglon++;
    count_palabra = 0;
  }

  while(!feof(src))
  {
    c_last = c;
    c = fgetc(src);

    ///if(c=='\n' ||c==EOF)
    ///  printf("[\\n]");
    ///else
    ///  printf("[%c]",c);

    if(isalnum(c_last) && !isalnum(c))
    {
      count_palabra++;
    }

    if(c == '\n')
    {
      printf("Renglon %d palabras %d\n", count_renglon, count_palabra);
      count_renglon++;
      count_palabra = 0;
      c_last  = c;
    }
  }

  if(isalnum(c_last) && !isalnum(c))
  {
    printf("Renglon %d palabras %d\n", count_renglon, count_palabra);
  }


  fclose(src);

  return 0;
}
