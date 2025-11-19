# Laboratorio 8 - Algoritmos de Ordenamiento Interno y Medición de Tiempos  

**Nombre:** Gabriela Antonia Sepúlveda Rojas  
**Asignatura:** Algoritmo y Estructura de Datos - Universidad de Talca

## Descripción General  
Este programa implementa y compara el rendimiento de cinco algoritmos clásicos de **ordenamiento interno**, midiendo el tiempo que cada uno demora en ordenar **el mismo conjunto de datos inicial**.

Los algoritmos implementados son:
1. Burbuja = O(n²) 
2. Inserción = O(n²) 
3. Selección = O(n²) 
4. Shellsort = O(n log n) 
5. Quicksort = O(n log n) 

El programa recibe dos parámetros:

1. **N**: Cantidad de elementos a generar (positivo)  
2. **VER**:
   - `s` : Mostrar vectores (inicial y ordenados)  
   - `n` : Ocultar contenido de los vectores   
En este caso, los valores del vector se generan de forma aleatoria usando `rand()`, con valores desde 0 hasta 4999

## Ejecución
Compilar: g++ Sepulveda_Gabriela_Laboratorio8.cpp -o Sepulveda_Gabriela_Laboratorio8 
Ejecutar: ./Sepulveda_Gabriela_Laboratorio8 N s/n
Ejemplos:
1. 10.000 elementos sin mostrar vectores = ./Sepulveda_Gabriela_Laboratorio8 10000 n
2. 10 elementos mostrando vectores = ./Sepulveda_Gabriela_Laboratorio8 10 s

## Estructura del código
El programa contiene:
1. Funciones individuales para cada algoritmo
2. medir_tiempo() para medir duración con `chrono`
3. Impresión de vectores cuando corresponde
4. Tabla comparativa final de tiempos

Validaciones consideradas:
1. N debe ser entero positivo
2. La opción VER debe ser `s` o `n`
3. Se verifica cantidad mínima de argumentos
4. Se generan copias independientes del vector base
5. Todos los algoritmos trabajan sobre los mismos datos

## Notas finales
El laboratorio permite observar experimentalmente la diferencia entre algoritmos cuadráticos y logarítmicos, especialmente con grandes cantidades de datos.