#include "square.h"

void list_append(struct square *Head,struct square *Square){
	struct square *temp=Head;
	while(temp->next->isNULL==0){
		temp = temp->next;
	}
	temp->next = Square;
	Square->next = &NULLSQUARE;
}

void list_remove(struct square *Head,struct square *Square){
	struct square *last=Head;
	struct square *temp;
	temp=Head->next;
	while(temp->isNULL==0){
		if(temp==Square){
			break;
		}
			
		last = last->next;
		temp = temp->next;
	}
	
	last->next = temp->next;
	temp->next = &NULLSQUARE;
	
}

void list_show(struct square *Head){
	struct square *temp;
	temp = Head;
	printf("[");
	
	while(temp->isNULL==0){
		printf("(%d,%d),",temp->xMin,temp->yMax);
		temp=temp->next;
	}
	printf("]\r\n");
}


