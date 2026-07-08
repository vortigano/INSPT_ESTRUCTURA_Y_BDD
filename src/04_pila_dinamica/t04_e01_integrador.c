/*
  MATERIA:    Estructura y base de datos
  TITULO:     Pila dinámica
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-07-04 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1: Ejercicio integrador con estructura dinámica de tipo pila

  Escribir el código de una aplicación en C que permita realizar el ordenamiento de una pila, utilizando el algoritmo `qsort` y memoria dinámica.

  El desarrollo del programa consiste en vaciar la pila sobre un vector dinámico, ordenar el mismo y por último volcar la información ordenada sobre la pila.

  > Puede partir como base del código `pila_dinamica.c`
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct r nodo;

struct r
{
  int nro;
  nodo* ptr;
};

nodo* ingresarDato(void);
int pilaVacia(nodo*);
void apilar(nodo**,nodo*);
nodo desapilar(nodo**);
void mostrarDato(nodo);
void listarPila(nodo*);
void eliminarPila(nodo*);
int menu(void);

void apilarValor(nodo **p, int valor)
{
  nodo *q = (nodo*) malloc(sizeof(nodo));

  q->nro = valor;

  q->ptr=*p;
  *p=q;
}

int menor_que(const void *a, const void *b)
{
  return( (*(int*)a ) - (*(int*)b ) );
}

void ordenar(nodo **p)
{
  nodo *q = (*p);
  int   element_count = 0;
  while(q)
  {
    q = (q)->ptr;
    element_count++;
  }

  int *valores = (int*) malloc(sizeof(int) * element_count);

  q = (*p);
  element_count = 0;
  while(q)
  {
    valores[element_count] = q->nro;
    q = q->ptr;
    element_count++;
  }

  qsort(valores, element_count, sizeof(int), menor_que );

  while(*p)
  {
    desapilar(p);
  }

  for(int i=0; i<element_count; i++)
  {
    apilarValor(p, valores[i]);
  }

  free(valores);
}

int main(void)
{
  nodo *p,*q,dato;
  int op;
  p=NULL;
  srand(time(NULL));
  do
  {
    op=menu();
    switch(op)
    {
    case 1:
      q=ingresarDato();
      apilar(&p,q);
      break;
    case 2:
      if(pilaVacia(p))
      {
        dato=desapilar(&p);
        mostrarDato(dato);
      }
      break;
    case 3:
      if(pilaVacia(p))
        listarPila(p);
      break;
    case 4:
      if(pilaVacia(p))
        ordenar(&p);
      break;
    }
  }
  while(op<5);

  if(p!=NULL)
  {

    eliminarPila(p);
    pilaVacia(p);
  }
  return 0;
}

//**********************************************************************
nodo* ingresarDato(void)
{
  int nro;
  nodo *q;

  q=(nodo*)malloc(sizeof(nodo));

  system("cls");
  printf("\n\nIngrese un numero:  ");
  nro=rand()%(10-1+1)+1;
  //scanf("%d",&nro);

  q->nro=nro;
  return q;
}

//**********************************************************************
int pilaVacia(nodo*p)
{
  if(p==NULL)
  {
    system("cls");
    printf("\nPILA VACIA\n");
    system("pause");

    return 0;
  }
  else
    return 1;
}

//**********************************************************************
void apilar(nodo**p,nodo*q)
{
  q->ptr=*p;
  *p=q;
}
//**********************************************************************
nodo desapilar(nodo**p)
{
  nodo dato,*aux;
  aux=*p;
  dato=**p;
  *p=(*p)->ptr;
  free(aux);
  return dato;
}

//**********************************************************************
void mostrarDato(nodo dato)
{
  system("cls");
  printf("\n\n\nDato desapilado: %d",dato.nro);
  printf("\n\n");
  system("pause");
}
//**********************************************************************
void listarPila(nodo*p)
{
  system("cls");
  printf("\nCONTENIDO DE LA PILA\n\n");

  while(p)
  {
    printf("\tDireccion:<%p> dato:%d siguiente-> %p\n",(void *)p, p->nro, (void *)p->ptr);
    p=p->ptr;
  }
  printf("\n\n");
  system("pause");
}
//**********************************************************************
void eliminarPila(nodo*p)
{
  nodo *aux;
  while(p)
  {
    aux=p;
    p=p->ptr;
    free(aux);
  }
}
//**********************************************************************
int menu(void)
{
  int op;
  do
  {
    system("cls");
    printf("MENU DE OPCIONES\n\n");
    printf("1- Apilar\n");
    printf("2- Desapilar\n");
    printf("3- Listar\n");
    printf("4- Ordenar\n");
    printf("5- Salir\n");

    printf("Ingrese Opcion:  ");
    scanf("%d",&op);
    while(getchar()!='\n');
  }
  while(op<1||op>5);
  return op;
}
//**********************************************************************
