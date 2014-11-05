
// sdktestDlg.h : header file
//

#pragma once


// CsdktestDlg dialog
class CsdktestDlg : public CDialogEx
{
// Construction
public:
	CsdktestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SDKTEST_DIALOG };

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
	afx_msg void OnBnClickedBtnImg2pdf();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnPdf2Tif();
	afx_msg void OnBnClickedBtnPdf2tiff();
	afx_msg void OnBnClickedBtnDeletepage();
	afx_msg void OnBnClickedBtnIspdfa();
	afx_msg void OnBnClickedBtnGetbitmapinfo();
	afx_msg void OnBnClickedBtnPdf2bmp();
	afx_msg void OnBnClickedBtnPdf2png();
	afx_msg void OnBnClickedBtnPdf2jpg();
	afx_msg void OnBnClickedBtnPdf2jpx();
	afx_msg void OnBnClickedBtnImg2pdfR90();
	afx_msg void OnBnClickedBtnImg2pdfR180();
	afx_msg void OnBnClickedBtnImg2pdfR270();
	afx_msg void OnBnClickedBtnTrimpdf();
	afx_msg void OnBnClickedBtnGetencrypt();
	afx_msg void OnBnClickedBtnPdfcs();
	afx_msg void OnBnClickedBtnSgdoc();
	afx_msg void OnCbnDropdownCombo3();
	afx_msg void OnCbnDropdownCombo5();
};
