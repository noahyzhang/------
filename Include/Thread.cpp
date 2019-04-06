//Download by http://www.NewXing.com
#include "stdafx.h"
#include "Thread.h"
//===================================================================================
CThread::CThread()
{
	m_Stop = false;
	m_pWorkFun=0;
	m_Param=0;
	m_hThread=0;
}
CThread::~CThread(){}

//==================================================================================
void	CThread::Create(DWORD (*pWorkFun)(void* lpParam,CThread*),void* lpParam)			//����������ã�������̨�߳�
{
	DWORD dwThreadId;
	m_pWorkFun=pWorkFun;
	m_Param=lpParam;
	m_hThread = CreateThread( 
			NULL,			// default security attributes 
			0,				// use default stack size  
			ThreadFun,		// thread function 
			this,			// argument to thread function 
			0,				// use default creation flags 
			&dwThreadId);	// returns the thread identifier 
}

//==================================================================================
bool	CThread::IsStop()
{
	bool stop ;
	m_Lock.Lock();
	stop = m_Stop;
	m_Lock.UnLock();
	return stop;
}
//==================================================================================
void	CThread::Destroy()
{
	m_Lock.Lock();
	m_Stop = true;//�رպ�̨�߳�
	m_Lock.UnLock();

    WaitForSingleObject(m_hThread, 2000);//�ȴ���̨�߳�ȷʵ�Ѿ��ر�
	CloseHandle(m_hThread);
}
//=================================================================================
DWORD WINAPI ThreadFun(void* lpParam)
{
	CThread *p=(CThread*)lpParam;
	if(p->m_pWorkFun)
	return p->m_pWorkFun(p->m_Param,p);
	return 0;
}
//==================================================================================