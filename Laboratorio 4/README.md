Laboratorio 4 - Árboles Binarios de Búsqueda

Nombre: Gabriela Antonia Sepúlveda Rojas
Asignatura: Algoritmos y Estructuras de Datos
Carrera: Ingeniería Civil en Bioinformática - Universidad de Talca

Descripción:
Este programa implementa un Árbol Binario de Búsqueda (ABB) que almacena números enteros.
Permite realizar operaciones básicas sobre la estructura y genera un grafo visual mediante la herramienta Graphviz.

Estructura del código:
- Nodo: Estructura base del ABB.
- insertarNodo, eliminarNodo, existe: Operaciones fundamentales del árbol.
- preorden, inorden, posorden: Recorridos recursivos.
- generarDot, escribirGraphviz, generarYAbrirGrafo: Generación y visualización con Graphviz.
- leerEntero, leerSiNo: Validaciones seguras de entrada.
- liberarArbol: Libera toda la memoria antes de salir.

Funcionalidades principales:
1. Insertar número: Agrega un nuevo valor al árbol, evitando duplicados.
2. Eliminar número:	Elimina un valor existente, manejando correctamente los casos de 0, 1 o 2 hijos.
3. Modificar número: Reemplaza un valor viejo por uno nuevo (internamente elimina e inserta).
4. Mostrar recorridos: Imprime los recorridos según el orden (Preorden, Inorden y Posorden).
5. Generar grafo (Graphviz): Crea un archivo grafo.txt y genera grafo.png mostrando la estructura del árbol.
6. Cargar conjunto de ejemplo: Inserta el conjunto de prueba especificado en la guía.
7. Eliminar árbol: Libera la memoria del árbol actual.
8. Salir: Termina el programa limpiamente.

Conjunto de ejemplo: 120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56
Recorrido esperado: 
- Preorden: 120 - 87 - 43 - 22 - 65 - 56 - 99 - 93 - 140 - 130 - 135
- Inorden: 22 - 43 - 56 - 65 - 87 - 93 - 99 - 120 - 130 - 135 - 140
- Posorden: 22 - 56 - 65 - 43 - 93 - 99 - 87 - 135 - 130 - 140 - 120

Ejecución:
- Compilación: g++ Sepulveda_Gabriela_Laboratorio4.cpp -o Sepulveda_Gabriela_Laboratorio4
- Ejecución: ./Sepulveda_Gabriela_Laboratorio4