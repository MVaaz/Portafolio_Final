# Portafolio_Final
Portafolio final de la materia Estructuras de Datos

ADA 1: Pilas

Problema. Parser de Expresiones Aritméticas

Descripción: Evaluar expresiones aritméticas tales como: 2+3, 2*(3+4) o ((2+4)*7)+3*(9–5) es tarea de un
analizador sintáctico (parser). Para realizar la evaluación de estas expresiones, muchos lenguajes de
programación utilizan un algoritmo de dos pasos:

1. Transformar la expresión aritmética en notación de postfija (Notación Polaca Inversa).
2. Evaluar la expresión de postfija.

La notación postfija de las expresiones antes mencionadas: 3 2 + , 2 3 4 + *, 2 4 + 7 * 3 9 5 - * +
Realizar un programa que por medio de la línea de comando (cmd o terminal) lea un archivo de entrada con un
conjunto de líneas con expresiones aritméticas (infijas) con delimitador final punto y coma; genere un archivo de
salida con un conjunto de líneas con las expresiones postfijas correspondientes, así como el resultado de evaluar
tal expresión postfija y con delimitador final punto y coma.

Ejemplo:
Archivo de entrada: exp_infijas.txt
Archivo de salida: exp_postfijas.txt
Ejecutable: InfijoAPostfijoApp.c
Ejemplo contenido exp_infijas.txt
2+3;
2*(3+4);
((2+4)*7)+3*(9–5);

Ejecución:
./InfijoAPostfijoApp exp_infijas.txt
Ejemplo contenido exp_postfijas.txt
Expresión: 3 2 +; Resultado: 5
Expresión: 2 3 4 + *; Resultado: 14
Expresión: 2 4 + 7 * 3 9 5 - * +; Resultado: 54

Los operadores que van a utilizar y el orden de sus prioridades, se da en la siguiente tabla. Los operadores en la
misma fila de la tabla indica que tienen la misma prioridad y su evaluación es de izquierda a derecha.

Operador     | Orden de Prioridad
----------------------------------
+, -         | Menor
----------------------------------
*, /         | 
----------------------------------
^ (potencia) |
----------------------------------
( )          | Mayor
----------------------------------

ADA 2: Simulador de Atención al Cliente en un Banco (Queues)

Objetivo: Implementar un sistema de simulación de atención en un banco que maneje dos o tres
colas de clientes, permitiendo analizar tiempos de espera y eficiencia del servicio.

Descripción del Problema: Desarrollar un programa que simule la atención en un banco con 3 cajas
de atención. Los clientes llegan de forma aleatoria a las cajas:
La aplicación debe:

  - Generar a los clientes con el número de transacciones bancarias (tiempo en que estará en la
caja)
  - Asignar de forma aleatoria a cada cliente a la cola correspondiente (cola 1, 2 o 3).
  - Atender a los clientes (indicar cuando ingresa a la cola el cliente, a qué cola ingresó y cuando
salió el cliente)
  - Calcular algunas estadísticas como: tiempo promedio de espera en cada cola, número de
clientes atendidos en cada cola, etc.

Notas para el desarrollo: Para el desarrollo tenga en cuenta lo siguiente:
  • Utilizar structs de C
  • Utilizar funciones para la lectura, cálculos, i

ADA 3: Implementación de lista de Movies con Listas

Descripción: Utilizando el archivo Movie.csv implemente una Lista Doblemente Ligada de Movies (películas). La
implementación deberá contar con los siguientes procesos:

  • Pueden seleccionar los atributos del archivo Movie que consideren más relevantes y puede seleccionar
