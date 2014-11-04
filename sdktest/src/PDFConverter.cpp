#include "../include/PDFConverter.h"
#include "../include/PDFDocHandle.h"
#include "../../include/pdf/fpdf_extstd.h"
#include "time.h"
#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

FS_RESULT GetBitmapByRenderer(string testfile, FS_INT32 imageType);
FSCRT_IMAGE GetImageFromMemory(string filename);
int ImgGeneratePDF(FSCRT_IMAGE image, int rotateangle);
FS_RESULT DeleteAndSave(string filename);
void getbitmapInfo(string bitmapName);


const int IMG_2_PDF = 1;
const int IMG_2_PDF_R90 = 10;
const int IMG_2_PDF_R180 = 11;
const int IMG_2_PDF_R270 = 12;
const int PDF_2_TIF = 2;
const int PDF_2_BMP = 6;
const int PDF_2_PNG = 7;
const int PDF_2_JPG = 8;
const int PDF_2_JPX = 9;


FS_RESULT PDFConverter::Generate(string strFileName, int type)
{
	FS_RESULT ret = false;
	switch (type)
	{
	case IMG_2_PDF:
		ret = PDFConverter::GeneratePDF(strFileName, 0);
		break;
	case IMG_2_PDF_R90:
		ret = PDFConverter::GeneratePDF(strFileName, 90);
		break;
	case IMG_2_PDF_R180:
		ret = PDFConverter::GeneratePDF(strFileName, 180);
		break;
	case IMG_2_PDF_R270:
		ret = PDFConverter::GeneratePDF(strFileName, 270);;
		break;
	case PDF_2_TIF:
		ret = PDFConverter::GenerateImage(strFileName, FSCRT_IMAGETYPE_TIF);;
		break;
	case PDF_2_BMP:
		ret = PDFConverter::GenerateImage(strFileName, FSCRT_IMAGETYPE_BMP);;
		break;
	case PDF_2_PNG:
		ret = PDFConverter::GenerateImage(strFileName, FSCRT_IMAGETYPE_PNG);;
		break;
	case PDF_2_JPG:
		ret = PDFConverter::GenerateImage(strFileName, FSCRT_IMAGETYPE_JPG);
		break;
	case PDF_2_JPX:
		ret = PDFConverter::GenerateImage(strFileName, FSCRT_IMAGETYPE_JPX);
		break;
	}
	return ret;
}


FS_RESULT PDFConverter::GeneratePDF(string strFileName, int rotateangle)
{
	FSCRT_IMAGE image = GetImageFromMemory(strFileName);
	ImgGeneratePDF(image,rotateangle);
	return true;
}

FS_RESULT PDFConverter::GenerateImage(string strFile, FS_INT32 imageType)
{

	FS_RESULT res = GetBitmapByRenderer(strFile, imageType);
	return res;
}






