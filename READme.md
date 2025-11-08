# Laboratorio 6 - Algoritmo de Dijkstra con pasos intermedios y grafo

**Nombre:** Gabriela Antonia Sepúlveda Rojas  
**Asignatura:** Algoritmos y Estructura de Datos - Universidad de Talca

## Descripción general
Este laboratorio implementa el **Algoritmo de Dijkstra** en C++, mostrando todos los **pasos intermedios del proceso** (los conjuntos `S`, `VS` y el vector de distancias `D[]`) a medida que se van actualizando las distancias mínimas entre los nodos.
Además, genera una **visualización del grafo** utilizando **Graphviz**, con los nodos representados.

## Conceptos clave
- **Grafo dirigido ponderado:** Este representado mediante una matriz de tipo NxN.  
- **Peso `-1`:** Este indica ausencia de arista (un camino no existente).  
- **Dijkstra:** Este encuentra las rutas más cortas desde un nodo origen hacia todos los demás, actualizando progresivamente los valores de distancia mínima.  
- **Conjuntos:**
  - `S`: Nodos con distancia final determinada.
  - `VS`: Nodos pendientes de revisión.
  - `D[]`: Vector de distancias actuales.

## Estructura del programa

- Sepulveda_Gabriela_Laboratorio6.cpp - Código principal del programa
- gafo.txt - Archivo generado en formato Graphviz
- grafo.png - Imagen del grafo
- README.md 

## Compilación y ejecución

Desde una terminal: g++ Sepulveda_Gabriela_Laboratorio6.cpp -o Sepulveda_Gabriela_Laboratorio6 ./Sepulveda_Gabriela_Laboratorio6

Ejemplo de ejecución:
Ingrese N (numero de nodos, max 26): 5
Ingrese nodo origen (letra entre a y e): a
Ingrese la matriz 5x5 (fila por fila, use -1 para sin arista):
0 4 11 -1 -1
-1 0 -1 6 2
-1 3 0 6 -1
-1 -1 -1 0 -1
-1 -1 5 3 0

Salida en Consola:

- Estado inicial -
   0    4   11   -1   -1 
  -1    0   -1    6    2 
  -1    3    0    6   -1 
  -1   -1   -1    0   -1 
  -1   -1    5    3    0 

S = { }
VS = { b c d e }
D[] inicial:
a: 0   b: 4   c: 11   d: INF   e: INF

> Iter 1: elige vertice b con D = 4
> Actualizando distancias usando v = b
D[d] cambia: INF -> 10 (por b + 6)
D[e] cambia: INF -> 6 (por b + 2)
D[] ahora: a: 0   b: 4   c: 11   d: 10   e: 6
...
