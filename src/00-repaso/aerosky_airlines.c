/*
  MATERIA:    Estructura y base de datos
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-05-01
  ESTUDIANTE: Alberto Martín Capurro

  Sistema de Gestión de Reservas para AeroSky Airlines
  Objetivo
  Desarrollar una aplicación para administrar la reserva de asientos en los vuelos de la aerolínea AeroSky Airlines. El sistema permitirá gestionar las solicitudes de los pasajeros de manera ordenada, optimizando la asignación de asientos y asegurando un control eficiente de la disponibilidad.
  Los asientos del avión estarán representados en una matriz bidimensional, donde cada uno será una estructura con la siguiente información:
  1. Número de fila (1 a 25).
  2. Letra de la columna del asiento ('A', 'B', 'C', 'D').
  3. Estado del asiento (disponible/reservado).
  4. Nombre del pasajero (si el asiento está reservado).

  Requisitos del Programa
  El sistema debe ofrecer un menú interactivo con las siguientes funciones:
  1. Realizar una reserva:
    • Pedir al usuario el número de fila (1 a 25) y la columna ('A', 'B', 'C', 'D').
    • Verificar si el asiento está disponible:
      o Si está libre, solicitar el nombre del pasajero y completar la reserva.
      o Si está ocupado, informar al usuario y permitirle elegir otro asiento.
  2. Cancelar una reserva:
    • Solicitar la fila y la columna del asiento a liberar.
    • Si el asiento está reservado, eliminar la reserva y marcarlo como disponible.
    • Si el asiento ya estaba libre, notificar al usuario.
  3. Mostrar estado del avión:
    • Listar todos los asientos, indicando si están disponibles o reservados.
    • Para los asientos ocupados, mostrar el nombre del pasajero.
  4. Buscar reservas por pasajero:
    • Solicitar el nombre de un pasajero.
    • Mostrar todos los asientos reservados a su nombre, si existen.
    • Informar cuántos asientos están libres y cuántos ocupados en total.
  5. Salir del programa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definición de la estructura Asiento
typedef struct
{
  int   fila;
  char  columna;
  int   ocupado; // 0 = libre, 1 = ocupado
  char  pasajero[50];
} Asiento;

// Definición de la matriz de asientos
#define FILAS 25
#define COLUMNAS 4
Asiento avion[FILAS][COLUMNAS];

// Prototipos de funciones
void  inicializarAsientos (Asiento avion[][COLUMNAS]);
void  pausa (void);
int   menu  (void);
void  reservarAsiento     (Asiento avion[][COLUMNAS]);
void  cancelarReserva     (Asiento avion[][COLUMNAS]);
void  mostrarEstado       (Asiento avion[][COLUMNAS]);
void  consultarReservas   (Asiento avion[][COLUMNAS]);

void  limpia_buffer_de_entrada();
int   avion_lleno(Asiento avion[][COLUMNAS]);

void  limpia_buffer_de_entrada()
{
  while(getchar()!='\n');
}

int avion_lleno(Asiento avion[][COLUMNAS])
{
  int pasajeros = 0;
  for(int x=0; x<COLUMNAS; x++)
  {
    for(int y=0; y<FILAS; y++)
    {
      pasajeros += avion[y][x].ocupado;
    }
  }
  return pasajeros == FILAS*COLUMNAS;
}

void  pausa(void)
{
  printf("Presiona ENTER para continuar...");
  limpia_buffer_de_entrada();
}

int main()
{
  int op;
  inicializarAsientos(avion);
  do
  {
    op = menu();
    system("cls");
    switch (op)
    {
    case 1:
      if(!avion_lleno(avion))
        reservarAsiento(avion);
      else
        printf("Imposible reservar, avion lleno!\n");
      break;
    case 2:
      cancelarReserva(avion);
      break;
    case 3:
      mostrarEstado(avion);
      break;
    case 4:
      consultarReservas(avion);
      break;
    }
  }
  while (op < 5);
  return 0;
}

void inicializarAsientos(Asiento avion[][COLUMNAS])
{
  for (int i = 0; i < FILAS; i++)
  {
    for (int j = 0; j < COLUMNAS; j++)
    {
      avion[i][j].fila = i + 1;
      avion[i][j].columna = 'A' + j;
      avion[i][j].ocupado = 0;
      strcpy(avion[i][j].pasajero, "");
    }
  }
}

int menu(void)
{
  int op;
  do
  {
    system("cls");
    printf("\n\t\t\t MENU DE RESERVAS DEL ESTACIONAMIENTO\n");
    printf("\n 1. Reservar un asiento\n");
    printf(" 2. Cancelar una reserva\n");
    printf(" 3. Mostrar asientos ocupados y libres\n");
    printf(" 4. Consultar reservas por pasajero\n");
    printf(" 5. Salir\n");
    printf(" Ingrese una opcion [1-5]: ");
    scanf("%d", &op);
    limpia_buffer_de_entrada();
  }
  while (op < 1 || op > 5);
  return op;
}

void  strtoupper(char* str)
{
  if(str!=NULL)
  {
    int i = 0;
    while(str[i]!='\0')
    {
      str[i] = toupper(str[i]);
      i++;
    }
  }
}

/*
  1. Realizar una reserva:
    • Pedir al usuario el número de fila (1 a 25) y la columna ('A', 'B', 'C', 'D').
    • Verificar si el asiento está disponible:
      o Si está libre, solicitar el nombre del pasajero y completar la reserva.
      o Si está ocupado, informar al usuario y permitirle elegir otro asiento.
*/
void  reservarAsiento     (Asiento avion[][COLUMNAS])
{
  int   numero_de_fila;
  char  columna   ;
  int   reintentar;

  do
  {
    numero_de_fila  = 0;
    columna         = 0;
    reintentar      = 0;

    printf("Ingrese numero de fila 1 a 25\n");
    scanf("%d", &numero_de_fila);
    limpia_buffer_de_entrada();
    pausa();

    if(numero_de_fila>=1 && numero_de_fila<=FILAS)
    {
      printf("Ingrese columna 'A','B','C','D'\n");
      scanf("%c", &columna);
      limpia_buffer_de_entrada();
      pausa();
      columna = toupper(columna);

      if(columna>='A' && columna <='D')
      {
        if(avion[numero_de_fila-1][columna - 'A'].ocupado)
        {
          printf("Asiento ocupado\n");
          reintentar = 1;
        }
        else
        {
          reintentar = 0;
          printf("Ingrese nombre de pasajero\n");
          scanf("%49s", avion[numero_de_fila-1][columna-'A'].pasajero);
          limpia_buffer_de_entrada();
          strtoupper(avion[numero_de_fila-1][columna-'A'].pasajero);
          avion[numero_de_fila-1][columna-'A'].ocupado = 1;
        }
      }
      else
      {
        printf("Columna fuera de rango, reintentando...\n");
        reintentar = 1;
      }
    }
    else
    {
      printf("Fila fuera de rango, reintentando...\n");
      reintentar = 1;
    }

  }
  while(reintentar);

  pausa();
}

