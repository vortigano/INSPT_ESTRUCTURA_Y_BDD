/*
  PRACTICA:   Pilas dinámicas
  TITULO:     Paréntesis balanceado
  FECHA:      2026-07-16 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  # Ejercicio: Verificador de Paréntesis Balanceados (Pila Dinámica)

  ## Objetivo
  Implementar una función que determine si una cadena de texto tiene sus paréntesis correctamente balanceados, utilizando una pila dinámica. Este es un ejercicio clásico para reforzar el uso de pilas y el patrón de validación de entrada.

  ## Descripción
  Dada una cadena que contiene paréntesis `()`, corchetes `[]` y llaves `{}`, el programa debe indicar si están correctamente balanceados. Se considera balanceado si cada símbolo de apertura tiene su correspondiente símbolo de cierre en el orden correcto.

  ## Comportamiento esperado
  - **Entrada:** `"({[]})"` -> **Salida:** `"Balanceado"`
  - **Entrada:** `"({[})"` -> **Salida:** `"No balanceado"`
  - **Entrada:** `"((("` -> **Salida:** `"No balanceado"`
  - **Entrada:** `"Hola mundo"` (sin paréntesis) -> **Salida:** `"Balanceado"`

  ## Funcionalidades requeridas
  1. **Leer una cadena** desde teclado (podés usar tu función `leer_cadena_hasta_salto_de_linea`).
  2. **Recorrer la cadena** carácter por carácter.
  3. **Si es un símbolo de apertura** (`(`, `[`, `{`), apilarlo.
  4. **Si es un símbolo de cierre** (`)`, `]`, `}`), verificar que el tope de la pila sea su correspondiente apertura. Si coincide, desapilar. Si no, la cadena no está balanceada.
  5. **Al finalizar**, si la pila está vacía, la cadena está balanceada. Si quedan elementos, no lo está.
  6. **Liberar** la memoria de la pila al terminar.

  ## Consideraciones
  - Implementar tu propia pila dinámica (sin depender de `pila_dinamica.c`).
  - Usar tu patrón de validación para el menú de entrada.
  - No es necesario un menú complejo; con una sola ejecución que pida la cadena y muestre el resultado alcanza.

  ## Extra opcional (si te sobra tiempo)
  - Extenderlo para verificar también comillas dobles `"` y simples `'`, considerando que deben aparecer en pares.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define EXPRESION_MAX_CHARS 51

typedef struct {
  char  c;
  int   pos;
} t_token;

typedef struct st_nodo{
  t_token token;
  struct st_nodo *sig;
} t_nodo;

typedef struct {
  t_nodo *pila;
} t_analisis;

void leer_cadena_hasta_salto_de_linea(char *buffer, size_t buffer_size)
{
  int i = 0;
  char c;
  while(i<buffer_size-1 && ((c = getchar())!='\n') )
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

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

t_nodo *pila_nodo_nuevo(t_token t)
{
  t_nodo *nodo_nuevo;
  if( (nodo_nuevo = (t_nodo*) malloc(sizeof(t_nodo)))==NULL)
  {
    fprintf(stderr, "ERROR AL ASIGNAR MEMORIA PARA NODO\n");
    exit(1);
  }
  nodo_nuevo->token = t;
  nodo_nuevo->sig   = NULL;
  return nodo_nuevo;
}

void pila_tok_apilar(t_analisis *analisis, t_token t)
{
  t_nodo *nodo = pila_nodo_nuevo(t);

  if(analisis->pila==NULL)
  {
    analisis->pila  = nodo;
    nodo->sig       = NULL;
  }
  else
  {
    nodo->sig       = analisis->pila;
    analisis->pila  = nodo;
  }
}

t_token pila_tok_desapilar(t_analisis *analisis)
{
  t_token t = {0, -1};

  if(analisis->pila!=NULL)
  {
    t = analisis->pila->token;
    t_nodo *nodo_tmp  = analisis->pila;
    analisis->pila    = analisis->pila->sig;
    free(nodo_tmp);
  }

  return t;
}

t_token pila_tok_peek(t_analisis *analisis)
{
  t_token token = {0, -1};

  if(analisis->pila != NULL)
  {
    token = analisis->pila->token;
  }
  return token;
}

void pila_tok_vaciar(t_analisis *analisis)
{
  while(pila_tok_desapilar(analisis).pos!=-1);
}

#ifdef DEBUG
void pila_tok_mostrar(t_analisis *analisis)
{
  t_nodo *nodo_tmp = analisis->pila;
  int i = 0;
  while(nodo_tmp!=NULL)
  {
    printf("Token %c %d\n", nodo_tmp->token.c, nodo_tmp->token.pos+1);
    nodo_tmp = nodo_tmp->sig;
    i++;
  }
}
#endif

void analizar_expresion(t_analisis *analisis, char * expresion)
{
  int error = 0;
  int i = 0;
  while(!error && *expresion)
  {
    //printf("[%c]", *expresion);
    t_token tok = {*expresion, i};
    switch(*expresion)
    {
      case ']':
      {
        if(pila_tok_peek(analisis).c!='[')
          error = 1;
        else
          pila_tok_desapilar(analisis);
        break;
      }
      case '}':
      {
        if(pila_tok_peek(analisis).c!='{')
          error = 1;
        else
          pila_tok_desapilar(analisis);
        break;
      }
      case ')':
      {
        if(pila_tok_peek(analisis).c!='(')
          error = 1;
        else
          pila_tok_desapilar(analisis);
        break;
      }
      case '[': case '{': case '(':
      {
        pila_tok_apilar(analisis, tok);
        break;
      }
    }
    expresion++;
    i++;
  }
  puts("");
  if(!error && analisis->pila != NULL)
    error = 2;

  switch(error)
  {
    case 1:
    {
      printf("ERROR: error de cierre, no coincide o falta apertura\n");
      break;
    }
    case 2:
    {
      printf("ERROR: Faltan cierres, la pila no quedo vacia\n");
      break;
    }
    default:
    {
      printf("GOOD: Expresion balanceada\n");
    }
  }
}

int main(void)
{
  char expresion[EXPRESION_MAX_CHARS] = {0};

  t_analisis analisis = {0};

  do
  {
    limpiar_pantalla();

    printf("Ingresar una expresion de hasta %d caracteres, con ()[]{}\n", EXPRESION_MAX_CHARS - 1);
    printf("Escribir EXIT para terminar\n");

    leer_cadena_hasta_salto_de_linea(expresion, EXPRESION_MAX_CHARS);

    printf("%s\n", expresion);

    analizar_expresion(&analisis, expresion);
    printf("Presione ENTER para continar\n");
    while(getchar()!='\n');
    pila_tok_vaciar(&analisis);
  }
  while(!expresion_es_salir(expresion));

  return 0;
}
