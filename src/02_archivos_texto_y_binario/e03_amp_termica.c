/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de archivos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-06-08
  ESTUDIANTE: Alberto Martín Capurro

  Sistema para gestión de registros de temperatura por ciudad

  Se necesita desarrollar un sistema que registre las temperaturas máximas y mínimas por día, de un determinado mes.

  El mismo debe permitir al usuario realizar las siguientes operaciones:
  - Ingreso de Registros: El usuario puede ingresar registros de temperatura para diferentes
    ciudades, incluyendo el código de la ciudad, el nombre, las temperaturas mínima y máxima registradas.
    El fin de la carga es ingresando código de ciudad igual a cero.
    El desarrollo debe tener control de ese ingreso, lo que significa que si se ingresa
    un código de ciudad que ya existe, el sistema no debe permitir el ingreso del mismo.
    También, el sistema debe controlar el correcto ingreso de las temperaturas, siendo
    la máxima mayor a la mínima y obviamente la mínima menor a la máxima.
    Una vez realizado en ingreso, se tendrán que visualizar los siguientes resultados:

  - Visualización de Estadísticas: El sistema proporciona una opción para que el usuario
    pueda ver estadísticas sobre las temperaturas registradas, incluyendo la temperatura mínima,
    máxima y la amplitud térmica (diferencia entre la temperatura máxima y mínima) de cada ciudad.
    ESTADISTICA DE TEMPERATURA DE CIUDADES
    COD    CIUDAD     MINIMA  MAXIMA  AMPLITUD
    1   Mar del Plata 4.00    25.00   21.00
    2   La Pampa      2.00    20.00   18.00
    3   San Nicolas   6.00    30.00   24.00

    la amplitud máxima es 24.00 y corresponde a  la ciudad de San Nicolás.

  - Identificación de Amplitud Máxima: Además, el sistema identifica y muestra la ciudad
    con la mayor amplitud térmica registrada.

    El sistema utiliza un archivo binario para almacenar los registros de temperaturas
    correspondientes a las ciudades a través del siguiente
    struct:
    typedef struct {
      int cod_ciu;
      char nom_ciu[30];
      float t_min;
      float t_max;
      float dif_t;
    } registro;
*/

#include <stdio.h>
#include <stdlib.h>

#define NOM_CIU_LEN 30
typedef struct
{
  int   cod_ciu;
  char  nom_ciu[NOM_CIU_LEN];
  float t_min;
  float t_max;
  float dif_t;
} registro;

#define STRING_FORMAT_LEN 16
#define ARCHIVO_DE_TEMPERATURAS "temp.dat"

void archivo_crear_o_vaciar(char *nombre)
{
  FILE *src;

  if( (src = fopen(nombre, "wb")) == NULL)
  {
    perror(nombre);
    exit(1);
  }
  fclose(src);
}

void pausa()
{
  printf("Presiona enter para continuar...\n");
  while(getchar()!='\n');
}

void guardar_registro_en_disco(char *archivo_nombre, registro *reg)
{
  FILE *src;
  if( (src = fopen(archivo_nombre, "rb+")) == NULL)
  {
    perror(archivo_nombre);
    exit(2);
  }
  fseek(src, 0, SEEK_END);
  fwrite(reg, sizeof(registro), 1, src);
  fclose(src);
}

int  existe_registro_en_disco(char *archivo_nombre, int id_registro)
{
  FILE *src;
  if( (src = fopen(archivo_nombre, "rb+")) == NULL)
  {
    perror(archivo_nombre);
    exit(2);
  }
  rewind(src);

  registro reg = {0};
  int encontrado = 0;

  while(!encontrado && !feof(src))
  {
    if(fread(&reg, sizeof(registro), 1, src) != 0)
    {
      if(reg.cod_ciu == id_registro)
      {
        encontrado = 1;
      }
    }
  }

  fclose(src);

  return encontrado;
}

// - Visualización de Estadísticas: El sistema proporciona una opción para que el usuario
//   pueda ver estadísticas sobre las temperaturas registradas, incluyendo la temperatura mínima,
//   máxima y la amplitud térmica (diferencia entre la temperatura máxima y mínima) de cada ciudad.
//   ESTADISTICA DE TEMPERATURA DE CIUDADES
//   COD    CIUDAD     MINIMA  MAXIMA  AMPLITUD
//   1   Mar del Plata 4.00    25.00   21.00
//   2   La Pampa      2.00    20.00   18.00
//   3   San Nicolas   6.00    30.00   24.00
//
//   la amplitud máxima es 24.00 y corresponde a  la ciudad de San Nicolás.
//
// - Identificación de Amplitud Máxima: Además, el sistema identifica y muestra la ciudad
//   con la mayor amplitud térmica registrada.

