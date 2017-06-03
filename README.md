//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

Algoritmo para la solución del problema:

	Primero tenemos que partir de la construcción de la matríz de MxN
	Pondremos un total de X células iniciales en el tablero, y en base a eso comenzará el juego
	
	Deben definirse estados para las células, por lo que definimos el conjunto de estados y sus representaciones:
	E = {Muerta -> 0
		 Viva 	-> 1 }
	
	Deben definirse reglas para cambiar el estado de las células, por lo que tendremos un conjunto Q de reglas:
	Q = {1) Una célula viva con una o cero células vecinas muere de soledad
		 2) Una célular viva con cuatro o o más vecinas muere debido a la sobrepoblación
		 3) Una célucla muerta con dos o tres células vecinas vivas, vuelve a la vida
		 4) Cualquier otro caso, las células mantienen su estado sin cambiar}



Para compilar el programa junto con las librerías introducir el comando: gcc life_game.c DoubleLinkedList.c Cell.c -o life_game -g

Para correr el programa es necesario pasar como parámetros: número de filas, número de columnas y número de células vivas inicialmente

Ejemplo: ./life_game 10 12 15
Lo que nos daría una matriz de 10x12 y aproximadamente 15 células vivas inicialmente

