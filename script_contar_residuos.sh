#!/usr/bin/env bash
# Programa: Script para contar residuos de archivos PDB.
# Autora: Gabriela Antonia Sepúlveda Rojas
# Descripción: Recorre todos los archivos .pdb del directorio y genera un archivo CSV con el conteo de cada residuo presente en la proteína.
# Este script ignora los PDB derivados (LYS.pdb/LYS-CA.pdb).

# Recorremos cada archivo con terminación en .pdb
for pdb in *.pdb; do
    # Si el archivo es un derivado (-LYS o -LYS-CA), lo saltamos para evitar su analización.
    if [[ "$pdb" == *"-LYS.pdb" ]] || [[ "$pdb" == *"-LYS-CA.pdb" ]]; then
        continue
    fi
    # Quitamos la extensión .pdb para cra¿ear un nuevo nombre de salida.
    base="${pdb%.*}"
    csv="${base}_residue_counts.csv"

# Procesamiento con awk: Se leen todas las lineas correspondientes a ATOM/HETATM, se extrae el nombre del residuo desde la columna estándar, se limpian los espacios del residuo y finalmente se cuenta la cantidad de veces que aparece cada uno de ellos.
    awk '
        # Procesamos líneas ATOM y HETATM (las que describen los átomos del archivo PDB)
        (/^ATOM/ || /^HETATM/) {
            # Extraemos el nombre del residuo:
            # En un PDB estándar, columnas 18-20 corresponden al residuo
            res = substr($0,18,3)

            # Eliminamos espacios internos, en el caso de que vinieran con padding
            gsub(/ /, "", res)

            # Se incrementa el contador del residuo mientras se van encontrando
            counts[res]++
        }

        # Se imprime al terminar el archivo
        END {
            # Encabezado solicitado
            printf "aas;%s\n\n", base

            #  Para cada residuo procesado se imprime NOMBRE;CANTIDAD
            for (r in counts)
                printf "%s;%d\n", r, counts[r]
        }
    ' "$pdb" > "$csv"

    # Mostramos un mensaje final para indicarle al usuario que se han generado los archivos.
    echo "Generado: $csv"

done

