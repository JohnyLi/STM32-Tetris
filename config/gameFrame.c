#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"

gameFrame GameFrame;
nextFrame NextFrame;
struct square HeadSquare;
struct square DropSquareHead;
struct square tempSquareHead;
struct square NULLSQUARE;
struct heightROW *heightHead;
u16 SQUARE_LENGTH;
u8 SIMPLE_SQUARE_LENGTH;
u8 SQUARE_GROUP_NUM;
u8 dropXmin;
u8 dropXmax;
u16 dropYmax;
u16 score;
u8 score_change;

void init_gameFrame(void){
	u16 interval_left_and_right = 20;   	//框框与左右两边的距离，左右两边距离相等.
	u16 interval_up = 90;								//框框与上面的距离
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
	SIMPLE_SQUARE_LENGTH = SQUARE_LENGTH/2;
	HeadSquare.isNULL = 0;
	DropSquareHead.isNULL = 0;
	tempSquareHead.isNULL = 0;
	HeadSquare.next = &NULLSQUARE;
	DropSquareHead.next = &NULLSQUARE;
	tempSquareHead.next = &NULLSQUARE;
	
	
	nowSpeed = originSpeed;
	NULLSQUARE.isNULL=1;
	initHeightHead();
	
	SQUARE_GROUP_NUM = 7;
	score = 0;
	score_change = 10;
}

//画游戏界面
void draw_gameFrame(void){
	
	u16 xMin = GameFrame.xMin;
	u16 yMin = GameFrame.yMin;
	u16 xMax = GameFrame.xMax;
	u16 yMax = GameFrame.yMax;
	POINT_COLOR = BLACK;
	
	//绘图
	LCD_DrawLine(xMin,yMin,xMin,yMax);//左
	LCD_DrawLine(xMax,yMin,xMax,yMax);//右
	LCD_DrawLine(xMin,yMin,xMax,yMin);//上
	LCD_DrawLine(xMin,yMax,xMax,yMax);//下
	
}

void init_nextFrame(void){
	u16 interval_right = 1;   	
	u16 interval_up = 1;								//框框与上面的距离
	u16 width = 50;			
	u16 height = 50;			 
	u16 xMin = lcddev.width-interval_right-width;
	u16 yMin = interval_up;
	u16 xMax = lcddev.width - interval_right;
	u16 yMax = height - interval_up;
	NextFrame.xMin = xMin;
	NextFrame.yMin = yMin;
	NextFrame.yMax = yMax;
	NextFrame.xMax = xMax;
	
}

//画下一方块界面
void draw_nextFrame(void){
	
	u16 xMin = NextFrame.xMin;
	u16 yMin = NextFrame.yMin;
	u16 xMax = NextFrame.xMax;
	u16 yMax = NextFrame.yMax;
	POINT_COLOR = BLACK;
	LCD_Fill(xMin,yMin,xMax,yMax,WHITE);
	//绘图
	LCD_DrawLine(xMin,yMin,xMin,yMax);//左
	LCD_DrawLine(xMax,yMin,xMax,yMax);//右
	LCD_DrawLine(xMin,yMin,xMax,yMin);//上
	LCD_DrawLine(xMin,yMax,xMax,yMax);//下
	LCD_ShowString(xMin+3,yMax+1,50,16,16,"NEXT");
	
}


void draw_score(void){
	POINT_COLOR = BLACK;
	LCD_ShowString(10,50,40,16,16,"Score");
	LCD_ShowNum(10,70,score,4,16);
	
	
}



void draw_time(void){
	POINT_COLOR = BLACK;
	LCD_ShowString(10,10,40,16,16,"Time");
	LCD_ShowNum(10,30,gameTime,4,16);
}
