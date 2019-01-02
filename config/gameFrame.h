#include "stdlib.h"
#include "sys.h"	

typedef struct  
{										    
	u16 width;			//��Ϸ����
	u16 height;			 //��Ϸ��߶�
	u16 xMin;
	u16 yMin;
	u16 xMax;
	u16 yMax;
	u8 rowNum;			//һ�ж��ٸ�����
	u16 interval_left_and_right;   	//������������ߵľ��룬�������߾������.
	u16 interval_up;								//���������ľ���
	u16 interval_down;							//���������ľ���
	u16 square_length_of_side;			//һ������ı߳�
	
}gameFrame;

typedef struct
{
	u8 width;			
	u8 height;			 
	u16 xMin;
	u16 yMin;
	u16 xMax;
	u16 yMax;
}nextFrame; //��ʾ��һ��������Ľ���

extern gameFrame GameFrame;

void init_gameFrame(void); //��ʼ����Ϸ��������ͷ���߳�

void draw_gameFrame(void); //����Ϸ����

void init_nextFrame(void); 

void draw_time(void); //ʱ��

void draw_score(void);

void draw_nextFrame(void);

extern nextFrame NextFrame;
