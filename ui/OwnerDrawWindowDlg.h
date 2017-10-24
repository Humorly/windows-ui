
// OwnerDrawWindowDlg.h : 头文件
//

#pragma once

#include "ImageButton.h"

// 最小化、最大化、还原、关闭按钮
#define		WIDGIT_BUTTON_NUM					4

#define MINI_BTN_PATH_NOR			_T("img\\btn\\btn_min_normal.png")
#define MINI_BTN_PATH_HOVER			_T("img\\btn\\btn_min_hover.png")
#define MINI_BTN_PATH_DOWN			_T("img\\btn\\btn_min_down.png")
										
#define MAX_BTN_PATH_NOR			_T("img\\btn\\btn_max_normal.png")
#define MAX_BTN_PATH_HOVER			_T("img\\btn\\btn_max_hover.png")
#define MAX_BTN_PATH_DOWN			_T("img\\btn\\btn_max_down.png")
										
#define RESTORE_BTN_PATH_NOR		_T("img\\btn\\btn_max_restore_normal.png")
#define RESTORE_BTN_PATH_HOVER		_T("img\\btn\\btn_max_restore_hover.png")
#define RESTORE_BTN_PATH_DOWN		_T("img\\btn\\btn_max_restore_down.png")
										
#define QUIT_BTN_PATH_NOR			_T("img\\btn\\btn_quit_normal.png")
#define QUIT_BTN_PATH_HOVER			_T("img\\btn\\btn_quit_hover.png")
#define QUIT_BTN_PATH_DOWN			_T("img\\btn\\btn_quit_down.png")

#define MINI_BTN_ID					10000
#define MAX_BTN_ID					10001
#define MAX_RESTORE_BTN_ID			10002
#define QUIT_BTN_ID					10003

// COwnerDrawWindowDlg 对话框
class COwnerDrawWindowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COwnerDrawWindowDlg)
// 构造
public:
	COwnerDrawWindowDlg(UINT nIDTemplate, CWnd* pParent = NULL);			// 标准构造函数

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 创建几个BUTTON
	CImageButton * m_pWidgitBtn[WIDGIT_BUTTON_NUM];

	int InitImageButton();

	// 绘制窗体
	void DrawWindow();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnBnClickedMini();
	afx_msg void OnBnClickedMax();
	afx_msg void OnBnClickedRestore();
	afx_msg void OnBnClickedQuit();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	LRESULT CalcWindowHitWhere();


	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
