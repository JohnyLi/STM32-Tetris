#include "stdlib.h"
#include "sys.h"	


typedef struct  
{										    
	u16 xMin;
	u16 yMin;
	u16 xMax;
	u16 yMax;
	u8 isHead;
	u8 isStop;
	struct square *next;
}square;


extern u16 SQUARE_LENGTH;

extern square HeadSquare;

void change_coordinate(square * Square,u16 xMin,u16 yMax); //更改方块的坐标

square get_square(u16 xMin,u16 yMax); //获得一个新的方块

void drawSquare(square * Square); //画一个方块

