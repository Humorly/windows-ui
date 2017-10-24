#include "stdafx.h"
#include "OwnerDrawRadioButton.h"


COwnerDrawRadioButton::COwnerDrawRadioButton()
{
}


COwnerDrawRadioButton::~COwnerDrawRadioButton()
{
}
BEGIN_MESSAGE_MAP(COwnerDrawRadioButton, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void COwnerDrawRadioButton::OnPaint()
{
	CPaintDC dc(this);
	CRect rt;
	GetClientRect(&rt);

	// 先绘制背景
	CBrush bhh(RGB(240, 240, 240));
	dc.FillRect(&rt, &bhh);

	// 先绘制背景
	CBrush bh(RGB(0, 139, 160));
	//dc.FrameRect(&rt, &bh);

	// 绘制未选中时的空格子
	CBrush bsh(RGB(195, 195, 195));
	CBrush bshb(RGB(195, 195, 195));
	RECT rm = rt;
	rm.top = rm.bottom / 5;
	rm.bottom = rm.bottom - rm.top;
	rm.left = rm.top;
	rm.right = rm.bottom;

	rm.right -= 1;
	rm.bottom -= 1;

	RECT rmm = rm;

	rmm.left -= 1;
	rmm.top -= 1;
	rmm.right += 1;
	rmm.bottom += 1;

	if (GetCheck())
	{
		dc.SelectObject(bsh);
		//dc.Ellipse(&rmm);

		dc.SelectObject(bh);
		dc.Ellipse(&rm);


		//dc.FrameRect(&rm, &bshb);
	}
	else
	{
		dc.SelectObject(bshb);
		dc.Ellipse(&rm);
		//dc.FrameRect(&rm, &bsh);
	}

	CString str;
	GetWindowText(str);
	// 准备字体
	HFONT ft = CreateFont((rt.bottom - rt.top) * 7 / 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("微软雅黑"));
	HFONT hOldFont = (HFONT)SelectObject(dc, ft);

	RECT rrm;
	rrm = rt;
	rrm.left = rm.right + rm.top;

	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(str, str.GetLength(), &rrm, DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	SelectObject(dc, hOldFont);
	DeleteObject(ft);
}
