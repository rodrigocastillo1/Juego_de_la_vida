//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

typedef struct{
	int pos_i;
	int pos_j;
	int status;
} Cell_t;

Cell_t * newCell(int i, int j, int s);
void createCells(DLList *cell_list, int rows, int cols, int seeds_num);
void changeCellStatus(Cell_t *cell, int new_status);
void showCells(DLList *cell_list, int n, int m);
int getRandomNumber(int max_value, int last);
void generateAdjacencyMatrix(DLList *cell_list, DLList *adjMat);
void newTurn(DLList *cell_list, DLList *adjMat, int rows, int cols);
int checkRules(Cell_t *c, int alive);
