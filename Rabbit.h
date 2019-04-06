//Download by http://www.NewXing.com
#ifndef _RABBIT_H_
#define _RABBIT_H_
#pragma once
//==============================================================================
#include "./Include/AnimCtrl.h"
#include "MazeView.h"
//===============================================================================
class CRabbit  :public CAnimCtrl
{
public:
	virtual	void	New(CBmp24*p,int w,int h,CMazeView*pView);
	virtual	int		Play(void*);
	virtual	void	Draw(CBmp24*p);
private:
	int  bHitLeft();			//�Ƿ�ײ�����
	int  bHitRight();			//�Ƿ�ײ���ұ�
	int  bHitTop();				//�Ƿ�ײ���ϱ�
	int  bHitBottom();			//�Ƿ�ײ���±�
	int  bSucceed();			//�Ƿ��Ѿ�ʤ��
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
private:
	int			m_Direct;//���ӵĵ�ǰ����
	int			m_Wait;	//�����ж������費��Ҫ�ȴ��ļ�����
	int			m_v;	//����ÿ���ƶ���������
	CMazeView*	m_pMazeView;//�����ƶ���ͬʱ����Ҫ������Ұ
public:
	CRabbit();
	virtual ~CRabbit();

};
//=================================================================================
#define RABBIT_VX 			19		//����ͼƬ����ƫ����
#define RABBIT_VY 			35 		//����ͼƬ����ƫ����
#define RABBIT_CX			24		//����ͼƬ��ˮƽ����
#define RABBIT_CY			18		//����ͼƬ��ˮƽ���
//========================================================================================
#endif