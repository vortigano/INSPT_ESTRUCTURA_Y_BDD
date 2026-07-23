#include "analizador.h"
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

typedef struct ctx{
  t_analisis  analisis;
  t_error     error;
} ctx;

static t_nodo *pila_nodo_nuevo(t_token t)
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

static void pila_tok_apilar(t_analisis *analisis, t_token t)
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

static t_token pila_tok_desapilar(t_analisis *analisis)
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

static t_token pila_tok_peek(t_analisis *analisis)
{
  t_token token = {0, -1};

  if(analisis->pila != NULL)
  {
    token = analisis->pila->token;
  }
  return token;
}

static void pila_tok_vaciar(t_analisis *analisis)
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

void analizar_expresion(ctx *contexto, char * expresion)
{
  t_analisis *analisis = &contexto->analisis;
  pila_tok_vaciar(analisis);

  t_error error = {0,-1};
  
  const char COMILLA_DOBLE  = '\"';
  const char COMILLA_SIMPLE = '\'';
  typedef struct{
    int   en_cadena;
    char  delimitador;
    int   init_pos;
  } t_cadena_status;
  t_cadena_status cadena_status = {0, 0, 0};

  int i = 0;
  while(!error.code && *expresion)
  {
    #ifdef DEBUG
      printf("[%c]", *expresion);
    #endif
    t_token tok = {*expresion, i};
    if(*expresion == COMILLA_SIMPLE || *expresion == COMILLA_DOBLE)
    {
      if(!cadena_status.en_cadena)
      {
        cadena_status.en_cadena   = 1;
        cadena_status.delimitador = *expresion;
        cadena_status.init_pos    = i;
      }
      else if(*expresion == cadena_status.delimitador)
      {
        cadena_status.en_cadena   = 0;
        cadena_status.delimitador = 0;
        cadena_status.init_pos    = 0;
      }
    }

    if(!cadena_status.en_cadena)
    {
      switch(*expresion)
      {
        case ']':
        {
          if(pila_tok_peek(analisis).c!='[')
          {
            error.code  = 1;
            error.pos   = i;
          }
          else
            pila_tok_desapilar(analisis);
          break;
        }
        case '}':
        {
          if(pila_tok_peek(analisis).c!='{')
          {
            error.code  = 1;
            error.pos   = i;
          }
          else
            pila_tok_desapilar(analisis);
          break;
        }
        case ')':
        {
          if(pila_tok_peek(analisis).c!='(')
          {
            error.code  = 1;
            error.pos   = i;
          }
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
    }
    expresion++;
    i++;
  }
  
  if(cadena_status.en_cadena)
  {
    error.code  = 3;
    error.pos   = cadena_status.init_pos;
  }

  if(!error.code && analisis->pila != NULL)
  {
    error.code  = 2;
    error.pos   = pila_tok_peek(analisis).pos;
  }

  #ifdef DEBUG
  puts("");
  switch(error.code)
  {
    case 1:
    {
      for(int i=0; i<error.pos; i++)
      {
        printf(" ");
      }
      printf("^\n");
      printf("ERROR: error de cierre, no coincide o falta apertura\n");
      break;
    }
    case 2:
    {
      for(int i=0; i<error.pos; i++)
      {
        printf(" ");
      }
      printf("^\n");
      printf("ERROR: apertura sin cierre, la pila no quedo vacia\n");
      break;
    }
    case 3:
    {
      for(int i=0; i<error.pos; i++)
      {
        printf(" ");
      }
      printf("^\n");
      printf("ERROR: la cadena no tiene cierre\n");
      break;
    }
    default:
    {
      printf("GOOD: Expresion balanceada\n");
    }
  }
  #endif
  contexto->error.code  = error.code;
  contexto->error.pos   = error.pos;
}

t_error analizador_get_error(ctx* contexto)
{
  return contexto->error;
}

ctx *analizador_init()
{
  ctx *contexto = (ctx*) malloc(sizeof(ctx));
  if(contexto == NULL)
  {
    fprintf(stderr, "ERROR DE ASIGNACION DE MEMORIA\n");
    exit(1);
  }
  memset(&contexto->analisis, 0, sizeof(t_analisis));
  return contexto;
}

void analizador_finalize(ctx **contexto)
{
  if(contexto != NULL)
    free(*contexto);
}

//int main(void)
//{
//  char expresion[EXPRESION_MAX_CHARS] = {0};
//
//  t_analisis analisis = {0};
//
//  do
//  {
//    limpiar_pantalla();
//
//    printf("Ingresar una expresion de hasta %d caracteres, con ()[]{}\n", EXPRESION_MAX_CHARS - 1);
//    printf("Escribir EXIT para terminar\n");
//
//    leer_cadena_hasta_salto_de_linea(expresion, EXPRESION_MAX_CHARS);
//
//    //printf("%s\n", expresion);
//
//    analizar_expresion(&analisis, expresion);
//    printf("Presione ENTER para continuar\n");
//    while(getchar()!='\n');
//    pila_tok_vaciar(&analisis);
//  }
//  while(!expresion_es_salir(expresion));
//
//  return 0;
//}
