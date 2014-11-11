
// sdktestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sdktest.h"
#include "sdktestDlg.h"
#include "afxdialogex.h"
#include "include/PDFConverter.h"
#include "include/PDFDocHandle.h"
#include "include/PDFImageHandle.h"
#include <string>

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsdktestDlg dialog




CsdktestDlg::CsdktestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsdktestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsdktestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
}

BEGIN_MESSAGE_MAP(CsdktestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TIF2PDF, &CsdktestDlg::OnBnClickedBtnImg2pdf)
	ON_BN_CLICKED(IDC_BTN_PDF2TIFF, &CsdktestDlg::OnBnClickedBtnPdf2tiff)
	ON_BN_CLICKED(IDC_BTN_DELETEPAGE, &CsdktestDlg::OnBnClickedBtnDeletepage)
	ON_BN_CLICKED(IDC_BTN_ISPDFA, &CsdktestDlg::OnBnClickedBtnIspdfa)
	ON_BN_CLICKED(IDC_BTN_GetBitmapInfo, &CsdktestDlg::OnBnClickedBtnGetbitmapinfo)
	ON_BN_CLICKED(IDC_BTN_PDF2BMP, &CsdktestDlg::OnBnClickedBtnPdf2bmp)
	ON_BN_CLICKED(IDC_BTN_PDF2PNG, &CsdktestDlg::OnBnClickedBtnPdf2png)
	ON_BN_CLICKED(IDC_BTN_PDF2JPG, &CsdktestDlg::OnBnClickedBtnPdf2jpg)
	ON_BN_CLICKED(IDC_BTN_PDF2JPX, &CsdktestDlg::OnBnClickedBtnPdf2jpx)
	ON_BN_CLICKED(IDC_BTN_IMG2PDF_R90, &CsdktestDlg::OnBnClickedBtnImg2pdfR90)
	ON_BN_CLICKED(IDC_BTN_IMG2PDF_R180, &CsdktestDlg::OnBnClickedBtnImg2pdfR180)
	ON_BN_CLICKED(IDC_BTN_IMG2PDF_R270, &CsdktestDlg::OnBnClickedBtnImg2pdfR270)
	ON_BN_CLICKED(IDC_BTN_TRIMPDF, &CsdktestDlg::OnBnClickedBtnTrimpdf)
	ON_BN_CLICKED(IDC_BTN_GetEncrypt, &CsdktestDlg::OnBnClickedBtnGetencrypt)
	ON_BN_CLICKED(IDC_BTN_PDFCS, &CsdktestDlg::OnBnClickedBtnPdfcs)
	ON_BN_CLICKED(IDC_BTN_SGDoc, &CsdktestDlg::OnBnClickedBtnSgdoc)
	ON_WM_DESTROY()
	
	ON_CBN_DROPDOWN(IDC_COMBO3, &CsdktestDlg::OnCbnDropdownCombo3)
	ON_CBN_DROPDOWN(IDC_COMBO5, &CsdktestDlg::OnCbnDropdownCombo5)
	ON_BN_CLICKED(IDC_BUTTON2, &CsdktestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CsdktestDlg message handlers

BOOL CsdktestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CsdktestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsdktestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsdktestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsdktestDlg::OnBnClickedBtnImg2pdf()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		test.Generate(strStd, 1);
		ShellExecute(this->m_hWnd,_T("open"),_T("output.pdf"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}
	fileName.ReleaseBuffer();
}

void CsdktestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	
}

