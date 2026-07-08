/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ultimo palito pierde
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-07-04 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  EJERCICIO 2: El Último Palito con Pilas Dinámicas

  ## Objetivo
  Implementar el juego “El Último Palito Pierde” utilizando pilas dinámicas para representar los palitos disponibles. El objetivo es profundizar en el manejo de estructuras dinámicas tipo pila (LIFO) en lenguaje C.

  ## Descripción del Juego
  Dos jugadores (o un jugador y la computadora) se turnan para retirar entre 1 y N palitos de una pila. El jugador que se ve obligado a sacar el último palito pierde.

  ## Reglas
  - El juego parte de una pila que contiene una cierta cantidad de palitos (por defecto 30).
  - En cada turno, un jugador puede retirar entre 1 y N palitos (por defecto 3).
  - El jugador que retire el último palito de la pila pierde la partida.
  - Visualizar los palitos como una serie de barras verticales |, una por cada nodo de la pila.
  - El juego finaliza cuando la pila queda vacía.

  ## Requisitos Técnicos
  - El programa debe ser modular, con al menos 8 funciones distintas, sugeridas:
    - `inicializarPila()`
    - `apilar()`
    - `desapilar()`
    - `mostrarPila()`
    - `jugarTurno()`
    - `menuPrincipal()`
    - `jugarVsJugador()`
    - `jugarVsCPU()`

  ``` c
  typedef struct nodo {
   char valor; // representar palito como '|'
   struct nodo* sig;
  } nodo;
  ```
  Implementar un Menu Principal, que tenga
  ```
  1. Jugar
  2. Cambiar palitos iniciales (default: 30)
  3. Cambiar máximo de palitos a sacar por turno (default: 3)
  0. Salir
  ```

  ## Comportamiento esperado
  - El usuario elige si juega contra otro jugador o contra la computadora.
  - En cada turno, se desapilan la cantidad de palitos que el jugador indica (validar límites).
  - El juego muestra visualmente los palitos restantes (ej.: `|||||||||||||`).
  - Cuando queda un solo palito y es el turno del jugador, pierde.
  - Si juega contra la computadora, el CPU elige una cantidad aleatoria entre 1 y el máximo permitido.
  - Agregar función `vaciarPila()` para liberar memoria al finalizar.
  - Agregar opción de volver al menú tras finalizar una partida.
  - Agregar mensaje personalizado al perder (ej. `"¡Jugador2 perdió! Se quedó con el último palito."`)

  Si elige cambiar la cantidad máxima de palitos a sacar:
  - El valor a sacar por turno: mínimo 3, máximo 10% del total de palitos iniciales (no menor a 3).
  - Si eso ocurre, se debe mostrar un mensaje de error y pedir un valor valido.
*/
#ifdef _WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>

#define PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE  10.0

#define PALITOS_INICIALES_MAX_SUPERIOR  100
#define PALITOS_INICIALES_MIN           30
#define PALITOS_INICIALES_DEFAULT 30
#define PALITOS_POR_TURNO_DEFAULT 3
#define PALITOS_POR_TURNO_MIN     3

typedef struct nodo
{
  char valor; // representar palito como '|'
  struct nodo* sig;
} nodo;

enum {MODO_DE_JUEGO_1_V_1 = 1, MODO_DE_JUEGO_1_V_CPU};
typedef struct
{
  nodo *palitos_pila;
  int palitos_iniciales;
  int palitos_por_turno;
  int modo_de_juego;
  int turno; //
} t_game_context;

void pausa(char *fmt, char *msg)
{
  printf(fmt, msg);
  while(getchar()!='\n');
}

void mostrar_partida(t_game_context *ctx);

