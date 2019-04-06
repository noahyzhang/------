//Download by http://www.NewXing.com
#ifndef _THREAD_H_ 
#define _THREAD_H_
#pragma once
//=====================================================================================
#include "Lock.h"
//=====================================================================================
//							һ���߳�ģ����
//���ȣ�����һ��DWORD pWorkFun(void*pParam,CThread*pThread)���͵ĺ�����Ϊ�̵߳����к�����
//�����е���pThread->IsStop()���ж��Ƿ�Ҫ�˳��ú��������棺��Ҫ��pThread�������������ͱ���
//��Σ����������У�����Create������̨�̣߳��������˳�ʱ������Destroy���رպ�̨�̡߳�
//��󣬹���������һ���࣬��Ϊ�˴�������á���Ȼ�����ã�̫���ˣ���Ϊ�Һ���������
//=====================================================================================
class CThread  
{
public:
	void	Create(	DWORD (*pWorkFun)(void*pParam,CThread*),void* lpParam);			//����������ã�������̨�߳�
	void	Destroy();			//����������ã��رպ�̨�̣߳��ͷ���Դ
	CThread();
	virtual ~CThread();
	friend DWORD WINAPI ThreadFun(void* lpParam);	//��̨�����̺߳���
	bool	IsStop();		//�Ƿ�ֹͣ����
private:
	void*		m_Param;
	DWORD		(*m_pWorkFun)(void*pParam,CThread*);
	bool		m_Stop;		//�Ƿ�ֹͣ�߳�
	CLock		m_Lock;		//���ڶ�m_Stop���ʵĻ������
	HANDLE		m_hThread;	//�̵߳ľ��
};
//======================================================================================
#endif