void CsdktestDlg::OnBnClickedBtnPdf2tiff()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;


	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		int index=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
		CString Quality;
		((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(index,Quality);
		int QA =200;

		if(Quality == "low") QA =200;
		else if(Quality == "Medium") QA =700;
		else if(Quality == "High") QA =1200;

		test.Generate_QA_Img(strStd, 2, QA);

		ShellExecute(this->m_hWnd,_T("open"),_T("Generated.tif"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnDeletepage()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		
		int index=((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();
		CString Page_num;
		((CComboBox*)GetDlgItem(IDC_COMBO3))->GetLBText(index,Page_num);
		int bitcount=_wtoi(Page_num);	

		test.DocHandle_Delete(strStd, bitcount);
 
        ShellExecute(this->m_hWnd,_T("open"),_T("After_Delete.pdf"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnIspdfa()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		test.DocHandle(strStd, 2);
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnGetbitmapinfo()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, 
		L".bmp", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.bmp|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFImageHandler test;
		test.ImageHandle(strStd, 1);
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnPdf2bmp()
{
	// TODO: Add your control notification handler code here
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		int index=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
		CString Quality;
		((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(index,Quality);
		int QA =200;
		if(Quality == "low") QA =200;
		else if(Quality == "Medium") QA =700;
		else if(Quality == "High") QA =1200;
		test.Generate_QA_Img(strStd, 6, QA);

		ShellExecute(this->m_hWnd,_T("open"),_T("Generated.bmp"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnPdf2png()
{
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		int index=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
		CString Quality;
		((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(index,Quality);
		int QA =200;
		if(Quality == "low") QA =200;
		else if(Quality == "Medium") QA =700;
		else if(Quality == "High") QA =1200;
		test.Generate_QA_Img(strStd, 7, QA);

		ShellExecute(this->m_hWnd,_T("open"),_T("Generated.png"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnPdf2jpg()
{
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		int index=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
		CString Quality;
		((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(index,Quality);
		int QA =200;
		if(Quality == "low") QA =200;
		else if(Quality == "Medium") QA =700;
		else if(Quality == "High") QA =1200;
		test.Generate_QA_Img(strStd, 8, QA);

		ShellExecute(this->m_hWnd,_T("open"),_T("Generated.jpg"),NULL,NULL, SW_SHOW );
		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnPdf2jpx()
{
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;

		int index=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCurSel();
		CString Quality;
		((CComboBox*)GetDlgItem(IDC_COMBO5))->GetLBText(index,Quality);
		int QA =200;
		if(Quality == "low") QA =200;
		else if(Quality == "Medium") QA =700;
		else if(Quality == "High") QA =1200;
		test.Generate_QA_Img(strStd, 9, QA);

		//Finalize PDF module.
		FSDK_PDFModule_Finalize();
		//Finalize SDK library.
		FSDK_FinalizeLibrary();
	}

	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnImg2pdfR90()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 10);
		ShellExecute(this->m_hWnd,_T("open"),_T("output.pdf"),NULL,NULL, SW_SHOW );
		FSDK_PDFModule_Finalize();
		FSDK_FinalizeLibrary();
	}
	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnImg2pdfR180()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 11);
		ShellExecute(this->m_hWnd,_T("open"),_T("output.pdf"),NULL,NULL, SW_SHOW );
		FSDK_PDFModule_Finalize();
		FSDK_FinalizeLibrary();
	}
	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnImg2pdfR270()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();

		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 12);
		ShellExecute(this->m_hWnd,_T("open"),_T("output.pdf"),NULL,NULL, SW_SHOW );
		FSDK_PDFModule_Finalize();
		FSDK_FinalizeLibrary();
	}
	fileName.ReleaseBuffer();
}



void CsdktestDlg::OnBnClickedBtnTrimpdf()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();

		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		test.DocHandle(strStd, 3);
		ShellExecute(this->m_hWnd,_T("open"),_T("Trim.pdf"),NULL,NULL, SW_SHOW );
		FSDK_PDFModule_Finalize();
		FSDK_FinalizeLibrary();
	}
	fileName.ReleaseBuffer();
}


void CsdktestDlg::OnBnClickedBtnGetencrypt()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();
		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	

		CString s;
		m_edit1.GetWindowText(s);
		CT2CA pszName(s);
		std::string m_NameStd(pszName); 


		PDFDocHandler test;
		test.DocHandle_PWD(strStd, 4, m_NameStd);
		FSDK_PDFModule_Finalize();
		FSDK_FinalizeLibrary();
		//Sleep(1000);
		//ShellExecute(this->m_hWnd,_T("open"),_T("pfu_encrypt_output.pdf"),NULL,NULL, SW_SHOW );
	}
	fileName.ReleaseBuffer();
}




void CsdktestDlg::OnBnClickedBtnPdfcs()
{
	CFileDialog fileDlg(TRUE, 
		L".*", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.*|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();

		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		test.DocHandle(strStd, 6);
	}
	fileName.ReleaseBuffer();
}

void CsdktestDlg::OnBnClickedBtnSgdoc()
{
	CFileDialog fileDlg(TRUE, 
		L".pdf", 
		NULL, 
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		L"All Supported DEM Types|*.pdf|"
		);
	CString fileName;
	const int c_cMaxFiles = 100;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	fileDlg.GetOFN().nMaxFile = c_cbBuffSize;


	

	if (fileDlg.DoModal() == IDOK)	{
		if (!FSDK_InitializeLibray(true))
		{
			return ;
		}

		//Initialize PDF module
		if(!FSDK_PDFModule_Initialize())
		{
			FSDK_FinalizeLibrary();
			return ;
		}
		CString str = fileDlg.GetFileName();

		fileName.ReleaseBuffer();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		test.DocHandle(strStd, 5);
	}
	fileName.ReleaseBuffer();
}





void CsdktestDlg::OnCbnDropdownCombo3()
{
	// TODO: Add your control notification handler code here
	int iCount=((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCount();
	CString strTemp;
	if(iCount<1){
		for(int i=0;i<=9;i++)
		{
		   strTemp.Format(L"%d",i);
		   ((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(strTemp);
		}
  }

}


void CsdktestDlg::OnCbnDropdownCombo5()
{
	// TODO: Add your control notification handler code here
	int iCount=((CComboBox*)GetDlgItem(IDC_COMBO5))->GetCount();

	if(iCount<1){
		((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T("High"));
		((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T("Medium"));
		((CComboBox*)GetDlgItem(IDC_COMBO5))->AddString(_T("Low"));
	}
}





void CsdktestDlg::OnBnClickedButton2()
{
	CString s;
	m_edit1.GetWindowText(s);
	float x = _wtof(s);
	if (x >= 0) {
		x = sqrt(x);
		s.Format(_T("%f"),sqrt(x));
		m_edit1.SetWindowText(s);  
	}
	else {
		MessageBox(_T("Please Enter a positive number"));
		m_edit1.SetWindowText(_T(""));
		m_edit1.SetFocus();
	}
}
