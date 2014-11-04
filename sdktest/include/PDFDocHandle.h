#include <afx.h>
#include <cstring>
#include "fgsdk_common.h"
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

class PDFDocHandler
{
public:
	PDFDocHandler(){}
	~PDFDocHandler(){}

	FS_RESULT DocHandle(string strFileName, int ty);
	FS_RESULT LoadPage(FSCRT_DOCUMENT doc, FS_INT32 index, FSCRT_PAGE *page )
	{
		FS_RESULT ret =  FSPDF_Doc_GetPage(doc, index, page);
		if(FSCRT_ERRCODE_SUCCESS != ret)
		{
			printf("Failed to get the page %d\n", index+1);
			return ret;
		}

		FSCRT_PROGRESS progress;
		ret = FSPDF_Page_StartParse(*page, FSPDF_PAGEPARSEFLAG_NORMAL, &progress);
		if (FSCRT_ERRCODE_SUCCESS != ret)
		{
			printf("Failed to parse pages.\n");
			return ret;
		}

		//Continue to parse page, without pausing.
		ret = FSCRT_Progress_Continue(progress, NULL);
		if (FSCRT_ERRCODE_FINISHED != ret)
		{
			printf("Failed to finish parsing progress! \n", ret);
		} else {
			ret = FSCRT_ERRCODE_SUCCESS;
			printf("Succeed to Parse a given PDF page! \n");
		}

		FSCRT_Progress_Release(progress);
		return ret;
	}
	void InitConsoleWindow()
	{
		int nCrt = 0;
		FILE* fp;
		AllocConsole();
		nCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		fp = _fdopen(nCrt, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	} 
private:
	FS_RESULT DeletePage(string strFile);
	FS_RESULT IsPDFA(string strFile);
	FS_RESULT TrimPDF(string strFile);
	FS_RESULT EncryPDF(string strFile);
	void SetGetTest(string strFile);
	FS_RESULT GetColorSpace(string strFile);
	
};