#pragma once


// MineDlg 对话框

class MineDlg : public CDialog
{
	DECLARE_DYNAMIC(MineDlg)
	
public:
	MineDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MineDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
};
