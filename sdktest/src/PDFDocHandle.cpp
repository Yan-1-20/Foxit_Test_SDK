#include "../include/PDFDocHandle.h"
#include "../../include/pdf/fpdf_extstd.h"
#include "time.h"
#include <string>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>


FS_RESULT DeleteAndSave(string filename);
FS_RESULT trimPDF(string strFile);
FS_RESULT GenerateEncryptPDF(string strFile);
void SetDocInfo(string pdfName);
void GetDocInfo(string pdfName);

const int Delete_a_Page = 1;
const int Is_a_PDFA = 2;
const int Trim_a_PDF = 3;
const int Encrypt_a_PDF = 4;
const int SGDoc_a_PDF = 5;
const int Get_Color_Space = 6;

FS_RESULT PDFDocHandler::DocHandle(string strFileName, int type)
{
	FS_RESULT ret = false;
	switch (type){
		case Delete_a_Page:
			ret = PDFDocHandler::DeletePage(strFileName);
			break;

		case Is_a_PDFA:
			ret = PDFDocHandler::IsPDFA(strFileName);
			break;
	
		case Trim_a_PDF:
			ret = PDFDocHandler::TrimPDF(strFileName);
			break;

		case Encrypt_a_PDF:
			ret = PDFDocHandler::EncryPDF(strFileName);
			break;

		case SGDoc_a_PDF:
			PDFDocHandler::SetGetTest(strFileName);
			break;

		case Get_Color_Space:
			PDFDocHandler::GetColorSpace(strFileName);
			break;
	}

	return ret;

}

FS_RESULT PDFDocHandler::DeletePage(string strFile)
{

	FS_RESULT res = DeleteAndSave(strFile);
	return res;
}

int PDFDocHandler::IsPDFA(string strFile)
{

	FSCRT_DOCUMENT doc;
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);

	FS_INT32 count = 0;
	ret = FSPDF_Doc_CountPages(doc, &count);

	FS_INT32 file_version = 0;
	ret = FSPDF_Doc_GetFileVersion(doc, &file_version);
	FS_INT32 version = -1;
	ret = FSPDF_Doc_GetPDFAVersion(doc, &version);
	
	if(version == 0) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_1A", file_version);
	}
	else if(version == 1) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_1B", file_version);
	}
	else if(version == 2) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_2A", file_version);
	}
	else if(version == 3) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_2B", file_version);
	}
	else if(version == 4) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_2U", file_version);
	}
	else if(version == 5) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_3A", file_version);
	}
	else if(version == 6) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_3B", file_version);
	}
	else if(version == 7) {
		InitConsoleWindow();
		printf("The File Version is %d, The PDFA Version is PDFA_3U", file_version);
	}
	else {
		InitConsoleWindow();
		printf("The File Version is %d, Not a PDFA file", file_version);
	}
	return ret;
}

FS_RESULT PDFDocHandler::TrimPDF(string strFile)
{
	return trimPDF(strFile);
}

FS_RESULT PDFDocHandler::EncryPDF(string strFile)
{
	return GenerateEncryptPDF(strFile);
}

void PDFDocHandler::SetGetTest(string strFile)
{
	SetDocInfo(strFile);
	string newpdf= "new"+strFile;
	GetDocInfo(newpdf);
}

