#include "stdlib.h"
#include "sys.h"

extern u16 gameTime; //游戏时间

extern u16 refreshMs; //刷新间隔毫秒

extern u8 originSpeed; //原本速度
extern u8 fastSpeed; //加速的速度

extern u16 ACTION_LEFT;
extern u16 ACTION_RIGHT;
extern u16 ACTION_CHANGE;
extern u16 ACTION_STOP;
extern u16 ACTION_DOWN;

u8 getRemoteAction(void);

void updateGame(u16 action);

