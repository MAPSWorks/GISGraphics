// MyLine1.cpp: implementation of the CMyLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGExe.h"
#include "MyLine1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyLine::CMyLine()
{
	crColor=RGB(255,0,0);
	nPenStyle=PS_DASH;
	nWidth=1;
	pt1=CPoint(300,100);
	pt2=CPoint(500,400);
	testStr="�人��ѧ";

	pts.Add(CPoint(600,100));
	pts.Add(CPoint(500,300));
	pts.Add(CPoint(560,400));
	pts.Add(CPoint(800,300));
	pts.Add(CPoint(600,200));
	pts.Add(CPoint(700,150));
	pts.Add(CPoint(600,100));

}

CMyLine::~CMyLine()
{

}

void CMyLine::setWidth(int nWidth)
{
	nWidth=4;
}

void CMyLine::setPenStyle(int nPenStyle1)
{
	nPenStyle=nPenStyle1;
}

void CMyLine::setPoints(CPoint pta, CPoint ptb)
{
	
}

void CMyLine::setColor(int nColor)
{
	nColor=RGB(0,0,255);
}

void CMyLine::Draw(CDC *pDC)
{
	//����һ��CPen������������ֱ�߶�
	CPen pen(nPenStyle,nWidth,crColor);

	//��PDCѡ�øö�����Ϊ��ͼ�ʣ�ͬʱ��ԭ��Ĭ�ϵĻ�ͼ�ʱ�����oldPen��
	CPen *oldPen=pDC->SelectObject(&pen);

	//�����߶�
	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);

	//�ָ���ͼ��
	pDC->SelectObject(oldPen);

	//��������
	CFont font;
	//�������塢�ִ���С
	font.CreateFont(20,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"����");
	//����ѡ�����壬������ԭ��������Ϣ��pFont
	CFont *pFont=pDC->SelectObject(&font);

	//��������
	pDC->TextOut(400,200,testStr);

	//�ָ�������Ϣ
	pDC->SelectObject(pFont);

	int size=pts.GetSize();
	for(int i=0;i<size;i++)
	{
		if(i==0)
			pDC->MoveTo(pts[i]);
		else
			pDC->LineTo(pts[i]);
	}
/*	FillPolygon(pDC,CPoint(600,120),RGB(255,0,0));*/
}


void CMyLine::FillPolygon(CDC *pDC, CPoint pt, int Color)
{
	HDC hdc;
	if (GetPixel(hdc,pt.x,pt.y) != crColor&&GetPixel(hdc,pt.x,pt.y) != Color)
	{
		SetPixel(hdc,pt.x,pt.y,Color);
	FillPolygon(pDC,(pt.x+1,pt.y),Color);
	FillPolygon(pDC,(pt.x-1,pt.y), Color);
	FillPolygon(pDC,(pt.x,pt.y+1), Color);
	FillPolygon(pDC,(pt.x,pt.y-1), Color);	
	FillPolygon(pDC,(pt.x+1,pt.y-1), Color);
	FillPolygon(pDC,(pt.x-1,pt.y-1), Color);
	FillPolygon(pDC,(pt.x+1,pt.y+1), Color);
	FillPolygon(pDC,(pt.x-1,pt.y+1), Color);
	}
}

