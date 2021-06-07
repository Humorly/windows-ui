#include "pch.h"
#include "OwnerDrawCheckButton.h"


COwnerDrawCheckButton::COwnerDrawCheckButton()
{
}


COwnerDrawCheckButton::~COwnerDrawCheckButton()
{
}
BEGIN_MESSAGE_MAP(COwnerDrawCheckButton, CButton)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void COwnerDrawCheckButton::OnPaint()
{
	//CButton::OnPaint();

	CPaintDC dc(this); 
	CRect rt;
	GetClientRect(&rt);

	dc.SetBkMode(TRANSPARENT);
	dc.SetBkColor(TRANSPARENT);

	// 先绘制背景
	CBrush bhh(RGB(240, 240, 240));
	dc.FillRect(&rt, &bhh);

	// 先绘制背景
	CBrush bh(RGB(55, 55, 55));
	//dc.FrameRect(&rt, &bh);

	// 绘制未选中时的空格子
	CBrush bsh(RGB(0, 139, 160));
	CBrush bshb(RGB(215, 215, 215));
	RECT rm		= rt;
	rm.top		= rm.bottom / 5;
	rm.bottom	= rm.bottom - rm.top;
	rm.left		= rm.top;
	rm.right	= rm.bottom;	

	RECT rmm = rm;
	rmm.left += 1;
	rmm.top += 1;
	rmm.right -= 1;
	rmm.bottom -= 1;

	RECT rmmm = rmm;
	rmmm.left += 1;
	rmmm.top += 1;
	rmmm.right -= 1;
	rmmm.bottom -= 1;

	if (GetCheck())
	{
		//dc.FillRect(&rm, &bsh);
		//CPen pen(PS_SOLID, 3, RGB(63, 37, 136));
		CPen pen(PS_SOLID, 3, RGB(50, 50, 50));
		dc.SelectObject(pen);

		CPoint pt[] = { { rm.left + 3, rm.bottom - rm.bottom / 4 - 3 }, { rm.left + rm.right / 4, rm.bottom - 4 }, { rm.right - 3, rm.top + rm.bottom / 4 } };
		dc.MoveTo(pt[0]);
		dc.LineTo(pt[1]);
		dc.LineTo(pt[2]);

		dc.FrameRect(&rm, &bh);
		dc.FrameRect(&rm, &bh);
	}
	else
	{
		dc.FillRect(&rm, &bshb);
		dc.FrameRect(&rm, &bh);
		dc.FrameRect(&rm, &bh);
	}

	CString str;
	GetWindowText(str);
	// 准备字体
	HFONT ft = CreateFont((rt.bottom - rt.top) * 7 / 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("微软雅黑"));
	HFONT hOldFont = (HFONT)SelectObject(dc, ft);

	RECT rrm;
	rrm = rt;
	rrm.left = rm.right + rm.top;

	if (!IsWindowEnabled())
	{
		dc.SetTextColor(RGB(122, 123, 124));
	}

	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(str, str.GetLength(), &rrm, DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	SelectObject(dc, hOldFont);
	DeleteObject(ft);
}


void COwnerDrawCheckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CButton::OnLButtonDown(nFlags, point);
}


void COwnerDrawCheckButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	CButton::OnLButtonUp(nFlags, point);
}
