#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"
#include <stdlib.h>

u16 SQUARE_COLOR;

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
	POINT_COLOR = SQUARE_COLOR;
	if(Square->isStop==1)
		POINT_COLOR = BLACK;
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

void drawSimpleSquare(struct simpleSquare * Square){ 
	u8 sXstart,sYstart,x,y,xMin,yMin,xMax,yMax;
	x = Square->x;
	y = Square->y;
	sXstart = NextFrame.xMin + SIMPLE_SQUARE_LENGTH - 1;
	sYstart = NextFrame.yMax - SIMPLE_SQUARE_LENGTH;
	xMin = x*SIMPLE_SQUARE_LENGTH + sXstart;
	xMax = xMin + SIMPLE_SQUARE_LENGTH;
	yMax = sYstart - y*SIMPLE_SQUARE_LENGTH;
	yMin = yMax - SIMPLE_SQUARE_LENGTH;
	POINT_COLOR = BLACK;
	
	LCD_DrawLine(xMin,yMin,xMax,yMin); //��
	LCD_DrawLine(xMin,yMax,xMax,yMax); //��
	LCD_DrawLine(xMin,yMin,xMin,yMax); //��
	LCD_DrawLine(xMax,yMin,xMax,yMax); //��
	
	LCD_DrawLine(xMin,yMin+1,xMax,yMin+1); //��
	LCD_DrawLine(xMin,yMax-1,xMax,yMax-1); //��
	LCD_DrawLine(xMin+1,yMin,xMin+1,yMax); //��
	LCD_DrawLine(xMax-1,yMin,xMax-1,yMax); //��
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
	newSquare.xMin = s->xMin;
	newSquare.yMax = s->yMax;
	
	return newSquare;
}

void setSquareGroup(void){
	
	// �����µķ�����
	u8 choose,xStart,yStart;
	struct square *a;
	struct square *b;
	struct square *c;
	struct square *d;
	xStart = GameFrame.xMin + SQUARE_LENGTH*3;
	yStart = GameFrame.yMin;
	
	
	choose = rand()%SQUARE_GROUP_NUM;
	nowSpeed = originSpeed; //�����ٶ�
	
	//���տ�ʼ��������һ��������
	if(makeNextSeek==0){
		makeSimpleSquareGroup(choose);
		makeNextSeek=1;
	}
	
	a = getSquareSeek(sa.x*SQUARE_LENGTH + xStart ,yStart - sa.y*SQUARE_LENGTH);
	b = getSquareSeek(sb.x*SQUARE_LENGTH + xStart ,yStart - sb.y*SQUARE_LENGTH);
	c = getSquareSeek(sc.x*SQUARE_LENGTH + xStart ,yStart - sc.y*SQUARE_LENGTH);
	d = getSquareSeek(sd.x*SQUARE_LENGTH + xStart ,yStart - sd.y*SQUARE_LENGTH);
	list_append(&DropSquareHead,a);
	list_append(&DropSquareHead,b);
	list_append(&DropSquareHead,c);
	list_append(&DropSquareHead,d);
	
	
	makeSimpleSquareGroup(choose);
	
	draw_nextFrame();
	drawSimpleSquare(&sa);
	drawSimpleSquare(&sb);
	drawSimpleSquare(&sc);
	drawSimpleSquare(&sd);
	
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
//ˢ��ֹͣ�������������x,y���ֵ����Сֵ
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
	u16 xMin1,yMax1,yMin1,xMin2,yMax2;
	xMin1 = s1->xMin;
	yMax1 = s1->yMax;
	xMin2 = s2->xMin;
	yMax2 = s2->yMax;
	yMin1 = yMax1 - SQUARE_LENGTH;
	
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
			if(checkSeek!=0){
				return checkSeek;
			}
			tempStop = tempStop->next;
		}
		tempDrop = tempDrop->next;
	}
	return 0;
}


