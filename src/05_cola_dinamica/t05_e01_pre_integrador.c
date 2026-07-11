/*
  MATERIA:    Estructura y base de datos
  TITULO:     Cola dinamica
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-07-09 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO: pre integrador con estructura dinámica de tipo cola

  Escribir el código de una aplicación en C que permita realizar el ordenamiento de una cola, utilizando el algoritmo `qsort` y memoria dinámica.

El desarrollo del programa consiste en vaciar la cola sobre un vector dinámico, ordenar el mismo y por último volcar la información ordenada sobre la cola.

> Puede partir como base del código `cola_dinamica.c`
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento
{
  int dato;
  struct elemento *sig;
} nodo;

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void listar(nodo *);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_dato(void);
void dato_eliminado(nodo);
int menu(void);

typedef enum {
  COLA_OPCION_PRE_ACOLAR    = 1,
  COLA_OPCION_PRE_DESACOLAR = 2,
  COLA_OPCION_PRE_LISTAR    = 3,
  COLA_OPCION_PRE_ORDENAR   = 4,
  COLA_OPCION_PRE_VACIAR    = 5,
  COLA_OPCION_PRE_SALIR     = 6
} t_menu_cola_opciones;

int cola_n_elementos(nodo *p)
{
  nodo *n_tmp     = p;
  int n_elementos = 0;
  while(n_tmp)
  {
    n_elementos ++;
    n_tmp = n_tmp->sig;
  }
  return n_elementos;
}

int mayor_que(const void *a, const void *b)
{
  return ( (*(int*) a) - (*(int*) b) );
}

void ordenar(nodo **p, nodo **q)
{
  int n_elementos = cola_n_elementos(*p);
  int *valores = (int *) malloc(sizeof(int) * n_elementos);

  if(n_elementos > 0)
  {
    int i = 0;
    while(*p)
    {
      nodo nodo_tmp = desacolar(p);
      valores[i] = nodo_tmp.dato;
      i++;
    }

    qsort(valores, n_elementos, sizeof(int), mayor_que);

    #ifdef DEBUG
    for(int i=0; i<n_elementos; i++)
    {
      printf("%d", valores[i]);
      if(i<n_elementos-1) printf("-");
    }
    printf("\n");
    #endif

    for(int i=0; i<n_elementos; i++)
    {
      nodo nodo_tmp = {valores[i], NULL};
      acolar(nodo_tmp, p, q);
    }
  }

  free(valores);
  printf("Presiona ENTER para continuar\n");
  while(getchar()!='\n');
}

int main()
{
  nodo *p = NULL, *q, r;
  int op;
  //system("cls");
  //system("color 9f");
  do
  {
    op = menu();
    switch (op)
    {
      case COLA_OPCION_PRE_ACOLAR:
      {
        r = ingresar_dato();
        acolar(r, &p, &q);
        break;
      }
      case COLA_OPCION_PRE_DESACOLAR:
      {
        if (verificar(p) != NULL)
        {
          r = desacolar(&p);
          dato_eliminado(r);
        }
        break;
      }
      case COLA_OPCION_PRE_LISTAR:
      {
        if (verificar(p) != NULL)
        {
          printf("Contenido de la cola:\n");
          listar(p);
          while(getchar()!='\n');
        }
        break;
      }
      case COLA_OPCION_PRE_VACIAR:
      {
        if (verificar(p) != NULL)
          vaciar(&p);
        break;
      }
      case COLA_OPCION_PRE_ORDENAR:
      {
        printf("ORDENANDO...\n");
        ordenar(&p, &q);
        break;
      }
      case COLA_OPCION_PRE_SALIR:
      {
        printf("Saliendo de la aplicacion\n");
      }
    }
  } while (op != COLA_OPCION_PRE_SALIR);
  if (verificar(p) != NULL)
    vaciar(&p);
  return 0;
} // CIERRA MAIN
//**********************************************************************
nodo *nuevonodo(nodo r)
{
    nodo *x;
    x = (nodo *)malloc(sizeof(nodo));
    x->dato = r.dato; //*x=r;
    x->sig = NULL;
    return (x);
}
//**********************************************************************
void acolar(nodo r, nodo **p, nodo **q)
{
    nodo *nuevo;
    nuevo = nuevonodo(r);
    if (*p == NULL)
        *p = nuevo;
    else
        (*q)->sig = nuevo;
    *q = nuevo;
} // CIERRA ACOLAR
//**********************************************************************
nodo desacolar(nodo **p)
{
    nodo r, *aux;
    r = **p;
    aux = *p;
    *p = (*p)->sig;
    free(aux);
    return (r);
} // CIERRA DESACOLAR
//**********************************************************************
void listar(nodo *p)
{
    if (p)
    {
        printf(" - %4d\n", p->dato);
        listar(p->sig);
    }
} // CIERRA LISTAR
//**********************************************************************
void vaciar(nodo **p)
{
    nodo *aux;
    while (*p != NULL)
    {
        aux = *p;
        *p = (*p)->sig;
        free(aux);
    }
} // CIERRA VACIAR
//**********************************************************************
nodo *verificar(nodo *p)
{
    if (p == NULL)
    {
        printf("Cola vaciada!\n");
        printf("Pulse ENTER para continuar...\n");
        while(getchar()!='\n');
    }
    return (p);
} // CIERRA VERIFICAR
//**********************************************************************
nodo ingresar_dato(void)
{
    nodo r;
    system("cls"); // clrscr();
    printf("\nIngrese un nro.: ");
    scanf("%d", &r.dato);
    while(getchar()!='\n');
    return (r);
} // CIERRA INGRESAR_DATO
//**********************************************************************
void dato_eliminado(nodo r)
{
    system("cls"); // clrscr();
    printf("\nValor eliminado: %d", r.dato);
    printf("\n\n\nPulse ENTER para continuar...");
    while(getchar()!='\n');
} // CIERRA DATO_ELIMINADO
//**********************************************************************
int menu(void)
{
    int op;

    do
    {
        system("cls");
        printf("Menu principal\n");

        printf("%2d - Acolar   \n", COLA_OPCION_PRE_ACOLAR);
        printf("%2d - Desacolar\n", COLA_OPCION_PRE_DESACOLAR);
        printf("%2d - Listar   \n", COLA_OPCION_PRE_LISTAR);
        printf("%2d - Ordenar  \n", COLA_OPCION_PRE_ORDENAR);
        printf("%2d - Vaciar   \n", COLA_OPCION_PRE_VACIAR);
        printf("%2d - Salir    \n", COLA_OPCION_PRE_SALIR);

        printf("Opcion nro.:");
        scanf("%d", &op);
        while(getchar()!='\n');
    } while (op < 1 || op > 6);
    return (op);
} // CIERRA MENU
