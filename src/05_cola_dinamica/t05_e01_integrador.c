/*
  MATERIA:    Estructura y base de datos
  TITULO:     Cola dinamica
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-07-11 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 1: Ejercicio integrador con estructura dinámica de tipo cola

  # Ejercicio integrador con estructura dinámica de tipo cola

  ## Descripción
  Escribir el código de una aplicación en lenguaje C que simule la cola de impresión de una impresora compartida.

  ## Información del trabajo de impresión
  Cada trabajo de impresión deberá almacenar la siguiente información:
  - Identificador del trabajo.
  - Nombre del documento.
  - Cantidad de páginas.
  - Nombre del usuario que envió el trabajo.

  ## Funcionalidades
  El programa deberá permitir:
  1. Agregar un nuevo trabajo de impresión.
  2. Imprimir el siguiente documento de la cola.
  3. Mostrar los trabajos pendientes.
  4. Buscar un trabajo por su identificador.
  5. Informar la cantidad de trabajos pendientes.
  6. Eliminar todos los trabajos enviados por un usuario determinado.
  7. Vaciar la cola de impresión.
  8. Salir.

  ## Consideraciones adicionales
  - La eliminación por usuario deberá remover todos los trabajos enviados por dicho usuario, conservando el orden relativo de los trabajos restantes en la cola.
  - La aplicación deberá implementarse mediante una cola dinámica, utilizando memoria dinámica para la creación y eliminación de nodos, y respetando el orden FIFO.

  ## Requisitos Técnicos
  - Estructura de datos: cola dinámica (FIFO).
  - Gestión de memoria dinámica con `malloc()` y `free()`.
  - Modularización del código (al menos funciones para agregar, imprimir, mostrar, buscar, contar, eliminar por usuario, vaciar y salir).

  > **Nota:** Puede partir como base del código `cola_dinamica.c`.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
  ## Información del trabajo de impresión
  Cada trabajo de impresión deberá almacenar la siguiente información:
- Identificador del trabajo.
- Nombre del documento.
- Cantidad de páginas.
- Nombre del usuario que envió el trabajo.
*/

#define NOMBRE_DE_DOCUMENTO_MAX_LEN 50
#define NOMBRE_DE_USUARIO_MAX_LEN   50

typedef struct
{
  int id;
  char nombre_de_documento[NOMBRE_DE_DOCUMENTO_MAX_LEN];
  int paginas;
  char nombre_de_usuario[NOMBRE_DE_USUARIO_MAX_LEN];
} t_trabajo;

typedef struct elemento
{
  t_trabajo trabajo;
  //int dato;
  struct elemento *sig;
} nodo;

enum {
  OPCION_AGREGAR_NUEVO_TRABAJO = 1,
  OPCION_IMPRIMIR_SIGUIENTE_DOC,
  OPCION_MOSTRAR_TRABAJOS_PENDIENTES,
  OPCION_BUSCAR_UN_TRABAJO_POR_ID,
  OPCION_INFORMAR_CANT_DE_TRABAJOS_PENDIENTES,
  OPCION_ELIMINAR_TRABAJOS_POR_USUARIO,
  OPCION_VACIAR_COLA_DE_IMPRESION,
  OPCION_SALIR
};

void acolar(nodo, nodo **, nodo **);
nodo *nuevonodo(nodo);
nodo desacolar(nodo **);
void vaciar(nodo **);
nodo *verificar(nodo *);
nodo ingresar_trabajo(int *);
void dato_eliminado(nodo);
int menu(void);
void listar(nodo *);
void mostrar_trabajo(t_trabajo *trab)
{
  printf("ID: %3d, UN: %8s, PG: %3d, DN: %8s\n", trab->id, trab->nombre_de_usuario,  trab->paginas, trab->nombre_de_documento);
}

nodo ingresar_trabajo_auto(t_trabajo t, int *);
void string_to_upper(unsigned char* buffer);

void inicialiar_cola_de_impresion(nodo **p, nodo **q, int *idcount)
{
  t_trabajo trab[] = {
    {0, "DOC1", 22, "USER_1"},
    {0, "DOC2", 22, "USER_1"},
    {0, "DOC3", 22, "USER_2"},
    {0, "DOC4", 22, "USER_3"},
    {0, "DOC5", 22, "USER_2"},
    {0, "DOC6", 22, "USER_3"},
    {0, "DOC7", 22, "USER_2"},
    {0, "DOC8", 22, "USER_4"}
  };

  for(int i=0; i<(sizeof(trab) / sizeof(t_trabajo)); i++)
  {
    nodo r = ingresar_trabajo_auto(trab[i], idcount);
    acolar(r, p, q);
  }
}

nodo ingresar_trabajo_auto(t_trabajo t, int *idcount)
{
  nodo r;
  (*idcount)++;
  r.trabajo.id = *idcount;
  printf("id: %d\n", r.trabajo.id);
  strcpy(r.trabajo.nombre_de_usuario, t.nombre_de_usuario);
  string_to_upper((unsigned char*) r.trabajo.nombre_de_usuario);
  strcpy(r.trabajo.nombre_de_documento, t.nombre_de_documento);
  string_to_upper((unsigned char*) r.trabajo.nombre_de_documento);
  r.trabajo.paginas = t.paginas;

  mostrar_trabajo(&r.trabajo);
  return (r);
}

