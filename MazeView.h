//Download by http://www.NewXing.com
#ifndef _MAZEVIEW_H_
#define _MAZEVIEW_H_
#pragma once
//==========================================================================================
#include "./Include/AnimCtrl.h"
#include "./Include/AnimCtrlEx.h"
//======================================================================================
class CMazeView  :public CAnimCtrl
{
public:
	virtual	void	New(int w,int h);
	virtual	int		Play(void*);
	virtual	void	Draw(CBmp24*p);	
	int		m_MaxX;	//��Ұ���Թ���ͼ�ϵ����ˮƽ���꣨���أ�
	int		m_MaxY;	//��Ұ���Թ���ͼ�ϵ��ֱƽ���꣨���أ�
	CMazeView();
	virtual ~CMazeView();
private:
	void MarkMap();	//��ǵ�ͼ������������ĵ�ͼ���б�ǣ��Ա���ʾ����
	int  GetMarkCode(int i,int j);//ȡ�õ�ͼ��i��j�����ı����
private:
	CAnimCtrlEx		m_ExitCtrl;//������ʾ���ڶ���
	POINT			m_Exit;		//�������꣨����λ�ã�
};
//======================================================================================
//PM����Ļ�����Թ���ʾ����
#define PM_I 				9		//��Ļˮƽ��ͼƬ����
#define PM_J 				7 		//��Ļ��ֱ��ͼƬ����
#define PM_X				63		//��Ļ����ʾ���ϵ�ˮƽ����
#define PM_Y				63		//��Ļ����ʾ���ϵĴ�ֱ����
#define PM_CX				64*8	//�Թ���ʾ����ˮƽ����
#define PM_CY				64*6	//�Թ���ʾ����ֱ�߶�
//==================================================================================
#endif 