FS_RESULT PageToBitmap(FSCRT_PAGE page, FS_INT32 imagetype)
{
	FSCRT_BITMAP m_bitmap;
	//Get the given page's size.
	FS_FLOAT width = 0, height = 0;
	FS_RESULT ret = FSPDF_Page_GetSize(page, &width, &height);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		FSDK_OutputLog("Failure: In function FSPDF_Page_GetSize with error code %d.\r\n", ret);
		return ret;
	}

	width  = width * 200 / 72.0f + 0.5f;
	height = height * 200 / 72.0f + 0.5f;

	//Get a bmp handler to hold bmp data from rendering progress.
	ret = FSCRT_Bitmap_Create((FS_INT32)width, (FS_INT32)height, FSCRT_BITMAPFORMAT_24BPP_RGB, NULL, 0, &m_bitmap);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		FSDK_OutputLog("Failure: In function FSCRT_Bitmap_Create with error code %d.\r\n", ret);
		return ret;
	}
		
	//Set rect area and color space of bitmap.
	FSCRT_RECT rect = {0, 0, (FS_INT32)width, (FS_INT32)height};
	ret = FSCRT_Bitmap_FillRect(m_bitmap, FSCRT_ARGB_Encode(0xff, 0xff, 0xff, 0xff), &rect);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		FSDK_OutputLog("Failure: In function FSCRT_Bitmap_FillRect with error code %d.\r\n", ret);
		return ret;
	}

	//Get the page's matrix.
	FSCRT_MATRIX mt;
	ret = FSPDF_Page_GetMatrix(page, 0, 0, (FS_INT32)width, (FS_INT32)height, 0, &mt);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		FSDK_OutputLog("Failure: In function FSPDF_Page_GetMatrix with error code %d.\r\n", ret);
		return ret;
	}

	//Create a renderer on the given bitmap.
	FSCRT_RENDERER renderer;
	ret = FSCRT_Renderer_CreateOnBitmap(m_bitmap, &renderer);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		FSDK_OutputLog("Failure: In function FSCRT_Renderer_CreateOnBitmap with error code %d.\r\n", ret);
		return ret;
	}

	//Create a render context and render a page to get a bmp later.
	FSPDF_RENDERCONTEXT rendercontext;
	ret = FSPDF_RenderContext_Create(&rendercontext);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		//Release render
		FSCRT_Renderer_Release(renderer);
		FSDK_OutputLog("Failure: In function FSPDF_RenderContext_Create with error code %d.\r\n", ret);
		return ret;
	}

	//Set the matrix of the given render context.
	ret = FSPDF_RenderContext_SetMatrix(rendercontext, &mt);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		//Release render
		FSCRT_Renderer_Release(renderer);
		//Release render context
		FSPDF_RenderContext_Release(rendercontext);
		FSDK_OutputLog("Failure: In function FSPDF_RenderContext_SetMatrix with error code %d.\r\n", ret);
		return ret;
	}

	//Start to render with the given render context, renderer, page to get the render progress.
	DWORD dwStartCount = ::GetTickCount();
	FSCRT_PROGRESS renderProgress = NULL;

	ret = FSPDF_RenderContext_StartPage(rendercontext, renderer, page,FSPDF_PAGERENDERFLAG_NORMAL, &renderProgress);
	if (ret != FSCRT_ERRCODE_SUCCESS) 
	{
		//Release render
		FSCRT_Renderer_Release(renderer);
		//Release render context
		FSPDF_RenderContext_Release(rendercontext);
		FSDK_OutputLog("Failure: In function FSPDF_RenderContext_StartPage with error code %d.\r\n", ret);
		return ret;
	}
	
	//Continue to render if it's not completed.
	ret = FSCRT_Progress_Continue(renderProgress, NULL);
	printf("time is %d \n", ::GetTickCount()- dwStartCount);


	if (ret != FSCRT_ERRCODE_FINISHED) 
	{
		FSDK_OutputLog("Failure: In function FSCRT_Progress_Continue with error code %d.\r\n", ret);
	}

	if (ret == FSCRT_ERRCODE_FINISHED) 
	{
		ret = FSCRT_ERRCODE_SUCCESS;
		FSDK_OutputLog("Success: Render the page to bitmap.\r\n");
	}

	const char* fileName;

	switch (imagetype)
	{
	case FSCRT_IMAGETYPE_BMP:
		fileName = "Generated.bmp";;
		break;
    case FSCRT_IMAGETYPE_JPG:
		fileName = "Generated.jpg";;
		break;
	case FSCRT_IMAGETYPE_PNG:
		fileName = "Generated.png";;
		break;
	case FSCRT_IMAGETYPE_TIF:
		fileName = "Generated.tif";;
		break;
	case FSCRT_IMAGETYPE_JPX:
		fileName = "Generated.jpx";;
		break;
	}
	FSDK_SaveImageFile(m_bitmap, imagetype, fileName);
	//Release render progress 
	FSCRT_Progress_Release(renderProgress);
	
	//Release render
	FSCRT_Renderer_Release(renderer);
	//Release render context
	FSPDF_RenderContext_Release(rendercontext);
	return ret;
}
FS_RESULT GetBitmapByRenderer(string testfile, FS_INT32 imagetype)
{
	string strFile = testfile;
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");

	FSCRT_DOCUMENT doc;
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load PDF document\n");
		return ret;
	}

	FSCRT_PAGE page = NULL;
	PDFDocHandler GBBR;
	ret = GBBR.LoadPage(doc, 0, &page);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load a given page.\n");
		return ret;
	}

	PageToBitmap(page, imagetype);

	FSPDF_Doc_Close(doc);
	return ret;
}
FSCRT_IMAGE GetImageFromMemory(string filename)
{
	string res = filename;
	const char *cstr = res.c_str();
	FSCRT_FILE imageFile = FSDK_OpenFile(cstr, "rb");
	if (!imageFile)
		NULL;

	//Follow the same procedure as before
	FSCRT_IMAGE image = NULL;
	FS_RESULT ret = FSCRT_Image_LoadFromFile(imageFile, &image);
	return ret == FSCRT_ERRCODE_SUCCESS? image : NULL;
}
int ImgGeneratePDF(FSCRT_IMAGE image, int rotateangle)
{
	if (image == NULL)
		return -1;
	int start = clock(), end = 0;
	FS_INT32 nFrameNum = 0;
	// Load an image file to get the image object and frame number
	FS_RESULT ret = FSCRT_Image_CountFrames(image, &nFrameNum);
	if (FSCRT_ERRCODE_SUCCESS != ret || nFrameNum < 1){
		return ret;
	}

	FSCRT_DOCUMENT pdfDoc = NULL;
	ret = FSPDF_Doc_Create(&pdfDoc);
	if (FSCRT_ERRCODE_SUCCESS != ret){
		return ret;
	}
	ret = FSCRT_Image_LoadFrame(image, 0);
	FS_INT32 PageWidth, PageHeight;
	ret = FSCRT_Image_GetCurrentFrameSize(image, &PageWidth, &PageHeight);
	float pw = (float)PageWidth * 72/200;
	float ph = (float)PageHeight * 72/200;

	//for 90 and 270

	if(rotateangle == 90 || rotateangle == 270){
		float temp = pw;
		pw = ph;
		ph = temp;
	}
	for (int i =0 ;i<1; i++){
		for (FS_INT32 i = 0; i < nFrameNum; i++)
		{
			FSCRT_PAGE page = NULL;
			ret = FSPDF_Page_Create(pdfDoc, i, &page);
			if (ret != FSCRT_ERRCODE_SUCCESS)
			{
				return -1;
			}
					// Set page size
		
		// Create image object based on a page
			FSPDF_PAGEOBJECT imageObj = NULL;
			ret = FSPDF_ImageObject_Create(page, &imageObj);
			if (FSCRT_ERRCODE_SUCCESS != ret){
				return ret;
			}

			ret = FSCRT_Image_LoadFrame(image, i);
			if (FSCRT_ERRCODE_SUCCESS != ret){
				return ret;
			}

			ret = FSPDF_ImageObject_SetImage(page, imageObj, image);
			if (FSCRT_ERRCODE_SUCCESS != ret){
				FSPDF_PageObject_Release(page, imageObj);
				return ret;
			}

			// Get the size of current image
			FS_INT32 width = 0;
			FS_INT32 height = 0; 
			ret = FSCRT_Image_GetCurrentFrameSize(image, &width, &height);
			if (FSCRT_ERRCODE_SUCCESS != ret){
				return ret;
			}

			ret = FSPDF_Page_SetSize(page, pw, ph);

			// Compose an image matrix based on calculation as above
			FSCRT_MATRIX imageMatrix;
			if(rotateangle == 90 || rotateangle == 270){
				FSCRT_MATRIX Matrix = {ph, 0, 0, pw, 0, 0};
				imageMatrix = Matrix;
			}else {
				FSCRT_MATRIX Matrix = {pw, 0, 0, ph, 0, 0};
				imageMatrix = Matrix;
			}

			FSCRT_MATRIX matrix = imageMatrix;
			if(rotateangle == 90){ //rotate 90
					matrix.a = imageMatrix.b * (-1);
					matrix.b = imageMatrix.a;
					matrix.c = imageMatrix.d * (-1);
					matrix.d = imageMatrix.c;
					matrix.e = imageMatrix.f * (-1);
					matrix.f = imageMatrix.e;
					matrix.e += pw;
			}
			if(rotateangle == 180){
					matrix.a = imageMatrix.a * (-1);
					matrix.b = imageMatrix.b * (-1);
					matrix.c = imageMatrix.c * (-1);
					matrix.d = imageMatrix.d * (-1);
					matrix.e = imageMatrix.e * (-1);
					matrix.f = imageMatrix.f * (-1);

					matrix.e += pw;
					matrix.f += ph;
			}
			if(rotateangle == 270){
					matrix.a = imageMatrix.b;
					matrix.b = imageMatrix.a * (-1);
					matrix.c = imageMatrix.d;
					matrix.d = imageMatrix.c * (-1);
					matrix.e = imageMatrix.f;
					matrix.f = imageMatrix.e * (-1);
					matrix.f += ph;
			}
			ret = FSPDF_PageObject_SetMatrix(page, imageObj, &matrix);

			// Get page objects in a page and prepare to insert an image object
			FSPDF_PAGEOBJECTS pageObjs;
			ret = FSPDF_Page_GetPageObjects(page, &pageObjs);
			if (FSCRT_ERRCODE_SUCCESS != ret){
				FSPDF_PageObject_Release(page, imageObj);
				return ret;
			}

			// Insert an image object into page objects which in a page 
			ret = FSPDF_PageObjects_InsertObject(page, pageObjs, FSPDF_PAGEOBJECT_ALL, 1, imageObj);
			if (ret != FSCRT_ERRCODE_SUCCESS){
				FSPDF_PageObject_Release(page, imageObj);
				return ret;
			}

			// Generate contents which are covered in page objects
			ret = FSPDF_PageObjects_GenerateContents(page, pageObjs);
			if (ret != FSCRT_ERRCODE_SUCCESS){
				FSPDF_PageObject_Release(page, imageObj);
				return ret;
			}

			FSPDF_Page_Clear(page);
		}
	}
	end  = clock();
	PDFDocHandler test;
	test.InitConsoleWindow();
	printf("Time is %d", end - start);
	FSDK_SavePDFFile(pdfDoc, "output.pdf", FSPDF_SAVEFLAG_INCREMENTAL | FSPDF_SAVEFLAG_OPTIMIZE);
	FSPDF_Doc_Close(pdfDoc);
}