void leer_cadena_hasta_salto_de_linea(char *buffer, size_t buffer_size);

int main()
{
  nodo *p = NULL, *q, r;
  int op;
  system("cls");
  int idcount = 0;
  inicialiar_cola_de_impresion(&p, &q, &idcount);
  do
  {
    op = menu();
    switch (op)
    {
      case OPCION_AGREGAR_NUEVO_TRABAJO:
      {
        r = ingresar_trabajo(&idcount);
        acolar(r, &p, &q);
        break;
      }
      case OPCION_IMPRIMIR_SIGUIENTE_DOC:
      {
        if(p!=NULL)
        {
          nodo desacolado = desacolar(&p);
          printf("-------- IMPRIMIENDO --------\n");
          mostrar_trabajo(&desacolado.trabajo);
          printf("-----------------------------\n");
          printf("Presione ENTER para continuar\n");
          while(getchar()!='\n');
        }
        else
        {
          printf("No hay documentos pendientes de impresion, cola vacia\n");
          while(getchar()!='\n');
        }
        break;
      }
      case OPCION_INFORMAR_CANT_DE_TRABAJOS_PENDIENTES:
      {

        nodo *cursor = p;
        int trabajos_pendientes = 0;
        while(cursor)
        {
          cursor = cursor->sig;
          trabajos_pendientes++;
        }
        printf("Trabajos pendientes: %d\n", trabajos_pendientes);
        printf("Presione ENTER para continuar\n");
        while(getchar()!='\n');
        break;
      }
      case OPCION_BUSCAR_UN_TRABAJO_POR_ID:
      {
        if( verificar(p) != NULL)
        {
          //ingresar ID
          //repetir hasta que termine la cola o se encuentre el ID
          //buscar coincidencia de ID
          //si existe un trabajo en un nodo con dicho ID mostrarlo
          int id_buscado    = 0;
          int id_encontrado = 0;
          printf("ingresar ID:");
          scanf("%d", &id_buscado);
          while(getchar()!='\n');

          nodo *cursor = p;

          while(cursor && !id_encontrado)
          {
            if(cursor->trabajo.id == id_buscado)
            {
              id_encontrado = 1;
              mostrar_trabajo(&cursor->trabajo);
            }
            else
              cursor = cursor->sig;
          }
          if(!id_encontrado)
          {
            printf("No se halla el ID %d\n", id_buscado);
          }
        }
        else
        {
          printf("Cola de impresion vacia\n");
        }
        printf("Presione ENTER para continuar\n");
        while(getchar()!='\n');
        break;
      }
      case OPCION_ELIMINAR_TRABAJOS_POR_USUARIO:
      {
        if (verificar(p) != NULL)
        {
          //ingresar usuario
          //repetir hasta que termine la cola
          //buscar usuario
          //si existe un trabajo en un nodo con dicho usuario eliminar nodo
          char nombre[NOMBRE_DE_USUARIO_MAX_LEN]="";
          printf("Ingresar nombre de usuario:");
          leer_cadena_hasta_salto_de_linea(nombre, NOMBRE_DE_USUARIO_MAX_LEN);
          string_to_upper((unsigned char*) nombre);
          printf("Nombre ingresado: [%s]\n", nombre);

          nodo *cursor  = p;
          nodo *prev    = NULL;
          while(cursor)
          {
            if(strcmp(cursor->trabajo.nombre_de_usuario,nombre)==0)
            {
              printf("nodo mismo usuario!!!\n");
              if(p==cursor)
              {
                nodo *aux = cursor;
                cursor    = cursor->sig;
                p         = cursor;
                if(p==NULL) q=NULL;
                free(aux);
              }
              else
              {
                nodo *aux = cursor;
                if(q == cursor)
                {
                  q = prev;
                  q->sig = NULL;
                  cursor = NULL;
                  free(aux);
                }
                else
                {
                  cursor    = cursor->sig;
                  prev->sig = cursor;
                  free(aux);
                }
              }
            }
            else
            {
              prev    = cursor;
              cursor  = cursor->sig;
            }
          }


          while(getchar()!='\n');
        }
        else
        {
          printf("Cola de impresion vacia\n");
        }
        printf("Presiona ENTER para continuar...\n");
        while(getchar()!='\n');
        break;
      }
      case OPCION_MOSTRAR_TRABAJOS_PENDIENTES:
      {
        if (verificar(p) != NULL)
        {
          printf("Trabajos pendientes:\n");
          listar(p);
        }
        else
        {
          printf("Cola de impresion vacia\n");
        }
        while(getchar()!='\n');
        break;
      }
      case OPCION_VACIAR_COLA_DE_IMPRESION:
      {
        if (verificar(p) != NULL)
          vaciar(&p);
        break;
      }
      case OPCION_SALIR:
      {
        if (verificar(p) != NULL)
          vaciar(&p);
        break;
      }
      default:
      {
        printf("Funcionalidad no implementada todavia\n");
      }
    }
  }
  while (op != OPCION_SALIR);
  return 0;
} // CIERRA MAIN
//**********************************************************************
nodo *nuevonodo(nodo r)
{
  nodo *x;
  x = (nodo *)malloc(sizeof(nodo));
  //x->dato = r.dato; //*x=r;
  memcpy(&x->trabajo, &r.trabajo, sizeof(t_trabajo));
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
    //printf("\t\t%d\n", p->dato);
    mostrar_trabajo(&p->trabajo);
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
  //if (p == NULL)
  //{
  //  system("cls"); // clrscr();
  //  printf("\nCola vacia!");
  //  printf("\n\n\n\nPulse enter para continuar...");
  //  while(getchar()!='\n');
  //}
  return (p);
} // CIERRA VERIFICAR
//**********************************************************************
void leer_cadena_hasta_salto_de_linea(char *buffer, size_t buffer_size)
{
  int index = 0;
  char c = 0;
  while( (index < buffer_size-1) && ((c = getchar())!='\n') )
  {
    buffer[index] = c;
    index ++;
  }
  buffer[index] = '\0';
  if(c == '\n') ungetc(c, stdin);
}

