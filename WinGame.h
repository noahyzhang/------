//Download by http://www.NewXing.com
#ifndef _WINGAME_H_ 
#define  _WINGAME_H_
#pragma once
//=====================================================================================
#include "resource.h"
#include "./include/MemDC.h"
#include "./Include/Bmp24.h"

//======================================================================================
extern unsigned int g_I;						//ȫ�ּ�����
extern HWND	g_hWnd;
extern CMemDC			g_MemDC;
//=======================================================================================
BOOL MyRegisterClass(HINSTANCE hInstance);//ע�ᴰ����
BOOL InitInstance(HINSTANCE,int);//��������
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//������Ϣ����ص�����
void OnPaint(HWND hWnd);//���ƴ���
void OnCreate(HWND hWnd);//���ڸմ���ʱ�ģ�������ʼ���ĺ���
void OnDesdroy();//�˳�ʱ�ģ����ٺ��������ͷ��ڴ���ƺ���
#endif