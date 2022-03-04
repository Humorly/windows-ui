
// OwnerDrawWindowDlg.cpp : 实现文件
//

#include "pch.h"
#include "OwnerDrawWindowDlg.h"
#include "afxdialogex.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

IMPLEMENT_DYNAMIC(COwnerDrawWindowDlg, CDialogEx)

COwnerDrawWindowDlg::COwnerDrawWindowDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{
	// 创建四个按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		m_pWidgitBtn[i] = nullptr;
	}
	htcaption_flag_ = false;
	clinet_hit_flag_ = false;
}

void COwnerDrawWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COwnerDrawWindowDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(MINI_BTN_ID, &COwnerDrawWindowDlg::OnBnClickedMini)
	ON_BN_CLICKED(MAX_BTN_ID, &COwnerDrawWindowDlg::OnBnClickedMax)
	ON_BN_CLICKED(MAX_RESTORE_BTN_ID, &COwnerDrawWindowDlg::OnBnClickedRestore)
	ON_BN_CLICKED(QUIT_BTN_ID, &COwnerDrawWindowDlg::OnBnClickedQuit)
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// COwnerDrawWindowDlg 消息处理程序

BOOL COwnerDrawWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 初始GDI+
	CGdiPlusMakeUi::CGdiPlusMakeUiInit();
	//ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);
	ModifyStyle(WS_TILEDWINDOW, 0, 0);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_RIGHT);
	//::SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	m_pBackgroundImage.reset(new Image(SplicFullFilePath(WINDOW_BACKGROUND)));

	InitImageButton();
	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(RGB(0, 0, 0), 240, LWA_ALPHA);

	RefreshWidget();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COwnerDrawWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COwnerDrawWindowDlg::OnPaint()
{
	DrawOwnerWindow();
	CDialogEx::OnPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COwnerDrawWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL COwnerDrawWindowDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 无效
BOOL COwnerDrawWindowDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialogEx::PreCreateWindow(cs);
}

// 最大化
void COwnerDrawWindowDlg::OnBnClickedMax()
{
	// 保存位置
	GetWindowRect(&m_rcRestoreArea);

	CRect rcWorkArea;
	// 获取工作区
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	MoveWindow(&rcWorkArea);

	m_pWidgitBtn[1]->ShowWindow(false);
	m_pWidgitBtn[2]->ShowWindow(true);
}

// 还原
void COwnerDrawWindowDlg::OnBnClickedRestore()
{
	//ShowWindow(SW_RESTORE);
	MoveWindow(&m_rcRestoreArea);

	m_pWidgitBtn[1]->ShowWindow(true);
	m_pWidgitBtn[2]->ShowWindow(false);
}

void COwnerDrawWindowDlg::OnBnClickedQuit()
{
	//CDialogEx::OnClose();
	// 发送关闭消息给继承窗体
	SendMessage(WM_CLOSE, 0, 0);
}

void COwnerDrawWindowDlg::OnBnClickedMini()
{
	ShowWindow(SW_MINIMIZE);
}

#define WINDOW_BTN_WIDTH			48
#define WINDOW_BTN_HEIGHT			32

// 初始按钮
int COwnerDrawWindowDlg::InitImageButton()
{
	// 创建四个按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		m_pWidgitBtn[i].reset(new CImageButton());
	}

	m_pWidgitBtn[0]->SetButtonImage(SplicFullFilePath(MINI_BTN_PATH_NOR), SplicFullFilePath(MINI_BTN_PATH_HOVER), SplicFullFilePath(MINI_BTN_PATH_DOWN));
	m_pWidgitBtn[1]->SetButtonImage(SplicFullFilePath(MAX_BTN_PATH_NOR), SplicFullFilePath(MAX_BTN_PATH_HOVER), SplicFullFilePath(MAX_BTN_PATH_DOWN));
	m_pWidgitBtn[2]->SetButtonImage(SplicFullFilePath(RESTORE_BTN_PATH_NOR), SplicFullFilePath(RESTORE_BTN_PATH_HOVER), SplicFullFilePath(RESTORE_BTN_PATH_DOWN));
	m_pWidgitBtn[3]->SetButtonImage(SplicFullFilePath(QUIT_BTN_PATH_NOR), SplicFullFilePath(QUIT_BTN_PATH_HOVER), SplicFullFilePath(QUIT_BTN_PATH_DOWN));

	RECT rect;
	GetClientRect(&rect);

	CString str[] = { _T("_"), _T("u"), _T("U"), _T("*") };

	int nId = MINI_BTN_ID;
	// 创建按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		GetClientRect(&rect);
		rect.left = rect.right - WINDOW_BTN_WIDTH * (WIDGIT_BUTTON_NUM - 1 - ((i >= 2 ? (i - 1) : i))) - 1;
		rect.right = rect.left + WINDOW_BTN_WIDTH;
		rect.top = 1;
		rect.bottom = rect.top + WINDOW_BTN_HEIGHT;

		m_pWidgitBtn[i]->Create(str[i], WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, rect, this, nId + i);
		m_pWidgitBtn[i]->ShowWindow(SW_SHOW);

		if (NULL != m_pWidgitBtn[2]->m_hWnd)
		{
			m_pWidgitBtn[2]->ShowWindow(SW_HIDE);
		}
		//if (NULL != m_pWidgitBtn[1]->m_hWnd)
		//{
		//	m_pWidgitBtn[1]->ShowWindow(SW_HIDE);
		//}
		//if (NULL != m_pWidgitBtn[0]->m_hWnd)
		//{
		//	m_pWidgitBtn[0]->ShowWindow(SW_HIDE);
		//}
	}

	return 0;
}