void string_to_upper(unsigned char* buffer)
{
  while(*buffer)
  {
    *buffer = toupper(*buffer);
    buffer++;
  }
}

nodo ingresar_trabajo(int *idcount)
{
  nodo r;
  system("cls"); // clrscr();
  (*idcount) ++;
  r.trabajo.id = *idcount;
  printf("id: %d\n", r.trabajo.id);
  printf("Ingrese un nombre de usuario: ");
  leer_cadena_hasta_salto_de_linea(r.trabajo.nombre_de_usuario, NOMBRE_DE_USUARIO_MAX_LEN);
  string_to_upper((unsigned char*) r.trabajo.nombre_de_usuario);
  while(getchar()!='\n');
  printf("Ingrese un nombre de documento: ");
  leer_cadena_hasta_salto_de_linea(r.trabajo.nombre_de_documento, NOMBRE_DE_DOCUMENTO_MAX_LEN);
  string_to_upper((unsigned char*) r.trabajo.nombre_de_documento);
  while(getchar()!='\n');
  printf("Ingrese numero de paginas: ");
  scanf("%d", &r.trabajo.paginas);
  while(getchar()!='\n');

  mostrar_trabajo(&r.trabajo);
  printf("Presione enter para continuar...\n");
  while(getchar()!='\n');
  return (r);
} // CIERRA INGRESAR_DATO
//**********************************************************************
void dato_eliminado(nodo r)
{
  system("cls"); // clrscr();
  //printf("Valor eliminado: %d\n", r.dato);
  mostrar_trabajo(&r.trabajo);
  printf("Pulse una tecla para continuar...\n");
  while(getchar()!='\n');
} // CIERRA DATO_ELIMINADO
//**********************************************************************
/*
  ## Funcionalidades
  El programa deberá permitir:
  1. Agregar un nuevo trabajo de impresión.
  2. Imprimir el siguiente documento de la cola.
  3. Mostrar los trabajos pendientes.
  4. Buscar un trabajo por su identificador.
  5. Informar la cantidad de trabajos pendientes.
  6. Eliminar todos los trabajos enviados por un usuario determinado.
  7. Vaciar la cola de impresión.
  8. Salir.
*/
int menu(void)
{
  int op;
  do
  {
    system("cls");
    printf("+----------------------------- Menu principal -----------------------------+\n");
    printf("|%2d. Agregar un nuevo trabajo de impresion.                                |\n",
           OPCION_AGREGAR_NUEVO_TRABAJO);
    printf("|%2d. Imprimir el siguiente documento de la cola.                           |\n",
           OPCION_IMPRIMIR_SIGUIENTE_DOC);
    printf("|%2d. Mostrar los trabajos pendientes.                                      |\n",
           OPCION_MOSTRAR_TRABAJOS_PENDIENTES);
    printf("|%2d. Buscar un trabajo por su identificador.                               |\n",
           OPCION_BUSCAR_UN_TRABAJO_POR_ID);
    printf("|%2d. Informar la cantidad de trabajos pendientes.                          |\n",
           OPCION_INFORMAR_CANT_DE_TRABAJOS_PENDIENTES);
    printf("|%2d. Eliminar todos los trabajos enviados por un usuario determinado.      |\n",
           OPCION_ELIMINAR_TRABAJOS_POR_USUARIO);
    printf("|%2d. Vaciar la cola de impresion.                                          |\n",
           OPCION_VACIAR_COLA_DE_IMPRESION);
    printf("+--------------------------------------------------------------------------+\n");
    printf("|%2d. Salir.                                                                |\n",OPCION_SALIR);
    printf("+--------------------------------------------------------------------------+\n");
    printf("Opcion nro.: ");
    scanf("%d", &op);
    while(getchar()!='\n');
  }
  while (op < 1 || op > 8);
  return (op);
} // CIERRA MENU
