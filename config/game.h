#include "stdlib.h"
#include "sys.h"

extern u16 gameTime; //��Ϸʱ��

extern u16 refreshMs; //ˢ�¼������

extern u8 originSpeed; //ԭ���ٶ�
extern u8 fastSpeed; //���ٵ��ٶ�

extern u16 ACTION_LEFT;
extern u16 ACTION_RIGHT;
extern u16 ACTION_CHANGE;
extern u16 ACTION_STOP;
extern u16 ACTION_DOWN;

u8 getRemoteAction(void);

void updateGame(u16 action);

