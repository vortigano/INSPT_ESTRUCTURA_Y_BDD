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