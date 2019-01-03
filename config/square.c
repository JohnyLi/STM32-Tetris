#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"
#include <stdlib.h>

u16 SQUARE_COLOR;

 //更改方块的坐标
void change_coordinate(struct square * Square,u16 xMin,u16 yMax){
	Square->xMin = xMin;
	Square->yMax = yMax;
}

//获得一个新的方块
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

void drawSquare(struct square * Square){ //画一个方块
	u16 xMin = Square->xMin;
	u16 yMin = Square->yMax - SQUARE_LENGTH;
	u16 yMax = Square->yMax;
	u16 xMax = Square->xMin + SQUARE_LENGTH;
	POINT_COLOR = SQUARE_COLOR;
	if(Square->isStop==1)
		POINT_COLOR = BLACK;
	//LCD_Fill(Square->xMin,Square->yMax - SQUARE_LENGTH,Square->xMin + SQUARE_LENGTH,Square->yMax,BLACK);
	
	LCD_DrawLine(xMin,yMin,xMax,yMin); //上
	LCD_DrawLine(xMin,yMax,xMax,yMax); //下
	LCD_DrawLine(xMin,yMin,xMin,yMax); //左
	LCD_DrawLine(xMax,yMin,xMax,yMax); //右
	
	LCD_DrawLine(xMin,yMin+2,xMax,yMin+2); //上
	LCD_DrawLine(xMin,yMax-2,xMax,yMax-2); //下
	LCD_DrawLine(xMin+2,yMin,xMin+2,yMax); //左
	LCD_DrawLine(xMax-2,yMin,xMax-2,yMax); //右
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
	
	LCD_DrawLine(xMin,yMin,xMax,yMin); //上
	LCD_DrawLine(xMin,yMax,xMax,yMax); //下
	LCD_DrawLine(xMin,yMin,xMin,yMax); //左
	LCD_DrawLine(xMax,yMin,xMax,yMax); //右
	
	LCD_DrawLine(xMin,yMin+1,xMax,yMin+1); //上
	LCD_DrawLine(xMin,yMax-1,xMax,yMax-1); //下
	LCD_DrawLine(xMin+1,yMin,xMin+1,yMax); //左
	LCD_DrawLine(xMax-1,yMin,xMax-1,yMax); //右
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
	
	// 创建新的方块组
	u8 choose,xStart,yStart;
	struct square *a;
	struct square *b;
	struct square *c;
	struct square *d;
	xStart = GameFrame.xMin + SQUARE_LENGTH*3;
	yStart = GameFrame.yMin;
	
	
	choose = rand()%SQUARE_GROUP_NUM;
	nowSpeed = originSpeed; //重置速度
	
	//若刚开始则制作下一个方块组
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
//刷新停止方块组的整个的x,y最大值和最小值
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

//左边相切返回1,右边相切返回2,不相切返回0
//1为stop，2为drop
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
	
	//侧面相切
	//右边相切
	if(xMin1 == xMax2 ){
		//1的上底在2中 或 2的上底在1中
		if((yMin1<yMax2 && yMin1 > yMin2)||(yMin2 < yMax1 && yMin2 > yMin1)){
			return 2;
		}
	}
	//侧面相切
	//左边相切
	else if(xMin2 == xMax1){
		//1的上底在2中 或 2的上底在1中
		if((yMin1<yMax2 && yMin1 > yMin2)||(yMin2 < yMax1 && yMin2 > yMin1)){
			return 1;
		}
	}
	return 0;
	
}



//查看是否垂直相交 返回相交的大小
//若无相交则返回100，有相交或重叠则返回插入的大小
//方块1为stop的,方块2为drop的
//只考虑x坐标重叠时,方块2从上面插入方块1的情况
u8 checkTwoSquareCrossVertical(struct square *s1,struct square *s2){
	u16 xMin1,yMax1,yMin1,xMin2,yMax2;
	xMin1 = s1->xMin;
	yMax1 = s1->yMax;
	xMin2 = s2->xMin;
	yMax2 = s2->yMax;
	yMin1 = yMax1 - SQUARE_LENGTH;
	
	if(xMin1 == xMin2){
		//方块1在方块2下面,所以方块2下底在方块1中 或方块2下底与方块1上底重合
		if(yMax2<yMax1 && yMax2>=yMin1){
			u8 loss = yMax2-yMin1;
			return loss;
		}
	}
	return 100;
	
}

