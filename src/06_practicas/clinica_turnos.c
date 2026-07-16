/*
  PRACTICA:   Colas dinámicas
  TITULO:     Clínica de turnos
  FECHA:      2026-07-15 (AAAA-MM-DD)
  ESTUDIANTE: Alberto Martín Capurro

  # Ejercicio: Sistema de Turnos para una Clínica (Cola Dinámica)

  ## Objetivo
  Implementar un sistema de gestión de turnos para una clínica utilizando una cola dinámica. El objetivo es reforzar el manejo de estructuras FIFO, memoria dinámica y operaciones de búsqueda y eliminación sobre la cola.

  ## Descripción
  Cada paciente que llega a la clínica toma un turno y espera a ser atendido en orden de llegada. El sistema debe permitir registrar nuevos pacientes, atender al siguiente en la cola, consultar la lista de espera y realizar búsquedas o eliminaciones específicas.

  ## Información de cada turno
  - **ID del turno** (autoincremental, generado por el sistema).
  - **Nombre del paciente** (cadena de hasta 30 caracteres).
  - **Motivo de consulta** (cadena de hasta 50 caracteres).
  - **Obra social** (cadena de hasta 20 caracteres).

  ## Funcionalidades requeridas
  1. **Agregar un nuevo paciente a la cola.**
  2. **Atender al siguiente paciente** (sacarlo de la cola y mostrar sus datos).
  3. **Mostrar todos los pacientes en espera.**
  4. **Buscar un paciente por su ID de turno.**
  5. **Informar la cantidad de pacientes en espera.**
  6. **Eliminar todos los turnos de un paciente por su nombre** (case-insensitive).
  7. **Vaciar la cola de turnos.**
  8. **Salir.**

  ## Consideraciones
  - La eliminación por nombre debe conservar el orden relativo de los turnos restantes.
  - El ID de turno debe ser autoincremental (comienza en 1).
  - Utilizar menú interactivo con validación de entrada.
  - Implementar con cola dinámica y funciones propias (`encolar`, `desencolar`, etc.).
  - La comparación de nombres debe ser case-insensitive.

  ## Sugerencia
  Podés basarte en la estructura de tu `t05_e01_integrador.c` y adaptar el dominio.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define PACIENTE_NAME_MAX_LEN 30
#define PACIENTE_CONSULTA_MAX_LEN 50
#define PACIENTE_OBRA_SOCIAL_MAX_LEN 20

typedef struct {
  int   id_turno;
  char  nombre[PACIENTE_NAME_MAX_LEN];
  char  consulta_motivo[PACIENTE_CONSULTA_MAX_LEN];
  char  obra_social[PACIENTE_OBRA_SOCIAL_MAX_LEN];
} t_paciente;

typedef struct st_nodo{
  t_paciente paciente;
  struct st_nodo *sig;
} t_nodo;

typedef struct {
  int     id_count;
  t_nodo *head;
  t_nodo *tail;
} t_cola;

void mostrar_pacientes(t_cola *cola);
void agregar_paciente(t_cola *cola, t_paciente paciente);
t_paciente ingresar_paciente_datos();

int menu_clinica();

enum {
  CLINICA_AGREGAR_PACIENTE              = 1,
  CLINICA_ATENDER_PACIENTE              = 2,
  CLINICA_MOSTRAR_PACIENTES_EN_ESPERA   = 3,
  CLINICA_BUSCAR_PACIENTE_POR_ID        = 4,
  CLINICA_MOSTRAR_CANTIDAD_EN_ESPERA    = 5,
  CLINICA_ELIMINAR_TURNOS_POR_NOMBRE    = 6,
  CLINICA_VACIAR_TURNOS                 = 7,
  CLINICA_SALIR                         = 8
};

void string_to_upper(unsigned char* cadena)
{
  while(*cadena)
  {
    *cadena = toupper(*cadena);
    cadena ++;
  }
}

void leer_cadena_hasta_salto_de_linea(char *buffer, size_t buffer_size)
{
  int i=0;
  char c;

  while(i < buffer_size-1 && ( (c = getchar())!='\n') )
  {
    buffer[i] = c;
    i++;
  }
  buffer[i] = '\0';
  if(c!='\n') while(getchar()!='\n');
}

t_paciente ingresar_paciente_datos()
{
  t_paciente paciente_tmp;
  printf("Ingresar nombre de paciente\n");
  //scanf("%s", paciente_tmp.nombre);
  leer_cadena_hasta_salto_de_linea(paciente_tmp.nombre, PACIENTE_NAME_MAX_LEN);
  string_to_upper((unsigned char*) paciente_tmp.nombre);

  printf("Ingresar motivo de consulta\n");
  //scanf("%s", paciente_tmp.consulta_motivo);
  leer_cadena_hasta_salto_de_linea(paciente_tmp.consulta_motivo, PACIENTE_CONSULTA_MAX_LEN);
  string_to_upper((unsigned char*) paciente_tmp.consulta_motivo);

  printf("ingresar nombre obra social\n");
  //scanf("%s", paciente_tmp.obra_social);
  leer_cadena_hasta_salto_de_linea(paciente_tmp.obra_social, PACIENTE_OBRA_SOCIAL_MAX_LEN);
  string_to_upper((unsigned char*) paciente_tmp.obra_social);
  return paciente_tmp;
}

void limpiar_pantalla()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void inicialiar_turnos(t_cola *cola)
{
  t_paciente pacientes[] =
  {
    {0, "PACIENTE1", "MOTIVO1", "OBRASOCIAL1"},
    {0, "PACIENTE2", "MOTIVO2", "OBRASOCIAL2"},
    {0, "PACIENTE3", "MOTIVO3", "OBRASOCIAL1"},
    {0, "PACIENTE1", "MOTIVO4", "OBRASOCIAL1"},
    {0, "PACIENTE4", "MOTIVO5", "OBRASOCIAL3"},
    {0, "PACIENTE1", "MOTIVO6", "OBRASOCIAL1"},
    {0, "PACIENTE5", "MOTIVO7", "OBRASOCIAL2"}
  };

  for(int i=0; i< sizeof(pacientes)/sizeof(t_paciente); i++)
  {
    agregar_paciente(cola, pacientes[i]);
  }
}

t_paciente siguiente_paciente(t_cola *turnos)
{
  t_paciente paciente_tmp = {0};

  if(turnos->head != NULL)
  {
    paciente_tmp      = turnos->head->paciente;
    t_nodo *nodo_tmp  = turnos->head;
    turnos->head      = turnos->head->sig;
    if(turnos->head == NULL) turnos->tail = NULL;
    free(nodo_tmp);
  }
  else
  {
    paciente_tmp.id_turno = -1;
  }
  return paciente_tmp;
}

void mostrar_paciente(t_paciente *paciente);

int  cola_vacia(t_cola *turnos)
{
  return (turnos->head == NULL);
}

int cola_n_turnos(t_cola *turnos)
{
  int n_turnos = 0;

  t_nodo *cur = turnos->head;

  while(cur)
  {
    n_turnos ++;
    cur = cur->sig;
  }

  return n_turnos;
}

void cola_vaciar(t_cola *turnos)
{
  while(!cola_vacia(turnos))
  {
    siguiente_paciente(turnos);
  }
}

int ingresar_id_buscado()
{
  int id_buscado;
  int valido = 0;
  do
  {
    printf("Buscar paciente por ID (entero positivo)\n");
    printf("Ingrese el ID del turno del paciente buscado:");
    int scanned = scanf("%d", &id_buscado);
    while(getchar()!='\n');

    if(scanned != 1)
    {
      printf("ERROR DE LECTURA\n");
    }
    else if(id_buscado>0 && id_buscado<INT_MAX)
    {
      valido = 1;
    }
    else
    {
      printf("ERROR: ID buscado fuera de rango\n");
    }
  }
  while(!valido);

  return id_buscado;
}

t_paciente buscar_paciente_por_id(t_cola *turnos, int id_buscado)
{
  int encontrado      = 0;
  t_paciente paciente = {0};
  paciente.id_turno   = -1;

  t_nodo *cur = turnos->head;

  while(!encontrado && cur != NULL)
  {
    if(cur->paciente.id_turno == id_buscado)
    {
      paciente    = cur->paciente;
      encontrado  = 1;
    }
    cur = cur->sig;
  }

  return paciente;
}

int eliminar_turnos_por_nombre(t_cola *turnos, char *nombre)
{
  int registros_eliminados = 0;

  t_nodo *cur   = turnos->head;
  t_nodo *prev  = NULL;

  string_to_upper((unsigned char*) nombre);

  while(cur)
  {
    if(strcmp(cur->paciente.nombre, nombre)==0)
    {
      t_nodo *aux = cur;
      cur           = cur->sig;
      if(prev == NULL)
      {
        //cur           = cur->sig;             //factor común sale del if
        turnos->head  = cur;
        //if(cur == NULL) turnos->tail = NULL;  //factor común sale del if
      }
      else
      {
        //cur           = cur->sig;             //factor común sale del if
        prev->sig     = cur;
        //if(cur == NULL) turnos->tail = NULL;  //factor común sale del if
      }
      if(cur == NULL) turnos->tail = NULL;
      free(aux);
      registros_eliminados ++;
    }
    else
    {
      prev  = cur;
      cur   = cur->sig;
    }
  }

  return registros_eliminados;
}

int main(void)
{
  t_cola  turnos  = {0};

  inicialiar_turnos(&turnos);

  int opcion;

  do
  {
    opcion = menu_clinica();
    switch(opcion)
    {
      case CLINICA_AGREGAR_PACIENTE:
      {
        t_paciente paciente_tmp = ingresar_paciente_datos();
        agregar_paciente(&turnos, paciente_tmp);
        break;
      }
      case CLINICA_ATENDER_PACIENTE:
      {
        if(!cola_vacia(&turnos))
        {
          t_paciente paciente_tmp = siguiente_paciente(&turnos);
          mostrar_paciente(&paciente_tmp);
        }
        else
        {
          printf("No hay pacientes en espera\n");
        }
        while(getchar()!='\n');
        break;
      }
      case CLINICA_MOSTRAR_PACIENTES_EN_ESPERA:
      {
        if(!cola_vacia(&turnos))
        {
          printf("Pacientes en espera:\n");
          mostrar_pacientes(&turnos);
        }
        else
        {
          printf("No hay pacientes en espera\n");
        }
        while(getchar()!='\n');
        break;
      }
      case CLINICA_BUSCAR_PACIENTE_POR_ID:
      {
        if(!cola_vacia(&turnos))
        {
          int id_buscado = ingresar_id_buscado();
          t_paciente paciente = buscar_paciente_por_id(&turnos, id_buscado);
          if(paciente.id_turno > 0)
          {
            mostrar_paciente(&paciente);
          }
          else
          {
            printf("Ningun paciente tiene el turno %d\n", id_buscado);
          }
        }
        else
        {
          printf("No hay pacientes en espera\n");
        }
        while(getchar()!='\n');
        break;
      }
      case CLINICA_MOSTRAR_CANTIDAD_EN_ESPERA:
      {
        printf("Pacientes en espera %d\n", cola_n_turnos(&turnos));
        while(getchar()!='\n');
        break;
      }
      case CLINICA_ELIMINAR_TURNOS_POR_NOMBRE:
      {
        printf("Eliminar turnos por nombre de paciente\n");
        char nombre_buscado[PACIENTE_NAME_MAX_LEN] = {0};
        leer_cadena_hasta_salto_de_linea(nombre_buscado, PACIENTE_NAME_MAX_LEN);

        printf("Registros eliminados: %d\n",
               eliminar_turnos_por_nombre(&turnos, nombre_buscado));
        while(getchar()!='\n');
        break;
      }
      case CLINICA_VACIAR_TURNOS:
      {
        printf("Vaciado de cola de turnos\n");
        cola_vaciar(&turnos);
        while(getchar()!='\n');
        break;
      }
    }
  }
  while(opcion != CLINICA_SALIR);

  cola_vaciar(&turnos);
  return 0;
}

int menu_clinica()
{
  int opcion;
  int valido = 0;
  do
  {
    limpiar_pantalla();
    printf("  1. Agregar un nuevo paciente a la cola\n");
    printf("  2. Atender al siguiente paciente\n");
    // (sacarlo de la cola y mostrar sus datos)
    printf("  3. Mostrar todos los pacientes en espera\n");
    printf("  4. Buscar un paciente por su ID de turno\n");
    printf("  5. Informar la cantidad de pacientes en espera\n");
    printf("  6. Eliminar todos los turnos de un paciente por su nombre\n");
    // (case-insensitive)
    printf("  7. Vaciar la cola de turnos\n");
    printf("  8. Salir\n");

    int scanned = scanf("%d", &opcion);
    while(getchar()!='\n');

    if(scanned == 0)
    {
      printf("ERROR DE LECTURA\n");
      while(getchar()!='\n');
    }
    else if(opcion>=CLINICA_AGREGAR_PACIENTE && opcion<=CLINICA_SALIR)
    {
      valido = 1;
    }
    else
    {
      printf("ERROR: opcion fuera de rango\n");
      while(getchar()!='\n');
    }
  }
  while(!valido);

  return opcion;
}

void mostrar_paciente(t_paciente *paciente)
{
  printf("%3d: %30s %35s %20s\n",
         paciente->id_turno,
         paciente->nombre,
         paciente->consulta_motivo,
         paciente->obra_social);
}

void mostrar_pacientes(t_cola *cola)
{
  t_nodo *cur = cola->head;
  while(cur)
  {
    mostrar_paciente(&cur->paciente);
    cur = cur->sig;
  }
}

void agregar_paciente(t_cola *cola, t_paciente paciente)
{
  t_nodo *n = malloc(sizeof(t_nodo));
  n->paciente = paciente;
  n->paciente.id_turno = ++cola->id_count;

  if(cola->head == NULL)
  {
    cola->head  = n;
    cola->tail  = cola->head;
    n->sig      = NULL;
  }
  else
  {
    cola->tail->sig = n;
    cola->tail      = n;
    cola->tail->sig = NULL;
  }
}

