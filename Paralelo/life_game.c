//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#include "Cell.h"
#include <omp.h>

int dataValidation(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
	if(dataValidation(argc, argv) == 0){
		printf("Hacen falta datos. Ingrese: número de filas, número de columnas, número de células iniciales vivas\n");
		return 0;
	}
	//Ponemos nombres a los parámetros que se pasan
	int rows = atoi(argv[1]), cols = atoi(argv[2]), seeds = atoi(argv[3]), max_it = atoi(argv[4]), flag = atoi(argv[5]);		
	int adjMat[rows*cols][rows*cols];
	DLList *cell_list = newDLList();											//Creamos una lista de células vacía
	createCells(cell_list, rows, cols, seeds);									//La llenamos
	generateAdjacencyMatrix(cell_list, rows*cols, adjMat, rows, cols);			//Generamos la matríz de adyacencia de la lista anterior

	if(flag == -1)
		printAdjacencyMatrix(rows*cols, adjMat, rows, cols);

	#pragma omp parallel
	#pragma omp master
	for(int i=0; i<max_it; i++){												//Iteraremos el número de veces que se indiquen:
		cell_list = newTurn(cell_list, rows*cols, adjMat, rows, cols);									
		if(flag == -1){
			printf("\n-- Iteración[%d] -- \n", i+1);
			showCells(cell_list, rows, cols);
		}
	}
	if(flag == 0)
		showCells(cell_list, rows, cols);
	return 0;
}

int dataValidation(int argc, char const *argv[]){
	if(argc < 6)
		return 0;
	return 1;
}