FS_RESULT PDFDocHandler::GetColorSpace(string strFile)
{
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");

	FSCRT_DOCUMENT doc;
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load PDF document\n");
		return ret;
	}

	FS_INT32 pageCount = 0;

	FSCRT_PAGE page = NULL;
	PDFDocHandler GCS;
	ret = GCS.LoadPage(doc, 0, &page);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load a given page.\n");
		return ret;
	}

	FSPDF_PAGEOBJECTS pageObjs=NULL;
	ret = FSPDF_Page_GetPageObjects(page, &pageObjs);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to get page objects.\n");
		return ret;
	}
	FS_INT32 imageCount = 0;
	ret = FSPDF_PageObjects_CountObjects(page, pageObjs, FSPDF_PAGEOBJECT_IMAGE, &imageCount);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to get the number of image objects.\n");
		return ret;
	}
	FSPDF_PAGEOBJECT pageObj = NULL;
	ret = FSPDF_PageObjects_GetObject(page, pageObjs, FSPDF_PAGEOBJECT_IMAGE, 0, &pageObj);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to get an image object.\n");
		return ret;
	}
	FS_INT32 colorspace =  0;
	FS_RESULT ret_1 = FSPDF_ImageObject_GetColorSpace(page,pageObj, &colorspace);
    if (FSCRT_ERRCODE_SUCCESS == ret_1)
	{
		InitConsoleWindow();
		printf("colorspace is %d", colorspace);
	}
	FSPDF_Doc_Close(doc);
	return ret;
}


FS_RESULT DeleteAndSave(string filename)
{
	FSCRT_DOCUMENT doc;
	string strFile = filename;
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");
	
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load PDF document\n");
		return ret;
	}

	FS_INT32 pageCount = 0;
	ret = FSPDF_Doc_CountPages(doc, &pageCount);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to get page numbers.\n");
		return ret;
	}

	for (int i=0; i<pageCount; i++)
	{
		FSCRT_PAGE page = NULL;
		PDFDocHandler PageDelete;
		ret = PageDelete.LoadPage(doc, i, &page);
		FS_RESULT ret_1 = FSCRT_ERRCODE_ERROR;// delete a page
		if (i==0)  
		{
			ret_1 = FSPDF_Page_Delete(page);
			if (FSCRT_ERRCODE_SUCCESS != ret_1)
			{
				printf("Failed to load a given page.\n");
				return ret;
			}
		}
		if (FSCRT_ERRCODE_SUCCESS != ret)
		{
			printf("Failed to load a given page.\n");
			return ret;
		}
		//FS_INT32 pageCount_1 = 0;
	    FS_RESULT ret_2 = FSPDF_Doc_CountPages(doc, &pageCount);
		printf("page count = %d", pageCount);	
	}
	const char strEncryptFile[] = "After_Delete.pdf";
	FS_BOOL bRet = FSDK_SavePDFFile(doc, strEncryptFile, FSPDF_SAVEFLAG_NOORIGINAL | FSPDF_SAVEFLAG_OPTIMIZE);	
	if(!bRet)
	{
		printf("Failure: Fail to save a PDF files!\n");
	}

	FSPDF_Doc_Close(doc);
	return ret;
}

FS_RESULT trimPDF(string strFile)
{
	FSCRT_DOCUMENT doc;
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");
	
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load PDF document\n");
		return ret;
	}

	FS_INT32 pageCount = 0;
	ret = FSPDF_Doc_CountPages(doc, &pageCount);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to get page numbers.\n");
		return ret;
	}

	
	FSCRT_PAGE page = NULL;
	PDFDocHandler Tp;
	ret = Tp.LoadPage(doc, 0, &page);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load a given page.\n");
		return ret;
	}
	FSCRT_RECTF rect;
	rect.left = 5;
	rect.bottom = 10;
	rect.right = 40;
	rect.top = 41;
	FS_RESULT rett = FSPDF_Page_SetBox(page, 0, &rect);	
	if(rett == 0) printf("success");
	else 
	{
		printf("fail");
		return rett;
	}
	const char strEncryptFile[] = "Trim.pdf";
	FS_BOOL bRet = FSDK_SavePDFFile(doc, strEncryptFile, FSPDF_SAVEFLAG_REMOVESECURITY);	
	if(!bRet)
	{
		printf("Failure: Fail to save a PDF files!\n");
	}

	FSPDF_Doc_Close(doc);
	return ret;
}