void limpiar_pantalla()
{
  #ifdef __WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void titulo()
{
  printf("+--  ULTIMO PALITO PIERDE  ---------------  ALBERTO MARTIN CAPURRO  --+\n");
  printf("|  Profesor: Lic. Jonathan G. Pecora                                  |\n");
  printf("|  Materia : Estructura y Base de datos  -  Pilas dinamicas           |\n");
  printf("+---------------------------------------------------------------------+\n");
}

double palitos_maximo_por_turno(t_game_context *ctx)
{
  return ctx->palitos_iniciales * PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE * 0.01;
}

void menu_palitos_por_turno(t_game_context *ctx)
{
  int opcion;
  int cancelado = 0;
  int valido    = 0;
  do
  {
    limpiar_pantalla();
    titulo();
    printf("|  Ingresar cantidad de palitos por turno a sacar maximo              |\n");
    printf("|    Minimo   : %6d                     Maximo   : %6.0f          |\n",
           PALITOS_POR_TURNO_MIN, floor(palitos_maximo_por_turno(ctx)));
    printf("+---------------------------------------------------------------------+\n");
    printf("|    Palitos por turno: %6d                                        |\n",
           ctx->palitos_por_turno);
    printf("+---------------------------------------------------------------------+\n");
    printf("|  0. Salir                                                           |\n");
    printf("+---------------------------------------------------------------------+\n");
    int scanned = scanf("%d", &opcion);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      pausa("%s\n", "ERROR: lectura no valida");
    }
    else if(opcion >= PALITOS_POR_TURNO_MIN && opcion <= floor(palitos_maximo_por_turno(ctx)))
    {
      valido = 1;
    }
    else if(opcion == 0)
    {
      cancelado = 1;
    }
    else
    {
      pausa("%s\n", "ERROR: dato fuera de rango");
    }
  }
  while(!cancelado && !valido);

  if(valido)
  {
    ctx->palitos_por_turno = opcion;
    // asegurarse que el máximo de palitos a sacar
    // sea menor o igual al 10% de los palitos iniciales
    if( ctx->palitos_por_turno >
        ctx->palitos_iniciales * PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE * 0.01 )
    {
      char *msg   = NULL;
      int msg_len = snprintf(
                     msg,
                     0,
                     "INFO: El numero de palitos por turno debe ser menor \
o igual a %%%6.2f de los palitos iniciales",
                     PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE);
      msg = (char*) malloc(sizeof(char) * msg_len + 1);
      sprintf(
        msg,
        "INFO: El numero de palitos por turno debe ser menor \
o igual a %.0f%% de los palitos iniciales",
        PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE);

      pausa("%s\n", msg);
      ctx->palitos_por_turno =
        ctx->palitos_iniciales * PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE * 0.01;
      free(msg);
    }
  }
}

void menu_palitos_iniciales(t_game_context *ctx)
{
  int opcion;
  int cancelado = 0;
  int valido    = 0;
  do
  {
    limpiar_pantalla();
    titulo();
    printf("|  Ingresar cantidad de palitos iniciales                             |\n");
    printf("|    Minimo   : %6d                     Maximo   : %6d          |\n", PALITOS_INICIALES_MIN, PALITOS_INICIALES_MAX_SUPERIOR);
    printf("+---------------------------------------------------------------------+\n");
    printf("|    Inciales : %6d                                                |\n", ctx->palitos_iniciales);
    printf("+---------------------------------------------------------------------+\n");
    printf("|  0. Salir                                                           |\n");
    printf("+---------------------------------------------------------------------+\n");
    int scanned = scanf("%d", &opcion);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      pausa("%s\n", "ERROR: lectura no valida");
    }
    else if(opcion >= PALITOS_INICIALES_MIN && opcion <= PALITOS_INICIALES_MAX_SUPERIOR)
    {
      valido = 1;
    }
    else if(opcion == 0)
    {
      cancelado = 1;
    }
    else
    {
      pausa("%s\n", "ERROR: dato fuera de rango");
    }
  }
  while(!cancelado && !valido);

  if(valido)
  {
    ctx->palitos_iniciales = opcion;
    // asegurarse que el máximo de palitos a sacar
    // sea menor o igual al 10% de los palitos iniciales
    if( ctx->palitos_por_turno >
        ctx->palitos_iniciales * PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE * 0.01 )
    {
      ctx->palitos_por_turno =
        ctx->palitos_iniciales * PALITOS_POR_TURNO_DEFAULT_MAX_PORCENTAJE * 0.01;
    }
  }
}

int menu_principal(t_game_context *ctx)
{
  int opcion;
  int cancelado = 0;
  int valido    = 0;
  do
  {
    limpiar_pantalla();
    titulo();
    printf("|  1. Jugar                                                           |\n");
    printf("|  2. Cambiar palitos iniciales : %6d                              |\n", ctx->palitos_iniciales);
    printf("|  3. Cambiar maximo de palitos a sacar por turno : %4d              |\n", ctx->palitos_por_turno);
    printf("+---------------------------------------------------------------------+\n");
    printf("|  0. Salir                                                           |\n");
    printf("+---------------------------------------------------------------------+\n");
    int scanned = scanf("%d", &opcion);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      printf("ERROR: lectura no valida\n");
    }
    else if(opcion >= 0 && opcion <= 3)
    {
      valido = 1;
    }
    else
    {
      printf("ERROR: opcion invalida\n");
    }
  }
  while(!cancelado && !valido);


  return opcion;
}

