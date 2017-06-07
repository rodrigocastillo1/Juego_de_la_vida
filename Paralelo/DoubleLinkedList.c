//AUTORES: Rodrigo Castillo, Rodrigo Vivas, Ricardo Hernández

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"


DLList * newDLList()
{
	DLList * newList = (DLList *)calloc(1, sizeof(DLList)); //Creamos el espacio para la lista
	newList->head = NULL; //Inicializamos a la lista
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}


DLNode * newDLNode(void* data)
{
	DLNode *new = (DLNode *)malloc(sizeof(DLNode)); //Creamos el espacio para un nodo nuevo
	new->data = data; //Almacenamos el dato recibido en el nodo
	new->next = NULL; //Inicializamos el nodo
	new->prev = NULL;
	return new;
}


void recycleDLList(DLList *list)
{
	DLNode *cursor, *aux;
	cursor = list->head; //Inicializamos el cursor en la cabeza de la lista
	while(cursor != NULL) //Mientras no se llegue al final de la lista...
	{
		aux = cursor->next; //Usamos una variable auxiliar para no perder la referencia del siguiente del cursor
		free(cursor); //Liberamos el nodo al que apunta el cursor
		cursor = aux; //Ahora el cursor es el siguiente
	}
	free(list); //Liberamos el espacio de la lista
}


int isEmpty(DLList *list)
{
	return list->head == NULL; //Si la cabeza de la lista es NULL entonces la lista está vacía
}


int search(DLList *list, void *data)
{
	DLNode * cursorH, *cursorT;
	int j,i;
	cursorH=list->head; 
	cursorT=list->tail;
		
		for(i=0, j=list->size-1; cursorH!=NULL; i++, j--) //Se seguirá iterando hasta que el cursorH (que va hacia al frente) llegue a NULL 
		{
			if(cursorH->data == data) //Si el dato que está en el cursor que va hacia la derecha regresamos el contador
				return i;
			cursorH = cursorH->next; //Sino, desplazamos el cursor
		
			if(cursorT->data == data) //Si el dato que está en el cursor que va hacia la izquierda regresamos el contador
				return j;
			cursorT = cursorT->prev; //Sino, desplazamos el cursor
		}
	return -1; //Si no se encuentra el elemento y se termina de recorrer la lista hacia ambos lados, regresamos una posición imposible
}

void insertAt(DLList *list, int pos, void *data)
{	
	int i;
	DLNode * cursor, * new;
	new = newDLNode(data);
	if(pos > (list->size)) //Si la posición en la que se quiere ingresar supera los límites de la lista...
	{
		printf("No es posible insertar en la posición %d. Está fuera del límite\n",pos);
		return;
	}
	
	if(isEmpty(list) && pos == 0) //Si la posición en la que se quiere ingresar en la 0 y la pila está vacía...
	{ 
		list->head = new; //Head será el nuevo
		list->tail = new; //Tail también será el nuevo
		list->size++; //Incrementamos el tamaño de la lista
		return;
	}

	if(pos == 0) //Si la posición en la que queremos insertar en la 0 (no necesariamente cuando la lista está vacía)...
	{
		new->next = list->head; //El siguiente del auxiliar será el que está en la cabeza de la lista
		list->head->prev = new; //El anterior de la cabeza será el auxiliar
		list->head = new; //Hacemos el la nueva cabeza sea el auxiliar
		list->size++; //Incrementamos el tamaño de la lista
		return;
	}
	
	if(pos == list->size) //Si la posición que se solicitó es la misma que el tamaño de la lista...
	{
		new->prev = list->tail; //El anterior del auxiliar será el que está en el "tope"
		list->tail->next = new; //El siguiente del "tope" será el auxiliar
		list->tail = new; //Hacemos que el tope también sea el auxiliar
		list->size++; //Finalmente incrementamos el tamaño
		return;
	}	

	if((list->size)/2 > pos) //Si el número de elementos de la lista divido entre dos es mayor que la posición dada (significa que es más rápido buscarla desde el extremo izquierdo)
	{
		cursor = list->head; //Nuestro cursor para recorrer la lista comenzará en head hasta el extremo buscado
		for(i=0; i<pos; i++) //Recorremos la lista hasta la posición		
			cursor = cursor->next;
	}	
	else //Si no se cumple la primera condición quiere decir que el elemento está más cerca del extremo derecho de la lista
	{	
		cursor = list->tail; //Comenzamos a recorrer desde tail (derecha)
		for(i=list->size-1; i<=pos; i--) //Recorremos la lista hasta la posición	
			cursor =cursor->prev;
	}
	//Una vez que llegamos a la posición deseada...
	new->next = cursor; //Hacemos que el siguiente del nuevo nodo sea el nodo que está en el cursor
	new->prev = cursor->prev; //Hacemos que el anterior del nuevo nodo sea el nodo anterior al que está en el cursor
	(cursor->prev)->next = new; //Hacemos que el siguiente del nodo anterior al que está en el cursor sea el nuevo
	cursor->prev = new; //Hacemos que el anterior del cursor sea el nuevo nodo
	list->size++; //Finalmente incrementamos el tamaño de la lista
	return;
}


