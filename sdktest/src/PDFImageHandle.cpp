#include "../include/PDFImageHandle.h"
#include "../include/PDFDocHandle.h"
#include "../../include/pdf/fpdf_extstd.h"
#include "time.h"
#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

void getbitmapInfo(string bitmapName);

const int Get_BM_Info = 1;

FS_RESULT PDFImageHandler::ImageHandle(string strFileName, int type)
{
	FS_RESULT ret = false;
	switch(type)
	{
		case Get_BM_Info: PDFImageHandler::GetBitmapinfo(strFileName);
	}
    return ret;
}

void PDFImageHandler::GetBitmapinfo(string strFile){
	getbitmapInfo(strFile);
}

void getbitmapInfo(string bitmapName)
{
	if(!FSDK_IsSupportedImageFile(bitmapName.c_str())) 
		return ;
	CAutoImage autoImage((bitmapName).c_str(), "rb");
	FS_RESULT ret = autoImage.LoadImage();
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		return;
	}
	FS_INT32 iframecount = 0;
	ret = FSCRT_Image_CountFrames(autoImage.GetImage(), &iframecount);
	if ( FSCRT_ERRCODE_SUCCESS != ret)
		return;
	
	if( iframecount >0)
	{
		FSCRT_BITMAP dstDib = NULL;
		ret = FSCRT_Image_LoadFrame(autoImage.GetImage(), 0);
		if(ret != FSCRT_ERRCODE_SUCCESS){
			FSDK_OutputLog("Failure: In function FSCRT_Image_LoadFrame with error code %d.\r\n", ret);
			return;
		}
			
		//get current Fram Bitmap 
		ret = autoImage.GetCurrentFramBitmap();
		if(ret != FSCRT_ERRCODE_SUCCESS){
			return;
		}
		FSCRT_BITMAPINFO *bitmapInfo=NULL;
		FS_DWORD size = 0;
		FSCRT_BITMAP BMP = autoImage.GetBitmap();
		FS_RESULT res = FSCRT_Bitmap_GetBitmapInfo(BMP, NULL, &size);//get  size
		if(res != 0)
		{
			printf("falied to get size");
		}
		bitmapInfo = (FSCRT_BITMAPINFO *)malloc(size);// create a new  memory
		res = FSCRT_Bitmap_GetBitmapInfo(BMP, bitmapInfo, &size);
		if(res == 0){
			printf("success\n");
			fflush(stdout);
			FS_INT32 nWidth = 0, nHeight = 0;
			FS_INT32 format;
			FSCRT_Bitmap_GetSize(BMP, &nWidth, &nHeight);
	        FSCRT_Bitmap_GetFormat(BMP, &format);	
			PDFDocHandler test;
			test.InitConsoleWindow();
			printf("size=%d, width=%d, height=%d", bitmapInfo->bmiHeader.size, bitmapInfo->bmiHeader.width ,bitmapInfo->bmiHeader.height);	
		}
	}
}