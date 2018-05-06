// CGExeView.cpp : implementation of the CCGExeView class
//

#include "stdafx.h"
#include "CGExe.h"

#include "CGExeDoc.h"
#include "CGExeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGExeView

IMPLEMENT_DYNCREATE(CCGExeView, CView)

BEGIN_MESSAGE_MAP(CCGExeView, CView)
	//{{AFX_MSG_MAP(CCGExeView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGExeView construction/destruction

CCGExeView::CCGExeView()
{
	// TODO: add construction code here
	this->isPressed=FALSE;
	this->isCityLoaded=FALSE;
	map = NULL;

}

CCGExeView::~CCGExeView()
{
}

BOOL CCGExeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGExeView drawing

void CCGExeView::OnDraw(CDC* pDC)
{
	CCGExeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	/*ddaLine.setPoint(100,100,500,400);
	ddaLine.Draw(pDC);
	myLine.Draw(pDC);

	if(this->isCityLoaded)
		chnCity.Draw(pDC);

	bezier.clearAllPoints();
	bezier.addPoint_Ct(CPoint(100,100));
	bezier.addPoint_Ct(CPoint(300,250));
	bezier.addPoint_Ct(CPoint(200,400));
	bezier.addPoint_Ct(CPoint(400,500));
	bezier.Draw(pDC);*/

	convexHull.Draw(pDC);

/*	if(map!=NULL)
	{
		map->Draw(pDC);
		mapPrj->Draw(pDC);
	}*/


}

/////////////////////////////////////////////////////////////////////////////
// CCGExeView printing

BOOL CCGExeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGExeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGExeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGExeView diagnostics

#ifdef _DEBUG
void CCGExeView::AssertValid() const
{
	CView::AssertValid();
}

void CCGExeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGExeDoc* CCGExeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGExeDoc)));
	return (CCGExeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGExeView message handlers

void CCGExeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
/*	this->isPressed=TRUE;                     //������걻����״̬��־
	pt1=point;                                //��㡢�յ�ָ��ͬһ��point������갴�µ�
	pt2=point;*/
	
	CView::OnLButtonDown(nFlags, point);
}

void CCGExeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	/*this->isPressed=FALSE;                    //������갴��Ϊ����Ӧ״̬
	//this->Invalidate();                     //ÿ�������Ļ��������ʱͼ��

	CClientDC dc(this);                       //��ȡ��ǰ����ͼ������Ļ��ƶ���
	
	CBrush *brush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); 
	CBrush *oldBrush=dc.SelectObject(brush);  //ѡ��ÿձ�ˢ����������ǰ��ˢ��oldBrush

	CPen pen(PS_DOT,1,RGB(255,0,0));          //��ɫ���߱�
	CPen *oldPen=dc.SelectObject(&pen);       //ѡ��ú�ɫ���߱ʣ���������ǰ�ʵ�oldPen

	pt2=point;                                //�µ㸳ֵ
	dc.Rectangle(pt1.x,pt1.y,pt2.x,pt2.y);    //������ͼ��

	dc.SelectObject(oldBrush);                //�ָ���ˢ
	dc.SelectObject(oldPen);                  //�ָ���ǰ����*/
	
	
	/*pt2=point;
	OnPrepareDC(&dc);                         //����OnPrepareDC��ʵ�ֶ�dc��ͬ������ӳ��
	dc.DPtoLP(&pt1);                          //�������豸�����pt1��ת��Ϊ��������
	dc.DPtoLP(&pt2);                          //�������豸�����point��ת��Ϊ��������
	int minx=min(pt1.x,pt2.x);
	int miny=min(pt1.y,pt2.y);
	int maxx=max(pt1.x,pt2.x);
	int maxy=max(pt1.y,pt2.y);                //��ȡ�µľ�������

	CRect rect(minx,miny,maxx,maxy);
	this->wcRect=rect;
	Invalidate();*/

	CView::OnLButtonUp(nFlags, point);
}

void CCGExeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!this->isPressed)                      //������û�б����£�ƽ�Ʋ����κ����飬ֱ�ӷ���
		return;

    CClientDC dc(this);                       //��ȡ��ǰ����ͼ������Ļ��ƶ���
	dc.SetROP2(R2_NOT);                       //���û�ͼģʽΪȡ����ɫΪ�෴ɫ
	/*
	dc.MoveTo(pt1);                           //�ƶ�����һ��
	dc.LineTo(pt2);                           //�����ϵ�����

	pt2=point;                                //�յ����Ϊ��ǰ��point
	dc.MoveTo(pt1);                           //�ƶ�����һ��
	dc.LineTo(pt2);                           //���Ƶ��ڶ���
	*/

	//�����Ĭ��Ϊ��䣬������Ҫ����һ���ձ�ˢ��ʹ�û���ֻ���Ǳ߽�
	CBrush *brush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	CBrush *oldBrush=dc.SelectObject(brush);  //ѡ��ÿձ�ˢ����������ǰ�ı�ˢ��oldBrush

	CPen pen(PS_DASHDOT,1,RGB(255,0,0));      //��ɫ���߱�
	CPen *oldPen=dc.SelectObject(&pen);       //ѡ��ú�ɫ���߱ʣ���������ǰ�ʵ�oldPen

	dc.Rectangle(pt1.x,pt1.y,pt2.x,pt2.y);    //�����ϵ�ͼ��
	pt2=point;                                //�µ㸳ֵ
	dc.Rectangle(pt1.x,pt1.y,pt2.x,pt2.y);    //������ͼ��

	dc.SelectObject(oldBrush);                //�ָ���ˢ
	dc.SelectObject(oldPen);                  //�ָ���ǰ����

	CView::OnMouseMove(nFlags, point);
}