algunas filas
  • Su Lista Ligada almacenará cada uno de los datos de las películas.
  • Los procesos o funciones para contemplar son:
    o Importación de los datos a la lista (carga de datos).
    o Búsqueda de alguna película por título (puede ser nombre exacto o no) y que muestre toda la
    información de esa película (director, actores, año de estreno, etc.)
    o Búsqueda de algún actor (cast) por nombre (puede ser nombre exacto o no) y que muestre toda
    la información del actor (nombre de la película en la que ha trabajado, con el director de la
    película, el año de estreno, etc.)
    o Insertar una nueva película con todos sus datos, la inserción puede ser en cualquier lugar de la
    lista, al principio, al final, etc.
    o Eliminar una película por título (puede ser nombre exacto o no) y que muestre toda la información
    de la película antes de eliminar indicando con un mensaje al usuario ¿desea eliminar?
    o Actualizar algunos datos de la película, aquí primero se debe hacer una búsqueda por título de la
    película y posteriormente se le indica al usuario que dato de la película se quiere modificar.

Notas para el desarrollo: Para el desarrollo tenga en cuenta lo siguiente:
  • Utilizar structs de C
  • Utilizar funciones para los cálculos, impresiones, lectura y escritura
  • Hacer buen uso de la estructura Listas Doblemente Ligadas

ADA 4: Gestión de estudiantes con árboles binarios de búsqueda

Objetivo: Desarrollar un sistema de gestión de estudiantes utilizando árboles binarios de búsqueda (ABB).

Descripción: Se implementará un sistema que almacene y gestione información de los estudiantes usando un
ABB, donde la matrícula (numérico) del estudiante será el atributo según el que se ordenará la información en el
árbol. Los datos mínimos del estudiante son {matrícula, nombre, apellido, calificaciones{}}. El número de
calificaciones del alumno representa todas las materias que ha cursado, puede variar entre alumnos (es dinámico).

El sistema permitirá:
  1. Generar un reporte de todos los estudiantes, ordenados por su matrícula.
  2. Generar un reporte de todos los estudiantes, ordenados por el promedio de sus calificaciones.
  3. Generar un reporte de todos los estudiantes, cuyo promedio de calificaciones es menor a 70.
  4. Generar un reporte de todos los estudiantes, cuyo promedio de calificaciones es mayor o igual a 70.
  5. Insertar un nuevo estudiante en el árbol, de acuerdo con su matrícula.
  6. Eliminar un estudiante dado su matrícula (el usuario proporciona la matrícula).
  7. Actualizar las calificaciones de un alumno de acuerdo con la matrícula proporcionada. Considerar la
  actualización de solamente una calificación, no de todas las que tiene.
  8. Dada una matrícula, contar el número de alumnos que tienen una calificación menor a él.
  9. Mostrar los valores de los nodos de un nivel proporcionado (el usuario lo proporciona) del árbol.
  10. Mostrar el árbol binario de búsqueda de manera gráfica (puede ser con ASCII).

Notas para el desarrollo: Para el desarrollo tenga en cuenta lo siguiente:
  • Utilizar structs de C y arreglos dinámicos
  • Utilizar funciones para los cálculos, impresiones, lectura y escritura
  • Hacer buen uso de la estructura Árbol Binario de Búsqueda.

ADA 5: Investigación/Presentación algoritmos de ordenamiento

Descripción: Objetivo: Investigar y presentar un algoritmo de ordenamiento asignado, explicando su
funcionamiento, características, eficiencia y casos de uso, según la categoría correspondiente.
Categoría de los algoritmos de ordenamiento:

Ordenamiento por Intercambio: Bubble Sort (E01), Quick Sort (E02), Cocktail Sort (E03).
Ordenamiento por Selección: Selection Sort (E04), Heap Sort (E05).
Ordenamiento con Árboles: Tree Sort (E06), Heap Sort (E07), Tournament Sort (E10)
Ordenamiento por Inserción: Insertion Sort (E08), Shell Sort (E09).

Elementos a Incluir en la Investigación y Presentación

