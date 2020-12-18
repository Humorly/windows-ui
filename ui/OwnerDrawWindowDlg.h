
// OwnerDrawWindowDlg.h : 头文件
//

#pragma once

#include "TransparentMake.h"
#include "ImageButton.h"

#include <memory>

// 最小化、最大化、还原、关闭按钮
#define		WIDGIT_BUTTON_NUM					4

#define MINI_BTN_PATH_NOR			_T("img\\btn\\min.png")
#define MINI_BTN_PATH_HOVER			_T("img\\btn\\min_h.png")
#define MINI_BTN_PATH_DOWN			_T("img\\btn\\min_d.png")
										
#define MAX_BTN_PATH_NOR			_T("img\\btn\\max.png")
#define MAX_BTN_PATH_HOVER			_T("img\\btn\\max_h.png")
#define MAX_BTN_PATH_DOWN			_T("img\\btn\\max_d.png")
										
#define RESTORE_BTN_PATH_NOR		_T("img\\btn\\restore.png")
#define RESTORE_BTN_PATH_HOVER		_T("img\\btn\\restore_h.png")
#define RESTORE_BTN_PATH_DOWN		_T("img\\btn\\restore_d.png")
										
#define QUIT_BTN_PATH_NOR			_T("img\\btn\\close.png")
#define QUIT_BTN_PATH_HOVER			_T("img\\btn\\close_h.png")
#define QUIT_BTN_PATH_DOWN			_T("img\\btn\\close_d.png")

#define WINDOW_BACKGROUND			_T("img\\window\\back.png")

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
	virtual ~COwnerDrawWindowDlg();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 创建几个BUTTON
	std::shared_ptr<CImageButton> m_pWidgitBtn[WIDGIT_BUTTON_NUM];
	// 背景图片
	std::shared_ptr<Image> m_pBackgroundImage;
	// 桌面最大化位置
	CRect m_rcRestoreArea;

	// 初始按钮
	int InitImageButton();
	// 更新控件位置
	void RefreshWidget();

	// 绘制窗体
	void DrawOwnerWindow();

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
	afx_msg LRESULT OnNcHitTest(CPoint point);
	LRESULT CalcWindowHitWhere();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