void CCGExeView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	//�ռ�����
	/*CFileDialog fDlg(true); //������ļ��Ի���
	if(fDlg.DoModal()==IDOK) //���ļ�����ѡ���ļ�ok��
	{
		CString fileName=fDlg.GetPathName();  //��ȡ�ļ�����
		FILE *fp=fopen(fileName,"r"); //�����ļ�ָ�룬���򿪶�Ӧ�ļ�
		if(fp==NULL) //����ļ���ʧ�ܣ���ʾ��Ϣ
		{
			MessageBox("�ļ���ʧ��!");
			return;
		}
		int id;
		float lon,lat;
		CString name;
		float minl,minb,maxl,maxb;  //���ݷ�Χ
		int scale=1000000;   //����һ�����ߣ�ʹ�䱣֤ԭʼ���ݾ��ȣ�ͬʱ�������int��Ҫ
		minl=minb=180*scale;  //��γ�����ֵ
		maxl=maxb=-180*scale;   //��γ����Сֵ

		if(map!=NULL) return;
		map=new CGeoMap();//�����µĵ�ͼ����
		CGeoLayer *layer=new CGeoLayer();//������ͼ��
		CSpatialObject *object=NULL;//������Ҫ��

		while(!feof(fp)) //�ļ�û�н���
		{
			CSpatialObject *object=new CSpatialObject();//�����տռ�Ҫ��
			fscanf(fp,"%d%f%f%s",&id,&lon,&lat,name); //��ȡ����
			lon=lon*scale;
			lat=lat*scale;
			minl=minl>lon?lon:minl;    //��ȡ��С��Ӿ���
			minb=minb>lat?lat:minb;
			maxl=maxl<lon?lon:maxl;
			maxb=maxb<lat?lat:maxb;
			
			object->Id=id;
			object->lon=lon;
			object->lat=lat;
			object->name=name;
			layer->addObject(object);
		}
		map->addLayer(layer);
		fclose(fp);    //�ļ��ر�
		map->wcRect=CRect(minl,minb,maxl,maxb);//���������귶Χ
	}	
	Invalidate();  //ǿ������Ļ�ػ�*/

	//��ͼ���
	/*CFileDialog fDlg(true); //������ļ��Ի���
	if(fDlg.DoModal() == IDOK) //���ļ�����ѡ���ļ�ok��
	{
		CString fileName=fDlg.GetPathName();  //��ȡ�ļ�����
		FILE *fp=fopen(fileName,"r"); //�����ļ�ָ�룬���򿪶�Ӧ�ļ�
		if(fp==NULL) //����ļ���ʧ�ܣ���ʾ��Ϣ
		{
			MessageBox("�ļ���ʧ��!");
			return;
		}
		
		int flag1,flag2;
		float lon,lat;
		int size;
		float minb,minl,maxb,maxl;  //���ݷ�Χ
		float minx,miny,maxx,maxy;
		int scale=1000000;   //����һ�����ߣ�ʹ�䱣֤ԭʼ���ݾ��ȣ�ͬʱ�������int��Ҫ
		char *str1,*str2,*str3;
		str1=(char *)malloc(100*sizeof(char));
		str2=(char *)malloc(10*sizeof(char));
		minl=minb=180*scale;  //��γ�����ֵ
		maxl=maxb=-180*scale;   //��γ����Сֵ
		
		if(map!=NULL) return;
		map=new CGeoMap();//�����µĵ�ͼ����		
		CGeoLayer *layer=new CGeoLayer();//������ͼ��
		CGeoPolygon *poly=NULL;//������Ҫ��
		
		while(!feof(fp)) //�ļ�û�н���
		{
			fscanf(fp,"%s",str1);
			str2="1";
			flag1=strcmp(str1,str2);
			if(flag1==0)
			{
				poly=new CGeoPolygon();
				fscanf(fp,"%d",&size);
				for(int i=0;i<size;i++)
				{
					CPoint myPoint;
					fscanf(fp,"%f%f",&lon,&lat); //��ȡ����
					lat=lat*scale;				
					lon=lon*scale;
					minb=minb>lat?lat:minb;    //��ȡ��С��Ӿ���
					minl=minl>lon?lon:minl;
					maxb=maxb<lat?lat:maxb;
					maxl=maxl<lon?lon:maxl;
					myPoint.x=lon;
					myPoint.y=lat;
					poly->addPts(myPoint);   //������뵽������
				}
				layer->addPolygon(poly);

				do                           //��ȡ���ĵ�  
				{
					fscanf(fp,"%s",str1);
					str3="Center";
					flag2=strcmp(str1,str3);
				}while(flag2!=0);
				CPoint ctPt;
				fscanf(fp,"%f%f",&lon,&lat);
				ctPt.x=lon*scale;
				ctPt.y=lat*scale;
				poly->addCtPts(ctPt);
				
			}
		}
		map->addLayer(layer);
		fclose(fp);    //�ļ��ر�
		
		minl=minl/1000000.0;
		minb=minb/1000000.0;
		maxl=maxl/1000000.0;
		maxb=maxb/1000000.0;
		mapPrj->getXY(minl,minb,&minx,&miny);
		mapPrj->getXY(maxl,maxb,&maxx,&maxy);
		map->wcRect=CRect(minx,miny,maxx,maxy);  //���������귶Χ
	}	
	Invalidate();  //ǿ������Ļ�ػ�*/
	

	//��ͼͶӰ
    /*CFileDialog fDlg(true); //������ļ��Ի���
	if(fDlg.DoModal() == IDOK) //���ļ�����ѡ���ļ�ok��
	{
		CString fileName=fDlg.GetPathName();  //��ȡ�ļ�����
		FILE *fp=fopen(fileName,"r"); //�����ļ�ָ�룬���򿪶�Ӧ�ļ�
		if(fp==NULL) //����ļ���ʧ�ܣ���ʾ��Ϣ
		{
			MessageBox("�ļ���ʧ��!");
			return;
		}

		int flag;
		float lon,lat;
		int size;
		float minb,minl,maxb,maxl;  //���ݷ�Χ
		float minx,miny,maxx,maxy;
		int scale=1000000;   //����һ�����ߣ�ʹ�䱣֤ԭʼ���ݾ��ȣ�ͬʱ�������int��Ҫ
		char *str1,*str2;
		str1=(char *)malloc(100*sizeof(char));
		str2=(char *)malloc(10*sizeof(char));
		minl=minb=180*scale;  //��γ�����ֵ
		maxl=maxb=-180*scale;   //��γ����Сֵ

		if(map!=NULL) return;
		map=new CGeoMap();//�����µĵ�ͼ����		
		CGeoLayer *layer=new CGeoLayer();//������ͼ��
		CGeoPolyline *poly=NULL;//������Ҫ��
		
		while(!feof(fp)) //�ļ�û�н���
		{
			fscanf(fp,"%s",str1);
			str2="Pline";
			flag=strcmp(str1,str2);
			if(flag==0)
			{
				poly=new CGeoPolyline();
				fscanf(fp,"%d",&size);
				for(int i=0;i<size;i++)
				{
					CPoint myPoint;
					fscanf(fp,"%f%f",&lon,&lat); //��ȡ����
					lat=lat*scale;				
					lon=lon*scale;
					minb=minb>lat?lat:minb;    //��ȡ��С��Ӿ���
					minl=minl>lon?lon:minl;
					maxb=maxb<lat?lat:maxb;
					maxl=maxl<lon?lon:maxl;
					myPoint.x=lon;
					myPoint.y=lat;
					poly->addMyPoint(myPoint);   //������뵽������
				}
				layer->addPolyline(poly);
			}
		}
		map->addLayer(layer);
		fclose(fp);    //�ļ��ر�

		minl=minl/1000000.0;
		minb=minb/1000000.0;
		maxl=maxl/1000000.0;
		maxb=maxb/1000000.0;
		mapPrj->getXY(minl,minb,&minx,&miny);
		mapPrj->getXY(maxl,maxb,&maxx,&maxy);
		map->wcRect=CRect(minx,miny,maxx,maxy);  //���������귶Χ
	}	
	Invalidate();  //ǿ������Ļ�ػ�*/

    //͹������
	CFileDialog fDlg(true);
	if(fDlg.DoModal()==IDOK)
	{
		CString fileName=fDlg.GetPathName();
		FILE *fp=fopen(fileName,"r");
		if(fp==NULL)
		{
			MessageBox("�ļ���ʧ��");
			return;
		}
		float x,y;
		float minx,miny,maxx,maxy;
		while(!feof(fp))
		{
			fscanf(fp,"%f %f",&x,&y);
			minx=minx>x?x:minx;          
			miny=miny>y?y:miny;
			maxx=maxx<x?x:maxx;
			maxy=maxy<y?y:maxy;
			convexHull.pts.Add(CPoint((int)x,(int)y));
		}
		convexHull.crWCRect=CRect(minx,miny,maxx,maxy);
		this->crWCRect=convexHull.crWCRect;
		this->convexHull.getConvexHull();
		fclose(fp);
	}
	Invalidate();

    //ͼ�β���
	/*CFileDialog fDlg(true);
	if(fDlg.DoModal()==IDOK)
	{
		CString fileName=fDlg.GetPathName();
		FILE *fp=fopen(fileName,"r");
		if(fp==NULL)
		{
			MessageBox("�ļ���ʧ��");
			return;
		}

		int l,t,r,b;
		if(map!=NULL) return;
		map=new CGeoMap();//�����µĵ�ͼ����
		fscanf(fp,"%d%d%d%d",&l,&t,&r,&b);
		map->wcRect=CRect(l,t,r,b);

		CGeoLayer *layer=new CGeoLayer();//������ͼ��
		CGeoPolyline *poly=NULL;//������Ҫ��
		int size;
		int x,y;
		while(!feof(fp))
		{
			poly=new CGeoPolyline();
			fscanf(fp,"%d",&size);
			for(int i=0;i<size;i++)
			{
				fscanf(fp,"%d%d",&x,&y);
				poly->addPoint(CPoint(x,y));
			}
			layer->addPolyline(poly);
		}
		map->addLayer(layer);
		fclose(fp);
		map->clipRect=CRect(l/2,t/2,r/2,b/2);
		map->clipMap(map->clipRect);
	}
	Invalidate();*/

}

void CCGExeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

    if(map!=NULL)
	{
		CSize size;                          //��ʾ���εĿ�Ⱥ͸߶�
		CPoint pt;
		CRect rectD;

		this->GetClientRect(&rectD);         //��ÿͻ����������򣬵�ǰ�������Ͻ�x\yΪ0�����½�Ϊ��ǰ���ڵĿ�ȡ��߶�
		size.cx=rectD.Width();
		size.cy=rectD.Height();
		pt=rectD.CenterPoint();              //�������ĵ�����

		pDC->SetMapMode(MM_ISOTROPIC);     //����ָ���豸������ӳ��ģʽ
		pDC->SetViewportExt(size);           //���ô��ڳߴ�
		pDC->SetViewportOrg(pt);             //���ô������ĵ�Ϊ����ϵԭ��

		size=this->map->wcRect.Size();            
		size.cx=(int)(size.cx*1.02);
		size.cy=-(int)(size.cy*1.02);
		pt=this->map->wcRect.CenterPoint();

		pDC->SetWindowExt(size);             //���ô��ڳ���
		pDC->SetWindowOrg(pt);               //���ô���ԭ��
	}
	CView::OnPrepareDC(pDC, pInfo);
}
