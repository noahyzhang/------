//Download by http://www.NewXing.com
#ifndef _ANIMCTRLEX_H_ 
#define _ANIMCTRLEX_H_ 
#pragma once
//========================================================================================
#include "AnimCtrl.h"
//================================================================================================
//							���ڶ���֡�Ķ���������
//���ȣ����������õ�ͼƬ���а��ձ�ţ�λ�ã���ʾ�ӳٵȣ��ų�һ������֡���顣
//�ÿ����ཫ���ݶ���֡�����ָ���Ķ����������ͣ����ж������ơ�
//=================================================================================================
enum FRAME_TYPE//����֡�Ĳ�������				
{												
	FRAME_STATIC,		//��ֹ����				
	FRAME_PLAY_ONCE,	//һ���Զ���									//����֡�����ʾ����
	FRAME_REPEAT,		//�ظ��Զ���									//SAnimFrame DemoFrm[]={//һ������ƫ�ƵĶ���֡
	FRAME_GO_BACK		//����ѭ������									//			{0,5,0,2},
};																		//			{2,5,0,2},
struct	SAnimFrame		//����֡�Ľṹ����								//			{3,5,0,2},
{																		//			{4,5,0,2},
	int idx;			//СͼƬ���									//			{5,5,0,2},
	int x;				//ˮƽƫ�ƣ���ʾʱ�����ӵ�����ԭ��ˮƽ������	//			{0xffff,0xffff,0xffff,0xffff}//����֡������־
	int y;				//��ֱƫ�ƣ���ʾʱ�����ӵ�����ԭ�д�ֱ������	//			};
	int t;				//�ӳ�
};
class CAnimCtrlEx: public CAnimCtrl
{
public:	
	virtual	void	New(CBmp24*pBmp,int x,int y,SAnimFrame *pFrame,int FrameType);	//�����µĳ�ʼ����
	virtual	void	Draw(CBmp24*p);	//�Զ��嶯����ʾ������ָ֡����СͼƬ����ʾ����ԭ���������֡��������ӵ�λ��												
	virtual	int		Play(void*);	//�Զ��岥�Ŷ�����ֻ�������л�����֡
	int				GetCurentFrame(){return m_CurrentFrame;}//��ǰ����֡
	bool			bEndFrame(){return (m_pFrame[m_CurrentFrame].t==0xffff); }//�Ƿ��Ƕ�������֡
	void			SetHide(bool bHide)			{	m_bHide=bHide;	}	//�������ض�����
	CAnimCtrlEx();
	virtual ~CAnimCtrlEx();
protected:
	int			m_FrameType;	//����֡������
	int			m_Count;		//��������������ɶ���֡�е��ӳ�
	int			m_CurrentFrame;	//��ǰ����֡
	int			m_AddFrame;		//����֡�ƶ�ʱ��ƫ�ƣ�һ��Ϊ1�������ز������͵Ķ���֡�У�����ʱ��Ϊ��1
	bool		m_bHide;		//�������أ�����֮�󣬲�����ʾ��Ҳ���ᱻ�����Ŵ���
	SAnimFrame*	m_pFrame;
};
//============================================================================================
#endif