int menu_modo()
{
  int opcion    =-1;
  int cancelado = 0;
  int valido    = 0;

  do
  {
    limpiar_pantalla();
    titulo();
    printf("|  Seleccione modo de juego contra                                    |\n");
    printf("|    %d. Humano                                                        |\n", MODO_DE_JUEGO_1_V_1);
    printf("|    %d. CPU                                                           |\n", MODO_DE_JUEGO_1_V_CPU);
    printf("+---------------------------------------------------------------------+\n");
    printf("|  0. Salir                                                           |\n");
    printf("+---------------------------------------------------------------------+\n");
    int scanned = scanf("%d", &opcion);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      printf("ERROR: lectura no valida\n");
    }
    else if(opcion >=1 && opcion <=2)
    {
      valido = 1;
    }
    else if(opcion == 0)
    {
      printf("Cancelado\n");
      cancelado = 1;
    }
    else
    {
      printf("ERROR: opcion invalida\n");
    }
  }
  while(!cancelado && !valido);

  return opcion;
}

void pila_apilar(t_game_context *ctx, nodo *n)
{
  n->valor  = '|';
  n->sig            = ctx->palitos_pila;
  ctx->palitos_pila = n;
}

nodo* pila_desapilar(t_game_context *ctx)
{
  nodo* nodo_temp;

  nodo_temp = ctx->palitos_pila;
  if(ctx->palitos_pila)
    ctx->palitos_pila = ctx->palitos_pila->sig;

  return nodo_temp;
}

int pila_vacia(t_game_context *ctx)
{
  return ( ctx->palitos_pila == NULL );
}

void pila_mostrar(t_game_context *ctx)
{
  nodo *n = ctx->palitos_pila;
  printf("Palitos restantes:");
  while(n)
  {
    printf("%c", n->valor);
    n = n->sig;
  }
  printf("\n");
}

void pila_iniciar(t_game_context *ctx)
{
  if(pila_vacia(ctx))
  {
    nodo *n = NULL;

    for(int i=0; i<ctx->palitos_iniciales; i++)
    {
      if ( (n = (nodo*) malloc(sizeof(nodo))) == NULL)
      {
        fprintf(stderr, "ERROR ASIGNANDO MEMORIA PARA NODO\n");
        exit(1);
      }
      pila_apilar(ctx, n);
    }
  }
  else
    pausa("\n%s\n","ERROR: intento por iniciar pila que no estaba vacia!!\n");
}

int pila_es_ultimo_palito(t_game_context *ctx)
{
  return (ctx->palitos_pila && ctx->palitos_pila->sig==NULL);
}

void pila_vaciar(t_game_context *ctx)
{
  while(ctx->palitos_pila)
  {
    nodo *n = pila_desapilar(ctx);
    // Liberar NULL es SEGURO, liberar sin miedo
    // pila_desapilar() no puede retornar una dirección ya liberada
    free(n);
  }
}

void pila_desapilar_lote(t_game_context *ctx, int cantidad)
{
  while(!pila_es_ultimo_palito(ctx) && cantidad > 0)
  {
    free(pila_desapilar(ctx));
    cantidad--;
    mostrar_partida(ctx);
  }
}

char* modo_de_juego_to_ascii(t_game_context *ctx)
{
  char *retorno = "";

  if(ctx->modo_de_juego==MODO_DE_JUEGO_1_V_1)
  {
    retorno = "Modo de juego 1v1";
  }
  else if(ctx->modo_de_juego==MODO_DE_JUEGO_1_V_CPU)
  {
    retorno = "Modo de juego 1vCPU";
  }

  return retorno;
}

char* turno_de_to_ascii(t_game_context *ctx)
{
  char *retorno = "";

  switch(ctx->modo_de_juego)
  {
    case MODO_DE_JUEGO_1_V_1:
    {
      if(ctx->turno % 2 == 0)
      {
        retorno = "Jugador 1";
      }
      else
        retorno = "Jugador 2";
      break;
    }

    case MODO_DE_JUEGO_1_V_CPU:
    {
      if(ctx->turno % 2 == 0)
      {
        retorno = "Jugador 1";
      }
      else
        retorno = "Jugador CPU";
      break;
    }
  }

  return retorno;
}