/*
  2. Cancelar una reserva:
    • Solicitar la fila y la columna del asiento a liberar.
    • Si el asiento está reservado, eliminar la reserva y marcarlo como disponible.
    • Si el asiento ya estaba libre, notificar al usuario.
*/
void  cancelarReserva     (Asiento avion[][COLUMNAS])
{
  int   numero_de_fila;
  char  columna;

  printf("Ingrese numero de fila 1 a 25\n");
  scanf("%d", &numero_de_fila);
  limpia_buffer_de_entrada();

  if(numero_de_fila>=1 && numero_de_fila<=FILAS)
  {
    printf("Ingrese columna 'A','B','C','D'\n");
    scanf("%c", &columna);
    limpia_buffer_de_entrada();
    columna = toupper(columna);
    if(columna>='A' && columna <='D')
    {
      if(avion[numero_de_fila - 1][columna - 'A'].ocupado)
      {
        printf("Eliminando reserva...\n");
        avion[numero_de_fila - 1][columna - 'A'].ocupado      = 0;
        avion[numero_de_fila - 1][columna - 'A'].pasajero[0]  = '\0';
      }
      else
      {
        printf("El asiento no estaba ocupado, fila: %2d   columna: %2c\n", numero_de_fila, columna);
      }
    }
    else
    {
      printf("Columna fuera de rango %c\n", columna);
    }
  }
  else
    printf("Numero de fila fuera de rango %d\n", numero_de_fila);
  pausa();
}

/*
  3. Mostrar estado del avión:
    • Listar todos los asientos, indicando si están disponibles o reservados.
    • Para los asientos ocupados, mostrar el nombre del pasajero.
*/
void  mostrarEstado       (Asiento avion[][COLUMNAS])
{
  for (int i = 0; i < FILAS; i++)
  {
    for (int j = 0; j < COLUMNAS; j++)
    {
      if(avion[i][j].ocupado)
        printf("[%2d|%2c: %-13.13s]  ", i+1, 'A' + j, avion[i][j].pasajero);
      else
        printf("[%2d|%2c: %-13.13s]  ", i+1, 'A' + j, "LIBRE");
    }
    printf("\n");
  }
  pausa();
}

void  consultarReservas   (Asiento avion[][COLUMNAS])
{

}