FS_RESULT GenerateEncryptPDF(string strFile)
{
	FSCRT_FILE file = FSDK_OpenFile(strFile.c_str(), "rb");

	FSCRT_DOCUMENT doc;
	FS_RESULT ret  = FSPDF_Doc_StartLoad(file, NULL, &doc, NULL);
	if (FSCRT_ERRCODE_SUCCESS != ret)
	{
		printf("Failed to load PDF document, and the error code %d.\r\n", ret);
		return ret;
	}

	//Set print permission, and user can set other permission
	FS_DWORD permissions = FSPDF_PERMISSION_MODIFY ;
	//Define user and owner password, it not need to call ::FSCRT_BStr_Clear to clear
	FSCRT_BSTRC(userPwd,"foxit");
	FSCRT_BSTRC(ownerPwd,"welcome");
	//Encrypt the source PDF and save as a new file
	string strEncryptFile = "pfu_encrypt_output.pdf";
	FSCRT_FILE encryptFile = FSDK_OpenFile(strEncryptFile.c_str(), "wb");

	FSCRT_PROGRESS encryptProgress = NULL;
	ret = FSPDF_Security_StartPasswordEncryption(doc, permissions, &userPwd, &ownerPwd, FSCRT_CIPHER_RC4, 10, TRUE, encryptFile, FSPDF_SAVEFLAG_OBJECTSTREAM, &encryptProgress);
	if (ret != FSCRT_ERRCODE_SUCCESS)
	{
		FSDK_OutputLog("Failure. In function FSPDF_Security_StartPasswordEncryption with error code %d.\r\n", ret);
		return ret;
	}

	//Continue the progress of encrypting.
	ret = FSCRT_Progress_Continue(encryptProgress, NULL);
	if (FSCRT_ERRCODE_FINISHED != ret)
	{
		printf("Errors in encryption!\n");
	}

	FSCRT_Progress_Release(encryptProgress);//Release progress object
	FSPDF_Doc_Close(doc);

	return ret;
}

void SetMetadata(FSCRT_DOCUMENT pdfDoc)
{
	FSCRT_BSTR strItem[6];
	FSCRT_BStr_InitConstString(strItem[0], "Title");
	FSCRT_BStr_InitConstString(strItem[1], "Author");
	FSCRT_BStr_InitConstString(strItem[2], "Subject");
	FSCRT_BStr_InitConstString(strItem[3], "Keywords");
	FSCRT_BStr_InitConstString(strItem[4], "Creator");
	FSCRT_BStr_InitConstString(strItem[5], "Producer");

	FSCRT_BSTR strVal[6];
	FSCRT_BStr_InitConstString(strVal[0], "Tit");
	FSCRT_BStr_InitConstString(strVal[1], "Aut");
	FSCRT_BStr_InitConstString(strVal[2], "Sub");
	FSCRT_BStr_InitConstString(strVal[3], "Key");
	FSCRT_BStr_InitConstString(strVal[4], "Cre");
	FSCRT_BStr_InitConstString(strVal[5], "Pro");
	
	FS_RESULT ret = FSCRT_ERRCODE_SUCCESS;
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		//Set the value in metadata
		ret = FSPDF_Metadata_SetString(pdfDoc, &strItem[i], &strVal[i]);
		if (FSCRT_ERRCODE_SUCCESS == ret)
			printf("Success: Set metadata \"%s\" value: %s.\r\n", strItem[i].str, strVal[i].str);
		else
			printf("Failure: Fail to set metadata\"%s\" value: %s, with error code %d.\r\n", strItem[i].str, strVal[i].str, ret);
	}


	FSCRT_BStr_InitConstString(strItem[0], "CreationDate");
	FSCRT_BStr_InitConstString(strItem[1], "ModDate");

	//Init and set date zone
	FSCRT_DATETIMEZONE datezone;
	memset(&datezone, 0, sizeof(FSCRT_DATETIMEZONE));
	datezone.day = 2;
	datezone.hour = 3;
	datezone.minute = 4;
	datezone.month = 5;
	datezone.second = 6;
	datezone.year = 2013;
	for (i = 0; i < 2; i++)
	{
		//Set date time: 2013.05.02 03:04:06
		ret = FSPDF_Metadata_SetDateTime(pdfDoc, &strItem[i], &datezone);
		if (FSCRT_ERRCODE_SUCCESS == ret)
			printf("Success: Set \"%s\" value: 2013/05/02 03:04:06.\r\n", strItem[i].str);
		else
			printf("Failure: Fail to set \"%s\" value: 2013/05/02 03:04:06, with error code %d.\r\n", strItem[i].str, ret);
	}
}

