#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"

gameFrame GameFrame;
struct square HeadSquare;
struct square DropSquareHead;
struct square NULLSQUARE;
struct heightROW *heightHead;
u16 SQUARE_LENGTH;
u8 dropXmin;
u8 dropXmax;
u16 dropYmax;

void init_gameFrame(void){
	u16 interval_left_and_right = 20;   	//框框与左右两边的距离，左右两边距离相等.
	u16 interval_up = 50;								//框框与上面的距离
	u16 interval_down = 10;							//框框与下面的距离
	u16 width = lcddev.width-interval_left_and_right*2;			//游戏框宽度
	u16 height = lcddev.height - interval_up - interval_down;			 //游戏框高度
	u16 xMin = interval_left_and_right;
	u16 yMin = interval_up;
	u16 xMax = lcddev.width - interval_left_and_right;
	u16 yMax = lcddev.height - interval_down;
	u8 rowNum = 10;			//一行多少个方块
	u16 square_length_of_side = width/rowNum;			//一个方块的边长
	
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
	HeadSquare.isNULL = 0;
	DropSquareHead.isNULL = 0;
	HeadSquare.next = &NULLSQUARE;
	DropSquareHead.next = &NULLSQUARE;
	
	
	nowSpeed = originSpeed;
	NULLSQUARE.isNULL=1;
	initHeightHead();
	
}

//画游戏界面
void draw_gameFrame(void){
	u16 xMin = GameFrame.xMin;
	u16 yMin = GameFrame.yMin;
	u16 xMax = GameFrame.xMax;
	u16 yMax = GameFrame.yMax;
	
	//绘图
	LCD_DrawLine(xMin,yMin,xMin,yMax);//左
	LCD_DrawLine(xMax,yMin,xMax,yMax);//右
	LCD_DrawLine(xMin,yMin,xMax,yMin);//上
	LCD_DrawLine(xMin,yMax,xMax,yMax);//下
	
}

void draw_time(void){
	LCD_ShowString(10,10,40,16,16,"Time");
	LCD_ShowNum(10,30,gameTime,4,16);
}
