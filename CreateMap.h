//Download by http://www.NewXing.com
#ifndef _CREATEMAP_H_
#define	_CREATEMAP_H_
#pragma once
//===============================================================================
#include   <windows.h>
//===============================================================================
void CreateMap(int w,int h,POINT* pExit);		//������СΪw*h���Թ���ͼ��pExit���س���
//==================================================================================
extern int	g_MazeWidth;						//�Թ���ͼ���
extern int	g_MazeHeight;						//�Թ���ͼ�߶�
#define		MAX_MAZE_WIDTH		100				//�Թ��������
#define		MAX_MAZE_HEIGHT		100				//�Թ������߶�
extern int	g_MazeMap[][MAX_MAZE_HEIGHT+1];		//�����Թ���ͼ����
//===================================================================================
#endif

