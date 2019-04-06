//Download by http://www.NewXing.com
// AnimCtrlEx.cpp: implementation of the CAnimCtrlEx class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AnimCtrlEx.h"

//=============================���ڶ���֡�Ķ���������========================================================
void CAnimCtrlEx::New(CBmp24*pBmp,int x,int y,SAnimFrame *pFrame,int FrameType)
{
	m_pBmp=pBmp;
	m_x=x;
	m_y=y;
	m_Idx=0;
	m_EffectFlag=0;
	m_bHide=0;
	m_FrameType=FrameType;
	m_Count=0;
	m_CurrentFrame=0;
	m_AddFrame=1;
	m_pFrame=pFrame;
	m_bHide=0;
	CAnimCtrl::New();//һ�������ˣ���ӵ�g_AnimList
}
int	 CAnimCtrlEx::Play(void*)
{
	if(m_bHide) return 0;//���ص�ͼƬ��������
	if(m_FrameType==FRAME_STATIC) return 0;//��ֹ��ͼƬ��������
	m_Count++;
	if(m_Count>m_pFrame[m_CurrentFrame].t)//��֡��ʾ�ӳٽ���
	{
		m_Count=0;
		m_CurrentFrame+=m_AddFrame;//�л�����һ֡
	}
	if(m_Count>0xfffd)	m_Count;
	if(m_FrameType==FRAME_PLAY_ONCE && m_pFrame[m_CurrentFrame].t==0xffff)
		return 1;

	return 0;
}
void	CAnimCtrlEx::Draw(CBmp24*p)
{
	int x,y;
	if(m_bHide) return;

	if(m_CurrentFrame<0)
	{
		m_CurrentFrame=1;
		m_AddFrame=1;
	}
	else if(m_pFrame[m_CurrentFrame].t==0xffff)
	{
		switch(m_FrameType)
		{

			case FRAME_PLAY_ONCE:
				m_CurrentFrame-=1;
				break;
			case FRAME_REPEAT:
				m_CurrentFrame=0;
				break;
			case FRAME_GO_BACK:
				m_CurrentFrame-=2;
				m_AddFrame=-1;
				break;
			default:
				m_CurrentFrame=0;
		}
	}
	x=m_x+m_pFrame[m_CurrentFrame].x;
	y=m_y+m_pFrame[m_CurrentFrame].y;
	m_Idx=m_pFrame[m_CurrentFrame].idx;
	m_pBmp->DrawBmp(p,x,y,m_Idx,m_EffectFlag);
}
CAnimCtrlEx::CAnimCtrlEx(){}
CAnimCtrlEx::~CAnimCtrlEx(){}
