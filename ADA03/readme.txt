Para iniciar el programa, haga doble click en ADA04.exe.

El programa primero carga el archivo Movies.csv ubicado en la misma carpeta donde se encuentra el programa, si no se encuentra este archivo,
el programa marcara un error y terminara

Una vez cargado el archivo se le presentara un menu como este :

===== MENÚ =====
1. Buscar película por título
2. Buscar película por ID
3. Insertar nueva película
4. Eliminar película
5. Actualizar datos
6. Mostrar todas las películas
7. Salir

Para seleccionar una opcion, escribe el numero de la opcion que quieras usar:

1. Buscar película por título:

Escribe el titulo de la pelicula y presiona enter para buscar la pelicula que quieras. No necesita ser el nombre completo, 
solo con que coincida parcialmente funciona (Por ejemplo, solo buscar "star" deberia mostras "Star Wars" )

2. Buscar película por ID:

Escribe el Id de la pelicula y presiona enter para buscar la pelicula que quieras.

3. Insertar nueva película:

Al seleccionar esta opcion, añadiras una nueva pelicula a la lista, tendras que ingresar, en orden:
	-Un Id
	-Un titulo
	-Una calificacion (en numeros)
	-La fecha de salida de la pelicula (dd/mm/aaaa)
	-Los generos que quieras añadir, separados por comas
	-Las etiquetas que quieras agregar, separadas por comas

4. Eliminar película:

Escribe el nombre de la pelicula que quieras eliminar y presiona enter, si la pelicula se encuentra en la lista, se mostrara y preguntara si quieres elliminarla. 
Escribe s o n para confirmar o cancelar el proceso.

5. Actualizar datos:

Escribe el nombre de la pelicula que quieras eliminar y presiona enter, si la pelicula se encuentra en la lista, se mostrara y aparecera un menu como este:
	
	Seleccione campo a modificar:
	1. Título
	2. Puntuación
	3. Fecha
	4. Géneros
	5. Palabras clave

Escribe el numero de la opcion que quieras elegir y presiona enter. Despues, escribe los datos que quieras modificar y presiona enter (esto reemplazara por completo los datos anteriores):

	1-Un titulo
	2-Una calificacion (en numeros)
	3-La fecha de salida de la pelicula (dd/mm/aaaa)
	4-Los generos que quieras añadir, separados por comas
	5-Las etiquetas que quieras agregar, separadas por comas

6. Mostrar todas las películas:

Muestra todas las peliculas que se encuentran en el archivo movies.csv, con sus respectivos datos.

7. Salir

Sale del programa