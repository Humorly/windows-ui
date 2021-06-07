
// Defined By HUMORLY 2016/11/10
// 将combox用此类型定义
// 并绑定到对应控件即可
// 但是拥有该combox的窗体
// 必须重写OnDrawItem、OnMeasureItem
// 并去掉基类绘制函数调用方可使用

#pragma once
#include "afxwin.h"

// 绘制颜色
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

	// 必须重写否则断言错误
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

