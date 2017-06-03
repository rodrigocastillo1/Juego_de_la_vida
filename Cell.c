//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DoubleLinkedList.h"
#include "Cell.h"

Cell_t * newCell(int i, int j, int s){
	Cell_t *new = (Cell_t *)malloc(sizeof(Cell_t)); 				//Creamos el espacio para una célula nueva
	new->pos_i = i; 												//Almacenamos la posición en i
	new->pos_j = j;  												//Almacenamos la posición en j
	new->status = s;												//Almacenamos el estado
	return new;														//Retornamos la célula
}

void createCells(DLList *cell_list, int rows, int cols, int seeds_num){			//Función para la creación de células iniciales
	int random_number = -1;
	for(int i=0; i<rows; i++){													//Iteramos sobre los renglones:
		for(int j=0; j<cols; j++){												//Iteramos sobre las columnas:
			Cell_t *c = newCell(i, j, 0);										//Creamos una nueva célula, muerta...
			append(cell_list, c);												//La insertamos a la lista de células
		}
	}
	srand(time(0));																//Iniciamos una semilla para obtener un número aleatorio
	for(int i=0; i<seeds_num; i++){												//Por cada elemento en la lista de numero aleatorios
		random_number = getRandomNumber(rows*cols, random_number);
		//printf("Random [%d]: %d\n", i, random_number);
		changeCellStatus(lookAt(cell_list, random_number), 1);					//Cambiamos el estado a vivas, a las células que se encuentren en la posición en la lista correspondiente al número aleatorio iterado
	}
}

void changeCellStatus(Cell_t *cell, int new_status){		//Función para cambiar el estado de una célula
	cell->status = new_status;								//De la célula que se pasa como parámetro, cambiamos su estado por el nuevo
}

void showCells(DLList *cell_list, int n, int m){
	Cell_t * cell;											//Declaramos una variable de tipo Célula
	int board[n][m];										//Una matriz de NxM -> tamaño del tablero
	for(int i=0; i<cell_list->size; i++){					//Por cada célula en la lista de células:
		cell = lookAt(cell_list, i);						//Miramos en la posición que estamos iterando:
		board[cell->pos_i][cell->pos_j] = cell->status;		//Y ponemos en el tablero el estado que tiene la célula en una posición i,j
	}
	for(int i=0; i<n; i++){									//Hacemos una doble iteración para imprimir el contenido de la matriz Board
		for(int j=0; j<m; j++){
			printf("%d ", board[i][j]);						//Imprimimos el contenido de board en i,j
		}
		printf("\n");										//Imprimimos un salto de línea para cambiar de fila
	}
}

int getRandomNumber(int max_value, int last){
	int new_num;											//Se declara un arreglo de números con tamaño fijo, y una variable para alojar números aleatorios
	do{
		new_num = rand()%max_value;  						//Creamos un nuevo número aleatorio
	}while(new_num == last);								//Mientras el nuevo sea igual que el anterior
	return new_num;											//Cuando sean distintos, lo retornamos
}