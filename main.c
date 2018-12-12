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
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
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
		key = getRemoteAction();//����
		
		
		
		mSeconds += refreshMs;
		if(mSeconds >= 1000){
			mSeconds = 0;
			gameTime ++;
		}
		
		delay_ms(refreshMs);
		LED0=!LED0;
	}										    
}	
 

