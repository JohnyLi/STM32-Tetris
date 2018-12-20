#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"
#include <stdlib.h>


 //���ķ��������
void change_coordinate(struct square * Square,u16 xMin,u16 yMax){
	Square->xMin = xMin;
	Square->yMax = yMax;
}

//���һ���µķ���
struct square get_square(u16 xMin,u16 yMax){
	struct square Square;
	Square.xMin = xMin;
	Square.yMax = yMax;
	Square.next = &NULLSQUARE;
	Square.isNULL = 0;
	return Square;
	
}

struct square *getSquareSeek(u16 xMin,u16 yMax){
	struct square *Square = (struct square*)malloc(sizeof(struct square));
	Square->xMin = xMin;
	Square->yMax = yMax;
	Square->next = &NULLSQUARE;
	Square->isNULL = 0;
	return Square;
}

void drawSquare(struct square * Square){ //��һ������
	u16 xMin = Square->xMin;
	u16 yMin = Square->yMax - SQUARE_LENGTH;
	u16 yMax = Square->yMax;
	u16 xMax = Square->xMin + SQUARE_LENGTH;
	
	//LCD_Fill(Square->xMin,Square->yMax - SQUARE_LENGTH,Square->xMin + SQUARE_LENGTH,Square->yMax,BLACK);
	
	LCD_DrawLine(xMin,yMin,xMax,yMin); //��
	LCD_DrawLine(xMin,yMax,xMax,yMax); //��
	LCD_DrawLine(xMin,yMin,xMin,yMax); //��
	LCD_DrawLine(xMax,yMin,xMax,yMax); //��
	
	LCD_DrawLine(xMin,yMin+2,xMax,yMin+2); //��
	LCD_DrawLine(xMin,yMax-2,xMax,yMax-2); //��
	LCD_DrawLine(xMin+2,yMin,xMin+2,yMax); //��
	LCD_DrawLine(xMax-2,yMin,xMax-2,yMax); //��
}

u8 isNULL(struct square * Square){
	if(Square->isNULL)
		return 1;
	else
		return 0;
}

void dropSquare(struct square * Square,u8 speed){
	Square->yMax += speed;
}

void simpleClearSquare(struct square * Square){
	LCD_Fill(Square->xMin,Square->yMax - SQUARE_LENGTH,Square->xMin + SQUARE_LENGTH,Square->yMax,WHITE);
}

void shiftSquareLeft(struct square * Square,u8 speed){
	Square->xMin -= speed;
}

void shiftSquareRight(struct square * Square,u8 speed){
	Square->xMin += speed;
}



struct square getHeadSquare(void){
	struct square head;
	head.isNULL = 0;
	head.next = &NULLSQUARE;
	return head;
}


struct square SquareCopy(struct square *s){
	struct square newSquare;
	newSquare.isNULL = s->isNULL;
	newSquare.next = s->next;
	newSquare.xMin = s->xMin;
	newSquare.yMax = s->yMax;
	
	return newSquare;
}

void setSquareGroup(void){
	
	// �����µķ�����
	u8 choose;
	struct square *a;
	struct square *b;
	struct square *c;
	struct square *d;
	choose = rand()%2;
	nowSpeed = originSpeed; //�����ٶ�
	if(choose == 0){
		a = getSquareSeek(100,50);
		b = getSquareSeek(100+SQUARE_LENGTH,50);
		c = getSquareSeek(100+2*SQUARE_LENGTH,50);
		d = getSquareSeek(100+3*SQUARE_LENGTH,50);
		list_append(&DropSquareHead,a);
		list_append(&DropSquareHead,b);
		list_append(&DropSquareHead,c);
		list_append(&DropSquareHead,d);
		
		
	}
	else if(choose == 1){
		a = getSquareSeek(100,50);
		b = getSquareSeek(100+SQUARE_LENGTH,50);
		c = getSquareSeek(100+SQUARE_LENGTH,50+SQUARE_LENGTH);
		d = getSquareSeek(100+2*SQUARE_LENGTH,50);
		list_append(&DropSquareHead,a);
		list_append(&DropSquareHead,b);
		list_append(&DropSquareHead,c);
		list_append(&DropSquareHead,d);
		
		
	}
	refreshDropAttr();
}

void initHeightHead(void){
	struct heightROW *temp,*seek;
	u8 i;
	heightHead = (struct heightROW*)malloc(sizeof(struct heightROW));
	seek = heightHead;
	heightHead->yMin = GameFrame.yMax;
	for(i=0;i<GameFrame.rowNum;i++){
		temp = (struct heightROW*)malloc(sizeof(struct heightROW));
		temp->row = i;
		temp->yMin = GameFrame.yMax;
		seek->next = temp;
		temp->next = NULL;
		seek = temp;
	}
	
	
}

