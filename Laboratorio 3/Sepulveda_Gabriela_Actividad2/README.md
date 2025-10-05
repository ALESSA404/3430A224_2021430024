Preprocesamiento del archivo PDB (Proteína 3NIR)

Objetivo
El propósito de este proceso fue extraer la secuencia primaria de aminoácidos desde el archivo estructural 3nir.pdb, conservando únicamente la información esencial:
- El nombre del residuo (aminoácido).
- El identificador de la cadena (en este caso, la cadena A).
- El número de residuo.

Para esto, se emplearon comandos Bash y herramientas UNIX (awk, grep, uniq) que permiten filtrar y formatear la información del PDB antes de representarla gráficamente con Graphviz.

Archivos generados
A partir del archivo original 3nir.pdb, se obtienen los siguientes archivos intermedios:

- 3nir_Resids.pdb: Contiene los nombres de los residuos, cadena e identificadores separados por “;”.
- 3nir_Resids_ChainA.pdb: Filtrado para conservar solo los residuos pertenecientes a la cadena A.
- 3nir_Resids_ChainA_Format.pdb: Contiene solo el nombre del residuo y su número, sin separadores.
- 3nir_Resids_ChainA_Format_Uniq.pdb: Lista final, sin residuos repetidos, lista para el procesamiento gráfico.

Comandos utilizados:

1. Extracción de residuos desde el archivo PDB original:
awk 'BEGIN{OFS=";"} /^ATOM/ {print substr($0,18,3), substr($0,22,1), substr($0,23,4)}' 3nir.pdb > 3nir_Resids.pdb

- awk: herramienta para procesar texto estructurado.

- BEGIN{OFS=";"}: define el separador de salida como “;”.

- /^ATOM/: selecciona solo las líneas que comienzan con “ATOM”, ya que contienen información de átomos en los residuos.

- substr($0,18,3): extrae el nombre del residuo (columna 18 a 20 del archivo PDB).

- substr($0,22,1): extrae el identificador de cadena (por ejemplo, “A”).

- substr($0,23,4): extrae el número de residuo (identificador numérico del aminoácido).

- > 3nir_Resids.pdb: guarda el resultado en un nuevo archivo.

Resultado: Archivo 3nir_Resids.pdb

THR;A;   1
THR;A;   1
THR;A;   1
THR;A;   1
THR;A;   1
THR;A;   1
...

2. Filtrado por cadena específica (Cadena A):
grep ';A;' 3nir_Resids.pdb > 3nir_Resids_ChainA.pdb

- grep ';A;': busca solo las líneas que pertenecen a la cadena A.

- > 3nir_Resids_ChainA.pdb: almacena el resultado en un nuevo archivo.

Resultado: Solo quedan los residuos pertenecientes a la cadena A, descartando otras cadenas del PDB.

3. Formateo para eliminar separadores y dejar solo el nombre y número:
awk 'BEGIN{FS=";";OFS=""}{print $1, $3}' 3nir_Resids_ChainA.pdb > 3nir_Resids_ChainA_Format.pdb

- FS=";": indica que el separador de campos de entrada es “;”.

- OFS="": indica que no habrá separador en la salida.

- {print $1, $3}: imprime solo el nombre del residuo ($1) y su número ($3) juntos (THR;A;1) -> THR1

Resultado: Archivo con formato simplificado

THR;A;   1
THR;A;   1
THR;A;   1
THR;A;   1
...

4. Eliminación de duplicados
uniq 3nir_Resids_ChainA_Format.pdb > 3nir_Resids_ChainA_Format_Uniq.pdb

- uniq: elimina líneas duplicadas consecutivas (se recomienda aplicar sort antes de uniq si los duplicados no son consecutivos)

- > 3nir_Resids_ChainA_Format_Uniq.pdb: guarda la lista final sin repeticiones.

Resultado: Lista limpia de residuos únicos, lista para su uso en la representación de la estructura primaria mediante Graphviz.
El archivo 3nir_Resids_ChainA_Format_Uniq.pdb contiene la secuencia primaria de la cadena A de la proteína 3NIR, en formato legible y compatible con la generación de un grafo lineal:

THR   1
THR   2
CYS   3
CYS   4
PRO   5
SER   6
ILE   7
...

Este archivo es el que se utiliza como entrada para el programa en C++ que genera el grafo con Graphviz, representando la estructura primaria lineal de la proteína.