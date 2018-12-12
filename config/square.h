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

void change_coordinate(square * Square,u16 xMin,u16 yMax); //���ķ��������

square get_square(u16 xMin,u16 yMax); //���һ���µķ���

void drawSquare(square * Square); //��һ������

