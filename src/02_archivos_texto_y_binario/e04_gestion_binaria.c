/*
  MATERIA:    Estructura y base de datos
  TITULO:     Ejercicios de archivos de texto y binario
  PROFESOR:   Lic. Jonathan G. Pécora
  FECHA:      2026-06-08
  ESTUDIANTE: Alberto Martín Capurro

  Sistema para gestión de ventas
  Desarrollar un programa que permita gestionar un sistema de ventas, donde se registran clientes y artículos en archivos binarios. Cada cliente tiene un código único, un nombre y un saldo inicial, mientras que cada artículo tiene un código único, un nombre, un precio, una cantidad en stock y una facturación acumulada.

  Estructuras
  typedef struct
  {
    int   cod_art;
    char  nom_art[20];
    float pre_art;
    int   sto_art;
    float fact_art;
  } regarti;

  typedef struct
  {
    int   cod_cli;
    char  nom_cli[20];
    float cuenta;
  } regcli;

  El sistema debe ofrecer las siguientes funcionalidades:

  Inicio del sistema: Al inicio, el programa carga desde una función llamada, los archivos binarios de clientes y artículos.

  Para nuestro pequeño modelo, lo tendremos en vectores, cuestión de agilizar la carga, inicializándo los registros con datos predefinidos de clientes y artículos.

  char  nomcli[][20]  = {"LOPEZ",     "RODRIGUEZ",    "GARCIA",   "MARTINEZ", "RAMIREZ"};
  char  nomart[][20]  = {"COCA COLA", "AGUA TONICA",  "N.FANTA",  "SPRITE",   "POMELO", "MANDARINA"};
  float pre[]         = {2000.70,     3000.75,        3000.66,    2000.80,    2000.89,  3000.01};
  int   sto[]         = {73,          120,            76,         34,         77,       98};

  Mostrar información: Permite visualizar la información de los clientes y los artículos almacenados en los archivos.

  Ingreso de ventas: Permite ingresar ventas asociadas a un número de factura. Para finalizar los ingresos pondremos número de factura igual a cero.

  Ahora bien, deberemos poder seleccionar un cliente por su código al igual que los artículos que le facturaremos. El programa verifica si la cantidad solicitada del artículo está disponible en el stock antes de registrar la venta. Si hay suficiente stock, actualiza
  la facturación del artículo y reduce la cantidad disponible en el mismo. Además, actualiza el saldo del cliente con el monto total de la compra.
  El programa puede ser finalizado ingresando un número de factura igual a cero.
*/
// Archivo: gestion_binaria.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 5
#define MAX_ARTICULOS 6

typedef struct {
  int   codigo;
  char  nombre[20];
  float saldo;
} Cliente;

typedef struct {
  int   codigo;
  char  nombre[20];
  float precio;
  int   stock;
  float facturado;
} Articulo;

// Prototipos
void tecla();
void linea(int n);
void inicializarDatos (FILE *archClientes, FILE *archArticulos);//ok
void mostrarDatos     (FILE *archClientes, FILE *archArticulos);//ok
void ingresarVentas   (FILE *archClientes, FILE *archArticulos);//ok

void inicializarDatos(FILE *archClientes, FILE *archArticulos) {
    Cliente clientes[MAX_CLIENTES] = {
      {1, "Lopez",      0},
      {2, "Rodriguez",  0},
      {3, "Garcia",     0},
      {4, "Martinez",   0},
      {5, "Perez",      0}
    };

    Articulo articulos[MAX_ARTICULOS] = {
      {100, "Coca Cola",      2000, 10, 0},
      {101, "Agua Tonica",    3500, 20, 0},
      {102, "Naranja Fanta",  3600, 15, 0},
      {103, "Sprite",         2800, 8,  0},
      {104, "Pomelo",         2500, 12, 0},
      {105, "Mandarina",      1500, 25, 0}
    };

    for(int i=0; i<MAX_CLIENTES; i++)
    {
      fwrite(&clientes[i], sizeof(Cliente), 1, archClientes);
    }
    for(int i=0; i<MAX_ARTICULOS; i++)
    {
      fwrite(&articulos[i], sizeof(Articulo), 1, archArticulos);
    }
}