Cada equipo deberá desarrollar los siguientes puntos para su algoritmo asignado:

  1. Introducción y Contexto
    • Nombre del algoritmo y categoría a la que pertenece.
    • Breve historia o origen (si aplica).
    • Idea principal del algoritmo en 3-5 oraciones.

  2. Funcionamiento del Algoritmo
    • Explicación paso a paso con ejemplo visual (usar una lista pequeña [5, 2, 8, 1, 14, 17, 4, 3, 19]).
    • Ventajas y desventajas frente a otros algoritmos de la misma categoría.

  3. Características Técnicas
    • Describir las siguientes características técnicas e indicar como las maneja el algoritmo:
      o Estabilidad: ¿Mantiene el orden relativo de elementos iguales?
      o In-place: ¿Usa espacio adicional constante?
      o Adaptabilidad: ¿Se beneficia de listas parcialmente ordenadas?

  4. Eficiencia del Algoritmo
    • Describir las siguientes complejidades del algoritmo y como las maneja:
      o Complejidad Temporal:
        § Mejor caso, caso promedio y peor caso.
        § Ejemplo: Quick Sort tiene O(nlog(n))O(nlog(n)) en promedio, pero O(n2)O(n2) en el peor caso.
      o Complejidad Espacial:
     § Memoria adicional utilizada.
    • Comparación visual con otros algoritmos de la misma categoría (tabla o gráfica).
  5. Casos de Uso y Aplicaciones Prácticas
    • ¿En qué escenarios es más eficiente?
    • Ejemplos reales (ejemplos:, bases de datos, renderización de gráficos).
  7. Conclusiones
    • Resumen de por qué el algoritmo es útil o no en contextos específicos.
    • Recomendaciones de cuándo usarlo.

ADA 6: Implementación de ordenamiento

Descripción: Utilizando los algoritmos de ordenamiento presentados por sus compañeros, así como el código fuente en el repositorio https://github.com/luisbastoUADY/sorting-algorithms.git, implemente los algoritmos de ordenamiento que se le asignó al equipo. 

Consideraciones:

  • El repositorio contiene un README.md y el código fuente base (sorting.c) con diversas funciones:
    o Creación de arreglos dinámicos de forma aleatoria y manual por parte del usuario, 
    o Despliegue del arreglo
    o Funciones iniciales para cada uno de los algoritmos.
  • Su tarea consistirá en lo siguiente, por equipos:
    o Clonar el repositorio: Cada alumno o equipo clona el repositorio.
      § git clone https://github.com/luisbastoUADY/sorting-algorithms.git
    o Crear una rama por equipo: Por ejemplo, E01-burbuja.
    o Implementar las funciones de su algoritmo en su carpeta o sección, en caso de que se necesiten funciones auxiliares hay que crearlos también.
    o Hacer commits con mensajes claros.
    o Crear un pull request hacia la rama principal (main o master)
    
ADA 7:Descripción: Implementar en C/C++ los siguientes

Aplicación 01: Registro de Estudiantes con Colisiones Controladas
  
  Descripción: Un sistema para universidades que almacene estudiantes usando su matrícula como clave. La
clave está compuesta por solo números de máximo 6 dígitos. Los estudiantes deben ser recuperados
eficientemente, incluso con colisiones.
  
  Estructura: Tabla hash con matrícula del estudiante como clave y estructura/objeto Estudiante (nombre, carrera,
etc.) como valor.

  Manejo de colisiones: Direccionamiento abierto (sondeo lineal o cuadrático).

  Funcionalidades:
    • Agregar un estudiante por matrícula.
    • Buscar un estudiante por matrícula.
    • Eliminar un estudiante por matrícula.
    
Aplicación 02: Tabla de símbolos en un compilador

  Descripción: En un compilador o intérprete, se necesita mantener un registro de los identificadores (variables,
funciones, etc.) y sus atributos (tipo, valor, ámbito, etc.).

  Implementación: La clave es el nombre del identificador (string) y el valor es una estructura que contiene los
atributos. La tabla hash permite una búsqueda rápida para verificar si un identificador ya ha sido declarado y
para acceder a sus atributos.

  Manejo de colisiones: Listas ligadas

  Funcionalidades:
    • Agregar un identificador y sus atributos.
    • Buscar un identificador y sus atributos.
    • Eliminar un identificador y sus atributos.
