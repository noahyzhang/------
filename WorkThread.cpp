// WorkThread.cpp: implementation of the CWorkThread class.
// Download by http://www.NewXing.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorkThread.h"
#include "WinGame.h"
#include "./include/Key.h"
#include "Rabbit.h"
#include "./Include/AnimCtrl.h"
#include "AnimDate.h"
#include "PreRabbit.h"
#include "CreateMap.h"
#include "./Include/Thread.h"
//======================================================================================
CAnimCtrl		BkAnim1,BkAnim2;			//����ͼƬ����
CAnimCtrl		foregroundAnim;				//ǰ��ͼƬ����
CAnimCtrlEx		LeftExit,RightExit;			//��Ϸǰ���ϵ����ҳ��ڱ�־		
CAnimCtrlEx		Cloudy;		//��������Ч��
CPreRabbit		PreRabbit;	//��Ϸǰ���е�����
CRabbit			MyRabbit;		//���ӿ���
CMazeView		MazeView;		//�Թ���Ұ����
unsigned int	g_I=0;			//ȫ�ּ�����
//==================================================================================

DWORD	WorkFun(void*,CThread*p)
{
	CBmp24* pBmp;
	int	m_State=PRE_GAME_INIT;
	LoadAnimDate();
	Sleep(30);
	ClearAllKey();
	while(!p->IsStop())
	{

		ReadKey();
		switch(m_State)
		{
			case PRE_GAME_INIT://��Ϸǰ���ʼ��
				g_AnimList.ClearAllAnim();
				PreRabbit.New(&DownWaitBmp,288,230);
				PreRabbit.SetHide(1);
				PreRabbit.SetDepth(1);//����ͼƬ����ʾ�����
				BkAnim1.New(&BkBmp,0,100);
				BkAnim2.New(&BkBmp,320,100);
				BkAnim2.SetFlip(1);
				LeftExit.New(&LeftExitBmp,-5,240,g_LeftExitFrm,FRAME_REPEAT);
				RightExit.New(&LeftExitBmp,590,240,g_LeftExitFrm,FRAME_REPEAT);
				Cloudy.New(&CloudyBmp,0,0,g_CloudyFrm,FRAME_PLAY_ONCE);
				Cloudy.SetHide(1);
				RightExit.SetFlip(1);

				g_MemDC.FadeOut();
				m_State=CLOUDY_PLAY_INIT;
			break;
			case CLOUDY_PLAY_INIT://����Ч����ʼ��
				Cloudy.SetHide(0);
				m_State=CLOUDY_PLAY;
				break;
			case CLOUDY_PLAY://��������Ч��֮����ʾ����
				if(Cloudy.Play(0))
				{
					Cloudy.Delete();
					PreRabbit.SetHide(0);
					m_State=PRE_GAME_PLAY;
				}

				break;
			case PRE_GAME_PLAY://��Ϸǰ��
				LeftExit.Play(0);
				RightExit.Play(0);
				if(PreRabbit.Play(0))
				{
					m_State=MAZE_GAME_INIT;
					g_MemDC.FadeIn();
				}
			break;
			case MAZE_GAME_INIT://�Թ���Ϸ��ʼ��
				g_AnimList.ClearAllAnim();
				MazeView.New(g_MazeWidth,g_MazeHeight);//��Ұ���ﴴ�����Թ������Թ����ڵ�
				MyRabbit.New(&DownWaitBmp,g_MazeWidth,g_MazeHeight,&MazeView);//�Լ����Ƶ�����
				foregroundAnim.New(&foregroundBmp,0,0);//���ڵ�ͼ�ϵĿ�ͼ
				g_MemDC.FadeOut();
				m_State=MAZE_GAME_PLAY;
			break;
			case MAZE_GAME_PLAY://�����������Թ�
				MazeView.Play(0);//��ʵ����Ұ�ڲ����Թ����ڵĶ���
				if(MyRabbit.Play(0))//�����������Թ�
				{
					m_State=PRE_GAME_INIT;
					g_MemDC.FadeIn();
				}
			break;
		}
		//===========ˢ�»���====================================================
		pBmp=g_MemDC.GetBmp();
		g_AnimList.ShowAllAnim(pBmp);//�����еĶ���ͼƬ���Ȼ���g_MemDC��m_ScreenBmp
		g_MemDC.Draw();//����m_hMemDC
		//=============ȫ�ּ�����==================================================
		g_I++;
		if(g_I>0xfffe) g_I=0;
	}
	return 0;
}