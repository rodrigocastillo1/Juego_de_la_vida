//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#include "Cell.h"

int dataValidation(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
	int max_it = 5;
	if(dataValidation(argc, argv) == 0){
		printf("Datos no válidos o déficit de los mismos. Ingrese: número de filas, número de columnas, número de células iniciales vivas\n");
		return 0;
	}
	int rows = atoi(argv[1]), cols = atoi(argv[2]), seeds = atoi(argv[3]);		//Ponemos nombres a los parámetros que se pasan
	DLList *cell_list = newDLList();											//Creamos una lista de células vacía
	DLList *adjMat = newDLList();
	createCells(cell_list, rows, cols, seeds);									//La llenamos
	for(int i=0; i<max_it; i++){												//Iteraremos el número de veces que se indiquen:
		generateAdjacencyMatrix(cell_list, adjMat);								//Generamos la matríz de adyacencia de la lista anterior
		newTurn(cell_list, adjMat, rows, cols);									
		showCells(cell_list, rows, cols);
	}
	return 0;
}

int dataValidation(int argc, char const *argv[]){
	if(argc < 4){
		return 0;
	}
	/*for(int i=1; i<4; i++){
		if( sizeof(argv[i]) != sizeof(int))
			return 0;
	}*/
	return 1;
}



