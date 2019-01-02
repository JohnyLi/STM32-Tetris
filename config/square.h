#include "stdlib.h"
#include "sys.h"	

struct square{
	u8 xMin;
	u16 yMax;
	u8 isNULL;
	u8 isStop;
	struct square *next;
	
};

struct heightROW{
	u8 row;
	u16 yMin;
	struct heightROW *next;
};

struct simpleSquare{
	u8 x;
	u8 y;
};

extern u16 SQUARE_LENGTH;
extern u8 SIMPLE_SQUARE_LENGTH;
extern u8 SQUARE_GROUP_NUM;
extern u16 SQUARE_COLOR;

extern struct square HeadSquare;

extern struct square DropSquareHead;

extern struct square tempSquareHead;

extern struct simpleSquare sa,sb,sc,sd;

extern u8 makeNextSeek; // δ����next����Ϊ0,��������Ϊ1

struct square getHeadSquare(void);

void change_coordinate(struct square * Square,u16 xMin,u16 yMax); //���ķ��������

struct square get_square(u16 xMin,u16 yMax); //���һ���µķ���

struct square *getSquareSeek(u16 xMin,u16 yMax); //���һ���µķ����ָ��

u8 isNULL(struct square * Square);

extern struct square NULLSQUARE;

void drawSquare(struct square * Square); //��һ������

void dropSquare(struct square * Square,u8 speed); //�����½�

void shiftSquareLeft(struct square * Square,u8 speed); //����

void shiftSquareRight(struct square * Square,u8 speed); //����

void simpleClearSquare(struct square * Square); //LCD�������

void setSquareGroup(void);

void list_append(struct square *Head,struct square *Square);

void list_remove(struct square *Head,struct square *Square);

void list_show(struct square *Head);

struct square SquareCopy(struct square *s);

void initHeightHead(void);

void refreshHeight(void);

u8 checkDropSquareCanMoveLeftORRight(void);

u8 getLossDropSquareCanDrop(void);

void makeSimpleSquareGroup(u8 choose);

void drawSimpleSquare(struct simpleSquare * Square);

void rotateSquareGroup(void); //��ת������

u8 checkTwoSquareNear(struct square *s1,struct square *s2);

