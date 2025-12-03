# README - Sistema de Registro de Estudiantes con Tabla Hash

## Descripción

Este programa implementa un sistema de registro de estudiantes utilizando tablas hash con direccionamiento abierto (sondeo lineal) para manejar colisiones. Los datos se almacenan y recuperan desde un archivo CSV llamado estudiantes.csv.

El programa permite:

* Agregar estudiantes (matrícula, nombre, carrera)
* Buscar estudiantes por matrícula
* Eliminar estudiantes por matrícula
* Guardar los cambios en `estudiantes.csv`

El archivo estudiantes.csv es creado automáticamente si no existe.

---

## Archivos del proyecto

*ADA07_AP01.c → Código fuente en C del programa
*estudiantes.csv → Archivo de datos (se genera automáticamente)
*readme.txt → Este archivo

---

## Compilación

Para compilar el programa, abre la terminal de comandos y escribe lo siguiente en la carpeta donde se encuentra el archivo ADA07_AP01.c:

```
 gcc ADA07_AP01.c -o ADA07_AP01.exe
```

Esto generará un ejecutable llamado estudiantes.exe.

---

## Modo de uso

Al ejecutar el programa se mostrará un menú como el siguiente:

```
--- MENU ---
1. Agregar estudiante
2. Buscar estudiante
3. Eliminar estudiante
4. Salir
```

### 1.Agregar estudiante

El sistema pedirá:

* Matrícula (número entero de máximo 6 dígitos)
* Nombre
* Carrera

Ejemplo:

```
Matricula: 123456
Nombre: Juan
Carrera: Sistemas
```

### 2.Buscar estudiante

Ingresa la matrícula y el sistema mostrará los datos si existe.

### 3.Eliminar estudiante

Elimina el registro de un estudiante usando la matrícula.

### 5.Salir

Al salir, todos los datos se guardan automáticamente en estudiantes.csv.

---

## Formato del archivo estudiantes.csv

Cada registro se guarda así:

```
matricula,nombre,carrera
```

Ejemplo:

```
123456,Juan,Sistemas
789012,Ana,Industrial
```

---

## Requisitos

* GCC o cualquier compilador estándar de C
* Sistema operativo Linux, Windows o MacOS

---

## Notas

* El método de colisiones usado es sondeo lineal.
* La tabla hash tiene tamaño fijo de 1000 espacios.
* Los datos eliminados se marcan como borrados, sin afectar el funcionamiento del hash.

---
