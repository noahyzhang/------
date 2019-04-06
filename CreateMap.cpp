// Download by http://www.NewXing.com
#include"stdafx.h"
#include"CreateMap.h"
#include<stdlib.h>  
#include<time.h>  
//====================================================================================
int		g_MazeWidth;		//�Թ���ͼ���
int		g_MazeHeight;		//�Թ���ͼ�߶�
int		g_MazeMap[MAX_MAZE_WIDTH+1][MAX_MAZE_HEIGHT+1]={0};	//�Թ���ͼ����
//=======================�Թ���ͼ���������ģ��==========================================================
typedef struct 
{
	int tag;   						//���������ǵ�����
	int x,y;						//�������е�λ��g_MazeMap[x][y];
	int vx,vy;  					//x,y���ƶ�����
	int step;   					//��һ�������������ڵ�ͼ�ĳ���
	int maxX;						//x�����ֵ
	int maxY;						//y�����ֵ
}SDigMap;
//====================================================================
void ClearMap(int w,int h)//����ʾ�Թ���ͼ����������
{
	g_MazeWidth=w;
	g_MazeHeight=h;
	int i,j;
	for(i=0;i<=w;i++)
		for(j=0;j<=h;j++)
		{
			g_MazeMap[i][j]=0;
		}
		srand(time(0));
}
//=====================================================================================
void DigIt(SDigMap *p)//���ô��ڵ���������
{
	g_MazeMap[	p->x  ][ p->y  ] = p->tag;
}
//=====================================================================================
void Walk(SDigMap *p)//�ڵ�ͼ������ǰ��
{
	    p->x	+=	p->vx;
    	p->y	+=	p->vy; 
}
//=====================================================================================
int  IsNextDigged(int x,int y,int vx,int vy,SDigMap *p)//�ж���һ�������Ƿ񱻸��ö����ڵ�
{
	if( g_MazeMap[	x + vx  ][ y + vy ]	==	p->tag ) return 1;
	else 	return 0;
}
//==========================================================================================
void HitWall(SDigMap *p)//�ڵ�ͼ��������ײǽ������
{
	    if( p->x + p->vx < 1 || p->x + p->vx > p->maxX) 
			p->vx = -p->vx;
    	if( p->y + p->vy < 1 || p->y + p->vy > p->maxY)  
    		p->vy = -p->vy;
}
//======================================================================================
int  CanNextBeDigged(SDigMap *p)//�����һ�����Ƿ������
{
	   int x = p->x + p->vx;
	   int y = p->y + p->vy;             //��һ�������
       int vx = p->vy;					//��ԭ����ת��ķ���
       int vy = p->vx;
	   //�жϵ�ǰ�����һ����������ڵ��Ƿ��Լ��ڹ�,������Լ��ڹ�����һ�㲻�����ˣ�������Լ���ͨ��
       if( IsNextDigged( x, y, p->vx, p->vy, p ) ) return 0;//ǰһ���Ƿ��� 
       if( IsNextDigged( x, y, vx, vy, p ) ) return 0;//��һ���Ƿ��� 
       if( IsNextDigged( x, y, -vx, -vy, p ) )	return 0;//��һ���Ƿ���  
       return 1;		//��Χ��û����,�������Ա���
}
//====================================================================================
void Jump(SDigMap *p)//������һ�㣬������һ�����Χ��������
{
    	int vx=p->vy;
    	int vy=p->vx;	//��ԭ����ת�����������
 	    Walk(p);		//���ߵ���һ����
        if( IsNextDigged( p->x, p->y, p->vx, p->vy, p ) )  //ǰһ�㱻��,�߹�ȥ
        {
        	Walk(p);   
        }
        else if(IsNextDigged( p->x, p->y, vx, vy, p ))  //��һ�㱻��,�߹�ȥ
        {
           	p->x += vx;    
        	p->y += vy;   
        }
        else if(IsNextDigged( p->x, p->y, -vx, -vy, p))  //��һ�㱻��,�߹�ȥ
        {
           	p->x -= vx;
        	p->y -= vy;  
        }
}
//=====================================================================================
int  IsLinked(SDigMap *p)//����Ƿ���ͨ
{
       	int vx=p->vy;
       	int vy=p->vx;//��ԭ����ת�����������
       	//����ĵ�������ڵ㣬�Ȳ����������ֲ���0����õ㱻���SDigMap�ڹ�,���Ѿ���ͨ��
    	if( g_MazeMap[ p->x+vy ][ p->y+vx ] != p->tag && g_MazeMap[ p->x+vy ][p->y+vx ] !=0 )  return 1;  //ǰһ�����Ƿ񱻱����
    	if( g_MazeMap[ p->x+vx ][ p->y+vy ] != p->tag && g_MazeMap[ p->x+vx ][ p->y+vy ] != 0 ) return 1; //��һ�����Ƿ񱻱����	 
    	if( g_MazeMap[ p->x-vx ][ p->y-vy ] != p->tag && g_MazeMap[ p->x-vx ][ p->y-vy ] != 0 ) return 1;//��һ�����Ƿ񱻱����
    	return 0; 
}
//=====================================================================================
void RandomVxy(SDigMap *p)//�����������
{
	    int vx=p->vy;
    	int vy=p->vx;
		int k=rand()%50;
    	//�������3���ռ䣬ԭ����ؽ��ı�
    	if( 0<=k && k<10 )// ������ĸ���Ϊ����ת��ĸ���һ��
    	{    p->vx = -vx;
    		p->vy = -vy;
    	} 
    	if( 10<=k && k<30 )//����
    	{
     		p->vx = -vy;
    		p->vy = -vx;
    	} 
    	if( 30<=k && k<50 )//����    
    	{
    		p->vx = vy;
    		p->vy = vx;
    	}
}
//=====================================================================================
int  ContinuouslyDig( SDigMap *p )//������
{
    	int i=0; 
    	RandomVxy( p );//����һ���������
 		p->step =1+rand()%2;//��������ڸ÷������ڵ���������
    	while( i<p->step )
    	{
			 HitWall( p );  //���ȼ���Ƿ�ײǽ�����ײǽ����ȡ��
			 //������һ������ֲ���:1�߹� 2�߹�ȥ�ڵ� 3����ȥ
			if(IsNextDigged(p->x,p->y,p->vx,p->vy,p))//�����һ���Ƿ��Լ��ڹ�
				Walk(p);//�Ѿ����ڣ��߹�ȥ
			 else if( CanNextBeDigged( p ) )//û�б��ڣ��Ƿ������
				{
					Walk( p );//�����ڣ��߹�ȥ��
        			DigIt( p );//�ڵ�
        			if( IsLinked( p ) ) return 1;//�����ͨ������ѭ����������	
				}
			 else Jump( p );//�������ڣ�����ȥ	
			i++;
    	}
    	 return 0;
}
//=====================================================================================
int bSeed(int x,int y)//�Ƿ������Ϊ����
{	//�ĵ���ĸ��ڵ㶼û���ڣ�����ԴӸõ㿪ʼ�ڵ�ͼ
	if( g_MazeMap[x][y] != 0 )		return 0;
	if( g_MazeMap[x-1][y] != 0 )	return 0;
	if( g_MazeMap[x][y-1] != 0 )	return 0;
	if( g_MazeMap[x+1][y] != 0 )	return 0;
	if( g_MazeMap[x][y+1] != 0 )	return 0;
	return 1;
}
//=====================================================================================
void ImproveMap(int w,int h)//�����Թ�
{
	int		i,j;
	int 	tag=3;
	int		bLink=0;       //�жϵ�ͼ�Ƿ���ͨ
	//SDigMap:	tag	x	y	vx	vy	step	maxX	maxY
	SDigMap m={ 3,	1,	1,	1,	0,	1,		w-2,	h-2};//���Ϊ1�������꣨1��1����ʼ��
	for( i=1; i<w-1; i++ )
		for( j=1; j<h-1; j++ )
		{
             if(bSeed( i, j )==1)
			 {
				m.tag=tag;
				m.x=i;
				m.y=j;
				tag++;
				DigIt(&m);
				bLink=0;
				while( !bLink )
                     bLink=ContinuouslyDig( &m );
			 }
		}
}
//=====================================================================================
void RandomExit(SDigMap *p,int w,int h,POINT* pExit)//pExit�����Թ�����
{	//�����漴���ڣ��������λ�ÿ�Ϊ���Ͻǣ����½ǣ����Ͻ�
	int k=rand()%60;
	if( 0<=k && k<30 )//���������Ͻ�,�������
	{
		p->x=1;
		p->y=1;
		pExit->x=0;
		pExit->y=1;		
	}
	else if( 30<=k && k<45 )//���½�
	{
		p->x=1;
		p->y=h-2;
		pExit->x=0;
		pExit->y=h-2;		
	}
	else if( 45<=k && k<60 )//���Ͻ�
	{
		p->x=w-2;
		p->y=1;
		pExit->x=w-2;
		pExit->y=0;
	}
	g_MazeMap[pExit->x][pExit->y]=1;//�Ƚ��Թ������ڵ�
}
//========================================================================================
void CreateMap(int w,int h,POINT* pExit)//�����Թ���ͼ,��ͼ��СΪw*h,pExit���س�������
{
	//SDigMap:		tag		x		y		vx		vy		step	maxX		maxY
	SDigMap m1={ 	1,		1,		1,		1,		0,		1,		w-2,		h-2};//���Ϊ1�������꣨1��1����ʼ��
	SDigMap m2={ 	2,		w-2,	h-2,	-1,		0,		1,		w-2,		h-2};//���Ϊ2�������꣨N��N����ʼ��
	int		bLink=0;       //�жϵ�ͼ�Ƿ���ͨ
	ClearMap(w,h);//���ȣ�ȫ������			
	RandomExit(&m1,w,h,pExit);//��������������
	DigIt( &m1 );  	//��ʼ�����ڵ�    
	DigIt( &m2 );//���������½�
	while( !bLink )//������ͬʱ�ڣ����ڳ��ӿ�ʼ�������ڵ�ͨ·
	{  
		bLink	=	ContinuouslyDig( &m1 );//����ڿ�ʼ����ͼ�������������������������Ƿ���ͨ
		if(!bLink)	bLink=ContinuouslyDig( &m2 );//���Թ������ʼ����ͼ����
	}
	ImproveMap(w,h);//�Ľ���ͼ������Ƭû���ڵĵط������ڳ�һЩͨ�����õ�ͼ��������,�ٺ�!
}
