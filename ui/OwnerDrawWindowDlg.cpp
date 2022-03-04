
// OwnerDrawWindowDlg.cpp : ʵ���ļ�
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
	// �����ĸ���ť
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


// COwnerDrawWindowDlg ��Ϣ�������

BOOL COwnerDrawWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// ��ʼGDI+
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COwnerDrawWindowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COwnerDrawWindowDlg::OnPaint()
{
	DrawOwnerWindow();
	CDialogEx::OnPaint();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COwnerDrawWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL COwnerDrawWindowDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	return CDialogEx::PreTranslateMessage(pMsg);
}

// ��Ч
BOOL COwnerDrawWindowDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	return CDialogEx::PreCreateWindow(cs);
}

// ���
void COwnerDrawWindowDlg::OnBnClickedMax()
{
	// ����λ��
	GetWindowRect(&m_rcRestoreArea);

	CRect rcWorkArea;
	// ��ȡ������
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWorkArea, 0);
	MoveWindow(&rcWorkArea);

	m_pWidgitBtn[1]->ShowWindow(false);
	m_pWidgitBtn[2]->ShowWindow(true);
}

// ��ԭ
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
	// ���͹ر���Ϣ���̳д���
	SendMessage(WM_CLOSE, 0, 0);
}

void COwnerDrawWindowDlg::OnBnClickedMini()
{
	ShowWindow(SW_MINIMIZE);
}

#define WINDOW_BTN_WIDTH			48
#define WINDOW_BTN_HEIGHT			32

// ��ʼ��ť
int COwnerDrawWindowDlg::InitImageButton()
{
	// �����ĸ���ť
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
	// ������ť
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

// ˢ�¿ؼ�
void COwnerDrawWindowDlg::RefreshWidget()
{
	RECT rect;
	GetClientRect(&rect);
	CString str[] = { _T(" "), _T(" "), _T(" "), _T(" ") };

	int nId = MINI_BTN_ID;
	// ������ť
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

	//// ���ҿؼ���ˢ��֮
	//HWND hWndChild = ::GetWindow(m_hWnd, GW_CHILD);
	//// ��������ؼ���ˢ��֮
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

// ���ƴ���
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
	
	// �������滭��
	hMemDC = CreateCompatibleDC(dc->m_hDC);
	lBitmap = CreateCompatibleBitmap(dc->m_hDC, rc.right, rc.bottom);
	HBITMAP hPrevBitmap = (HBITMAP)SelectObject(hMemDC, lBitmap);
	SetBkMode(hMemDC, TRANSPARENT);
	SetBkColor(hMemDC, TRANSPARENT);


	FillRect(hMemDC, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	// GDI��������豸����
	Graphics* pImageGraphics;
	pImageGraphics = Graphics::FromHDC(hMemDC);
	VERIFY(pImageGraphics);

	// ����״̬����ͼƬ
	RectF rRect(static_cast<Gdiplus::REAL>(rc.left), static_cast<Gdiplus::REAL>(rc.top), static_cast<Gdiplus::REAL>(rc.right - rc.left), static_cast<Gdiplus::REAL>(rc.bottom - rc.top));
	//if (m_pBackgroundImage)
	//	pImageGraphics->DrawImage(m_pBackgroundImage.get(), rRect, 0, 0, static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetWidth()), static_cast<Gdiplus::REAL>(m_pBackgroundImage->GetHeight()), UnitPixel);

	CRect rt;
	rt = CRect(14, 8, 184, 36);
	// ׼������
	HFONT ft = CreateFont((rt.bottom - rt.top) * 3 / 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("΢���ź�"));
	HFONT hOldFont = (HFONT)SelectObject(hMemDC, ft);

	CString str;
	GetWindowText(str);
	DrawText(hMemDC, str, str.GetLength(), rt, DT_LEFT | DT_VCENTER);

	GetClientRect(&rt);
	DrawWindowRectUi(hMemDC, rt);

	// ��������
	BitBlt(dc->m_hDC, 0, 0, rc.right, rc.bottom, hMemDC, 0, 0, SRCCOPY);

	// ɾ������
	SelectObject(hMemDC, hOldFont);
	SelectObject(hMemDC, hPrevBitmap);
	DeleteObject(lBitmap);
	delete pImageGraphics;

	ReleaseDC(dc);
	DeleteObject(ft);
	DeleteDC(hMemDC);
}

// �����趨
LRESULT COwnerDrawWindowDlg::OnNcHitTest(CPoint point)
{
	// ��ȡ���
	LRESULT lResult = CalcWindowHitWhere();
	// ���¼���λ��
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

// ������
void COwnerDrawWindowDlg::OnSize(UINT nType, int cx, int cy)
{
	static bool bMiniSize = false;
	if (!bMiniSize)
		bMiniSize = (SIZE_MINIMIZED == nType);

	// ��С���Ƿ���
	if (!bMiniSize)
	{
		// ����С���µ�״̬���
		if (!IsZoomed())
		{
			// �޸İ�ť
			if (nullptr != m_pWidgitBtn[2])
				m_pWidgitBtn[2]->ShowWindow(false);
			if (nullptr != m_pWidgitBtn[1])
				m_pWidgitBtn[1]->ShowWindow(true);
		}
	}

	bMiniSize = (SIZE_MINIMIZED == nType);

	// ˢ�¿ؼ�λ��
	RefreshWidget();
}

//  ƴ������·��
CString COwnerDrawWindowDlg::SplicFullFilePath(CString strExeModuleName)
{
	// ��ȡ��ǰ·��
	// ׼��д�ļ�
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

// ����ʱ�����Ӧ�ڴ�
COwnerDrawWindowDlg::~COwnerDrawWindowDlg()
{
}

// ����������
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
		// ����λ��
		GetWindowRect(&m_rcRestoreArea);

		CRect rcWorkArea;
		// ��ȡ������
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
	//// ��ԭ����
	//if (clinet_hit_flag_ && nullptr != m_pWidgitBtn[2] && m_pWidgitBtn[2]->IsWindowVisible())
	//{
	//	OutputDebugString(TEXT("restore"));

	//	// ��ȡ����ڴ����еĸ߶�
	//	RECT ClientRect;
	//	GetClientRect(&ClientRect);
	//	POINT MovePoint, NowPoint;
	//	GetCursorPos(&MovePoint);
	//	GetCursorPos(&NowPoint);
	//	ScreenToClient(&MovePoint);

	//	// ���ݸ߶ȵ���
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
	//// �ƶ�����
	//if (clinet_hit_flag_)
	//{
	//	// ��ȡ����ڴ����еĸ߶�
	//	CRect WindowRect;
	//	GetWindowRect(&WindowRect);
	//	// ���ݸ߶ȵ���
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

// �Ҽ�����
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

