
// TestWindowsUIDlg.h: 头文件
//

#pragma once
#include "OwnerDrawWindowDlg.h"
#include "CButtonST.h"
#include "OwnerDrawRadioButton.h"
#include "OwnerDrawCheckButton.h"
#include "OwnerDrawCombox.h"

// CTestWindowsUIDlg 对话框
class CTestWindowsUIDlg : public COwnerDrawWindowDlg
{
// 构造
public:
	CTestWindowsUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTWINDOWSUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CButtonST m_btTest;
	COwnerDrawRadioButton m_rdTest;
	COwnerDrawCheckButton m_ckTest;
	COwnerDrawCombox m_cbTest;
};