// 刷新控件
void COwnerDrawWindowDlg::RefreshWidget()
{
	RECT rect;
	GetClientRect(&rect);
	CString str[] = { _T(" "), _T(" "), _T(" "), _T(" ") };

	int nId = MINI_BTN_ID;
	// 创建按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		GetClientRect(&rect);
		rect.left = rect.right - WINDOW_BTN_WIDTH * (WIDGIT_BUTTON_NUM - 1 - ((i >= 2 ? (i - 1) : i))) - 1;
		rect.right = rect.left + WINDOW_BTN_WIDTH;
		rect.top = 1;
		rect.bottom = rect.top + WINDOW_BTN_HEIGHT;

		if (NULL != m_pWidgitBtn[i])
		{
			m_pWidgitBtn[i]->MoveWindow(&rect, true);
			m_pWidgitBtn[i]->Invalidate();
		}
	}

	//Invalidate();

	//// 查找控件并刷新之
	//HWND hWndChild = ::GetWindow(m_hWnd, GW_CHILD);
	//// 遍历界面控件并刷新之
	//while (hWndChild)
	//{
	//	CWnd* pw = CWnd::FromHandle(hWndChild);
	//	int pid = pw->GetDlgCtrlID();
	//	if (pw != NULL)
	//	{
	//		CRect rect1;
	//		pw->GetWindowRect(rect1);
	//		ScreenToClient(rect1);
	//		pw->ShowWindow(SW_SHOW);
	//	}
	//	hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
	//}
}

// 绘制窗体
void COwnerDrawWindowDlg::DrawOwnerWindow()
{
	CDC * dc = GetDC();
	dc->SetBkColor(TRANSPARENT);
	dc->SetBkMode(TRANSPARENT);

	HDC hMemDC;
	HBITMAP	lBitmap;
	RECT rc;
	GetClientRect(&rc);
	//FillRect(dc->GetSafeHdc(), &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	
	// 构建缓存画布
	hMemDC = CreateCompatibleDC(dc->m_hDC);
	lBitmap = CreateCompatibleBitmap(dc->m_hDC, rc.right, rc.bottom);
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hMemDC, lBitmap);
	SetBkMode(hMemDC, TRANSPARENT);
	SetBkColor(hMemDC, TRANSPARENT);


	FillRect(hMemDC, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// GDI对象关联设备对象
	Graphics* pImageGraphics;
	pImageGraphics = Graphics::FromHDC(hMemDC);
	VERIFY(pImageGraphics);

	// 根据状态绘制图片
	RectF rRect(static_cast<Gdiplus::REAL>(rc.left), static_cast<Gdiplus::REAL>(rc.top), static_cast<Gdiplus::REAL>(rc.right - rc.left), static_cast<Gdiplus::REAL>(rc.bottom - rc.top));
	//if (m_pBackgroundImage)
	//	pImageGraphics->DrawImage(m_pBackgroundImage.get(), rRect, 0, 0, static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetWidth()), static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetHeight()), UnitPixel);

	CRect rt;
	rt = CRect(14, 8, 184, 36);
	// 准备字体
	HFONT ft = CreateFont((rt.bottom - rt.top) * 3 / 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("微软雅黑"));
	HFONT hOldFont = (HFONT)SelectObject(hMemDC, ft);

	CString str;
	GetWindowText(str);
	DrawText(hMemDC, str, str.GetLength(), rt, DT_LEFT | DT_VCENTER);

	GetClientRect(&rt);
	DrawWindowRectUi(hMemDC, rt);

	// 拷贝画布
	BitBlt(dc->m_hDC, 0, 0, rc.right, rc.bottom, hMemDC, 0, 0, SRCCOPY);

	// 删除对象
	SelectObject(hMemDC, hOldFont);
	SelectObject(hMemDC, hPrevBitmap);
	DeleteObject(lBitmap);
	delete pImageGraphics;

	ReleaseDC(dc);
	DeleteObject(ft);
	DeleteDC(hMemDC);
}