void mostrar_estadisticas(char *archivo_nombre)
{
  FILE *src;
  if( (src = fopen(archivo_nombre, "rb+")) == NULL)
  {
    perror(archivo_nombre);
    exit(2);
  }
  rewind(src);
  int   primera_lectura = 1;
  int   temp_amp_max_count = 0;
  float temp_amp_max;

  registro reg = {0};

  while(!feof(src))
  {
    if(fread(&reg, sizeof(registro), 1, src) != 0)
    {
      if(primera_lectura == 1)
      {
        printf(" COD %16s %8s %8s %8s\n", "NOM CIUD", "MAXIMA", "MINIMA", "AMPLITUD");
      }
      printf("%04d %16s %8.2f %8.2f %8.2f\n", reg.cod_ciu, reg.nom_ciu, reg.t_max, reg.t_min, reg.dif_t);
      if(primera_lectura == 1)
      {
        primera_lectura = 0;
        temp_amp_max_count++;
        temp_amp_max    = reg.dif_t;
      }
      else
      {
        if(temp_amp_max < reg.dif_t)
        {
          temp_amp_max_count = 1;
          temp_amp_max = reg.dif_t;
        }
        else
        if(temp_amp_max == reg.dif_t)
        {
          temp_amp_max_count++;
          temp_amp_max = reg.dif_t;
        }
      }
    }
  }

  rewind(src);
  printf("------- Amplitudes maximas registradas %d-------\n", temp_amp_max_count);
  while(!feof(src))
  {
    if(fread(&reg, sizeof(registro), 1, src) != 0)
    {
      if(reg.dif_t == temp_amp_max)
      {
        if(temp_amp_max_count==1)
          printf("La amplitud maxima es %8.2f y corresponde a la ciudad de %s.\n",
               reg.dif_t, reg.nom_ciu);
        else
          printf("- %8.2f %s.\n",
               reg.dif_t, reg.nom_ciu);
      }
    }
  }

  fclose(src);
}

int main(void)
{
  int limpiar = 0;
  printf("Limpiar base de registros? 1=si\n");
  scanf("%d", &limpiar);
  while(getchar()!='\n');

  if(limpiar == 1)
  {
    archivo_crear_o_vaciar(ARCHIVO_DE_TEMPERATURAS);
  }

  /*
  - Ingreso de Registros: El usuario puede ingresar registros de temperatura para diferentes
    ciudades, incluyendo el código de la ciudad, el nombre, las temperaturas mínima y máxima registradas.
    El fin de la carga es ingresando código de ciudad igual a cero.
    El desarrollo debe tener control de ese ingreso, lo que significa que si se ingresa
    un código de ciudad que ya existe, el sistema no debe permitir el ingreso del mismo.
    También, el sistema debe controlar el correcto ingreso de las temperaturas, siendo
    la máxima mayor a la mínima y obviamente la mínima menor a la máxima.
  */

  registro reg = {0};

  int cod_ciud = -1;
  int terminar = 0;
  do
  {

    printf("Ingresar codigo de ciudad, cero para terminar\n");
    scanf("%d", &cod_ciud);
    while(getchar()!='\n');

    if(cod_ciud == 0)
      terminar = 1;
    else
    {
      // buscar registro en disco
      // registro ciudad existe

      if(existe_registro_en_disco(ARCHIVO_DE_TEMPERATURAS, cod_ciud))
      {
        printf("Codigo de ciudad %d ya existe!!!\n", cod_ciud);
      }
      else
      {
        reg.cod_ciu = cod_ciud;
        // obtener registro por teclado
        printf("Ingrear nombre de la ciudad\n");

        char fmt[STRING_FORMAT_LEN];
        sprintf(fmt, "%%%d[^\\n]", NOM_CIU_LEN-1);
        scanf(fmt, reg.nom_ciu);
        while(getchar()!='\n');

        do
        {
          printf("La temperatura minima debe ser menor que la maxima\n");
          printf("Ingresar temperatura minima\n");
          scanf("%f", &reg.t_min);
          while(getchar()!='\n');
          printf("Ingresar temperatura maxima\n");
          scanf("%f", &reg.t_max);
          while(getchar()!='\n');
        }
        while(reg.t_max <= reg.t_min);
        reg.dif_t = reg.t_max - reg.t_min;

        printf("reg %03d %s %f %f %f\n", reg.cod_ciu, reg.nom_ciu, reg.t_max, reg.t_min, reg.dif_t);

        printf("Guardando a disco...\n");
        // guardar registro en disco
        guardar_registro_en_disco(ARCHIVO_DE_TEMPERATURAS, &reg);
      }

    }
  }
  while(terminar!=1);

  pausa();


  // - Visualización de Estadísticas: El sistema proporciona una opción para que el usuario
  //   pueda ver estadísticas sobre las temperaturas registradas, incluyendo la temperatura mínima,
  //   máxima y la amplitud térmica (diferencia entre la temperatura máxima y mínima) de cada ciudad.
  //   ESTADISTICA DE TEMPERATURA DE CIUDADES
  //   COD    CIUDAD     MINIMA  MAXIMA  AMPLITUD
  //   1   Mar del Plata 4.00    25.00   21.00
  //   2   La Pampa      2.00    20.00   18.00
  //   3   San Nicolas   6.00    30.00   24.00
  //
  //   la amplitud máxima es 24.00 y corresponde a  la ciudad de San Nicolás.
  //
  // - Identificación de Amplitud Máxima: Además, el sistema identifica y muestra la ciudad
  //   con la mayor amplitud térmica registrada.

  mostrar_estadisticas(ARCHIVO_DE_TEMPERATURAS);

  return 0;
}

