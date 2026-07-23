#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void limpiar_pantalla(void)
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void leer_cadena_hasta_salto_de_linea(char *buffer, size_t buffer_size)
{
  int i = 0;
  char c;
  while(i<(int)buffer_size-1 && ((c = getchar())!='\n') )
  {
    buffer[i] = c;
    i++;
  }

  buffer[i] = 0;

  if(c!='\n') while(getchar()!='\n');
}

void string_to_upper(unsigned char* buffer)
{
  while(*buffer)
  {
    *buffer = toupper(*buffer);
    buffer++;
  }
}

int expresion_es_salir(char *buffer)
{
  string_to_upper((unsigned char*) buffer);
  return strcmp(buffer, "EXIT")==0;
}