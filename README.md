# Laboratorio 10 - Manejo de Archivos en Bash

**Autora:** Gabriela Antonia Sepúlveda Rojas
**Asignatura:** Algoritmos y Estructura de Datos — Universidad de Talca

## Descripción

Este laboratorio desarrolla el uso de **comandos Bash** para la administración de archivos, búsquedas, redireccionamiento, filtrado, renombrado, procesamiento de archivos `.csv` y análisis básico de proteínas mediante archivos **PDB**.

El trabajo incluye:

- Manipulación de carpetas y archivos de texto
- Búsquedas avanzadas con `grep`
- Extracción de columnas con `awk`
- Generación de archivos derivados (`GO_*.csv`, `FuncionesBiologica_*.csv`)
- Obtención de residuos LYS en archivos `.pdb`
- Conteo de todos los residuos presentes mediante scripts

## Métodos y Comandos Utilizados

A continuación se presentan los **comandos utilizados**, acompañado de su respectiva descripción.


## Manejo de carpetas

- Crear carpeta de trabajo:
```bash
mkdir -p "ayed_bash"
```

- Entrar a la carpeta:
```bash
cd "ayed_bash"
```

- Descomprimir archivo .zip:

```bash
unzip "Lab 10.zip" -d "ayed_bash"
```

## Listados y filtrados de archivos

- Lista los archivos en formato columna:

```bash
ls -1
```

- Muestra solo archivos con extension `.txt`:

```bash
ls -1 *.txt
```

- Lista archivos cuyo nombre inicia con “G”:

```bash
ls -1 G*
```

- Muestra archivos que contienen la cadena `"_A"`:

```bash
ls -1 *" A"*
```

### Visualizar archivos ocultos

- Muestra todos los archivos, incluidos los ocultos (que son los que comienzan con `.`).

```bash
ls -la
```

- Lista únicamente archivos ocultos (excluyendo `.` y `..`):

```bash
ls -d .[!.]*
```

### Ordenamientos 

- Ordena los archivos alfabéticamente:

```bash
ls -1 | sort
```

- Ordena los archivos por fecha (los más recientes primero):

```bash
ls -1t
```

## Visualización de archivos

- Muestra el archivo completo: 

```bash
cat HEM.txt
```

- Muestra las primeras 10 líneas del archivo.

```bash
head -n 10 HEM.txt
```

- Muestra las últimas 10 líneas del archivo.

```bash
tail -n 10 HEM.txt
```

### Búsqueda de texto específico con resaltado

- Busca la cadena resaltándola en color:

```bash
grep -n --color=always "NUCLEOTIDE SEQUENCE" HEM.txt
```

## Búsqueda de términos GO

- Busca anotaciones `GO` dentro del archivo .txt:

```bash
grep -n --color=always "GO;" HEM.txt
```

- Busca recursivamente anotaciones `GO` en todos los archivos del directorio:

```bash
grep -R --color=always -n "GO;" .
```

## Renombrado y eliminación de archivos

- Elimina el punto inicial para hacer visibles esos archivos:

```bash
mv .GFP.txt GFP.txt
mv .ACE2.txt ACE2.txt
mv .borrar.txt borrar.txt
```

- Visualiza el contenido y luego elimina el archivo (en este caso `borrar.txt`):

```bash
cat borrar.txt
rm borrar.txt
```

## Guardar historial de comandos

- Exporta el historial de comandos a un archivo `.txt`:

```bash
fc -l > mis_comandos.txt
```

## Generación de archivos GO_*.csv

- Crea un archivo CSV por cada proteína con las líneas que contienen anotaciones GO:

```bash
grep -n "GO;" HEM.txt > GO_HEM.csv
grep -n "GO;" GFP.txt > GO_GFP.csv
grep -n "GO;" ACE2.txt > GO_ACE2.csv
```

## Concatenación y conteo

- Une todos los archivos `GO` en uno solo:

```bash
cat GO_*.csv > GO_proteinas_de_trabajo.csv
```

- Muestra número de líneas, palabras y caracteres:

```bash
wc GO_proteinas_de_trabajo.csv
```

- Elimina el archivo final:

```bash
rm GO_proteinas_de_trabajo.csv
```

## Extracción de la última columna (funciones biológicas)

- Usa `awk` para extraer el último campo (`$NF`) separado por `;`. Y después, repetimos el proceso con `GFP` y `ACE2`:

```bash
awk -F';' '{print $NF}' GO_HEM.csv > FuncionesBiologica_HEM.csv
awk -F';' '{print $NF}' GO_GFP.csv > FuncionesBiologica_GFP.csv
awk -F';' '{print $NF}' GO_ACE2.csv > FuncionesBiologica_ACE2.csv
```

## Procesamiento de PDB

### Crear carpeta de trabajo

```bash
mkdir -p Obtencion_Aminoacidos
cp *.pdb Obtencion_Aminoacidos/
cd Obtencion_Aminoacidos
```

### Obtener residuos LYS

- Extrae del PDB solo las líneas cuyo residuo es LYS:

```bash
awk '(/^ATOM/ || /^HETATM/) && substr($0,18,3) == "LYS"' "$pdb" > "${base}-LYS.pdb"
```

### Obtener átomos CA (alfa-carbono) dentro de LYS

- Filtra exclusivamente los átomos alfa-carbono de los LYS:

```bash
awk '(/^ATOM/ || /^HETATM/) && substr($0,18,3) == "LYS" && substr($0,13,4) == " CA "' "$pdb" > "${base}-LYS-CA.pdb"
```

### Contador de residuos

- Cuenta cuántas líneas hay, equivalente a número de residuos LYS:

```bash
wc -l < "${base}-LYS-CA.pdb"
```

## Conteo total de residuos del archivo PDB

- Cuenta la cantidad de cada residuo presente en la proteína y genera un archivo CSV:

```bash
awk '(/^ATOM/){res=substr($0,18,3); gsub(/ /,"",res); counts[res]++} \
END{printf "aas;%s\n\n", base; for(r in counts) printf "%s;%d\n", r, counts[r]}' "$pdb" \
> "${base}_residue_counts.csv"
```

Se generan tres archivos:
* `ACE2_A_residue_counts.csv`
* `GFP_A_residue_counts.csv`
* `HEM_A_residue_counts.csv`

## Script final

El laboratorio exige crear un script propio: `script_contar_residuos.sh`

```bash
#!/usr/bin/env bash
for pdb in *.pdb; do
    if [[ "$pdb" == *"-LYS.pdb" || "$pdb" == *"-LYS-CA.pdb" ]]; then continue; fi
    base="${pdb%.*}"
    awk '(/^ATOM/){res=substr($0,18,3); gsub(/ /,"",res); counts[res]++} \
    END{printf "aas;%s\n\n", base; for(r in counts) printf "%s;%d\n", r, counts[r]}' \
    "$pdb" > "${base}_residue_counts.csv"
done
```

- Permisos:

```bash
chmod +x script_contar_residuos.sh
```

## Archivos incluidos

- Carpeta `Obtencion_Aminoacidos/` con todos los derivados PDB
- `GO_HEM.csv`, `GO_GFP.csv`, `GO_ACE2.csv`
- `FuncionesBiologica_*.csv`
- `*_residue_counts.csv`
- `mis_comandos.txt`
- **script_contar_residuos.sh**
- **README.md**

## Notas Finales

- Los comandos fueron probados y generaron los archivos requeridos sin errores.
- El script final permite automatizar el cálculo de residuos para cualquier archivo PDB válido.