void append(DLList *list, void *data)
{	
	insertAt(list, list->size, data); //Para ingresar un dato al final de la lista simplemente le pasamos a insertAt el dato y le indicamos la posición final, que es el tamaño de la lista
	return;
}

void* lookAt(DLList *list, int pos){
	DLNode * cursor;
	char *temp;
	if(!isEmpty(list) && pos<=(list->size-1)){
		cursor = list->head;
		for(int i=0; i<pos; i++){
			cursor = cursor->next;
		}
		temp = cursor->data;
		//printf("Todo chido\n");
		//return(*(cursor->data));
		return(temp);
	}
}


void removeAt(DLList *list, int pos)
{	
	int i;
	DLNode *aux;

	if(isEmpty(list) || pos>=list->size) //Si la lista está vacía o la posición en la que se quiere extraer al dato es mayor al tamaño de la lista...
	{
		printf("No es posible remover ningún elemento en la posición %d. Está fuera del límite\n",pos);
		return;
	}	

	if(pos == list->size-1) //Si la posición requerida está en el "final" de la lista
	{
		aux = list->tail; //Guardamos en el auxiliar al último
		list->tail = list->tail->prev;//Ahora el último será el anterior del que estamos removiendo 
		free(aux); //Liberamos el nodo que quitamos de la lista
		list->size--; //Decrementamos el tamaño
		return;
	}	

	if(pos == 0)
	{
		aux = list->head; //Si la posición de la que se quiere extraer es la primera:
		list->head = list->head->next; //El nuevo principio será el siguiente del que estaba al principio
		free(aux); //Liberamos el nodo que estaba al principio
		list->size--; //Decrementamos en tamaño de la lista	
		return;
	}
	
	if((list->size/2) > pos) //Si el número de elementos de la lista divido entre dos es mayor que la posición dada (significa que es más rápido buscarla desde el extremo izquierdo)
	{
		aux = list->head; //Usamos a aux como un cursor y recorremos la lista desde head
		
		for(i=0; i!=pos; i++)	
			aux =aux->next;	
	}	
	else//Si no se cumple la primera condición quiere decir que el elemento está más cerca del extremo derecho de la lista
	{
		aux = list->tail; //Usamos a aux como un cursor y recorremos la lista desde tail
		
		for(i=list->size-1; i!=pos; i--) 	
			aux =aux->prev;
	}
	(aux->next)->prev = aux->prev; //Hacemos que el anterior del nodo siguiente a donde está el cursor sea el anterior del cursor
	(aux->prev)->next = aux->next; //Hacemos que el siguiente del nodo anterior al que está el cursor sea el siguiente del cursor
	free(aux); //Liberamos el nodo del cursor
	list->size--;//Decrementamos el tamaño de la lista
	return;
}


void remov(DLList * list, void *data)
{	
	int pos;
	pos = search(list, data); //Usamos la función de búsqueda para encontrar la posición en la que se encuentra el dato
	if(pos == -1) //Si regresa un -1 es porque no se encontró al dato dentro de la lista
	{
		printf("Ningún dato dentro de la lista coincide con la búsqueda\n");
		return;
	}
	removeAt(list, pos); //Si existe, simplemente lo eliminamos de la lista con la función de remover en una posición
}