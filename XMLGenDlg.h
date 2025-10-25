
// XMLGenDlg.h : header file
//

#pragma once


// CXMLGenDlg dialog
class CXMLGenDlg : public CDialogEx
{
// Construction
public:
	CXMLGenDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XMLGEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo4();
	CString m_Name;
	CString m_Date;
	CString m_ST;
	CString m_ET;
	CComboBox m_P;
	CComboBox m_TT;
	CComboBox m_TSD;
	CComboBox m_E;
	CComboBox m_A;
	CComboBox m_C;
	CString m_TN;
	CString m_V1;
	CString m_V2;
	CString m_V3;
	CString m_V4;
	CString m_V5;
	CString m_V6;
	CString m_V7;
	CString m_TD;
	CString m_V8;
	CString m_V9;
	CString m_V10;
	CString m_V11;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedPausebutton();
	afx_msg void OnBnClickedPlaybutton();
	afx_msg void OnNMCustomdrawVideoSlider(NMHDR* pNMHDR, LRESULT* pResult);
};
