#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"


 //更改方块的坐标
void change_coordinate(square * Square,u16 xMin,u16 yMax){
	Square->xMin = xMin;
	Square->xMax = xMin+SQUARE_LENGTH;
	Square->yMin = yMax-SQUARE_LENGTH;
	Square->yMax = yMax;
}

//获得一个新的方块
square get_square(u16 xMin,u16 yMax){
	square Square;
	Square.xMin = xMin;
	Square.xMax = xMin+SQUARE_LENGTH;
	Square.yMin = yMax-SQUARE_LENGTH;
	Square.yMax = yMax;
	Square.isHead = 0;
	Square.isStop = 0;
	return Square;
	
}

void drawSquare(square * Square){ //画一个方块
	
	
}

