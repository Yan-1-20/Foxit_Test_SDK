#include <afx.h>
#include <cstring>
#include "fgsdk_common.h"

class PDFImageHandler
{
public:
	PDFImageHandler(){}
	~PDFImageHandler(){}
	FS_RESULT ImageHandle(string strFileName, int ty);

private:
	void GetBitmapinfo(string strFile);
};