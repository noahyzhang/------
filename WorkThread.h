//Download by http://www.NewXing.com
#ifndef _WORKTHREAD_H_
#define _WORKTHREAD_H_
#pragma once
//====================================================
#include "./Include/Thread.h"
//====================================================================
enum GAME_STATE//��Ϸ״̬						
{												
	PRE_GAME_INIT,			//��Ϸǰ���ʼ��
	CLOUDY_PLAY_INIT,		//����Ч����ʼ��
	CLOUDY_PLAY,			//��������Ч��
	PRE_GAME_PLAY,			//��Ϸǰ��						
	MAZE_GAME_INIT,			//�Թ���Ϸ��ʼ��										
	MAZE_GAME_PLAY			//�Թ���Ϸ				
};
//==================================================================
DWORD	WorkFun(void*,CThread*);
//===================================================================
#endif 
