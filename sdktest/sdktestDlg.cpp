
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
}

BEGIN_MESSAGE_MAP(CsdktestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TIF2PDF, &CsdktestDlg::OnBnClickedBtnImg2pdf)
	ON_WM_DESTROY()
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 2);
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFDocHandler test;
		test.DocHandle(strStd, 1);
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
		FS_RESULT ret;
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
		FS_RESULT ret;
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 6);
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 7);
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 8);
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
		FS_RESULT ret;
		CString str = fileDlg.GetFileName();
		CT2CA pszConvertedAnsiString (str);
		std::string strStd (pszConvertedAnsiString);	
		PDFConverter test;
		test.Generate(strStd, 9);
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
		PDFDocHandler test;
		test.DocHandle(strStd, 4);
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
