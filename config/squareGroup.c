#include "gameFrame.h"
#include "lcd.h"
#include "square.h"
#include "game.h"
#include <stdlib.h>

struct simpleSquare sa,sb,sc,sd;
u8 makeNextSeek=0;

void makeColor(void){
	u8 choose;
	choose = rand()%5;
	if(choose==0)
		SQUARE_COLOR = BLACK;
	else if(choose==1)
		SQUARE_COLOR = YELLOW;
	else if(choose==2)
		SQUARE_COLOR = RED;
	else if(choose==3)
		SQUARE_COLOR = BLUE;
	else if(choose==4)
		SQUARE_COLOR = GREEN;
}

void makeSimpleSquareGroup(u8 choose){
	makeColor();
	sa.x = 0;
	sa.y = 0;
	if(choose == 0){
		sb.x = 1;
		sb.y = 0;
		sc.x = 2;
		sc.y = 0;
		sd.x = 3;
		sd.y = 0;
	}
	else if(choose == 1){
		sb.x = 1;
		sb.y = 0;
		sc.x = 1;
		sc.y = 1;
		sd.x = 2;
		sd.y = 0;
		
	}
	else if(choose == 2){
		sb.x = 1;
		sb.y = 0;
		sc.x = 1;
		sc.y = 1;
		sd.x = 1;
		sd.y = 2;
	}
	else if(choose == 3){
		sb.x = 1;
		sb.y = 0;
		sc.x = 1;
		sc.y = 1;
		sd.x = 0;
		sd.y = 1;
	}
	else if(choose == 4){
		sb.x = 1;
		sb.y = 0;
		sc.x = 1;
		sc.y = 1;
		sd.x = 2;
		sd.y = 1;
		
	}
	else if(choose == 5){
		sb.x = 0;
		sb.y = 1;
		sc.x = 1;
		sc.y = 1;
		sd.x = 1;
		sd.y = 2;
		
	}
	else if(choose == 6){
		sb.x=1;
		sb.y=0;
		sc.x=2;
		sc.y=0;
		sd.x=2;
		sd.y=1;
	}
	
	
	
	
	
}


