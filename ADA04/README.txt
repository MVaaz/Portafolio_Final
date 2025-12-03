README - Sistema ABB de Gestión de Estudiantes
-------------------------------------------------------------

Descripción general
-------------------
Este programa implementa un Árbol Binario de Búsqueda (ABB) que almacena y gestiona información de estudiantes.
Cada nodo representa a un estudiante identificado por su número de matrícula (entero de 8 dígitos).

El sistema permite insertar, eliminar, actualizar y consultar datos, así como generar distintos reportes.

-------------------------------------------------------------

Formato del archivo de datos (students.csv)
-------------------------------------------
Cada línea del archivo representa a un estudiante con el siguiente formato:

matricula;nombre;apellido;ncal;cal1,cal2,cal3,...

Ejemplo:
12345678;Juan;Perez;3;80,90,70
87654321;Maria;Lopez;2;95,88

El archivo se actualiza automáticamente al guardar desde el programa.

-------------------------------------------------------------

El programa mostrará un menú con las siguientes opciones:

-------------------------------------------------------------

Menú principal
--------------
1. Reporte: todos los estudiantes ordenados por matrícula (in-order)
2. Reporte: todos los estudiantes ordenados por promedio (descendente)
3. Reporte: estudiantes con promedio < 70
4. Reporte: estudiantes con promedio >= 70
5. Insertar nuevo estudiante
6. Eliminar estudiante por matrícula
7. Actualizar UNA calificación (por matrícula)
8. Dada una matrícula, contar alumnos con promedio menor que el promedio de esa matrícula
9. Mostrar valores de los nodos de un nivel (raíz = 0)
10. Mostrar árbol (ASCII)
11. Guardar en archivo y salir
0. Salir sin guardar

-------------------------------------------------------------

Detalles adicionales
--------------------
- El programa crea automáticamente el archivo 'students.csv' si no existe.
- Los datos se guardan en orden de matrícula.
- Las calificaciones se pueden actualizar individualmente.
- La opción (10) muestra el árbol de manera visual usando texto ASCII.
- La opción (11) guarda los cambios antes de salir.

-------------------------------------------------------------

