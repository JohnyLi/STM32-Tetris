#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "remote.h"
#include "key.h"

#include "gameFrame.h"
#include "game.h"
#include "square.h"

u16 mSeconds = 0;

void initAll(void){
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
  Remote_Init();
	KEY_Init();
	POINT_COLOR=BLACK;
	
	
	
}

void showMenu(void){
	LCD_ShowString(lcddev.width/2-40,lcddev.height/2-50,80,24,24,"Tetris");
	LCD_ShowString(lcddev.width/2-100,lcddev.height/2,200,16,16,"Press KEY1 to Start Game");
	while(1){
		u16 key;
		key=KEY_Scan(0);
		
		if(key==KEY1_PRES)
			break;
		
		delay_ms(refreshMs);
		LED0=!LED0;
		menuTime += refreshMs;
		
	}
	
	LCD_Clear(WHITE);
}


void doGame(void){
	
	srand(menuTime);
	init_gameFrame();
	draw_gameFrame();
	
	while(1)
	{
		
		updateGame();
		if(gameOver==1)
			break;
		mSeconds += refreshMs;
		if(mSeconds >= 1000){
			mSeconds = 0;
			gameTime ++;
				
		}
		
		delay_ms(refreshMs);
		LED0=!LED0;
		
	}			
	
	
}

void showResult(void){
	u16 xMin,yMin,xMax,yMax;
	u8 width,height;
	width = 150;
	height = 80;
	xMin = lcddev.width/2 - width/2;
	xMax = lcddev.width/2 + width/2;
	yMin = lcddev.height/2 - height/2;
	yMax = lcddev.height/2 + height/2;
	printf("%d,%d,%d,%d",xMin,yMin,xMax,yMax);
	
	LCD_Fill(xMin,yMin,xMax,yMax,WHITE);
	LCD_DrawLine(xMin,yMin,xMax,yMin); //上
	LCD_DrawLine(xMin,yMax,xMax,yMax); //下
	LCD_DrawLine(xMin,yMin,xMin,yMax); //左
	LCD_DrawLine(xMax,yMin,xMax,yMax); //右
	
	LCD_ShowString(xMin+width/2-40,yMin+10,80,16,16,"GAME OVER");
	LCD_ShowString(xMin+10,yMin+50,80,12,12,"Your score is:");
	LCD_ShowNum(xMax-30,yMin+50,gameTime,4,12);
	
}



 int main(void)
 { 

	
	initAll();
	showMenu();
	
	
	doGame();
	showResult();
	
}	
 

