//Download by http://www.NewXing.com
// AnimCtrl.cpp: implementation of the CAnimCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AnimCtrl.h"
#include <list>
//=======================================================================================
// ����������ľ���ʵ��
//=======================================================================================
CShowList g_AnimList;//������ж���������
//=========================================================================================
void	CAnimCtrl::New(CBmp24*p,int x,int y)
{
	m_pBmp=p;
	m_x=x;
	m_y=y;
	m_Idx=0;
	m_EffectFlag=0;
	m_Depth=0;//Ĭ��Ϊ��
	New();//һ�������ˣ���ӵ�g_AnimList
}
void CAnimCtrl::New(CBmp24*p,int x,int y,int depth)
{
	m_pBmp=p;
	m_x=x;
	m_y=y;
	m_Idx=0;
	m_EffectFlag=0;
	m_Depth=depth;
	New();//һ�������ˣ���ӵ�g_AnimList
}
void	CAnimCtrl::SetDepth(int depth)
{
	g_AnimList.Remove(this);
	m_Depth=depth;
	g_AnimList.Add(this);
}
//======================================================================================
CAnimCtrl::CAnimCtrl()
{
	m_x=m_y=0;
	m_Idx=0;
	m_EffectFlag=0;
	m_pBmp=0;
	m_Depth=0;
}
CAnimCtrl::~CAnimCtrl(){}
