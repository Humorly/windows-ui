#include "pch.h"
#include "OwnerDrawCombox.h"

COwnerDrawCombox::COwnerDrawCombox()
{
	
}

COwnerDrawCombox::~COwnerDrawCombox()
{
}
BEGIN_MESSAGE_MAP(COwnerDrawCombox, CComboBox)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_COMPAREITEM()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

void COwnerDrawCombox::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	PaintBk(&dc);

	// 填充背景
	CRect rc;
	GetClientRect(&rc);
	CBrush bh(OWNER_COLOR_BACKGROUND);

	dc.SelectObject(bh);

	CPen pn(PS_SOLID, 1, RGB(140, 140, 140));
	dc.SelectObject(pn);
	RoundRect(dc.GetSafeHdc(), rc.left, rc.top, rc.right, rc.bottom, 4, 4);

	//dc.FillRect(&rc, &bh);
	// 绘制3D边框
	//dc.Draw3dRect(rc, RGB(56, 56, 66), RGB(50, 50, 50));
	// 选中虚线框框
	//DrawFocusRect(dc, &rc);
	TCHAR str[255] = { 0 };
	GetWindowTextW(str, 255);

	// 字体宽度
	int nFontWidth = rc.bottom - rc.top;

	// 准备字体
	HFONT ft = CreateFont(nFontWidth * 4 / 5 + 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("微软雅黑"));
	HFONT hOldFont = (HFONT)SelectObject(dc, ft);
	// 绘制选中项文本
	if (CString(str).IsEmpty() == FALSE)
	{
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(OWNER_COLOR_HIGHLIGHT);
		rc.left += 5;
		dc.DrawTextW(str, wcslen(str), &rc, DT_VCENTER | DT_SINGLELINE | DT_LEFT);


		// 绘制下拉三角形
		CPoint pt[3] = { 
			CPoint(rc.right - 13, rc.top + 9), 
			CPoint(rc.right - 10, rc.bottom - 10), 
			CPoint(rc.right - 7, rc.top + 9) };
		
		CBrush bsh(OWNER_COLOR_HIGHLIGHT);
		CBrush* pOldBrush = dc.SelectObject(&bsh);
		dc.Polygon(pt, 3);
		dc.SelectObject(pOldBrush);	
	}

	// 还原及清理对象
	SelectObject(dc, hOldFont);
	DeleteObject(ft);
}

// 绘制选项
void COwnerDrawCombox::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 填充背景色
	CBrush bh(OWNER_COLOR_BACKGROUND);
	CBrush bhw(OWNER_COLOR_HIGHLIGHT);
	// 缓存文本
	WCHAR achTemp[256] = { 0 };
	// 提取绘制区域
	LPDRAWITEMSTRUCT lpdis = lpDrawItemStruct;

	// 空列表
	int index = lpdis->itemID;
	if (index < 0)
		return;

	// 提取对应列文本
	GetLBText(index, achTemp);

	// 透明背景
	SetBkMode(lpdis->hDC, TRANSPARENT);

	if (lpdis->itemState & ODS_SELECTED)
	{
		// 高亮即虚线框
		FillRect(lpdis->hDC, &lpdis->rcItem, bhw);
		//DrawFocusRect(lpdis->hDC, &lpdis->rcItem);

		SetTextColor(lpdis->hDC, OWNER_COLOR_BACKGROUND);
		// 绘制字符串
		DrawText(lpdis->hDC, achTemp, wcslen(achTemp), &lpdis->rcItem, DT_LEFT | DT_VCENTER);
	}
	else
	{
		// 常规背景
		FillRect(lpdis->hDC, &lpdis->rcItem, bh);
		SetTextColor(lpdis->hDC, OWNER_COLOR_HIGHLIGHT);
		// 绘制字符串
		DrawText(lpdis->hDC, achTemp, wcslen(achTemp), &lpdis->rcItem, DT_LEFT | DT_VCENTER);
	}
	//CComboBox::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void COwnerDrawCombox::PreSubclassWindow()
{
	// TODO:  在此添加专用代码和/或调用基类
	ModifyStyle(CBS_SORT, CBS_OWNERDRAWVARIABLE);
	CComboBox::PreSubclassWindow();
}


void COwnerDrawCombox::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) {}


int COwnerDrawCombox::OnCompareItem(int nIDCtl, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return 0;
	//return CComboBox::OnCompareItem(nIDCtl, lpCompareItemStruct);
}

void COwnerDrawCombox::PaintBk(CPaintDC * pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	}

	

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
} // End of PaintBk


void COwnerDrawCombox::OnSysColorChange()
{
	CComboBox::OnSysColorChange();

	m_dcBk.DeleteDC();
	m_bmpBk.DeleteObject();
} // End of OnSysColorChange


HBRUSH COwnerDrawCombox::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	pDC->SetBkMode(TRANSPARENT);   //设置透明属性
	return (HBRUSH)GetStockObject(NULL_BRUSH);   //返回空画刷
}