void mostrar_partida(t_game_context *ctx)
{
  limpiar_pantalla();
  titulo();
  printf("|  %-24s                                           |\n", modo_de_juego_to_ascii(ctx));
  printf("|  %-24s                                           |\n", turno_de_to_ascii(ctx));
  printf("+---------------------------------------------------------------------+\n");

  pila_mostrar(ctx);
}

void juega_jugador(t_game_context *ctx)
{
  int cantidad;
  int valido    = 0;
  do
  {
    limpiar_pantalla();
    mostrar_partida(ctx);
    printf("%s, ingrese cantidad de palitos a quitar\n", turno_de_to_ascii(ctx));
    printf("Cantidad minima: %d\n", 1);
    printf("Cantidad maxima: %d\n", ctx->palitos_por_turno);

    int scanned = scanf("%d", &cantidad);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      pausa("%s\n", "ERROR: lectura invalida\n");
    }
    else if(cantidad >= 1 && cantidad <= ctx->palitos_por_turno )
    {
      valido = 1;
    }
    else
    {
      pausa("%s\n", "ERROR: cantidad de palitos no permitida\n");
    }
  }
  while(!valido);

  //desapila lo pedido si puede
  pila_desapilar_lote(ctx, cantidad);
}

void demora(int milisecs)
{
  #ifdef _WIN32
    Sleep(milisecs);
  #else
    //posix unistd.h
    usleep(milisecs * 1000);
  #endif
}

void juega_cpu(t_game_context *ctx)
{
  int cantidad;

  limpiar_pantalla();
  mostrar_partida(ctx);
  printf("%s, ingrese cantidad de palitos a quitar\n", turno_de_to_ascii(ctx));
  printf("Cantidad minima: %d\n", 1);
  printf("Cantidad maxima: %d\n", ctx->palitos_por_turno);

  demora(2000);
  // rango [1,N]
  cantidad = (rand()%(ctx->palitos_por_turno))+1 ;
  printf("%d\n", cantidad);

  demora(2000);

  //desapila lo pedido si puede
  pila_desapilar_lote(ctx, cantidad);
}

void jugar(t_game_context *ctx)
{
  ctx->turno = 0;
  pila_iniciar(ctx);

  do
  {
    mostrar_partida(ctx);

    switch(ctx->modo_de_juego)
    {
      case MODO_DE_JUEGO_1_V_1:
      {
        juega_jugador(ctx);
        break;
      }
      case MODO_DE_JUEGO_1_V_CPU:
      {
        if(ctx->turno % 2 == 0)
        {
          juega_jugador(ctx);
        }
        else
          juega_cpu(ctx);
        break;
      }
    }

    if(!pila_es_ultimo_palito(ctx)) ctx->turno++;
  }
  while(!pila_es_ultimo_palito(ctx));

  mostrar_partida(ctx);

  printf("%s, ha sido derrotado, se quedo con el ultimo palito!!!\n", turno_de_to_ascii(ctx));

  if(!pila_vacia(ctx)) pila_vaciar(ctx);
}

void partida(t_game_context *ctx)
{
  int opcion = menu_modo();

  switch(opcion)
  {
    case 0:
    {
      pausa("%s\n", "INFO: Volviendo a menu principal");
      break;
    }
    case MODO_DE_JUEGO_1_V_1:
    {
      ctx->modo_de_juego = opcion;
      jugar(ctx);

      pausa("%s\n", "INFO: Partida terminada\n");
      break;
    }
    case MODO_DE_JUEGO_1_V_CPU:
    {
      ctx->modo_de_juego = opcion;
      jugar(ctx);

      pausa("%s\n", "INFO: Partida terminada\n");
      break;
    }
  }
}

int main(void)
{
  srand(time(NULL));

  int salir = 0;

  t_game_context ctx = {0};

  ctx.palitos_pila       = NULL;
  ctx.palitos_iniciales  = PALITOS_INICIALES_DEFAULT;
  ctx.palitos_por_turno  = PALITOS_POR_TURNO_DEFAULT;
  ctx.modo_de_juego      = MODO_DE_JUEGO_1_V_CPU;
  while(!salir)
  {
    int opcion = menu_principal(&ctx);

    switch(opcion)
    {
      case 0:
      {
        salir = 1;
        pausa("%s\n", "Saliendo del juego...");
        break;
      }
      case 1:
      {
        partida(&ctx);
        break;
      }
      case 2:
      {
        menu_palitos_iniciales(&ctx);
        break;
      }
      case 3:
      {
        menu_palitos_por_turno(&ctx);
        break;
      }
    }
  }
  return 0;
}
