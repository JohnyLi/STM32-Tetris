#include "list.h"
#include "square.h"

void list_append(square *Square){
	square *temp=&HeadSquare;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = Square;
	Square->next = NULL;
}

void list_remove(square *Square){
	square *last=&HeadSquare
	square *temp=HeadSquare.next;
	
	while(temp!=NULL){
		if(temp==Square)
			break;
		last = last->next;
		temp = temp->next;
	}
	
	last->next = temp->next;
	temp->next = NULL;
	
}

void list_show(void){
	printf("[");
	square *temp=&HeadSquare;
	while(temp!=NULL){
		printf("(%d,%d),",temp->xMin,temp->yMax);
		temp=temp->next;
	}
	printf("]");
}
