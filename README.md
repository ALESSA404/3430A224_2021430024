# Proyecto — Alineamiento Global de Secuencias (Needleman-Wunsch)

## 👩‍💻 Autores

**Nombre:** Ivonne Cancino y Gabriela Sepùlveda 
**Asignatura:** Algoritmos y Estructura de Datos 
**Carrera:** Ingeniería Civil en Bioinformática 
**Universidad:** Universidad de Talca - Facultad de Ingeniería 

---

##  Descripción

Este laboratorio implementa el **algoritmo de alineamiento global Needleman-Wunsch**, el cual permite comparar dos secuencias (por ejemplo, cadenas de ADN, ARN, proteínas o simplemente strings generales) para obtener el alineamiento óptimo entre ellas.

El programa utiliza:

- **Dos secuencias** en formato TXT o FASTA. 
- **Matriz de sustituciòn U** completamente personalizada. 
- **Penalidad de gap lineal** (valor configurable por parámetro).
- **Salida en archivo TXT** con el alineamiento, estadísticas y esquinas de la matriz DP. 
- **Visualización del alineamiento en formato DOT/JPG** coloreado mediante Graphviz.
- **Impresión por consola** del alineamiento en bloques de 50 caracteres 

El programa calcula:
- Matriz DP del alineamiento global.
- **Traceback** para recuperar el alineamiento óptimo.
- Porcentaje de similitud (matches)
- Concordancia por posición.
- Puntaje final del alineamiento.

---

## Estructura del proyecto

```
📂 Proyecto final
 ┣ 📜 alineamiento.cpp  # Código fuente principal
 ┣ 📜 README.md # Documento explicativo
 ┣ 📂 input/# Secuencias y matriz U
 ┗ 📂 Resultados_Alineamiento / # Archivos generados (.txt, .dot, .jpg)
```

---

##  Requisitos del sistema

Para ejecutar correctamente el programa, instala las siguientes herramientas en **Linux**:

```bash
sudo apt update
sudo apt install g++ graphviz eog
```

| Herramienta | Función |
|--------------|----------|
| **g++** | Compilador de C++ |
| **Graphviz** | Genera la imagen coloreada del alineamiento (.jpg)|
| **eog** | Visualizador del alineamiento |

---

## Compilación y ejecución

### Compilación:
```bash
g++ alineamiento.cpp -o alineamiento -std=c++17
```

###  Ejecución:
```bash
./alineamiento -C1 secuencia1.txt -C2 secuencia2.txt -U matrizU.txt -V -1

Paràmetros:
- C1: Archivo con la primera secuencia
- C2: Archivo con la segunda secuencia
- U: Archivo con la matriz de sustituciòn U
- V: Penalidad para los gaps (valor negativo recomendado)
```
Ejemplo:

./alineamiento -C1 cad1.txt -C2 cad2.txt -U funU.txt -V -10

---

## Flujo del programa

Al ejecutarse, el programa realiza:

```
1. Lectura de secuencias (acepta FASTA).
2. Carga de la matriz U desde archivo.
3. Construcción de la matriz DP con Needleman–Wunsch.
4. Traceback para recuperar el alineamiento óptimo.
5. Impresión por consola del alineamiento.
6. Escritura del alineamiento en TXT.
7. Generación del DOT y JPG con celdas coloreadas: verde -> match, rojo -> mismatch o gris -> gap
```

### Archivos generados
Al finalizar, el programa crea automáticamente dentro de output/:

| Archivo | Contenido |
|--------|--------------|
| **alineamiento.txt** | Alineamiento completo, similitud y esquinas de la matriz DP. |
| **alineamiento.dot** | Tabla coloreada del alineamiento en formato Graphviz. |
| **alineamiento.jpg** | Imagen generada a partir del archivo .dot|
---

## Estructura del código

| Función | Descripción |
|----------|--------------|
| `leer_secuencia()` | Lee la secuencia desde TXT o FASTA.|
| `leer_matriz_U()` | Carga la matriz de sustitución definida por el usuario. |
| `construir_matriz_DP()` | Implementa Needleman–Wunsch con penalidad de gap lineal. |
| `traceback()` | Reconstruye el alineamiento óptimo.|
| `calcular_similitud_pct()` | Calcula porcentaje de similitud real.|
| `escribir_salida_txt()` | Genera archivo TXT con alineamiento + DP. |
| `escribir_dot_color()` | Crea archivo DOT y lo convierte a JPG. |
| `imprimir_terminal()` | Muestra el alineamiento en la consola. |

---

## Ejemplo de salida en consola

```
--- Alineamiento óptimo ---
Largo alineamiento: 42
Posiciones comparadas (sin gaps): 38
Similitud: 78.9474 %

ACGTAC---TGA...
||..|....|.|...
AC-TACGTTGA...

```
---

## Formato del archivo TXT
- Alineamiento completo en bloques de 50 caracteres
- Línea de concordancia.
- Estadísticas del alineamiento.
- Puntaje final.
- Esquinas 15X15 de la matriz DP (superior izquierda e inferior derecha)

---

## Visualización en DOT/JPG

El archivo .dot genera una tabla coloreada:

- Match: Verde 
- Mismatch: Rojo 
- Gap: Gris
---

## Validaciones implementadas


```cpp
- Verifica que los archivos de secuencia existan y no estén vacíos.
- Confirma que la matriz U tenga encabezado válido.
- Verifica que Graphviz esté instalado (o muestra advertencia).
- Crea automáticamente la carpeta output/ si no existe.
```
---

## Conclusión

El programa implementa completamente el alineamiento global Needleman–Wunsch, permitiendo:

- Total personalización de la matriz de sustitución.
- Penalidades configurables.
- Visualización clara y profesional del alineamiento.
- Salidas exportables y reproducibles.

Es una herramienta útil para comprender y aplicar los fundamentos del alineamiento de secuencias en Bioinformática.

---

##  Ejemplo de flujo de trabajo con Git

```bash
git init
git add .
git commit -m "Alineamiento global Needleman-Wunsch completado"
git branch -M main
git push -u origin main

```

---
