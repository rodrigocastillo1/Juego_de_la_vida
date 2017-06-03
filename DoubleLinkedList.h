//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

struct DLNode
{											
	struct DLNode *next;
	struct DLNode *prev;
	void *data;
};

typedef struct DLNode DLNode;

typedef struct
{
	DLNode *head;
	DLNode *tail;
	int size;
} DLList;

//Funciones básicas:
DLNode *newDLNode(void* data); 							
DLList *newDLList();
int isEmpty(DLList *list);
void recycleDLList(DLList *list);
//Búsqueda:
int search(DLList *lista, void* data);						
//Inserción:
void insertAt(DLList *list, int position, void* data);		
void append(DLList *list, void* data);						
//Eliminación
void removeAt(DLList *list, int position);
void remov(DLList * lista, void* data);
//Copias:
void* lookAt(DLList *list, int pos);				