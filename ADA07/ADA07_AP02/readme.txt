========================================
    TABLA DE SÍMBOLOS EN C (HASH TABLE)
========================================

Este programa implementa una tabla de símbolos para un compilador
usando una tabla hash con manejo de colisiones mediante listas ligadas.

Se pueden almacenar identificadores con los siguientes atributos:
- nombre
- tipo
- valor
- ámbito

Los datos pueden guardarse y cargarse desde un archivo CSV llamado:
    symbol_table.csv

----------------------------------------
COMPILACIÓN
----------------------------------------

En Linux o macOS:
    gcc ADA07_AP02.c -o ADA07_AP02

En Windows (MinGW):
    gcc ADA07_AP02.c -o ADA07_AP02.exe

----------------------------------------
EJECUCIÓN
----------------------------------------

Linux/macOS:
    ./ADA07_AP02

Windows:
    ADA07_AP02.exe

----------------------------------------
FUNCIONALIDADES
----------------------------------------

1. Cargar archivo CSV (si existe)
2. Agregar un identificador y sus atributos
3. Buscar identificador
4. Eliminar identificador
5. Guardar al salir

El archivo CSV se genera automáticamente si no existe.

----------------------------------------
FORMATO DEL CSV
----------------------------------------

Cada línea contiene:

nombre,tipo,valor,ambito
