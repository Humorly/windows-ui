#pragma once
#include "afxwin.h"
class COwnerDrawRadioButton :
	public CButton
{
public:
	COwnerDrawRadioButton();
	~COwnerDrawRadioButton();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

