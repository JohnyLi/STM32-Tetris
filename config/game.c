#include "gameFrame.h"
#include "game.h"
#include "square.h"
#include "lcd.h"
#include "remote.h"
#include "key.h"

u16 menuTime = 0;
u8 gameOver = 0;
u8 PressKey = 0;

u16 ACTION_LEFT = 34;
u16 ACTION_RIGHT = 194;
u16 ACTION_CHANGE = 2;
u16 ACTION_STOP = 162;
u16 ACTION_DOWN = 168;
u16 ACTION_UP = 98;

u8 originSpeed = 1;
u8 changeSpeed = 3;
u8 maxSpeed = 9;
u16 gameTime = 0;
u16 refreshMs = 50;
u8 nowSpeed;



void updateGame(void){
	u8 action;
	action = getKeyAction();
	if(action == 0)
		action = getRemoteAction();
	
	if(heightHead->yMin<=GameFrame.yMin){
		gameOver = 1;
		return;
	}
		
	
	clearDropGroup();
	
	makeAction(action);
	makeDrop();
	
	checkNeedStop();
	drawDropGroup();
	
	draw_gameFrame();
	draw_time();
	
	//list_show(&DropSquareHead);
	//list_show(&HeadSquare);
	
	if(DropSquareHead.next->isNULL==1)
		setSquareGroup();
	
	
}


void makeAction(u8 action){
	
	if(action==ACTION_LEFT){
		struct square *tempSquare;
		tempSquare = DropSquareHead.next;
		
		if(dropXmin <= GameFrame.xMin) //坐标超出框
			return;
		else if(heightHead->yMin < dropYmax){ //当drop最大y坐标大于方块的最小y坐标时
			if(checkDropSquareCanMoveLeftORRight()==1) //检查是否可以左右移动
				return;
		}
		
		while(tempSquare->isNULL==0){
			shiftSquareLeft(tempSquare,SQUARE_LENGTH);
			tempSquare= tempSquare->next;
		}
		refreshDropAttr();
	}
	else if(action==ACTION_RIGHT){
		struct square *tempSquare;
		tempSquare = DropSquareHead.next;
		
		if(dropXmax >= GameFrame.xMax)//坐标超出框
			return;
		else if(heightHead->yMin < dropYmax){ //当drop最大y坐标大于方块的最小y坐标时
			if(checkDropSquareCanMoveLeftORRight()==2) //检查是否可以左右移动
				return;
		}
		
		while(tempSquare->isNULL==0){
			shiftSquareRight(tempSquare,SQUARE_LENGTH);
			tempSquare= tempSquare->next;
		}
		refreshDropAttr();
	}
	else if(action==ACTION_CHANGE){
		
		
	}
	else if(action==ACTION_STOP){
		
		
	}
	else if(action==ACTION_DOWN){
		nowSpeed += changeSpeed;
		if(nowSpeed > maxSpeed)
			nowSpeed = maxSpeed;
	}
	else if(action==ACTION_UP){
		if(nowSpeed < changeSpeed){
			nowSpeed = originSpeed;
		}
		else
			nowSpeed -= changeSpeed;
		
		
	}
	
	
	
}

void makeDrop(void){
		struct square *tempSquare;
		tempSquare = DropSquareHead.next;
		while(tempSquare->isNULL==0){
			dropSquare(tempSquare,nowSpeed);
			tempSquare= tempSquare->next;
		}
		refreshDropAttr();
}

void drawDropGroup(void){
		struct square *tempSquare;
		tempSquare = DropSquareHead.next;
		while(tempSquare->isNULL==0){
			drawSquare(tempSquare);
			tempSquare= tempSquare->next;
		}
	
}

void drawStopGroup(void){
		struct square *tempSquare;
		tempSquare = HeadSquare.next;
		
		while(tempSquare->isNULL==0){
			drawSquare(tempSquare);
			tempSquare= tempSquare->next;
		}
	
}

void clearDropGroup(void){
		struct square *tempSquare;
		tempSquare = DropSquareHead.next;
		while(tempSquare->isNULL==0){
			simpleClearSquare(tempSquare);
			tempSquare= tempSquare->next;
		}
}

void checkNeedStop(void){
	if(dropYmax>=GameFrame.yMax){				//当最大高度超过或等于下底时，将dropgroup对回底部，并将其从DropSquareHead链表移到HeadSquare
		u8 loss;
		struct square *tempSeek;
		loss = dropYmax - GameFrame.yMax;
		tempSeek = DropSquareHead.next;
		while(tempSeek->isNULL==0){
			struct square *temptempSquare;
			temptempSquare = tempSeek->next;
			tempSeek->yMax -= loss;
			list_remove(&DropSquareHead,tempSeek);
			list_append(&HeadSquare,tempSeek);
			tempSeek = temptempSquare;
		}
		drawStopGroup();
		refreshHeight();
	}
	else if(heightHead->yMin < dropYmax){    //当最大高度超过height的最小高度时
		u8 loss;
		struct square *tempSeek;
		loss = getLossDropSquareCanDrop();
		tempSeek = DropSquareHead.next;
		if(loss != 100){
			while(tempSeek->isNULL==0){
				struct square *temptempSquare;
				temptempSquare = tempSeek->next;
				tempSeek->yMax -= loss;
				list_remove(&DropSquareHead,tempSeek);
				list_append(&HeadSquare,tempSeek);
				tempSeek = temptempSquare;
			}
			drawStopGroup();
			refreshHeight();
			
		}
	}
	
	clearDropGroup();
}




void refreshDropAttr(void){
	u8 xMin,xMax;
	u16 yMax;
	struct square *tempDrop;
	xMin = GameFrame.xMax;
	xMax = 0;
	yMax = 0;
	tempDrop = DropSquareHead.next;
	while(tempDrop->isNULL==0){
		if(tempDrop->xMin<xMin)
			xMin = tempDrop->xMin;
		if(tempDrop->xMin+SQUARE_LENGTH>xMax)
			xMax = tempDrop->xMin+SQUARE_LENGTH;
		if(tempDrop->yMax>yMax)
			yMax = tempDrop->yMax;
		tempDrop = tempDrop->next;
	}
	dropXmin = xMin;
	dropYmax = yMax;
	dropXmax = xMax;
}


u8 getKeyAction(void){
	u16 key;
	key=KEY_Scan(0);
	
	if(key==KEY0_PRES)
		return ACTION_RIGHT;
	else if(key==KEY1_PRES)
		return ACTION_LEFT;
	else if(key==WKUP_PRES)
		return ACTION_DOWN;
	else{
		PressKey = 0;
		return 0;
	}
		
	
}


u8 getRemoteAction(void){
		u16 key;
		key=Remote_Scan();	
		
		if(key==0){	//未按键时
			if(PressKey!=0){//若PressKey不为0,则认为按键抬起,返回按下的键
				u16 tempKey = PressKey;
				PressKey = 0;
				return tempKey;
			}
		}
		else{	//按键时
			if(key==ACTION_LEFT||key==ACTION_RIGHT||key==ACTION_CHANGE||key==ACTION_STOP||key==ACTION_DOWN||key==ACTION_UP){  //若按键为指定按键，则认为该按键已按下
				if(PressKey==0||PressKey == key)
					PressKey = key;
				else if(PressKey!=key){
					u16 tempKey = PressKey;
					PressKey = key;
					return tempKey;
				}
			}
			else{
				if(PressKey != 0){
					u16 tempKey = PressKey;
					PressKey = 0;
					return tempKey;
				}
			}
				
		}
		return 0;
}
