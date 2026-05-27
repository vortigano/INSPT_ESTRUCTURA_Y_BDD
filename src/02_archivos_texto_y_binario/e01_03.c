/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de arcihvos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-26
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1.3:  Contar la cantidad de vocales por renglón que tiene un archivo de texto.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARCHIVO_FUENTE  "texto_de_prueba.txt"

int es_vocal(char c)
{
  int esvocal;

  switch(c)
  {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
      esvocal = 1;
    break;
    default :
      esvocal = 0;
  }
  return esvocal;
}

int main(void)
{
  FILE *src;

  if( (src = fopen(ARCHIVO_FUENTE, "r"))==NULL)
  {
    perror(ARCHIVO_FUENTE);
    exit(1);
  }

  int count_vocales = 0;
  int count_renglon = 1;
  int c;
  int c_last  = -1;

  // lectura adelantada
  c = fgetc(src);

  if(c=='\n')
  {
    printf("Renglon %d vocales %d\n", count_renglon, count_vocales);
    count_renglon++;
    count_vocales = 0;
  }
  else
  {
    if(c!=EOF && es_vocal(tolower(c)))
    {
      count_vocales++;
    }
  }

  while(!feof(src))
  {
    c_last = c;
    c = fgetc(src);

    ///if(c=='\n' ||c==EOF)
    ///  printf("[\\n]");
    ///else
    ///  printf("[%c]",c);

    if(c!=EOF && es_vocal(tolower(c)))
    {
      count_vocales++;
    }

    if(c == '\n')
    {
      printf("Renglon %d vocales %d\n", count_renglon, count_vocales);
      count_renglon++;
      count_vocales = 0;
    }
  }

  if(c_last!='\n' && c_last!=-1)
  {
    printf("Renglon %d vocales %d\n", count_renglon, count_vocales);
  }

  fclose(src);

  return 0;
}
