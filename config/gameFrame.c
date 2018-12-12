#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"

gameFrame GameFrame;
square HeadSquare;
u16 SQUARE_LENGTH;

void init_gameFrame(void){
	u16 interval_left_and_right = 20;   	//������������ߵľ��룬�������߾������.
	u16 interval_up = 50;								//���������ľ���
	u16 interval_down = 10;							//���������ľ���
	u16 width = lcddev.width-interval_left_and_right*2;			//��Ϸ�����
	u16 height = lcddev.height - interval_up - interval_down;			 //��Ϸ��߶�
	u16 xMin = interval_left_and_right;
	u16 yMin = interval_up;
	u16 xMax = lcddev.width - interval_left_and_right;
	u16 yMax = lcddev.height - interval_down;
	u8 rowNum = 20;			//һ�ж��ٸ�����
	u16 square_length_of_side = width/rowNum;			//һ������ı߳�
	
	GameFrame.interval_up = interval_up;
	GameFrame.interval_down = interval_down;
	GameFrame.width = width;
	GameFrame.height = height;
	GameFrame.xMin = xMin;
	GameFrame.yMin = yMin;
	GameFrame.xMax = xMax;
	GameFrame.yMax = yMax;
	GameFrame.rowNum = rowNum;
	GameFrame.square_length_of_side = square_length_of_side;
	
	
	SQUARE_LENGTH = square_length_of_side;
	HeadSquare.isHead = 1;
	HeadSquare.isStop = 1;
	
}

//����Ϸ����
void draw_gameFrame(void){
	u16 xMin = GameFrame.xMin;
	u16 yMin = GameFrame.yMin;
	u16 xMax = GameFrame.xMax;
	u16 yMax = GameFrame.yMax;
	
	//��ͼ
	LCD_DrawLine(xMin,yMin,xMin,yMax);//��
	LCD_DrawLine(xMax,yMin,xMax,yMax);//��
	LCD_DrawLine(xMin,yMin,xMax,yMin);//��
	LCD_DrawLine(xMin,yMax,xMax,yMax);//��
	
}

void draw_time(void){
	LCD_ShowString(10,10,40,16,16,"Time");
	LCD_ShowNum(10,30,gameTime,4,16);
}