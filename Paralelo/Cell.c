//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "DoubleLinkedList.h"
#include "Cell.h"
#include <omp.h>


Cell_t * newCell(int i, int j, int s){
	Cell_t *new = (Cell_t *)malloc(sizeof(Cell_t)); 				//Creamos el espacio para una célula nueva
	new->pos_i = i; 												//Almacenamos la posición en i
	new->pos_j = j;  												//Almacenamos la posición en j
	new->status = s;												//Almacenamos el estado
	return new;														//Retornamos la célula
}

void createCells(DLList *cell_list, int rows, int cols, int seeds_num){			//Función para la creación de células iniciales
	int random_number = -1;
	Cell_t * cell;
	#pragma omp parallel
	#pragma omp master
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
		cell = lookAt(cell_list, random_number);
		cell->status = 1;														//Cambiamos el estado a vivas, a las células que se encuentren en la posición en la lista correspondiente al número aleatorio iterado
	}
}

Cell_t * changeCellStatus(Cell_t *cell, int new_status){					//Función para cambiar el estado de una célula
	Cell_t * new_cell = newCell(cell->pos_i, cell->pos_j, new_status);		//De la célula que se pasa como parámetro, cambiamos su estado por el nuevo
	return new_cell;
}

void showCells(DLList *cell_list, int n, int m){
	Cell_t * cell;											//Declaramos una variable de tipo Célula
	int board[n][m];
	#pragma omp parallel
	#pragma omp master									//Una matriz de NxM -> tamaño del tablero
	for(int i=0; i<cell_list->size; i++){					//Por cada célula en la lista de células:
		cell = lookAt(cell_list, i);						//Miramos en la posición que estamos iterando:
		board[cell->pos_i][cell->pos_j] = cell->status;		//Y ponemos en el tablero el estado que tiene la célula en una posición i,j
	}
	#pragma omp parallel
	#pragma omp master
	for(int i=0; i<n; i++){									//Hacemos una doble iteración para imprimir el contenido de la matriz Board
		for(int j=0; j<m; j++){
			printf("%d ", board[i][j]);						//Imprimimos el contenido de board en i,j
		}
		printf("\n");										//Imprimimos un salto de línea para cambiar de fila
	}
}

void generateAdjacencyMatrix(DLList *cell_list, int order, int (*adjMat)[order], int rows, int cols){			//Función para generar una matríz de adyacencia
	Cell_t * c1, *c2;
	DLList * a;																//Se declaran las variables para las células
	int y = 1, n = 0;
	#pragma omp parallel
	#pragma omp master
	for(int i=0; i<cell_list->size; i++){									//Por cada célula en la lista de células...
		c1 = lookAt(cell_list, i);											//Guardamos en c1 a la célula iterada
		for(int j=0; j<cell_list->size; j++){								//De nuevo iteramos sobre la misma lista
			if(i != j){														//Y si los índices son distintos (no estamos iterando sobre la misma célula)
				c2 = lookAt(cell_list, j);									//Guardamos en c2 la otra célula
				if((c1->pos_i == c2->pos_i || c1->pos_i == (c2->pos_i)-1 || c1->pos_i == (c2->pos_i)+1) &&
				   (c1->pos_j == c2->pos_j || c1->pos_j == (c2->pos_j)-1 || c1->pos_j == (c2->pos_j)+1)){		//Si cumple unas condiciones curiosas, entonces las células son adyacentes, son vecinas																				//Indicamos en la matríz que sí son adyacentes
					adjMat[i][j] = 1;
				}
				else															//Si no cumplen las condiciones
					adjMat[i][j] = 0;
			}
			else																//Si no cumplen las condiciones
				adjMat[i][j] = 0;												//No son adyacentes
		}
	}
}

void printAdjacencyMatrix(int order, int (*adjMat)[order], int rows, int cols){
	printf("Matriz de adyacencia\n\n");

	#pragma omp parallel
	#pragma omp master
	for(int i=0; i<rows*cols; i++){
		for(int j=0; j<rows*cols; j++){
			printf("%d ", adjMat[i][j]);
		}
		printf("\n");
	}

	printf("\n--- Estados ---\n");
}

DLList * newTurn(DLList *cell_list, int order, int (*adjMat)[order], int rows, int cols){	//Función para generar un nuevo turno
	int alive = 0;														//Inicializamos un contador de las células vecinas vivas
	DLList *cell_list2 = newDLList();
	Cell_t * c, *c1, *new_cell;											//Declaramos una variable para una célula
	#pragma omp parallel
	#pragma omp master	
	for(int i=0; i<cell_list->size; i++){								//Iteramos sobre las filas de la matríz de adyacencia
		for(int j=0; j<cell_list->size; j++)							//Iteramos sobre las columnas de la matríz de adyacencia
			if( adjMat[i][j] == 1 ){									//Si la célula actual es adyacente a la célula en i,j
				//printf("Adyacente\n");
				c1 = lookAt(cell_list, j);								//Obtenemos la célula en la lista en la posición j
				if(c1->status == 1)										//Verificamos si dicha célula adyacente está viva
					alive++;											//Si lo está, incrementamos el contador
			}
		c = lookAt(cell_list, i);										//Traemos la célula que estamos iterando
		//printf("Vivas: %d\n", alive);
		new_cell = changeCellStatus(c, checkRules(c, alive));			//Cambiamos su estado en base a las reglas
		append(cell_list2, new_cell);
		alive = 0;
	}
	//cell_list = cell_list2;
	return cell_list2;
}

int checkRules(Cell_t *c, int alive){						//Reglas para cambiar el estado de una célula
	if(c->status == 1 && alive < 2)							//Si está viva y tiene 0 o 1 célula vecina viva...
		return 0;											//Muere :(
	if(c->status == 1 && alive > 3)							//Si está viva y tiene 4 o más vecinas vivas...
		return 0;											//Muere :(
	if(c->status == 0 && (alive == 2 || alive == 3))		//Si está muerta y tiene 2 o 3 vecinas vivas...
		return 1;											//Revive :O
	return c->status;										//En cualquier otro caso, no se inmuta
}

int getRandomNumber(int max_value, int last){
	int new_num;											//Se declara un arreglo de números con tamaño fijo, y una variable para alojar números aleatorios
	do{
		new_num = rand()%max_value;  						//Creamos un nuevo número aleatorio
	}while(new_num == last);								//Mientras el nuevo sea igual que el anterior
	return new_num;											//Cuando sean distintos, lo retornamos
}