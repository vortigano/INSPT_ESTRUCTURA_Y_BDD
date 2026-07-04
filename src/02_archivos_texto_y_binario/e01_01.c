/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de arcihvos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-25
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1.1:  Capturar un texto de varios renglones desde un archivo de orígen y guardarlo en su totalidad en un archivo de destino.
*/
#include <stdio.h>
#include <stdlib.h>

#define ARCHIVO_FUENTE  "texto_de_prueba.txt"
#define ARCHIVO_DESTINO "texto_copia.txt"
#define BUFFER_SIZE 8

int main(void)
{
  FILE *src;
  FILE *dst;

  if( (src = fopen(ARCHIVO_FUENTE, "r"))==NULL)
  {
    perror(ARCHIVO_FUENTE);
    exit(1);
  }

  if( (dst = fopen(ARCHIVO_DESTINO, "w"))==NULL)
  {
    perror(ARCHIVO_DESTINO);
    exit(2);
  }

  char buffer[BUFFER_SIZE];

  while(!feof(src))
  {
    if(fgets(buffer, BUFFER_SIZE, src) != NULL)
    {
      printf("%s", buffer);
      fprintf(dst, "%s", buffer);
    }
  }

  fclose(dst);
  fclose(src);

  return 0;
}
