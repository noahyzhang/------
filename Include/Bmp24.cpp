//Download by http://www.NewXing.com
// Bmp24.cpp: implementation of the CBmp24 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bmp24.h"
#include <stdio.h>
#include <wingdi.h>
#include<malloc.h>
//===================================================================================================================
void CBmp24::CreateBmp(long w,long h)
{
	//�ǲ����Ѿ��ù��ˣ��Ȱ�ԭ�ȵ��ڴ��ͷ���
	if(m_pBits!=NULL)		{free(m_pBits);			m_pBits=NULL;}
	m_BmpInf.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BmpInf.bmiHeader.biWidth = w;
	m_BmpInf.bmiHeader.biHeight = h;
	m_BmpInf.bmiHeader.biPlanes = 1;
	m_BmpInf.bmiHeader.biBitCount = 24;
	m_BmpInf.bmiHeader.biCompression = BI_RGB;
	m_BmpInf.bmiHeader.biSizeImage = w*h*3;
	m_BmpInf.bmiHeader.biXPelsPerMeter = 0;
	m_BmpInf.bmiHeader.biYPelsPerMeter = 0;
	m_BmpInf.bmiHeader.biClrUsed = 0;
	m_BmpInf.bmiHeader.biClrImportant = 0;
	m_pBits=(unsigned char*)malloc(w*h*3);
	memset(m_pBits,0,w*h*3);//�´�����ͼƬ��ȫĨ��
}
//===================================================================================================================
bool CBmp24::LoadBmp(char *fileName)
{
	FILE *fp;
	BITMAPFILEHEADER bmpFileHeader;
	unsigned long count=0;
	//�ǲ����Ѿ��ù��ˣ��Ȱ�ԭ�ȵ��ڴ��ͷ���
	if(m_pBits!=NULL)		{free(m_pBits);			m_pBits=NULL;}
	//��ͼ���ļ�
	if( (fp = fopen( fileName, "rb")) == NULL ) 
	{
		TRACE("�޷����ļ�: %s\n", fileName );
		return false;
	}
	//��ȡͼ���ļ�ͷ
 	if ((count=fread(&bmpFileHeader, 1, sizeof(bmpFileHeader), fp)) != sizeof(bmpFileHeader))
	{
		TRACE( "ERR004 ��ȡ BMP �ļ�ͷʧ��: count=%d\n", count);
				return false;
	}
	//�������ͼ���ļ�������Ҳ��ûϷ��
	if(bmpFileHeader.bfType!='MB')
	{
		TRACE("����BMP�ļ�\n");
		return false;
	}
	//��ȡͼ����Ϣͷ,��m_BmpInf.bmiHeader��������m_BmpInf���٣�
 	if ((count=fread(&m_BmpInf.bmiHeader, 1, sizeof(BITMAPINFOHEADER), fp)) != sizeof(BITMAPINFOHEADER))
	{
		TRACE( "ERR004 ��ȡ BMP ��Ϣʧ��: count=%d\n", count);
				return false;
	}
	//�������24���λͼ�����滹��ûϷ
	if(m_BmpInf.bmiHeader.biBitCount!=24)
	{
		TRACE("����24λBMP�ļ�\n");
		return false;
	}
	//Ϊ�˰�ȫ��������¼���ͼ�����ݳ��ȣ���Ϊ�е�ͼ��biSizeImageΪ��
	m_BmpInf.bmiHeader.biSizeImage=m_BmpInf.bmiHeader.biWidth*m_BmpInf.bmiHeader.biHeight*3;


	m_pBits=(unsigned char*)malloc(m_BmpInf.bmiHeader.biSizeImage);
	if(!m_pBits)//��Ȼû���뵽�ڴ棬�������ˣ����أ�
	{
		TRACE("ERROR CBmp24::LoadBmp malloc\n");
		return false;
	}
	
	//��ȡͼ�����������
 	if ((count=fread(m_pBits, 1, m_BmpInf.bmiHeader.biSizeImage, fp)) != m_BmpInf.bmiHeader.biSizeImage)
	{
		TRACE( "ERR004 ��ȡ BMP �ļ�����ʧ��: count=%d\n", count);
		return false;
	}
	fclose(fp);//�����ˣ�������ļ���лл��
	return true;//���ڳɹ��ˣ��٣�
}
//===================================================================================================================
bool	CBmp24::LoadBmp(char *fileName,COLORREF cTransparentColor)
{
	m_bTrasparented=1;		//�Ƿ���Ҫ͸����ʾ
	m_TransparentColor=cTransparentColor;		//͸��ɫ
	return LoadBmp(fileName);
}
//===================================================================================================================
//��ȫͼ��hdcָ��Ĵ�����ʾ��(x,y,w,h)Ϊ�����ϵľ���
void CBmp24::DrawDC(HDC hdc,int x,int y,int w,int h)
{
	StretchDIBits(hdc,x,y,w,h,0,0,m_BmpInf.bmiHeader.biWidth,m_BmpInf.bmiHeader.biHeight,m_pBits,&m_BmpInf,DIB_RGB_COLORS,SRCCOPY);
}
//===================================================================================================================
void CBmp24::DrawBmp(CBmp24*p,int tx,int ty,int Idx,int effectFlag)
{
	if(!m_bTrasparented)	DrawBmpEx(p,tx,ty,0,0,m_BmpInf.bmiHeader.biWidth,m_BmpInf.bmiHeader.biHeight,effectFlag);
	else	DrawBmpEx(p,tx,ty,0,0,m_BmpInf.bmiHeader.biWidth,m_BmpInf.bmiHeader.biHeight,effectFlag,m_TransparentColor);	
}
//==============================================================================================
//����:	CBmp24* p		ָ��Ŀ��ͼ
//		int tx			��Ŀ��ͼ�Ͽ�ʼ��ͼ��ˮƽ����
//		int ty			��Ŀ��ͼ�Ͽ�ʼ��ͼ�Ĵ�ֱ����
//		int	sx			��ͼ���軭ͼ��ˮƽ��ʼ����
//		int sy			��ͼ���軭ͼ�Ĵ�ֱ��ʼ����
//		int w			��ͼ���軭ͼ��ˮƽ����
//		int h			��ͼ���軭ͼ�Ĵ�ֱ�߶�
//		int	flipType	��ͼ�ķ�ת��־,0����ת��1ˮƽ��ת��2��ֱ��ת��3��ȫ��ת
//===============================================================================================
//���ܣ�����ͼ�ϵ�(sx,sy,w,h)���Σ�����pָ���Ŀ��ͼ�ϣ���Ŀ��ͼ��������(tx,ty)��ʼ����
//		ͬʱ��flipTypeָ���˻�ͼʱ�ķ�ת������
//===============================================================================================
void	CBmp24::DrawBmpEx(CBmp24*p,int tx,int ty,int sx,int sy,int w,int h,int flipType)
{
	int i,j,t,s,cx=w,cy=h;
	long w1=p->GetWidth();
	long h1=p->GetHeight();
	long w0=m_BmpInf.bmiHeader.biWidth;
	long h0=m_BmpInf.bmiHeader.biHeight;
	unsigned char* pBits1=p->GetDateBits();
	unsigned char* pBits0=this->GetDateBits();
	if(tx+cx>=w1)	cx=w1-tx;//�ȼ�����Ƿ񳬽�
	if(ty+cy>=h1)	cy=h1-ty;
	if(tx<0)	{sx-=tx;cx=cx+tx;tx=0;}
	if(ty<0)	{sy-=ty;cy=cy+ty;ty=0;}
	for(j=0;j<cy;j++)
		for(i=0;i<cx;i++)
		{	
			t=((h1-ty-j-1)*w1+tx+i)*3;
			s=FlipCount(flipType,sx,sy,cx,cy,j,i);
			pBits1[t+0]=pBits0[s+0];
			pBits1[t+1]=pBits0[s+1];
			pBits1[t+2]=pBits0[s+2];
		}
}
//==============================================================================================
//������ĺ���Ψһ�����𣬾���cTransparentColorָ����͸��ɫ���ᱻ��
void	CBmp24::DrawBmpEx(CBmp24*p,int tx,int ty,int sx,int sy,int w,int h,int flipType,COLORREF cTransparentColor)
{
	int i,j,t,s,cx=w,cy=h;
	long w1=p->GetWidth();
	long h1=p->GetHeight();
	long w0=m_BmpInf.bmiHeader.biWidth;
	long h0=m_BmpInf.bmiHeader.biHeight;
	unsigned char* pBits1=p->GetDateBits();
	unsigned char* pBits0=this->GetDateBits();
	unsigned char *pTrasparentColor=(unsigned char *)&cTransparentColor;
	if(tx+cx>=w1)	cx=w1-tx;
	if(ty+cy>=h1)	cy=h1-ty;
	if(tx<0)	{sx-=tx;cx=cx+tx;tx=0;}
	if(ty<0)	{sy-=ty;cy=cy+ty;ty=0;}
	for(j=0;j<cy;j++)
		for(i=0;i<cx;i++)
		{
			t=((h1-ty-j-1)*w1+tx+i)*3;
			s=FlipCount(flipType,sx,sy,cx,cy,j,i);
			if(pTrasparentColor[2]!=pBits0[s+0]|| pTrasparentColor[1]!=pBits0[s+1]|| pTrasparentColor[0]!=pBits0[s+2])
			{
				pBits1[t+0]=pBits0[s+0];
				pBits1[t+1]=pBits0[s+1];
				pBits1[t+2]=pBits0[s+2];
			}
		}
}
//==============================================================================================
//����:	type			��ͼ�ķ�ת��־,0����ת��1ˮƽ��ת��2��ֱ��ת��3��ȫ��ת
//		x				��ͼ���軭ͼ��ˮƽ��ʼ����
//		y				��ͼ���軭ͼ�Ĵ�ֱ��ʼ����
//		w				��ͼ���軭ͼ��ˮƽ����
//		h				��ͼ���軭ͼ�Ĵ�ֱ�߶�
//		i				�ڱ�ͼ���軭ͼ�ľ��������е�ˮƽ���꣨���С���εģ�
//		j				�ڱ�ͼ���軭ͼ�ľ��������еĴ�ֱ���꣨���С���εģ�
//==============================================================================================
//���ܣ�ָ�����Σ�x,y,w,h���е����꣨i,j����������Ҫ��ת�ı�־������õ��ڱ�ͼ���ػ������е�λ�á�
//===============================================================================================
int		CBmp24::FlipCount(int type,int x,int y,int w,int h,int j,int i)
{
	int W=m_BmpInf.bmiHeader.biWidth;
	int H=m_BmpInf.bmiHeader.biHeight;
	if(type==0)//����ת
	{
		y=y+j;
		x=x+i;
	}
	else if(type==1)//ˮƽ��ת
	{
		y=y+j;
		x=x+w-i-1;
	}
	else if(type==2)//��ֱ��ת
	{
		y=y+h-j-1;
		x=x+i;
	}
	else if(type==3) //��ȫ��ת
	{
		y=y+h-j-1;
		x=x+w-i-1;
	}
	return ((H-y-1)*W+x)*3;
}
//===================================================================================================================
void	CBmp24::MemsetBits(int i)
{
	memset(m_pBits,i,m_BmpInf.bmiHeader.biSizeImage);
}
//===================================================================================================================
CBmp24::CBmp24()
{
	memset(&m_BmpInf,0,sizeof(m_BmpInf));
	m_pBits=NULL;
}
//===================================================================================================================
CBmp24::~CBmp24()
{
	if(m_pBits!=NULL)
	{
		free(m_pBits);
		m_pBits=NULL;
	}
}
//=====================��ͼ����ľ���ʵ��=====================================================
bool	CMultiBmp::LoadBmp(char *fileName,int colum,int row)
{
	bool r;
	m_Colum=colum;				//�ж�����Сͼ
	m_Row=row;					//�ж�����Сͼ
	m_bTrasparented=0;
	r=CBmp24::LoadBmp(fileName);
	m_SubWidth	=	m_BmpInf.bmiHeader.biWidth/m_Colum;
	m_SubHeight	=	m_BmpInf.bmiHeader.biHeight/m_Row;
	return r; 
}
//===================================================================================================================
bool	CMultiBmp::LoadBmp(char *fileName,int colum,int row,COLORREF cTransparentColor)
{
	bool r;
	m_Colum=colum;				//�ж�����Сͼ
	m_Row=row;					//�ж�����Сͼ
	m_bTrasparented=1;
	m_TransparentColor=cTransparentColor;
	r=CBmp24::LoadBmp(fileName);
	m_SubWidth	=	m_BmpInf.bmiHeader.biWidth/m_Colum;
	m_SubHeight	=	m_BmpInf.bmiHeader.biHeight/m_Row;
	return r; 
}
//===================================================================================================================
void	CMultiBmp::DrawBmp(CBmp24*p,int tx,int ty,int Idx,int effectFlag)
{
	Idx=Idx%(m_Row*m_Colum);
	int c=Idx%m_Colum;
	int r=Idx/m_Colum;
	int w=m_SubWidth;
	int h=m_SubHeight;
	if(!m_pBits) return;
	if(!m_bTrasparented)	DrawBmpEx(p,tx,ty,c*w,r*h,w,h,effectFlag);
	else	DrawBmpEx(p,tx,ty,c*w,r*h,w,h,effectFlag,m_TransparentColor);
}
//===================================================================================================================
 void	CMultiBmp::DrawDC(HDC hdc,int x,int y,int w,int h,int Idx)
 {
	int c=Idx%m_Colum;
	int r=m_Row-Idx/m_Colum-1;//bmpͼ���ǰ��մ������Ϸŵ�
	StretchDIBits(hdc,x,y,w,h,c*m_SubWidth,r*m_SubHeight,m_SubWidth,m_SubHeight,m_pBits,&m_BmpInf,DIB_RGB_COLORS,SRCCOPY);
 }
//===================================================================================================================
CMultiBmp::CMultiBmp()
{
	memset(&m_BmpInf,0,sizeof(m_BmpInf));
	m_pBits=NULL;
}
//===================================================================================================================
CMultiBmp::~CMultiBmp()
{
	if(m_pBits!=NULL)
	{
		free(m_pBits);
		m_pBits=NULL;
	}
}
//===================================================================================================================
