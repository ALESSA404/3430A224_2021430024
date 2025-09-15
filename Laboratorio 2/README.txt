Algoritmo y Estructura de Datos - Laboratorio N°2

Nombre: Gabriela Antonia Sepúlveda Rojas
Fecha: 14 de Septiembre del 2025

Actividades:
- Actividad 1: Implementación de una pila con arreglos.
- Actividad 2: Simulación de un patio de contenedores con múltiples pilas.

Actividad 1 — Pila con Arreglos

Se implementa una pila utilizando un arreglo estático, donde el usuario puede:
- Definir el tamaño de la pila.
- Push: Agregar un elemento a la pila.
- Pop: Retirar el elemento en el tope de la pila.
- Mostrar: Ver el estado actual de la pila.
Además, este programa controla el desbordamiento (cuando la pila está llena) y subdesbordamiento (cuando está vacía).

Actividad 2 — Patio de Contenedores

Se simula un patio de contenedores representado por varias pilas, donde el programa recibe como parámetros:
- n: altura máxima de cada pila (n≤100).
- m: número de pilas (m≤20).
  
Las opciones del programas son:
- Mostrar estado del patio.
- Agregar contenedor (manual o automático).
- Retirar contenedor por ID (si hay contenedores encima, se mueven a otras pilas con espacio).
- Salir.
Además, este programa controla casos de error, como lo son las pilas llena, pilas vacías, contenedores no encontrados o sin espacio disponible.

Requisitos del laboratorio N°2:
- Compilador C++.
- Librerías usadas: <iostream>, <string>, <sstream>, <limits>.
- Sistema operativo Linux/Windows con terminal.

Compilación
- g++ Sepulveda_Gabriela_Actividad_1.cpp -o Sepulveda_Gabriela_Actividad_1
- g++ Sepulveda_Gabriela_Actividad_2.cpp -o Sepulveda_Gabriela_Actividad_2

Ejecución

- Actividad 1:./Sepulveda_Gabriela_Actividad_1
- Actividad 2:./Sepulveda_Gabriela_Actividad_2 <n> <m> (Ejemplo: ./Sepulveda_Gabriela_Actividad_2 2 2

Ejemplo breve de ejecución (Actividad 2)

- Ejecutamos con n = 2 y m =2:
	- ./Sepulveda_Gabriela_Actividad_2 2 2
- Ingreso de contenedores (automático): 
	- A1 A2 fin
- Estado inicial: 
	- Pila 0 (tope → base): A2 | A1 
	- Pila 1 (tope → base): (vacía)
- Retiro de A1: 
	- Mover A2 de pila 0 -> pila 1 = Retirado A1 de pila 0

- Estado final:
	- Pila 0 (tope - base): (vacía)
	- Pila 1 (tope - base): A2

Para concluir, este laboratorio permitió reforzar el uso de estructuras (struct) y el manejo de pilas con arreglos estáticos en C++.

- En la Actividad 1, se trabajó con una pila simple, implementando operaciones básicas (push, pop, mostrar) y controlando casos de error.
- En la Actividad 2, se extendió el concepto a un patio de contenedores, gestionando múltiples pilas, con opciones de ingreso manual/automático y el movimiento de contenedores para simular un retiro en la vida real.

De esta manera, se reforzaron los conceptos de estructuras de datos lineales, el uso de switch-case y los parámetros de línea de comandos, aplicándolos en ejercicios prácticos.