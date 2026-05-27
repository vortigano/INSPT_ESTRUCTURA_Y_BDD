/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de arcihvos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-27
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1.4:  Leer cifras binarias de 8bits desde un archivo de texto y calcular su valor en decimal a través del teorema fundamental.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ARCHIVO_FUENTE  "textoEnBinario.txt"

#define BUFFER_SIZE 100
#define CIFRAS_SIZE 8

int main(void)
{
  FILE *src;

  if( (src = fopen(ARCHIVO_FUENTE, "r"))==NULL)
  {
    perror(ARCHIVO_FUENTE);
    exit(1);
  }

  char buffer[BUFFER_SIZE] = {0};



  while(!feof(src))
  {
    if(fgets(buffer, BUFFER_SIZE, src)!=NULL)
    {
      int i=0;
      while(buffer[i]!= '\n' && buffer[i]!='\0')
      {
        i++;
      }
      buffer[i] = '\0';

      //printf("%s\n", buffer);

      int numero = 0;
      for(int i=0; i<CIFRAS_SIZE; i++)
      {
        //numero += (buffer[CIFRAS_SIZE-1-i]-'0') * (int) pow(2, i);
        if(buffer[i]=='1')
        {
          numero += 1<<(CIFRAS_SIZE-1-i);
        }
      }
      //printf("numero: %d %c", numero, (char)numero);
      printf("%c", numero);

    }
  }

  fclose(src);

  return 0;
}
