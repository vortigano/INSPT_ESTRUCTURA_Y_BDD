# El Último Palito con Pilas Dinámicas

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