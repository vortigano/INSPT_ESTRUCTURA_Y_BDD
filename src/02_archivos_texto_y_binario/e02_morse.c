/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de arcihvos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-27
  ESTUDIANTE: Alberto Martín Capurro

  Decodificador de Mensajes en Código Morse

  Se desea desarrollar un programa en lenguaje C que lea un archivo de texto que contiene mensajes codificados en código Morse y los traduzca a texto ASCII (letras y números normales).
  El programa debe realizar las siguientes acciones:
  1. Abrir un archivo de texto (morse.txt) ubicado en una ruta específica (modificable
    por el usuario) que contiene códigos Morse, uno por línea. Las líneas vacías
    representarán espacios entre palabras.
  2. Mostrar el contenido original del archivo en pantalla, tal como está almacenado.
  3. Decodificar cada línea del archivo:
    o Cada línea contiene un único símbolo en código Morse (una letra o un
      número).
    o Si la línea está vacía (\n solo), debe interpretarse como un espacio entre
      palabras.
  4. Reconstruir el mensaje completo, concatenando las letras traducidas y respetando los espacios detectados.
  5. Mostrar en pantalla el mensaje decodificado.
  6. Cerrar correctamente el archivo al finalizar.
  Detalles técnicos:
  • Utilizar una tabla de traducción (Traduccion) que asocia cada secuencia Morse a su carácter ASCII correspondiente (mayúsculas de la A a la Z y dígitos del 0 al 9).
  • El programa cuenta con una función ConvierteMorse que recibe un código Morse y devuelve la letra correspondiente.
  • El programa debe usar funciones auxiliares como mostrar, error y pausa para estructurar mejor el código.

  Ejemplo de archivo morse.txt
  ....
  .
  .-..
  .-..
  ---
  .--
  ---
  .-.
  .-..
  -..
  Salida esperada: HELLO WORLD

  Puntos clave del ejercicio:
  • Lectura de archivos de texto línea por línea.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 16
#define BUFFER_SALIDA_SIZE 512

typedef struct
{
  char ascii;
  char morse[8];

} Traduccion;

Traduccion tabla[] =
{
  {'A', ".-"},    {'B', "-..."},  {'C', "-.-."},  {'D', "-.."},   {'E', "."},
  {'F', "..-."},  {'G', "--."},   {'H', "...."},  {'I', ".."},    {'J', ".---"},
  {'K', "-.-"},   {'L', ".-.."},  {'M', "--"},    {'N', "-."},    {'O', "---"},
  {'P', ".--."},  {'Q', "--.-"},  {'R', ".-."},   {'S', "..."},   {'T', "-"},
  {'U', "..-"},   {'V', "...-"},  {'W', ".--"},   {'X', "-..-"},  {'Y', "-.--"},
  {'Z', "--.."},
  {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
  {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}
};

void pausa()
{
  printf("Pulse enter tecla para continuar...");
  while(getchar()!='\n');
}

void error(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

char convierte_morse(char *codigo_morse)
{
  size_t  indice_max  = sizeof(tabla) / sizeof(tabla[0]);
  int     indice      = 0;

  while(indice < indice_max && strcmp(codigo_morse, tabla[indice].morse))
  {
    indice ++;
  }

  if(indice >= indice_max || strcmp(codigo_morse, tabla[indice].morse)!=0)
  {
    indice = -1;
  }

  return (indice>=0)?(tabla[indice].ascii):(0);
}

void mostrar_archivo(FILE *src)
{
  char buffer[BUFFER_SIZE] = {0};

  rewind(src);
  while(!feof(src))
  {
    if(fgets(buffer, BUFFER_SIZE, src))
    {
      for(int i=0; i<strlen(buffer); i++)
      {
        if(buffer[i]=='\n') buffer[i] = 0;
      }
      printf("[%s]\n", buffer);
    }
  }
}

void decodificar_archivo(FILE *src, char* buffer_salida, int size_of_buffer)
{
  rewind(src);
  char buffer[BUFFER_SIZE] = {0};
  int buffer_index = 0;

  while(!feof(src))
  {
    if(fgets(buffer, BUFFER_SIZE, src))
    {
      if(buffer_index < size_of_buffer - 1)
      {
        int i= 0;
        while(i<strlen(buffer))
        {
          if(buffer[i]=='\n') buffer[i] = 0;
          i++;
        }
        if(i==1)
        {
          buffer_salida[buffer_index] = ' ';
        }
        else
          buffer_salida[buffer_index] = convierte_morse(buffer);

        buffer_index++;
      }
    }
    buffer_salida[buffer_index] = 0;
  }
}



int main(void)
{
  //- abrir archivo de texto (morse.txt)
  //- mostar el contenido original en pantalla
  //- decodificar cada línea del archivo
  //- reconstruir el mensaje completo
  //- mostrar en pantalla el mensaje decodificado
  //- cerrar archivo de texto (morse.txt)

  FILE *src;

  #define ARCHIVO_DE_ENTRADA "morse.txt"

  //- abrir archivo de texto (morse.txt)
  if( (src = fopen(ARCHIVO_DE_ENTRADA, "r")) == NULL )
  {
    perror(ARCHIVO_DE_ENTRADA);
    exit(1);
  }

  //- mostar el contenido original en pantalla
  printf("-------- mostrar archivo -------\n");

  mostrar_archivo(src);

  printf("-------- fin de archivo -------\n");


  //- decodificar cada línea del archivo
  //- reconstruir el mensaje completo
  printf("decodificando y reconstruyendo...\n");
  char buffer_salida[BUFFER_SALIDA_SIZE] = {0};
  decodificar_archivo(src, buffer_salida, BUFFER_SALIDA_SIZE);

  //- mostrar en pantalla el mensaje decodificado
  printf("-------- archivo decodificado ---------\n");
  printf("[%s]\n", buffer_salida);

  //- cerrar archivo de texto (morse.txt)
  fclose(src);


  return 0;
}
