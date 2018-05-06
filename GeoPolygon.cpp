// GeoPolygon.cpp: implementation of the CGeoPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGExe.h"
#include "GeoPolygon.h"
#include  "afxtempl.h"
#include "math.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGeoPolygon::CGeoPolygon() 
{

}

CGeoPolygon::~CGeoPolygon()
{

}

void CGeoPolygon::Draw(CDC *pDC,CMapProject *mapPrj)	
{
	int size = pts.GetSize();               //���Ƶ�ͼ
	float L,B;
	for(int i=0;i<size;i++)
	{
		CPoint pt1,pt2;
		float X,Y;
		pt1 = (CPoint)pts.GetAt(i);
		L=pt1.x/1000000.0;
		B=pt1.y/1000000.0;   //scale=1000000
		mapPrj->getXY(L,B,&X,&Y);
		pt2.x=X;
		pt2.y=Y;
		prjPts.Add(pt2);
	}
	pDC->Polygon(prjPts.GetData(),size);

	/*CPoint pt;                                 //�������ĵ�
	double x0,y0,x1,y1;
	int r=20000;
	pt = getCenterPt();
	x0=pt.x/1000000.0;
	y0=pt.y/1000000.0;
	mapPrj->getXY(x0,y0,&x1,&y1);
	pt.x=x1;
	pt.y=y1;
	pDC->Ellipse(pt.x-r,pt.y-r,pt.x+r,pt.y+r);

	CPoint pt;                                 
	double x0,y0,x1,y1;
	pt = getCenterPt();
	x0=pt.x/1000000.0;
	y0=pt.y/1000000.0;
	mapPrj->getXY(x0,y0,&x1,&y1);*/

	CPoint pt;
	float x0,y0,x1,y1;
	pt = (CPoint)ctPts.GetAt(0);
	x0=pt.x/1000000.0;
	y0=pt.y/1000000.0;
	mapPrj->getXY(x0,y0,&x1,&y1);
/*	int r=20000;
	pt.x=x1;
	pt.y=y1;
	pDC->Ellipse(pt.x-r,pt.y-r,pt.x+r,pt.y+r);*/
	CBrush brush(size*100);         //��ͼ���
	CBrush* oldBrush=(CBrush*)pDC->SelectObject(&brush);
	pDC->FloodFill(x1,y1,RGB(0,0,0));
	pDC->SelectObject(oldBrush);
}

void CGeoPolygon::addPts(CPoint pt)
{
	pts.Add(pt);
}

CPoint CGeoPolygon::getCenterPt()
{
	int index=0;
	int size=pts.GetSize();
	int i;
	CPoint p0,p1,p2,q,pt;
	p0=(CPoint)pts.GetAt(0);
	for(i=1;i<size;i++)           //Ѱ��һ��͹���㣬ʵ������͵�϶���͹����
	{
		CPoint tmp=pts.GetAt(i);
		if(tmp.y<p0.y)
		{
			p0=tmp;
			index=i;
		}
	}
	p1=pts.GetAt((index-1+size)%size); //�õ�p0��ǰһ������
	p2=pts.GetAt((index+1+size)%size); //�õ�p0�ĺ�һ������
	
	bool bin=false;
	double md=INFINITE;
	for(i=0;i<size;i++)                //Ѱ����������p0p1p2�����붥��p0����Ķ���q
	{
		if(i==index)continue;
		if(i==(index-1+size)%size)continue;
		if(i==(index+1+size)%size)continue;
		if(!InsideConvexPolygon(p1,p0,p2,pts[i]))continue;
		bin=true;
		if(dist(p0,pts[i])<md)
		{
			q=pts.GetAt(i);
			md=dist(p0,q);
		}
	}
	if(!bin)                        //û�ж�����������p0p1p2�ڣ������߶�p1p2�е�
	{
		pt.x=(p1.x+p2.x)/2;
		pt.y=(p1.y+p2.y)/2;
		return pt;
	}
	pt.x=(p0.x+q.x)/2;               //����p0q�е�
	pt.y=(p0.y+q.y)/2;
	return pt;
}

bool CGeoPolygon::InsideConvexPolygon(CPoint p1, CPoint p0, CPoint p2, CPoint q)
{
	if(crossProduct(p1,p0,q)>0&&crossProduct(p0,p2,q)>0&&crossProduct(p2,p1,q)>0||crossProduct(p1,p0,q)<0&&crossProduct(p0,p2,q)<0&&crossProduct(p2,p1,q)<0)//��q�ڶ������
	return true;
}

float CGeoPolygon::crossProduct(CPoint pt1, CPoint pt2,CPoint pt)
{
	return((pt1.x-pt.x)*(pt2.y-pt.y)-(pt2.x-pt.x)*(pt1.y-pt.y));
}

float CGeoPolygon::dist(CPoint pt1, CPoint pt2)
{
	return(sqrt((pt1.x-pt2.x)^2+(pt1.y-pt2.y)^2));
}

void CGeoPolygon::addCtPts(CPoint pt)
{
	ctPts.Add(pt);
}
