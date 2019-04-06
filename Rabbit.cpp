// Download by http://www.NewXing.com
#include "stdafx.h"
#include "Rabbit.h"
#include "./include/Key.h"
#include "CreateMap.h"
#include "AnimDate.h"
extern unsigned int g_I;						//ȫ�ּ�����
int	UpIdx[]={1,2,1,2,4,3,4};//7��
void	CRabbit::New(CBmp24*p,int w,int h,CMazeView*pView)
{
	m_v=5;
	m_Direct=0;
	m_Wait=4;
	m_pMazeView=pView;
	CAnimCtrl::New(p,0,0);
	m_x		=	(w-2)*64+32;	
	m_y		=	(h-2)*64+40;
}
int	CRabbit::Play(void*)
{
	if(IsMultiKey())m_v=4;//б���ߣ��ٶȷ�����С����֤���ٶȲ��
	else{m_v=5;}//��һ������

	if(Key_Up)MoveUp();
	if(Key_Down)MoveDown();
	if(Key_Left) MoveLeft();
	if(Key_Right)MoveRight();

		if(m_Wait>10)
		{
			switch(m_Direct)
			{
			case 0://����
				m_pBmp=&DownWaitBmp;
				SetFlip(0);
				break;
			case 1://����
				m_pBmp=&UpWaitBmp;
				SetFlip(0);
				break;
			case 2://����
				m_pBmp=&LeftWaitBmp;
				SetFlip(1);
				break;
			case 3://����
				m_pBmp=&LeftWaitBmp;
				SetFlip(0);
				break;
			}
			if(g_I%10==0)	SetIdx((g_I/10));
		}
		m_Wait++;
		if(bSucceed()) return 1;

				return 0;
}
int  CRabbit::bHitLeft()				//�Ƿ�ײ�����
{	if(m_x-m_v<0) return 1;
	int i = ( m_x - m_v )/64;
	int j = m_y/64;
	if( g_MazeMap[i][j]  <= 0 )
		return 1;
	j = ( m_y + RABBIT_CY )/64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	return 0;
}
int  CRabbit::bHitRight()				//�Ƿ�ײ���ұ�
{
	int i = ( m_x + m_v +  RABBIT_CX)/64;
	int j = m_y/64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	j = ( m_y +  RABBIT_CY )/64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	return 0;
}
int  CRabbit::bHitTop()				//�Ƿ�ײ���ϱ�
{
	if(m_y-m_v<0 ) return 1;
	int i = m_x /64;
	int j = ( m_y - m_v ) /64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	i = ( m_x +  RABBIT_CX ) /64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	return 0;
}
int  CRabbit::bHitBottom()			//�Ƿ�ײ���±�
{
	int i = m_x /64;
	int j = ( m_y + m_v +  RABBIT_CY ) /64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	i = ( m_x +  RABBIT_CX ) /64;
	if( g_MazeMap[i][j] <= 0 )
		return 1;
	return 0;
}
int  CRabbit::bSucceed()					//�Ƿ��Ѿ�ʤ��
{
		if( m_x < 10	||	m_y < 10 )
		return 1;
		return 0;	
}
void  CRabbit::MoveLeft()
{
	m_pBmp=&LeftRabbitBmp;
	if(!bHitLeft())	
	{
		AddXY(-m_v,0);
		if( (m_pMazeView->GetX() + PM_CX/2 > m_x) && (m_pMazeView->GetX()-m_v > 0) )
		{
			m_pMazeView->AddXY(-m_v,0);
		}	
	}
	SetIdx(g_I);
	SetFlip(0);
	m_Wait=0;
	m_Direct=3;
}
void  CRabbit::MoveRight()
{
	m_pBmp=&LeftRabbitBmp;
	if(!bHitRight())
	{
		AddXY(m_v,0);
	if( ( m_pMazeView->GetX() + PM_CX/2 < m_x) && (m_pMazeView->GetX()+m_v <= m_pMazeView->m_MaxX) )
		{
			m_pMazeView->AddXY(m_v,0);
		}
	}
	SetIdx(g_I);
	SetFlip(1);
	m_Wait=0;
	m_Direct=2;
}
void  CRabbit::MoveUp()
{
	m_pBmp=&UpRabbitBmp;
	if(!bHitTop())
	{
		AddXY(0,-m_v);
	if(( m_pMazeView->GetY() + PM_CY/2 > m_y ) && (m_pMazeView->GetY() - m_v >0 ) )
		{
				m_pMazeView->AddXY(0,-m_v);

		}
	}
	SetIdx(g_I);
	SetFlip(0);
	m_Wait=0;
	m_Direct=1;
}
void  CRabbit::MoveDown()
{
	m_pBmp=&DownRabbitBmp;
	if(!bHitBottom())
	{
		AddXY(0,m_v);
		if(( m_pMazeView->GetY() + PM_CY/2 <m_y ) && (m_pMazeView->GetY()+ m_v <= m_pMazeView->m_MaxY ) )
		{
				m_pMazeView->AddXY(0,m_v);
		}

	}
	SetIdx(g_I);
	SetFlip(0);
	m_Wait=0;
	m_Direct=0;
}
void	CRabbit::Draw(CBmp24*p)
{
	int x =m_x - m_pMazeView->GetX() +PM_X-RABBIT_VX;
	int y = m_y - m_pMazeView->GetY() +PM_Y-RABBIT_VY;
	m_pBmp->DrawBmp(p,x,y,m_Idx,m_EffectFlag);
}
CRabbit::CRabbit(){}
CRabbit::~CRabbit(){}