// 区域设定
LRESULT COwnerDrawWindowDlg::OnNcHitTest(CPoint point)
{
	// 获取结果
	LRESULT lResult = CalcWindowHitWhere();
	// 重新计算位置
	if (HTCAPTION == lResult || HTTOPLEFT == lResult || HTLEFT == lResult || HTBOTTOMLEFT == lResult || HTBOTTOM
		||
		HTBOTTOMRIGHT == lResult || HTRIGHT == lResult || HTTOPRIGHT || HTTOP == lResult
		)
	{
		return lResult;
	}
	return CDialogEx::OnNcHitTest(point);
}

#define	TITLEBAR_HEIGHT				30
LRESULT COwnerDrawWindowDlg::CalcWindowHitWhere()
{
	RECT ClientRect;
	GetClientRect(&ClientRect);
	POINT MovePoint;
	GetCursorPos(&MovePoint);
	ScreenToClient(&MovePoint);

	bool zoomed_ = m_pWidgitBtn[2]->IsWindowVisible();

	if (MovePoint.x >= 5
		&& MovePoint.x <= ClientRect.right - 5
		&& MovePoint.y >= 0
		&& MovePoint.y <= TITLEBAR_HEIGHT
		)
	{
		if (nullptr != m_pWidgitBtn[2] && m_pWidgitBtn[2]->IsWindowVisible())
			return HTCLIENT;
		else
			return HTCAPTION;	
	}

	if (!zoomed_ && MovePoint.x >= 0
		&& MovePoint.x <= 5

		&& MovePoint.y >= 0
		&& MovePoint.y <= 5
		)
	{
		return HTTOPLEFT;
	}
	if (!zoomed_ && MovePoint.x >= 0
		&& MovePoint.x <= 5
		&& MovePoint.y >= 5
		&& MovePoint.y <= ClientRect.bottom - 5 
		)
	{
		return HTLEFT;
	}

	if (!zoomed_ && MovePoint.x >= 0
		&& MovePoint.x <= 5

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOMLEFT;
	}

	if (!zoomed_ && MovePoint.x >= 5
		&& MovePoint.x <= ClientRect.right - 5

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOM;
	}

	if (!zoomed_ && MovePoint.x >= ClientRect.right - 5
		&& MovePoint.x <= ClientRect.right

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOMRIGHT;
	}


	if (!zoomed_ && MovePoint.x >= ClientRect.right - 5
		&& MovePoint.x <= ClientRect.right

		&& MovePoint.y >= 5
		&& MovePoint.y <= ClientRect.bottom - 5
		)
	{
		return HTRIGHT;
	}

	if (MovePoint.x >= ClientRect.right - 5
		&& MovePoint.x <= ClientRect.right

		&& MovePoint.y >= 0
		&& MovePoint.y <= 5
		)
	{
		return HTTOPRIGHT;
	}

	if (!zoomed_ && MovePoint.x >= 5
		&& MovePoint.x <= ClientRect.right - 5

		&& MovePoint.y >= 0
		&& MovePoint.y <= 5
		)
	{
		return HTTOP;
	}
	else
	{
		return HTCLIENT;
	}

	return HTCLIENT;
}

// 窗体变更
void COwnerDrawWindowDlg::OnSize(UINT nType, int cx, int cy)
{
	static bool bMiniSize = false;
	if (!bMiniSize)
		bMiniSize = (SIZE_MINIMIZED == nType);

	// 最小化是否按下
	if (!bMiniSize)
	{
		// 非最小化下的状态变更
		if (!IsZoomed())
		{
			// 修改按钮
			if (nullptr != m_pWidgitBtn[2])
				m_pWidgitBtn[2]->ShowWindow(false);
			if (nullptr != m_pWidgitBtn[1])
				m_pWidgitBtn[1]->ShowWindow(true);
		}
	}

	bMiniSize = (SIZE_MINIMIZED == nType);

	// 刷新控件位置
	RefreshWidget();
}

