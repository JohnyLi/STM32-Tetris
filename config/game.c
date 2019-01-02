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
u8 changeSpeed = 2;
u8 maxSpeed = 9;
u16 gameTime = 0;
u16 refreshMs = 50;
u8 nowSpeed;

u8 continueSeek = 1;
u8 cleanLineSeek = 0;
u8 stopTime = 10;	

u8 updateGame(u8 action){
	
	if(heightHead->yMin<GameFrame.yMin){
		gameOver = 1;
		return 1;
	}
	
	if(cleanLineSeek!=0){
		if(cleanLineSeek==stopTime)
			makeStopGroupDrop();
		
		cleanLineSeek--;
		if(cleanLineSeek==0){
			LCD_Fill(GameFrame.xMin,GameFrame.yMin,GameFrame.xMax,GameFrame.yMax,WHITE);
			draw_time();
			draw_gameFrame();
			drawStopGroup();
		}
		return 1;
	}
	
	if(continueSeek==0){
		return 0;
	}
		
	
	clearDropGroup();
	
	makeAction(action);
	makeDrop();
	
	checkNeedStop();
	drawDropGroup();
	
	draw_gameFrame();
	draw_time();
	draw_score();
	
	//list_show(&DropSquareHead);
	//list_show(&HeadSquare);
	
	if(DropSquareHead.next->isNULL==1)
		setSquareGroup();
	
	
	
	return 1;
	
	
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
		rotateSquareGroup();
		
	}
	else if(action==ACTION_STOP){
		//if(continueSeek == 1)
			//continueSeek = 0;
		//else
			//continueSeek = 1;
	}
	else if(action==ACTION_DOWN){
		nowSpeed += changeSpeed;
		if(nowSpeed >= maxSpeed)
			nowSpeed = maxSpeed;
	}
	else if(action==ACTION_UP){
		nowSpeed -= changeSpeed;
		if(nowSpeed <= changeSpeed){
			nowSpeed = originSpeed;
		}
			
		
		
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
	struct square *tempSeek;
	u8 loss = 100;
	if(dropYmax>=GameFrame.yMax){				//当最大高度超过或等于下底时，将dropgroup对回底部，并将其从DropSquareHead链表移到HeadSquare
		loss = dropYmax - GameFrame.yMax;
	}
	else if(heightHead->yMin < dropYmax){    //当最大高度超过height的最小高度时
		loss = getLossDropSquareCanDrop();
	}
	
	
	if(loss!=100){
		u8 result;
		tempSeek = DropSquareHead.next;
		while(tempSeek->isNULL==0){
			struct square *temptempSquare;
			temptempSquare = tempSeek->next;
			tempSeek->yMax -= loss;
			tempSeek->isStop = 1;
			list_remove(&DropSquareHead,tempSeek);
			list_append(&HeadSquare,tempSeek);
			tempSeek = temptempSquare;
		}
		result = checkLine();
		if(result==1){
			LCD_Clear(WHITE);
			draw_time();
			draw_gameFrame();
			cleanLineSeek = stopTime;
		}
		drawStopGroup();
		refreshHeight();
		
	}
	
	clearDropGroup();
}






void makeStopGroupDrop(void){
	u8 i,lineCount;
	struct square *temp;
	u8 lineNum = GameFrame.height/SQUARE_LENGTH;
	lineCount=0;
	for(i=0;i<lineNum;i++){
		u8 loss;
		u8 count=0;
		u16 yMax = GameFrame.yMax - SQUARE_LENGTH*i;
		loss = lineCount*SQUARE_LENGTH;
		temp = HeadSquare.next;
		while(temp->isNULL==0){
			if(temp->yMax == yMax){
				count++;
				temp->yMax+=loss;
			}
			temp=temp->next;
		}
		if(count==0)
			lineCount++;
	}
	
}

u8 checkLine(void){
	struct square *temp;
	u8 i,clearSeek;
	u8 oldStopNum,newStopNum;
	u8 lineNum = GameFrame.height/SQUARE_LENGTH;
	clearSeek = 0;
	oldStopNum = 0;
	newStopNum = 0;
	
	temp = HeadSquare.next;
	while(temp->isNULL==0){
		oldStopNum+=1;
		temp=temp->next;
	}
	
	for(i=0;i<lineNum;i++){
		u8 count = 0;
		u16 yMax = GameFrame.yMax - SQUARE_LENGTH*i;
		temp = HeadSquare.next;
		while(temp->isNULL==0){
			if(temp->yMax == yMax){
				count++;
			}
			temp=temp->next;
		}
		if(count==GameFrame.rowNum){
			clearSeek = 1;
			temp = HeadSquare.next;
			while(temp->isNULL==0){
				struct square *tempNext = temp->next;
				if(temp->yMax == yMax){
					list_remove(&HeadSquare,temp);
					simpleClearSquare(temp);
					free(temp);
				}
				temp = tempNext;
			}
			
		}
	}
	
	temp = HeadSquare.next;
	while(temp->isNULL==0){
		newStopNum+=1;
		temp=temp->next;
	}
	
	score += (oldStopNum-newStopNum)*score_change;
	
	return clearSeek;
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
	
	if(key==KEY0_PRES){
		PressKey = 0;
		return ACTION_RIGHT;
	}
	else if(key==KEY1_PRES){
		PressKey = 0;
		return ACTION_LEFT;
	}
	else if(key==WKUP_PRES){
		PressKey = 0;
		return ACTION_CHANGE;
	}
	else{
		
		return 0;
	}
		
	
}

u8 getRemoteAction1(void){
		u16 key;
		key=Remote_Scan();	
		
		if(key==0){	//未按键时
			
		}
		else{	//按键时
			if(PressKey!=0){//若PressKey不为0
				u16 tempKey = PressKey;
				PressKey = 0;
				return tempKey;
			}
			
			
			else if(key==ACTION_LEFT||key==ACTION_RIGHT||key==ACTION_CHANGE||key==ACTION_STOP||key==ACTION_DOWN||key==ACTION_UP){  //若按键为指定按键，则认为该按键已按下
				PressKey = key;
			}
			else{
				PressKey = 0;
			}
				
		}
		return 0;
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
