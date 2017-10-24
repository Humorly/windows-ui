#include "stdafx.h"
#include "OwnerDrawStatic.h"


COwnerDrawStatic::COwnerDrawStatic()
{
}


COwnerDrawStatic::~COwnerDrawStatic()
{
}
BEGIN_MESSAGE_MAP(COwnerDrawStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void COwnerDrawStatic::OnPaint()
{
	CPaintDC dc(this); 
	CBrush bh(OWNER_COLOR_BACKGROUND_SSTC);
	CBrush bhh(OWNER_COLOR_HIGHLIGHT_SSTC);

	CDC* pDC = CDC::FromHandle(dc.m_hDC);
	CRect itemRect;
	GetClientRect(&itemRect);
	pDC->SetBkMode(TRANSPARENT);

	pDC->FillRect(itemRect, &bh);

	CString str;
	GetWindowText(str);

	// ×¼±¸×ÖÌå
	HFONT ft = CreateFont((itemRect.bottom - itemRect.top) * 7 / 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Î¢ÈíÑÅºÚ"));
	HFONT hOldFont = (HFONT)SelectObject(pDC->m_hDC, ft);

	pDC->SetTextColor(OWNER_COLOR_HIGHLIGHT_SSTC);
	pDC->DrawText(str, str.GetLength(), &itemRect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	SelectObject(pDC->m_hDC, hOldFont);
	DeleteObject(ft);
}