int cliente_existe(FILE *archClientes, int clienteID, Cliente *cliente)
{
  int encontrado  = 0;
  rewind(archClientes);
  while(encontrado == 0 && !feof(archClientes))
  {
    if( fread(cliente, sizeof(Cliente), 1, archClientes)!=0 )
    {
      if(clienteID == cliente->codigo)
      {
        encontrado = 1;
      }
    }
  }

  return encontrado;
}
int articulo_existe(FILE *archArticulos, int articuloID, Articulo *art)
{
  int encontrado = 0;
  rewind(archArticulos);
  while(encontrado == 0 && !feof(archArticulos))
  {
    if( fread(art, sizeof(Articulo), 1, archArticulos)!=0 )
    {
      if(articuloID == art->codigo)
      {
        encontrado = 1;
      }
    }
  }

  return encontrado;
}

void actualizar_registro(FILE *archClientes, FILE *archArticulos, Cliente *cli, Articulo *art)
{
  rewind(archClientes);
  rewind(archArticulos);
  Cliente cli_temp  = {0};
  Articulo art_temp = {0};

  int encontrado    = 0;
  while(encontrado == 0 && !feof(archClientes))
  {
    if( fread(&cli_temp, sizeof(Cliente), 1, archClientes)!=0 )
    {
      if(cli->codigo == cli_temp.codigo)
      {
        encontrado = 1;
      }
    }
  }
  if(encontrado)
  {
    fseek(archClientes, (long) -(sizeof(Cliente)), SEEK_CUR);
    fwrite(cli, sizeof(Cliente), 1, archClientes);
  }
  encontrado = 0;
  while(encontrado == 0 && !feof(archArticulos))
  {
    if( fread(&art_temp, sizeof(Articulo), 1, archArticulos)!=0 )
    {
      if(art->codigo == art_temp.codigo)
      {
        encontrado = 1;
      }
    }
  }
  if(encontrado)
  {
    fseek(archArticulos, (long) -(sizeof(Articulo)), SEEK_CUR);
    fwrite(art, sizeof(Articulo), 1, archArticulos);
  }

  printf("Registros actualizados...");
  puts("presiona enter para continuar...");
  while(getchar()!='\n');
}

void ingresarVentas   (FILE *archClientes, FILE *archArticulos)
{
  // datos que necesito
  // cliente id , saber si existe y copiar registro (lectura)
  // articulos , articulo id, si existe copiar registro (lectura)
  // operar cliente id y articulos y grabar en ambos registros

  Cliente   cliente = {0};
  Articulo  articulo= {0};
  int clienteID_existe  = 0;
  int clienteID         = 0;
  int articuloID_existe = 0;
  int articuloID        = 0;
  do
  {
    printf("Ingresar cliente ID, 0 para terminar\n");
    scanf("%d", &clienteID);
    while(getchar()!='\n');

    if( (clienteID_existe = cliente_existe(archClientes, clienteID, &cliente)) )
    {
      clienteID = 0;
    }
  }while(clienteID!=0);

  if(clienteID_existe)
  {
    do
    {
      printf("Ingresar articulo ID, 0 para terminar\n");
      scanf("%d", &articuloID);
      while(getchar()!='\n');

      if( (articuloID_existe = articulo_existe(archArticulos, articuloID, &articulo)) )
      {
        int cantidad = 0;
        do
        {

          printf("Ingresar cantidad, 0 para terminar\n");
          scanf("%d", &cantidad);
          while(getchar()!='\n');

          if(cantidad>0)
          {
            if(articulo.stock >= cantidad)
            {
              cliente.saldo       += articulo.precio * cantidad;
              articulo.facturado  += articulo.precio * cantidad;
              articulo.stock      -= cantidad;
              actualizar_registro(archClientes, archArticulos, &cliente, &articulo);

              cantidad = 0;
            }
            else
            {
              printf("Articulo sin stock: %s %d\n", articulo.nombre, articulo.stock);
              if(articulo.stock == 0) { cantidad = 0; }
            }
          }
        }
        while(cantidad!=0);


      }

    }
    while(articuloID!=0);

  }


}

