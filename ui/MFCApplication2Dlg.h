
// MFCApplication2Dlg.h: 头文件
//

#pragma once

#include "OwnerDrawWindowDlg.h"

// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public COwnerDrawWindowDlg
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 更新控件位置
	virtual void RefreshWidget();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// TODO: 在此添加额外的初始化代码
	std::shared_ptr<CImageButton> test_btn_ = nullptr;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
