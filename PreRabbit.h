//Download by http://www.NewXing.com
#ifndef _PRERABBIT_H_
#define _PRERABBIT_H_
#pragma once
//=================================================================================
#include "INCLUDE\AnimCtrl.h"
//=================================================================================
class CPreRabbit : public CAnimCtrl  
{
public:
	virtual	void	New(CBmp24*p,int x,int y);
	virtual	int		Play(void*);
	CPreRabbit();
	virtual ~CPreRabbit();
private:
	int			m_Direct;//���ӵĵ�ǰ����
	int			m_Wait;	//�����ж������費��Ҫ�ȴ��ļ�����
	int			m_v;	//����ÿ���ƶ���������
};
//================================================================================
#endif 