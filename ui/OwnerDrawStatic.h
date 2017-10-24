#pragma once
#include "afxwin.h"


// »æÖÆÑÕÉ«
#define OWNER_COLOR_BACKGROUND_SSTC			RGB(240, 240, 240)
#define OWNER_COLOR_HIGHLIGHT_SSTC			RGB(55, 56, 55)
#define OWNER_COLOR_GRAY_SSTC				RGB(140, 140, 145)

class COwnerDrawStatic :
	public CStatic
{
public:
	COwnerDrawStatic();
	~COwnerDrawStatic();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};