void SetDocInfo(string pdfName)
{
	CAutoDocument autoDoc((pdfName).c_str(), "rb");
	FSCRT_FILE file = FSDK_OpenFile((pdfName).c_str(), "rb");
	if (!autoDoc.GetFileHander())
	{
		return;
	}
	if (FSCRT_ERRCODE_SUCCESS != autoDoc.LoadPDFDocument(NULL))
		return;
	SetMetadata(autoDoc.GetDocument());
	FSDK_SavePDFFile(autoDoc.GetDocument(), ("new" + pdfName).c_str());
}

void GetMetadata(FSCRT_DOCUMENT pdfDoc )
{
	FSCRT_BSTR strItem[6];
	FSCRT_BStr_InitConstString(strItem[0], "Title");
	FSCRT_BStr_InitConstString(strItem[1], "Author");
	FSCRT_BStr_InitConstString(strItem[2], "Subject");
	FSCRT_BStr_InitConstString(strItem[3], "Keywords");
	FSCRT_BStr_InitConstString(strItem[4], "Creator");
	FSCRT_BStr_InitConstString(strItem[5], "Producer");

	FS_RESULT ret = FSCRT_ERRCODE_ERROR;
	int i = 0;
	for ( i = 0; i < 6; i++)
	{
		FSCRT_BSTR strMeta;
		FSCRT_BStr_Init(&strMeta);
		//Get the value in metadata
		ret = FSPDF_Metadata_GetString(pdfDoc, &strItem[i], &strMeta);
		PDFDocHandler test;
		test.InitConsoleWindow();
		if (FSCRT_ERRCODE_SUCCESS == ret)
			printf("Success: Get metadata \"%s\" value: %s.\r\n", strItem[i].str, strMeta.str);
		else
			printf("Failure: Fail to get metadata\"%s\" value with error code %d.\r\n", strItem[i].str, ret);
		FSCRT_BStr_Clear(&strMeta);
	}
	
	FSCRT_BStr_InitConstString(strItem[0], "CreationDate");
	FSCRT_BStr_InitConstString(strItem[1], "ModDate");
	for (i = 0; i < 2; i++)
	{
		//Init data zone
		FSCRT_DATETIMEZONE datazone;
		memset(&datazone, 0, sizeof(FSCRT_DATETIMEZONE));
		//Get date time
		ret = FSPDF_Metadata_GetDateTime(pdfDoc, &strItem[i], &datazone);
		if (FSCRT_ERRCODE_SUCCESS == ret)
			printf("Success: Get \"%s\" value: %d/%d/%d %d:%d:%d.\r\n", strItem[i].str, 
						datazone.year, datazone.month, datazone.day, datazone.hour, datazone.minute, datazone.second);
		else
			printf("Failure: Fail to get \"%s\" value with error code %d.\r\n", strItem[i].str, ret);
	}
}

void GetDocInfo(string pdfName)
{
	CAutoDocument autoDoc((pdfName).c_str(), "rb");
	if (!autoDoc.GetFileHander())
	{
		return;
	}
	if (FSCRT_ERRCODE_SUCCESS != autoDoc.LoadPDFDocument(NULL))
		return;
	GetMetadata(autoDoc.GetDocument());
} 