//���������,�ص����ز���ľ���,���򷵻�100
u8 getLossDropSquareCanDrop(void){
	struct square *tempDrop,*tempStop;
	int xx = 1;
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


u8 checkTwoSquareNear(struct square *s1,struct square *s2){
	u16 x1,x2,y1,y2;
	x1 = s1->xMin;
	y1 = s1->yMax;
	x2 = s2->xMin;
	y2 = s2->yMax;
	if(x1==x2){
		if(y1-y2==SQUARE_LENGTH || y2-y1==SQUARE_LENGTH)
			return 1;
		else
			return 0;
	}
	else if(x1-x2==SQUARE_LENGTH||x2-x1==SQUARE_LENGTH){
		if(y1==y2)
			return 1;
		else
			return 0;
		
	}
	return 0;
	
	
}





//���������,�ص����ز���ľ���,���򷵻�100
u8 getLossTempSquareCanDrop(struct square *tempHead){
	struct square *tempDrop,*tempStop;
	
	tempDrop = tempHead->next;
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

//��ת����
void rotateSquareGroup(void){
	struct square *tempSquare,*temp1;
	struct square a,b,c,d;
	u16 xMax,yMax,xMin,yMin,xMiddle,yMiddle;
	u8 loss,seek;
	xMax = 0;
	yMax = 0;
	xMin = GameFrame.xMax;
	yMin = GameFrame.yMax;
	
	//���Ʒ�������
	a = SquareCopy(DropSquareHead.next);
	b = SquareCopy(DropSquareHead.next->next);
	c = SquareCopy(DropSquareHead.next->next->next);
	d = SquareCopy(DropSquareHead.next->next->next->next);
	
	//��������
	tempSquareHead.next = &(a);
	a.next = &(b);
	b.next = &(c);
	c.next = &(d);
	d.next = &NULLSQUARE;
	
	//�ҵ���ǰ���䷽����� xMax,yMax,xMin,yMin
	tempSquare = DropSquareHead.next;
	while(tempSquare->isNULL==0){
		if(tempSquare->xMin+SQUARE_LENGTH>xMax)
			xMax = tempSquare->xMin+SQUARE_LENGTH;
		if(tempSquare->yMax>yMax)
			yMax = tempSquare->yMax;
		if(tempSquare->xMin<xMin)
			xMin = tempSquare->xMin;
		if(tempSquare->yMax-SQUARE_LENGTH<yMin)
			yMin = tempSquare->yMax-SQUARE_LENGTH;
		tempSquare = tempSquare->next;
	}
	
	//�����е�
	xMiddle = (xMax-xMin)/2+xMin;
	yMiddle = (yMax-yMin)/2+yMin;
	
	
	tempSquare = &a;
	while(tempSquare->isNULL==0){
			u8 xLoss,yLoss,xm,ym;
			xm = tempSquare->xMin+SQUARE_LENGTH/2;
			ym = tempSquare->yMax-SQUARE_LENGTH/2;
		
			//��תx,y����
			if(xMiddle>=xm){
				yLoss = xMiddle-xm;
				tempSquare->yMax = yMiddle-yLoss+SQUARE_LENGTH/2;
			}
			else{
				yLoss = xm-xMiddle;
				tempSquare->yMax = yMiddle+yLoss+SQUARE_LENGTH/2;
			}
			if(yMiddle>=ym){
				xLoss = yMiddle-ym;
				tempSquare->xMin = (xMiddle+xLoss)-SQUARE_LENGTH/2;
			}
			else{
				xLoss = ym-yMiddle;
				tempSquare->xMin = (xMiddle-xLoss)-SQUARE_LENGTH/2;
			}
			
			//����x����
			while((tempSquare->xMin-GameFrame.xMin)%SQUARE_LENGTH!=0)
				tempSquare->xMin += SQUARE_LENGTH/2;
			
			tempSquare = tempSquare->next;
	}
	
	//������ǰxMin��xMax
	tempSquare = &a;
	xMin = GameFrame.xMax;
	xMax = 0;
	seek = 0; 
	while(tempSquare->isNULL==0){
		if(tempSquare->xMin+SQUARE_LENGTH>xMax)
			xMax = tempSquare->xMin+SQUARE_LENGTH;
		if(tempSquare->xMin<xMin)
			xMin = tempSquare->xMin;
		tempSquare = tempSquare->next;
	}
	
	//�鿴�Ƿ񳬳���Ϸ��
	if(xMin<GameFrame.xMin){
		seek = 1;
		loss = GameFrame.xMin-xMin;
	}
	else if(xMax>GameFrame.xMax){
		loss = xMax-GameFrame.xMax;
		seek = 2;
	}
	
	
	if(seek!=0){
		tempSquare = &a;
		while(tempSquare->isNULL==0){
			//����������
			if(seek==1)
				tempSquare->xMin += loss;
			//��������ұ�
			else if(seek==2)
				tempSquare->xMin -= loss;
			tempSquare = tempSquare->next;
		}
		
	}
		
	
	if(getLossTempSquareCanDrop(&tempSquareHead)!=100)  //��鴹ֱ�����������飬���в�����������ת
		return;
	else{
		//��������ת,��Է���������и�ֵ
		tempSquare = &a;
		temp1 = DropSquareHead.next;
		while(tempSquare->isNULL==0){
			temp1->xMin = tempSquare->xMin;
			temp1->yMax = tempSquare->yMax;
			
			tempSquare = tempSquare->next;
			temp1 = temp1->next;
			
		}
		
		
	}
	
}



