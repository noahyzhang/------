//Download by http://www.NewXing.com
#ifndef _BMP24_H_ 
#define _BMP24_H_ 
#pragma once
//===============================================================================================================
//										24λ���ͼ�������˵��
//		24λ���ͼ��ÿ��������3���ֽڣ���ɫֵ˳��Ϊ(b,g,r),��COLORREF�������е���ɫֵ˳��Ϊ(r,g,b).
//����ֵ��ע����ǣ�ͼ������ݴ洢Ϊ���д������ϴ�ģ���������һ��ͼ������λ��Ϊ(x,y),��Ҫת��(x,H-y-1),
//ͼ�񻺴�����ж�Ӧ��λ��Ϊ[(H-y-1)*W+x]*3,���У�WΪͼƬ��ȣ�HΪͼƬ�߶ȡ�
//		����ֻ����24λ���ͼ��ֱ�ӽ������ز������ܵض�ͼ����п��ٸ�Ч�ط�ת��͸����ʾ��,������������ϻ�ͼʱ��
//���Խ������š�
//		CBmp24������Ե���ͼƬ���д���ģ�CMultiBmp�̳���CBmp24������CMultiBmp�����һ��ͼƬ���б��Idxָ������ͼ�����,
//��ͼ�ǰ��ջ��֣������ң����ϵ��µ�˳���Զ���ŵģ����У����Ͻǵı��Ϊ0��
//		�ó�����ʹ����TRACE����win32����Ҫ���#include <afx.h>���ҷ���#include <windows.h>���棬
//Ȼ��project->settings->use MFC in a shared DLL.
//		��������£����Ǹ��������࣬�ٺ�
//																						--���ߣ�Ԭ�÷�
//																						--QQ��276081463
//																						--���ڣ�2008.9.29																			
//================================================================================================================
class CBmp24 
{
public:
					//����λͼ��������͸����ʾ
	virtual bool	LoadBmp(char *fileName);
					//����λͼ��ָ��͸��ɫ����Ҫ����͸����ʾ
	virtual bool	LoadBmp(char *fileName,COLORREF cTransparentColor);
					//����ͼ��ȫ������һ��ͼ�ϣ�pָ����һ��ͼ��(tx,ty)Ϊ����һ��ͼ��ʼ��������꣬Idx���ڴ˴������壬ֻΪ����ͳһ�Ľӿڣ�effectFlagͼƬ��Ч����־���緭ת��
	virtual void	DrawBmp(CBmp24*p,int tx,int ty,int Idx,int effectFlag);
					//����һ���յ�ͼƬ
	void			CreateBmp(long w,long h);
					/*��ȫͼ��ָ���豸������hdc�Ĵ��ڣ�(x,y��w,h)ΪĿ�괰���ϵľ���
					�ú������ܽ���͸����ʾ������С��һ���ǣ���������*/
	void			DrawDC(HDC hdc,int x,int y,int w,int h);
	long			GetWidth(){return m_BmpInf.bmiHeader.biWidth; }//ȡ��ͼƬ��ͼ
	long			GetHeight(){return m_BmpInf.bmiHeader.biHeight;}//ȡ��ͼƬ����
	unsigned char*	GetDateBits(){return (unsigned char*)m_pBits;}//ȡ��ͼƬ���������ݻ�����ָ��
	void			MemsetBits(int i);
protected:			//ԴͼƬ����λ�õķ�ת���㹫ʽ,��(x,y,w,h)���εķ�תʱ��Ӧ������λ�ã�(i��j)Ϊ��Сͼ�еĵ�ǰ����λ��
	int				FlipCount(int type,int x,int y,int w,int h,int j,int i);
					//��ͼ�ľ���ʵ�֣�(tx,ty)Ŀ��ͼ����ʼ���꣬(sx,sy,w,h)Դͼ�ľ��У�effectFlag��ͼ��Ч�����緭ת��
	void			DrawBmpEx(CBmp24*p,int tx,int ty,int sx,int sy,int w,int h,int effectFlag);
					//��ͼ�ľ���ʵ�֣�(tx,ty)Ŀ��ͼ����ʼ���꣬(sx,sy,w,h)Դͼ�ľ��У�effectFlag��ͼ��Ч�����緭ת�ȣ�cTransparentColorָ��͸��ɫ������������Ŀ��ͼ������
	void			DrawBmpEx(CBmp24*p,int tx,int ty,int sx,int sy,int w,int h,int effectFlag,COLORREF cTransparentColor);

protected:
	bool			m_bTrasparented;		//�Ƿ���Ҫ͸����ʾ
	COLORREF		m_TransparentColor;		//͸��ɫ
	BITMAPINFO		m_BmpInf;				//ͼƬ��λͼ��Ϣ
	unsigned char*	m_pBits;				//ͼƬ����������
public:
CBmp24();
virtual ~CBmp24();
};
class CMultiBmp: public CBmp24
{
public:				//����λͼ��������͸����ʾ,ͼƬ�����ֳ�c*r��Сͼ����
	bool			LoadBmp(char *fileName,int c,int r);
					//����λͼ��ͼƬ�����ֳ�c*r��Сͼ������Ҫ͸����ʾ��cTransparentColorָ��͸��ɫ
	bool			LoadBmp(char *fileName,int c,int r,COLORREF cTransparentColor);
					/*�����Idx��Сͼ����pָ������һ��ͼ�ϣ�(tx,ty)Ϊ����һ��ͼ��ʼ��������꣬effectFlagͼƬ��Ч����־���緭ת��
					����ǰ��մ����ң����ϵ��µ�˳���Զ���ŵģ����Ͻǵı��Ϊ0*/
  virtual void		DrawBmp(CBmp24*p,int tx,int ty,int Idx,int effectFlag);
  					/*�����Idx��Сͼ����hdcָ���Ĵ����ϣ�(x,y��w,h)ΪĿ�괰���ϵľ���
					�ú������ܽ���͸����ʾ������С��һ���ǣ���������*/
  void				DrawDC(HDC hdc,int x,int y,int w,int h,int Idx);
private:
	long			m_SubWidth;		//������Сͼ��ÿ��СͼƬ�Ŀ��	
	long			m_SubHeight;	//������Сͼ��ÿ��СͼƬ�ĸ߶�
	int				m_Colum;		//�ж�����Сͼ
	int				m_Row;			//�ж�����Сͼ
public:
CMultiBmp();
virtual ~CMultiBmp();
};
//========================================================================================
#endif