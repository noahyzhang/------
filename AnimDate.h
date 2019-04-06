//Download by http://www.NewXing.com
#ifndef _ANIMDATE_H__
#define _ANIMDATE_H__
#pragma once
//==================================================================================
#include"./include/Bmp24.h"
#include"./include/AnimCtrlEx.h"
//===============================================================================
void LoadAnimDate();//�������е�ͼƬ
//==============================================================================
extern CBmp24			BkBmp;				//����ͼƬ
extern CBmp24			foregroundBmp;		//ǰ��ͼƬ
extern CMultiBmp		LeftRabbitBmp;		//�����ߵ�����
extern CMultiBmp		DownRabbitBmp;		//�����ߵ�����
extern CMultiBmp		UpRabbitBmp;		//�����ߵ�����
extern CMultiBmp		LeftWaitBmp;		//����ȴ�������
extern CMultiBmp		DownWaitBmp;		//���µȴ�������
extern CMultiBmp		UpWaitBmp;			//���ϵȴ�������
extern CMultiBmp		LeftExitBmp;		//����ĳ���
extern CMultiBmp		UpExitBmp;			//���ϵĳ���
extern CMultiBmp		CloudyBmp;			//������������Ч����ͼƬ
extern CBmp24			MazeWall[5];		//����ƴ���Թ���5��ͼƬ
//=================================================================================
extern SAnimFrame		g_LeftExitFrm[];	//������Թ����ڶ���֡
extern SAnimFrame		g_UpExitFrm[];		//���ϵ��Թ����ڶ���֡
extern SAnimFrame		g_CloudyFrm[];		//����Ч������֡
//==================================================================================
#endif