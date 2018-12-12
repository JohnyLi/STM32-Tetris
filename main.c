#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "remote.h"


#include "gameFrame.h"
#include "square.h"
#include "game.h"

void initAll(void){
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
  Remote_Init();
	POINT_COLOR=BLACK;
	
	
	init_gameFrame();
}



 int main(void)
 { 
	u16 key;
	u16 mSeconds;
	mSeconds = 0;
	 
	initAll();
	
	
	while(1)
	{
		key = getRemoteAction();//按键
		
		
		
		mSeconds += refreshMs;
		if(mSeconds >= 1000){
			mSeconds = 0;
			gameTime ++;
		}
		
		delay_ms(refreshMs);
		LED0=!LED0;
	}										    
}	
 

