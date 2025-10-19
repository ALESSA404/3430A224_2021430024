Laboratorio 5 – Árbol AVL de Términos GO  

Nombre: Gabriela Antonia Sepúlveda Rojas 
Asignatura: Algoritmos y Estructuras de Datos 
Carrera: Ingeniería Civil en Bioinformática - Universidad de Talca

Descripción general: Este programa implementa un **Árbol AVL (balanceado)** en C++ que almacena información biológica proveniente de términos **Gene Ontology (GO)**. Cada nodo del árbol representa una función biológica con su código GO, nombre descriptivo y un puntaje (*score*) asociado.

El objetivo principal del laboratorio es:
- Comprender la inserción, eliminación y balanceo en árboles AVL.
- Manipular estructuras de datos enlazadas dinámicamente.
- Visualizar gráficamente la estructura del árbol utilizando Graphviz.

Estructura de cada nodo
Cada nodo del árbol almacena los siguientes datos:
- codigoGO (string): Identificador del término GO (ej. GO:0090398)
- funcion (string): Nombre de la función biológica
- score (float): Puntaje de relevancia asociado
- FE (int): Factor de equilibrio del nodo (calculado automáticamente por el AVL)

Operaciones básicas:
- Inserción balanceada: Añade nuevos términos manteniendo el equilibrio AVL.  
- Eliminación balanceada: Elimina nodos aplicando las rotaciones necesarias.  
- Búsqueda por código GO: Muestra todos los datos del nodo si existe.  

Recorridos del árbol
- Inorden: Recorre izquierda → raíz → derecha.  
- Preorden: Recorre raíz → izquierda → derecha.  
- Posorden: Recorre izquierda → derecha → raíz.  
Cada recorrido imprime: GO:xxxxxxx | Nombre de la función | Score | FE=x

El programa:
- Detecta automáticamente los separadores del archivo CSV 
- Ignora la primera línea si es cabecera.  
- Carga hasta 12 términos por defecto.
- Evita duplicados por "codigoGO" o "score".  
- Entrega un reporte final con los conteos de inserciones, duplicados e inválidos.

Visualización con Graphviz:
- Genera un grafo del árbol en formato DOT (`grafo.txt`) y luego crea una imagen (`grafo.png`).
- Cada nodo se representa como una caja con el formato: GO:0001302 - Replicative senescence - Score=0.97 - FE=0

Archivos incluidos:

- Sepulveda_Gabriela_Laboratorio5.cpp (Código fuente principal)
- Funciones_GO_minimal.csv (Archivo de entrada con 12 términos GO seleccionados)
- grafo.txt (Archivo DOT generado automáticamente)
- grafo.png (Imagen generada del árbol AVL)
- README.md (Documento explicativo)