
// Defined By HUMORLY 2016/11/10
// ��combox�ô����Ͷ���
// ���󶨵���Ӧ�ؼ�����
// ����ӵ�и�combox�Ĵ���
// ������дOnDrawItem��OnMeasureItem
// ��ȥ��������ƺ������÷���ʹ��

#pragma once
#include "afxwin.h"

// ������ɫ
#define OWNER_COLOR_BACKGROUND			RGB(231, 234, 235)
#define OWNER_COLOR_HIGHLIGHT			RGB(9, 7, 8)
class COwnerDrawCombox :
	public CComboBox
{
public:
	COwnerDrawCombox();
	~COwnerDrawCombox();
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();

	// ������д������Դ���
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);	
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct);

	void PaintBk(CPaintDC * pDC);
	afx_msg void OnSysColorChange();

	CDC m_dcBk;
	CBitmap m_bmpBk;
	CBitmap* m_pbmpOldBk;
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};