//检查相切情况,左边相切为1，右边相切为2，不相切为0
u8 checkDropSquareCanMoveLeftORRight(void){
	struct square *tempDrop,*tempStop;
	
	tempDrop = DropSquareHead.next;
	while(tempDrop->isNULL==0){
		tempStop = HeadSquare.next;
		while(tempStop->isNULL==0){
			u8 checkSeek;
			checkSeek = checkTwoSquareCrossHorizental(tempStop,tempDrop);//检查相切情况,左边相切为1，右边相切为2，不相切为0
			if(checkSeek!=0){
				return checkSeek;
			}
			tempStop = tempStop->next;
		}
		tempDrop = tempDrop->next;
	}
	return 0;
}


//检查插入情况,重叠返回插入的距离,无则返回100
u8 getLossDropSquareCanDrop(void){
	struct square *tempDrop,*tempStop;
	int xx = 1;
	tempDrop = DropSquareHead.next;
	while(tempDrop->isNULL==0){
		tempStop = HeadSquare.next;
		while(tempStop->isNULL==0){
			u8 checkSeek;
			checkSeek = checkTwoSquareCrossVertical(tempStop,tempDrop);//检查相交情况,100则为无相交,其他则为插入的距离
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





//检查插入情况,重叠返回插入的距离,无则返回100
u8 getLossTempSquareCanDrop(struct square *tempHead){
	struct square *tempDrop,*tempStop;
	
	tempDrop = tempHead->next;
	while(tempDrop->isNULL==0){
		tempStop = HeadSquare.next;
		while(tempStop->isNULL==0){
			u8 checkSeek;
			checkSeek = checkTwoSquareCrossVertical(tempStop,tempDrop);//检查相交情况,100则为无相交,其他则为插入的距离
			if(checkSeek!=100)
				return checkSeek;
			tempStop = tempStop->next;
		}
		tempDrop = tempDrop->next;
	}
	return 100;
}

//旋转方块
void rotateSquareGroup(void){
	struct square *tempSquare,*temp1;
	struct square a,b,c,d;
	u16 xMax,yMax,xMin,yMin,xMiddle,yMiddle;
	u8 loss,seek;
	xMax = 0;
	yMax = 0;
	xMin = GameFrame.xMax;
	yMin = GameFrame.yMax;
	
	//复制方块属性
	a = SquareCopy(DropSquareHead.next);
	b = SquareCopy(DropSquareHead.next->next);
	c = SquareCopy(DropSquareHead.next->next->next);
	d = SquareCopy(DropSquareHead.next->next->next->next);
	
	//制作链表
	tempSquareHead.next = &(a);
	a.next = &(b);
	b.next = &(c);
	c.next = &(d);
	d.next = &NULLSQUARE;
	
	//找到当前下落方块组的 xMax,yMax,xMin,yMin
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
	
	//制作中点
	xMiddle = (xMax-xMin)/2+xMin;
	yMiddle = (yMax-yMin)/2+yMin;
	
	
	tempSquare = &a;
	while(tempSquare->isNULL==0){
			u8 xLoss,yLoss,xm,ym;
			xm = tempSquare->xMin+SQUARE_LENGTH/2;
			ym = tempSquare->yMax-SQUARE_LENGTH/2;
		
			//旋转x,y坐标
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
			
			//矫正x坐标
			while((tempSquare->xMin-GameFrame.xMin)%SQUARE_LENGTH!=0)
				tempSquare->xMin += SQUARE_LENGTH/2;
			
			tempSquare = tempSquare->next;
	}
	
	//制作当前xMin和xMax
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
	
	//查看是否超出游戏框
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
			//如果超出左边
			if(seek==1)
				tempSquare->xMin += loss;
			//如果超出右边
			else if(seek==2)
				tempSquare->xMin -= loss;
			tempSquare = tempSquare->next;
		}
		
	}
		
	
	if(getLossTempSquareCanDrop(&tempSquareHead)!=100)  //检查垂直插入其他方块，若有插入则不允许旋转
		return;
	else{
		//若可以旋转,则对方块逐个进行赋值
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



