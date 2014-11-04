#include <afx.h>
#include <cstring>
#include "fgsdk_common.h"

class PDFConverter
{
public:
	PDFConverter(){}
	~PDFConverter(){}

	FS_RESULT Generate(string strFileName, int ty);

private:
	FS_RESULT GeneratePDF(string strFileName, int rotateangle);
	FS_RESULT GenerateImage(string strFile, FS_INT32 imageType);
	
};