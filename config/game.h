#include "stdlib.h"
#include "sys.h"


extern u16 menuTime;
extern u16 gameTime; //��Ϸʱ��
extern u8  gameOver;

extern u16 refreshMs; //ˢ�¼������

extern u8 originSpeed; //ԭ���ٶ�
extern u8 changeSpeed; //�ӵ��ٶ�
extern u8 nowSpeed; //���ڵ��ٶ�

extern u16 ACTION_LEFT;
extern u16 ACTION_RIGHT;
extern u16 ACTION_CHANGE;
extern u16 ACTION_STOP;
extern u16 ACTION_DOWN;
extern u16 ACTION_UP;

extern u8 dropXmin;
extern u8 dropXmax;
extern u16 dropYmax;
extern u16 dropYmax;

extern struct heightROW *heightHead;


u8 getRemoteAction(void);

u8 getKeyAction(void);

void updateGame(void);

void makeAction(u8 action);

void makeDrop(void);

void drawDropGroup(void);

void clearDropGroup(void);

void checkNeedStop(void);

void drawStopGroup(void);

void refreshDropAttr(void);



