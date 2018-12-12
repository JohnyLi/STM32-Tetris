#include "gameFrame.h"
#include "square.h"
#include "game.h"

#include "lcd.h"
#include "remote.h"

u8 PressKey=0;

u16 ACTION_LEFT = 34;
u16 ACTION_RIGHT = 194;
u16 ACTION_CHANGE = 2;
u16 ACTION_STOP = 162;
u16 ACTION_DOWN = 168;

u8 originSpeed = 1;
u8 fastSpeed = 3;
u16 gameTime = 0;
u16 refreshMs = 50;

void drawStopThing(void){
	draw_gameFrame();
	draw_time();
	
	
	
}



void updateGame(u16 action){
	drawStopThing();
	
	
	
	
	
	
	
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
			if(key==ACTION_LEFT||key==ACTION_RIGHT||key==ACTION_CHANGE||key==ACTION_STOP||key==ACTION_DOWN){  //若按键为指定按键，则认为该按键已按下
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
