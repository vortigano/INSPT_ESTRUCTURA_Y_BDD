# Ejercicio: Verificador de Paréntesis Balanceados (Pila Dinámica)

## Objetivo
Implementar una función que determine si una cadena de texto tiene sus paréntesis correctamente balanceados, utilizando una pila dinámica. Este es un ejercicio clásico para reforzar el uso de pilas y el patrón de validación de entrada.

## Descripción
Dada una cadena que contiene paréntesis `()`, corchetes `[]` y llaves `{}`, el programa debe indicar si están correctamente balanceados. Se considera balanceado si cada símbolo de apertura tiene su correspondiente símbolo de cierre en el orden correcto.

## Comportamiento esperado
- **Entrada:** `"({[]})"` → **Salida:** `"Balanceado"`
- **Entrada:** `"({[})"` → **Salida:** `"No balanceado"`
- **Entrada:** `"((("` → **Salida:** `"No balanceado"`
- **Entrada:** `"Hola mundo"` (sin paréntesis) → **Salida:** `"Balanceado"`

## Funcionalidades requeridas
1. **Leer una cadena** desde teclado (podés usar tu función `leer_cadena_hasta_salto_de_linea`).
2. **Recorrer la cadena** carácter por carácter.
3. **Si es un símbolo de apertura** (`(`, `[`, `{`), apilarlo.
4. **Si es un símbolo de cierre** (`)`, `]`, `}`), verificar que el tope de la pila sea su correspondiente apertura. Si coincide, desapilar. Si no, la cadena no está balanceada.
5. **Al finalizar**, si la pila está vacía, la cadena está balanceada. Si quedan elementos, no lo está.
6. **Liberar** la memoria de la pila al terminar.

## Consideraciones
- Implementar tu propia pila dinámica (sin depender de `pila_dinamica.c`).
- Usar tu patrón de validación para el menú de entrada.
- No es necesario un menú complejo; con una sola ejecución que pida la cadena y muestre el resultado alcanza.

## Extra opcional (si te sobra tiempo)
- Extenderlo para verificar también comillas dobles `"` y simples `'`, considerando que deben aparecer en pares.