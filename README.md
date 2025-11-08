# Laboratorio 7 - Algoritmo de Prim (Árbol de Expansión Mínimo)

**Nombre:** Gabriela Antonia Sepúlveda Rojas  
**Asignatura:** Algoritmo y Estructura de Datos – Universidad de Talca  

## Descripción general

Este programa implementa el **algoritmo de Prim** para construir el **árbol de expansión mínima (MST)** de un grafo no dirigido y ponderado, representado mediante una **matriz de adyacencia NxN**, siendo estos datos ingresados por el usuario.

El algoritmo se ejecuta paso a paso, mostrando el progreso del conjunto **L** (los nodos agregados al MST) y genera dos visualizaciones con **Graphviz**:

- `grafo_original.png`: El cual muestra el grafo inicial completo.  
- `grafo_mst.png`: El cual muestra únicamente las aristas seleccionadas por Prim.

## Compilación

Para compilar el programa en terminal: g++ Sepulveda_Gabriela_Laboratorio7.cpp -o Sepulveda_Gabriela_Laboratorio7
Luego el programa solicitará:
- El número de nodos N (máximo 26).
- La matriz de adyacencia NxN, ingresada fila por fila (usa -1 o 0 cuando no exista conexión entre dos nodos).
- Los nodos se etiquetan automáticamente como letras: a, b, c, etc.

## Ejemplo de Ejecucion

Entrada de terminal:
- Ingrese N (numero de nodos, max 26): 5
- Ingrese la matriz 5x5 (use -1 o 0 si no hay arista):
0 2 4 0 0
2 0 1 7 0
4 1 0 3 5
0 7 3 0 6
0 0 5 6 0

Salida en terminal:
Matriz ingresada:
   -   2   4   -   -
   2   -   1   7   -
   4   1   -   3   5
   -   7   3   -   6
   -   -   5   6   -

--- Ejecutando algoritmo de Prim ---
Nodo inicial: a

> Nodo agregado al MST: a
L = { a }

> Nodo agregado al MST: b
L = { a b }

> Nodo agregado al MST: c
L = { a b c }

> Nodo agregado al MST: d
L = { a b c d }

> Nodo agregado al MST: e
L = { a b c d e }

--- Arbol de costo mínimo (MST) ---
   -   2   4   -   -
   2   -   1   -   -
   4   1   -   3   5
   -   -   3   -   6
   -   -   5   6   -

## Visualización con Graphviz

El programa genera automáticamente dos archivos DOT y sus respectivas imágenes:
- En el caso del `grafo_original.txt`, este genera el `grafo_original.png`.
- Y en el caso del `grafo_mst.tx", este genera el "grafo_mst.png`.
