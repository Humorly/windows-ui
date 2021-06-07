#pragma once

#include "GdiPlusMakeUi.h"

class CImageButton : public CButton
{
public:
	CImageButton();
	void SetButtonImage(CString strNorPath, CString strHovPath, CString strPushPath);
	~CImageButton();

	Image * m_pNormalImage;
	Image * m_pHoverImage;
	Image * m_pDownImage;

	HBRUSH m_hBackBrush;

	BOOL m_MouseOnButton;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// ªÊ÷∆ΩÁ√Ê
	void DrawButton(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	virtual void PreSubclassWindow();
};