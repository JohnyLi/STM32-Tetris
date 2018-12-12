#include "stdlib.h"
#include "sys.h"	

typedef struct  
{										    
	u16 width;			//游戏框宽度
	u16 height;			 //游戏框高度
	u16 xMin;
	u16 yMin;
	u16 xMax;
	u16 yMax;
	u8 rowNum;			//一行多少个方块
	u16 interval_left_and_right;   	//框框与左右两边的距离，左右两边距离相等.
	u16 interval_up;								//框框与上面的距离
	u16 interval_down;							//框框与下面的距离
	u16 square_length_of_side;			//一个方块的边长
	
}gameFrame;

extern gameFrame GameFrame;

void init_gameFrame(void); //初始化游戏界面参数和方块边长

void draw_gameFrame(void); //画游戏界面

void draw_time(void); //时间
