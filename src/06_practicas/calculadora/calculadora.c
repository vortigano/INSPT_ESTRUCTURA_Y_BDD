#include <stdio.h>
#include "analizador.h"
#include "utils.h"


int main()
{
  
  ctx *contexto_analizador = analizador_init();

  char expresion[256]={0};
  int  terminar = 0;
  do
  {
    limpiar_pantalla();
    printf("Ingrese expresion (EXIT para salir): ");
    leer_cadena_hasta_salto_de_linea(expresion, sizeof(expresion));

    string_to_upper((unsigned char*)expresion);
    terminar = expresion_es_salir(expresion);

    analizar_expresion(contexto_analizador, expresion);
    t_error err = analizador_get_error(contexto_analizador);

    if (err.code == 0)
    {
      printf("GOOD: Expresion balanceada\n");
    } else {
      printf("ERROR: codigo %d, posicion %d\n", err.code, err.pos);
    }
    printf("Presione ENTER para continuar...");
    while(getchar()!='\n');

  } while (!terminar);

  analizador_finalize(&contexto_analizador);

  return 0;
}