//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
#include "Cell.h"

int dataValidation(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
	if(dataValidation(argc, argv) == 0){
		printf("Datos no válidos o déficit de los mismos. Ingrese: número de filas, número de columnas, número de células iniciales vivas\n");
		return 0;
	}
	int rows = atoi(argv[1]), cols = atoi(argv[2]), seeds = atoi(argv[3]);
	DLList *cell_list = newDLList();
	createCells(cell_list, rows, cols, seeds);
	showCells(cell_list, rows, cols);
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



