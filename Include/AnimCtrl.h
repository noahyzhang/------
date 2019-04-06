//Download by http://www.NewXing.com
#ifndef		_ANIMCTRL_H_ 
#define		_ANIMCTRL_H_ 
#pragma once
//========================================================================================================
#include"Bmp24.h"
#include"ShowList.h"
//=====================================================================================

extern CShowList g_AnimList;
//======================================================================================================
//		������Ķ���������˵��
//���еĶ�������������CAnimCtrl�����е�CAnimCtrl������Ķ��󶼱���ӵ�g_AnimList�У����ͳһ��ʾ
//ͨ������CAnimCtrl�е��麯������ͳһ�ӿڣ�����ɶ������Ƶ��Զ��幦�ܡ�
//======================================================================================================
class CAnimCtrl  
{
public:				
	virtual	void	New()						{	g_AnimList.Add(this);		}//���������¶����New���������룬���øú��������Լ���ӵ�g_AnimList
	virtual	void	New(CBmp24*p,int x,int y);
	virtual	void	New(CBmp24*p,int x,int y,int depth);
	virtual	int		Play(void*)					{	return 0;						}//����������ظú�����ʵ�־���Ķ������ƹ��ܣ�����1ʱ����ʾ�������Ž�����0û����
	virtual	void	Delete()					{	g_AnimList.Remove(this);		}//�������g_AnimList�����
	virtual	void	Draw(CBmp24*p)				{	if(!m_bHide) m_pBmp->DrawBmp(p,m_x,m_y,m_Idx,m_EffectFlag);}//�������ظú������Զ�������Ļ�ϻ滭�����ݣ�g_AnimList��󽫵��øú���
			void	SetIdx(int idx)				{	m_Idx=idx;						}//��ͼ�У���ǰСͼƬ�ı�š��ڵ�ͼ�иñ��������塣
			void	SetXY(int x,int y)			{	m_x=x;	m_y=y;					}//������λ������
			void	SetX(int x)					{	m_x=x;							}//���ö�����ˮƽ����
			void	SetY(int y)					{	m_y=y;							}//���ö����Ĵ�ֱ����
			int		GetX()						{	return	m_x;					}
			int		GetY()						{	return	m_y;					}
			void	AddXY(int x,int y)			{	m_x+=x;	m_y+=y;					}//�ƶ�������λ��
			void	SetFlip(int flipType)		{	m_EffectFlag=flipType;			}//0ԭͼ 1ˮƽ 2��ֱ 3��ȫ����ʱֻ��ʵ����ͼƬ�ķ�תЧ��
			void	SetHide(bool bHide)			{	m_bHide=bHide;	}	//�������ض�����
			int		GetDepth()					{	return m_Depth;}
			void	SetDepth(int depth);	//����ͼƬ��ʾ����ȣ���Χ��0-9,0Ϊ�����棬9Ϊ������
protected:
			int		m_x,m_y;		//����������
			int		m_Idx;			//��ͼ�У���ǰСͼƬ�ı�š��ڵ�ͼ�иñ��������塣
			int		m_EffectFlag;	//ͼƬ��ʾ��Ч������ʱֻ�з�תЧ������ȡֵΪ��0ԭͼ 1ˮƽ 2��ֱ 3��ȫ��ת
			bool	m_bHide;		//�������أ�����֮�󣬲�����ʾ��Ҳ���ᱻ�����Ŵ���
			int		m_Depth;
			CBmp24*	m_pBmp;			//�������õ���ͼƬ
public:
	CAnimCtrl();
	virtual ~CAnimCtrl();
};
//============================================================================================
#endif