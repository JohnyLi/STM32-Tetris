#include "stdlib.h"
#include "sys.h"


extern u16 menuTime;
extern u16 gameTime; //游戏时间
extern u8  gameOver;

extern u16 refreshMs; //刷新间隔毫秒

extern u8 originSpeed; //原本速度
extern u8 changeSpeed; //加的速度
extern u8 nowSpeed; //现在的速度

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



