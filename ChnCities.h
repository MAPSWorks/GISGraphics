// ChnCities.h: interface for the CChnCities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHNCITIES_H__FA4A8589_6618_4D28_AC65_E69DC1539E58__INCLUDED_)
#define AFX_CHNCITIES_H__FA4A8589_6618_4D28_AC65_E69DC1539E58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct city_Struct  //����ṹ��
{
	int id;         //ID
	float lon;      //����
	float lat;      //γ��
	CString name;   //��������
};

typedef struct city_Struct CITY; 

#include "afxtempl.h" //����֧�ְ�ȫ�����ͷ�ļ�

class CChnCities  
{
public:
	void Draw(CDC *pDC);
	void addCity(CITY city);
	CArray <CITY,CITY>cities; //��̬����cities����

	CRect wcRect;             //�������е㼯����Ӿ��Σ���¼ԭʼͼ�η�Χ


	CChnCities();
	virtual ~CChnCities();

};

#endif // !defined(AFX_CHNCITIES_H__FA4A8589_6618_4D28_AC65_E69DC1539E58__INCLUDED_)