void mostrarDatos     (FILE *archClientes, FILE *archArticulos)
{
  Cliente   clitemp;
  Articulo  arttemp;

  int primera_lectura = 0;
  while(!feof(archArticulos))
  {
    if(fread(&arttemp, sizeof(Articulo), 1, archArticulos)==1)
    {
      if(primera_lectura == 0)
      {
        primera_lectura = 1;
        printf("+ART+-------NOMBRE-------+----PRECIO--+--FACTURADO-+--STOCK--+\n");
      }
      printf("|%3d|%20s| $%10.2f| $%10.2f|     %3d |\n",
             arttemp.codigo, arttemp.nombre, arttemp.precio,
             arttemp.facturado, arttemp.stock);
    }
  }
  if(primera_lectura!=0)
    printf("+---+--------------------+------------+------------+---------+\n");

  primera_lectura = 0;
  while(!feof(archClientes))
  {
    if(fread(&clitemp, sizeof(Cliente), 1, archClientes)==1)
    {
      if(primera_lectura == 0)
      {
        primera_lectura = 1;
        printf("+COD+-------NOMBRE-------+----SALDO---+\n");
      }
      printf("|%3d|%20s| $%10.2f|\n",
             clitemp.codigo, clitemp.nombre, clitemp.saldo);
    }
  }
  if(primera_lectura!=0)
    printf("+---+--------------------+------------+\n");

}


#define ARCHIVO_CLIENTES  "archclientes.bin"
#define ARCHIVO_ARTICULOS "archarticulo.bin"

int main(void)
{
  //Inicio del sistema: Al inicio, el programa carga desde una función llamada, los archivos binarios de clientes y artículos.

  FILE *archivo_clientes;
  FILE *archivo_articulos;

  if( (archivo_clientes = fopen(ARCHIVO_CLIENTES, "wb"))==NULL)
  {
    perror(ARCHIVO_CLIENTES);
    exit(1);
  }

  if( (archivo_articulos = fopen(ARCHIVO_ARTICULOS, "wb"))==NULL)
  {
    perror(ARCHIVO_ARTICULOS);
    exit(2);
  }

  inicializarDatos(archivo_clientes, archivo_articulos);
  fclose(archivo_articulos);
  fclose(archivo_clientes);

  if( (archivo_clientes = fopen(ARCHIVO_CLIENTES, "rb"))==NULL)
  {
    perror(ARCHIVO_CLIENTES);
    exit(3);
  }

  if( (archivo_articulos = fopen(ARCHIVO_ARTICULOS, "rb"))==NULL)
  {
    perror(ARCHIVO_ARTICULOS);
    exit(4);
  }
  mostrarDatos(archivo_clientes, archivo_articulos);
  fclose(archivo_articulos);
  fclose(archivo_clientes);

  if( (archivo_clientes = fopen(ARCHIVO_CLIENTES, "rb+"))==NULL)
  {
    perror(ARCHIVO_CLIENTES);
    exit(5);
  }
  if( (archivo_articulos = fopen(ARCHIVO_ARTICULOS, "rb+"))==NULL)
  {
    perror(ARCHIVO_ARTICULOS);
    exit(6);
  }
  int factura = -1;
  do
  {
    printf("Ingresar factura, cero para terminar\n");
    scanf("%d", &factura);
    while(getchar()!='\n');
    if(factura > 0)
    {
      printf("Factura aceptada %d\n", factura);
      ingresarVentas(archivo_clientes, archivo_articulos);
    }
  }
  while(factura != 0);
  fclose(archivo_articulos);
  fclose(archivo_clientes);


  if( (archivo_clientes = fopen(ARCHIVO_CLIENTES, "rb"))==NULL)
  {
    perror(ARCHIVO_CLIENTES);
    exit(3);
  }

  if( (archivo_articulos = fopen(ARCHIVO_ARTICULOS, "rb"))==NULL)
  {
    perror(ARCHIVO_ARTICULOS);
    exit(4);
  }
  mostrarDatos(archivo_clientes, archivo_articulos);
  fclose(archivo_articulos);
  fclose(archivo_clientes);
  return 0;
}