//  拼接完整路径
CString COwnerDrawWindowDlg::SplicFullFilePath(CString strExeModuleName)
{
	// 提取当前路径
	// 准备写文件
	WCHAR strPath[MAX_PATH + 1] = { 0 };
	WCHAR * pTempPath;
	GetModuleFileName(NULL, strPath, MAX_PATH);
	pTempPath = strPath;
	while (wcschr(pTempPath, '\\'))
	{
		pTempPath = wcschr(pTempPath, '\\');
		pTempPath++;
	}
	*pTempPath = 0;

	CString strPathName;
	strPathName += strPath + strExeModuleName;
	return strPathName;
}

void COwnerDrawWindowDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void COwnerDrawWindowDlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight -= 2;
	CDialogEx::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


BOOL COwnerDrawWindowDlg::OnEraseBkgnd(CDC* pDC)
{
	return false;
}

// 结束时清理对应内存
COwnerDrawWindowDlg::~COwnerDrawWindowDlg()
{
}

// 标题栏按下
void COwnerDrawWindowDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	htcaption_flag_ = true;
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}

void COwnerDrawWindowDlg::OnNcLButtonUp(UINT nHitTest, CPoint point)
{
	htcaption_flag_ = false;
	CDialogEx::OnNcLButtonUp(nHitTest, point);
}

void COwnerDrawWindowDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	htcaption_flag_ = false;
	if (!m_pWidgitBtn[2]->IsWindowVisible())
	{
		// 保存位置
		GetWindowRect(&m_rcRestoreArea);

		CRect rcWorkArea;
		// 获取工作区
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
		MoveWindow(&rcWorkArea);

		m_pWidgitBtn[1]->ShowWindow(false);
		m_pWidgitBtn[2]->ShowWindow(true);
	}
	else
	{
		//ShowWindow(SW_RESTORE);
		MoveWindow(&m_rcRestoreArea);
		m_pWidgitBtn[1]->ShowWindow(true);
		m_pWidgitBtn[2]->ShowWindow(false);
	}

	CDialogEx::OnNcLButtonDblClk(nHitTest, point);
}

void COwnerDrawWindowDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//// 还原窗体
	//if (clinet_hit_flag_ && nullptr != m_pWidgitBtn[2] && m_pWidgitBtn[2]->IsWindowVisible())
	//{
	//	OutputDebugString(TEXT("restore"));

	//	// 获取鼠标在窗体中的高度
	//	RECT ClientRect;
	//	GetClientRect(&ClientRect);
	//	POINT MovePoint, NowPoint;
	//	GetCursorPos(&MovePoint);
	//	GetCursorPos(&NowPoint);
	//	ScreenToClient(&MovePoint);

	//	// 根据高度调整
	//	auto width_ = m_rcRestoreArea.Width();
	//	auto height_ = m_rcRestoreArea.Height();

	//	m_rcRestoreArea.left = NowPoint.x - width_ / 2;
	//	m_rcRestoreArea.top = NowPoint.y - MovePoint.y;
	//	m_rcRestoreArea.right = m_rcRestoreArea.left + width_;
	//	m_rcRestoreArea.bottom = m_rcRestoreArea.top + height_;

	//	m_pWidgitBtn[1]->ShowWindow(true);
	//	m_pWidgitBtn[2]->ShowWindow(false);

	//	MoveWindow(&m_rcRestoreArea);
	//}
	//// 移动窗体
	//if (clinet_hit_flag_)
	//{
	//	// 获取鼠标在窗体中的高度
	//	CRect WindowRect;
	//	GetWindowRect(&WindowRect);
	//	// 根据高度调整
	//	auto width_ = WindowRect.Width();
	//	auto height_ = WindowRect.Height();

	//	WindowRect.left += point.x - now_mouse_point_.x;
	//	WindowRect.top += point.y - now_mouse_point_.y;
	//	WindowRect.right = WindowRect.left + width_;
	//	WindowRect.bottom = WindowRect.top + height_;

	//	now_mouse_point_ = point;

	//	MoveWindow(&WindowRect);
	//}

	//CDialogEx::OnMouseMove(nFlags, point);
}

// 右键按下
void COwnerDrawWindowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	now_mouse_point_ = point;
	clinet_hit_flag_ = true;
	CDialogEx::OnLButtonDown(nFlags, point);
}

void COwnerDrawWindowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	clinet_hit_flag_ = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}

