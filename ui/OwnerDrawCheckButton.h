#pragma once
#include "afxwin.h"
class COwnerDrawCheckButton :
	public CButton
{
public:
	COwnerDrawCheckButton();
	~COwnerDrawCheckButton();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

