#pragma once
#include "afxwin.h"

#include <vector>
using namespace std;

// »æÖÆÑÕÉ«
#define OWNER_COLOR_BACKGROUND_STC			RGB(33, 33, 36)
#define OWNER_COLOR_HIGHLIGHT_STC			RGB(211, 211, 215)
#define OWNER_COLOR_GRAY_STC				RGB(140, 140, 145)

class COwnerDrawTabList :
	public CStatic
{
public:
	vector<CString> m_strVecTabTitle;
	int m_nSelectIndex;
	CWnd * m_pParent;

	COwnerDrawTabList();
	~COwnerDrawTabList();

	void SetParentCwnd(CWnd * pWnd);
	void SetTabTitle(vector<CString> strVecTabTitle);
	void SetSelectIndex(int index);
	int GetSelectIndex();

	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

