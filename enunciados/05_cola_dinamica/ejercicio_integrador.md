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