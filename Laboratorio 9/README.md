# Laboratorio 9 - Tablas Hash

**Autora:** Gabriela Antonia Sepúlveda Rojas  
**Asignatura:** Algoritmo y Estructura de Datos - Universidad de Talca

## Descripción
Este laboratorio implementa una **tabla hash de tamaño fijo (20 datos)**, utilizando cuatro métodos de manejo de colisiones estudiados en clases:
1. Método lineal (L)}
2. Método Cuadrático (C)
3. Método Doble Dirección (D)
4. Encadenamiento (E)
El programa permite **insertar, buscar e imprimir** la tabla con diversos valores entregado spor el usuario, como también la posibilidad de **cargar automáticamente los datos de ejemplo de la guía de laboratorio N°9**.


## Métodos implementados
1. Lineal - Si hay colisión en h1(k), se prueba: h(k, i) = (h1(k) + i) % 20
2. Cuadrática - Incrementación de cuadrados: h(k, i) = (h1(k) + i²) % 20
3. Doble Dirección - Utiliza dos funciones: h1(k) = k % 20; h2(k) = 1 + (k % 19); h(k, i) = (h1(k) + i*h2(k)) % 20
4. Encadenamiento - Cada celda mantiene una lista enlazada de valores.


## Funcionalidades del programa
Al ejecutarlo, el usuario debe indicar el método:

1. ./Sepulveda_Gabriela_Laboratorio9 L 
2. ./Sepulveda_Gabriela_Laboratorio9 C
3. ./Sepulveda_Gabriela_Laboratorio9 D
4. ./Sepulveda_Gabriela_Laboratorio9 E

Luego se muestra el menú:
1. Insertar número
2. Buscar número
3. Imprimir tabla
4. Insertar datos de ejemplo de la guía
5. Vaciar tabla
6. Salir del programa

## Datos de ejemplo del profesor
El programa incluye la carga automática de los siguientes datos: 23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64

## Compilación y ejecución
- g++ Sepulveda_Gabriela_Laboratorio9.cpp -o Sepulveda_Gabriela_Laboratorio9
- ./Sepulveda_Gabriela_Laboratorio9 L/C/D/E

## Notas importantes
- El programa muestra **todas las colisiones, intentos, y posiciones probadas**, considerando cada uno de los métodos.
- La tabla se imprime al estilo visto en clases, utilizando el formato "Pos 1 | 23"
- Tamaño fijo = **20**, según lo que indica la guía de trabajo.

## Archivos incluidos
- Sepulveda_Gabriela_Laboratorio9.cpp - Archivo con código funcional.
- README.md - Archivo explicativo.