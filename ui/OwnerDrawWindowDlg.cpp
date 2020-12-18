
// OwnerDrawWindowDlg.cpp : 实现文件
//

#include "pch.h"
#include "OwnerDrawWindowDlg.h"
#include "afxdialogex.h"

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

//  拼接完整路径
CString SplicFullFilePath(CString strExeModuleName);

// COwnerDrawWindowDlg 对话框

IMPLEMENT_DYNAMIC(COwnerDrawWindowDlg, CDialogEx)

COwnerDrawWindowDlg::COwnerDrawWindowDlg(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{
	// 创建四个按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		m_pWidgitBtn[i] = nullptr;
	}
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
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, 0);
	ModifyStyle(WS_TILEDWINDOW, 0, 0);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, WS_EX_RIGHT);

	m_pBackgroundImage.reset(new Image(SplicFullFilePath(WINDOW_BACKGROUND)));

	InitImageButton();
	Invalidate();

	ModifyStyleEx(0, WS_EX_LAYERED);
	SetLayeredWindowAttributes(RGB(0, 0, 0), 240, LWA_ALPHA);

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
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		DrawOwnerWindow();
	}
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

		m_pWidgitBtn[i]->Create(str[i], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | WS_CLIPCHILDREN, rect, this, nId + i);
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

	CString str[] = { _T("_"), _T("u"), _T("U"), _T("*") };

	int nId = MINI_BTN_ID;
	// 创建按钮
	for (int i = 0; i < WIDGIT_BUTTON_NUM; i++)
	{
		GetClientRect(&rect);
		rect.left = rect.right - WINDOW_BTN_WIDTH * (WIDGIT_BUTTON_NUM - 1 - ((i >= 2 ? (i - 1) : i))) - 4;
		rect.right = rect.left + WINDOW_BTN_WIDTH;
		rect.top = 3;
		rect.bottom = rect.top + WINDOW_BTN_HEIGHT;

		if (NULL != m_pWidgitBtn[i])
		{
			m_pWidgitBtn[i]->MoveWindow(&rect, true);
		}
	}

	Invalidate();

	// 查找控件并刷新之
	HWND hWndChild = ::GetWindow(m_hWnd, GW_CHILD);
	// 遍历界面控件并刷新之
	while (hWndChild)
	{
		CWnd* pw = CWnd::FromHandle(hWndChild);
		int pid = pw->GetDlgCtrlID();
		if (pw != NULL && pw->IsWindowVisible())
			pw->Invalidate();
		hWndChild = ::GetWindow(hWndChild, GW_HWNDNEXT);
	}
}

// 绘制窗体
void COwnerDrawWindowDlg::DrawOwnerWindow()
{
	CDC * dc = GetDC();
	dc->SetBkMode(TRANSPARENT);

	HDC hMemDC;
	HBITMAP	lBitmap;
	RECT rc;
	GetClientRect(&rc);
	// 双缓冲拿一套
	hMemDC = CreateCompatibleDC(dc->m_hDC);
	lBitmap = CreateCompatibleBitmap(dc->m_hDC, rc.right, rc.bottom);
	SelectObject(hMemDC, lBitmap);
	SetBkMode(hMemDC, TRANSPARENT);
	// GDI对象关联设备对象
	Graphics* pImageGraphics;
	pImageGraphics = Graphics::FromHDC(hMemDC);
	VERIFY(pImageGraphics);

	// 根据状态绘制图片
	RectF rRect(static_cast<Gdiplus::REAL>(rc.left), static_cast<Gdiplus::REAL>(rc.top), static_cast<Gdiplus::REAL>(rc.right - rc.left), static_cast<Gdiplus::REAL>(rc.bottom - rc.top));
	if (m_pBackgroundImage)
		pImageGraphics->DrawImage(m_pBackgroundImage.get(), rRect, 0, 0, static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetWidth()), static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetHeight()), UnitPixel);

	// 拷贝画布
	//BitBlt(dc->m_hDC, 0, 0, rc.right, rc.bottom, hMemDC, 0, 0, SRCCOPY);

	CRect rt;
	CBrush bh(RGB(240, 240, 240));

	GetClientRect(&rt);
	DrawWindowRectUi(dc->m_hDC, rt);

	rt = CRect(14, 8, 184, 36);
	// 准备字体
	HFONT ft = CreateFont((rt.bottom - rt.top) * 4 / 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("宋体"));
	HFONT hOldFont = (HFONT)dc->SelectObject(ft);

	CString str;
	GetWindowText(str);
	DrawText(dc->m_hDC, str, str.GetLength(), rt, DT_LEFT | DT_VCENTER);

	// 删除对象
	DeleteDC(hMemDC);
	SelectObject(hMemDC, lBitmap);
	DeleteObject(lBitmap);
	delete pImageGraphics;

	ReleaseDC(dc);
	DeleteObject(ft);
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

	if (MovePoint.x >= 5
		&& MovePoint.x <= ClientRect.right - 5
		&& MovePoint.y >= 0
		&& MovePoint.y <= TITLEBAR_HEIGHT
		)
	{
		return HTCAPTION;
	}


	if (MovePoint.x >= 0
		&& MovePoint.x <= 5

		&& MovePoint.y >= 0
		&& MovePoint.y <= 5
		)
	{
		return HTTOPLEFT;
	}
	if (MovePoint.x >= 0
		&& MovePoint.x <= 5
		&& MovePoint.y >= 5
		&& MovePoint.y <= ClientRect.bottom - 5
		)
	{
		return HTLEFT;
	}

	if (MovePoint.x >= 0
		&& MovePoint.x <= 5

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOMLEFT;
	}

	if (MovePoint.x >= 5
		&& MovePoint.x <= ClientRect.right - 5

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOM;
	}

	if (MovePoint.x >= ClientRect.right - 5
		&& MovePoint.x <= ClientRect.right

		&& MovePoint.y >= ClientRect.bottom - 5
		&& MovePoint.y <= ClientRect.bottom
		)
	{
		return HTBOTTOMRIGHT;
	}


	if (MovePoint.x >= ClientRect.right - 5
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

	if (MovePoint.x >= 5
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
CString SplicFullFilePath(CString strExeModuleName)
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
	return CDialogEx::OnEraseBkgnd(pDC);
}

// 结束时清理对应内存
COwnerDrawWindowDlg::~COwnerDrawWindowDlg()
{
}