void refreshHeight(void){
	struct heightROW *temp;
	struct square *tempSquare;
	u16 yMinALL;
	yMinALL = GameFrame.yMax;
	temp = heightHead->next;
	while(temp!=NULL){
		u16 xMin,yMin;
		xMin = temp->row * SQUARE_LENGTH + GameFrame.xMin;
		yMin = GameFrame.yMax;
		tempSquare = HeadSquare.next;
		while(tempSquare->isNULL==0){
			if(tempSquare->xMin==xMin){
				if(tempSquare->yMax-SQUARE_LENGTH < yMin){
					yMin = tempSquare->yMax-SQUARE_LENGTH;
				}
			}	
			tempSquare = tempSquare->next;
		}
		temp ->yMin = yMin;
		if(yMin<yMinALL)
			yMinALL = yMin;
		temp = temp->next;
	}
	heightHead->yMin = yMinALL;
}

//������з���1,�ұ����з���2,�����з���0
//1Ϊstop��2Ϊdrop
u8 checkTwoSquareCrossHorizental(struct square *s1,struct square *s2){
	u16 xMin1,yMax1,xMax1,yMin1,xMin2,yMax2,xMax2,yMin2;
	xMin1 = s1->xMin;
	yMax1 = s1->yMax;
	xMin2 = s2->xMin;
	yMax2 = s2->yMax;
	xMax1 = xMin1 + SQUARE_LENGTH;
	yMin1 = yMax1 - SQUARE_LENGTH;
	xMax2 = xMin2 + SQUARE_LENGTH;
	yMin2 = yMax2 - SQUARE_LENGTH;
	
	//��������
	//�ұ�����
	if(xMin1 == xMax2 ){
		//1���ϵ���2�� �� 2���ϵ���1��
		if((yMin1<yMax2 && yMin1 > yMin2)||(yMin2 < yMax1 && yMin2 > yMin1)){
			return 2;
		}
	}
	//��������
	//�������
	else if(xMin2 == xMax1){
		//1���ϵ���2�� �� 2���ϵ���1��
		if((yMin1<yMax2 && yMin1 > yMin2)||(yMin2 < yMax1 && yMin2 > yMin1)){
			return 1;
		}
	}
	return 0;
	
}



//�鿴�Ƿ�ֱ�ཻ �����ཻ�Ĵ�С
//�����ཻ�򷵻�100�����ཻ���ص��򷵻ز���Ĵ�С
//����1Ϊstop��,����2Ϊdrop��
//ֻ����x�����ص�ʱ,����2��������뷽��1�����
u8 checkTwoSquareCrossVertical(struct square *s1,struct square *s2){
	u16 xMin1,yMax1,xMax1,yMin1,xMin2,yMax2,xMax2,yMin2;
	xMin1 = s1->xMin;
	yMax1 = s1->yMax;
	xMin2 = s2->xMin;
	yMax2 = s2->yMax;
	xMax1 = xMin1 + SQUARE_LENGTH;
	yMin1 = yMax1 - SQUARE_LENGTH;
	xMax2 = xMin2 + SQUARE_LENGTH;
	yMin2 = yMax2 - SQUARE_LENGTH;
	
	if(xMin1 == xMin2){
		//����1�ڷ���2����,���Է���2�µ��ڷ���1�� �򷽿�2�µ��뷽��1�ϵ��غ�
		if(yMax2<yMax1 && yMax2>=yMin1){
			u8 loss = yMax2-yMin1;
			return loss;
		}
	}
	return 100;
	
}

//����������,�������Ϊ1���ұ�����Ϊ2��������Ϊ0
u8 checkDropSquareCanMoveLeftORRight(void){
	struct square *tempDrop,*tempStop;
	
	tempDrop = DropSquareHead.next;
	while(tempDrop->isNULL==0){
		tempStop = HeadSquare.next;
		while(tempStop->isNULL==0){
			u8 checkSeek;
			checkSeek = checkTwoSquareCrossHorizental(tempStop,tempDrop);//����������,�������Ϊ1���ұ�����Ϊ2��������Ϊ0
			if(checkSeek!=0)
				return checkSeek;
			tempStop = tempStop->next;
		}
		tempDrop = tempDrop->next;
	}
	return 0;
}


//���������,�ص����ز���ľ���,���򷵻�100
u8 getLossDropSquareCanDrop(void){
	struct square *tempDrop,*tempStop;
	
	tempDrop = DropSquareHead.next;
	while(tempDrop->isNULL==0){
		tempStop = HeadSquare.next;
		while(tempStop->isNULL==0){
			u8 checkSeek;
			checkSeek = checkTwoSquareCrossVertical(tempStop,tempDrop);//����ཻ���,100��Ϊ���ཻ,������Ϊ����ľ���
			if(checkSeek!=100)
				return checkSeek;
			tempStop = tempStop->next;
		}
		tempDrop = tempDrop->next;
	}
	return 100;
	
	
}

