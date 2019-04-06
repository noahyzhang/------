//Download by http://www.NewXing.com
#ifndef _MEMDC_H_ 
#define _MEMDC_H_
#pragma once
//================================================================================
#include "Lock.h"
#include "Bmp24.h"
class CMemDC  
{
public:
	void	Init(HWND hWnd);
	HDC		GetDC();
	HDC		Reset();
	void	Wait();
	CBmp24*	GetBmp();
	void	Draw();
	void	Release();
	void	Destroy();

	void	UpdateDC(CBmp24* p);
	void	FadeOut();			//�õ������
	void	FadeIn();			//�õ�����
	void	FadeOutEx();		//����
	void	FadeInEx();			//����

private:
	CLock		m_Lock;
	HWND		m_hWnd;
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBRUSH		m_hBrush;
	HBITMAP		m_hOldBitmap;
	CBmp24		m_ScreenBmp;
	CBmp24		m_TempBmp;
	int			m_bFade;
public:
CMemDC();
virtual ~CMemDC();
};
//==================================================================================
#endif