#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

void limpiar_pantalla   (void);
void leer_cadena_hasta_salto_de_linea (char *buffer, size_t buffer_size);
void string_to_upper    (unsigned char* buffer);
int  expresion_es_salir (char *buffer);

#endif