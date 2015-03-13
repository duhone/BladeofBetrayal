// HTFBitmap.h: interface for the HTFBitmap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTFBITMAP_H__B6BE8DA9_F77B_4C0E_BC5A_0BDAE02CA68A__INCLUDED_)
#define AFX_HTFBITMAP_H__B6BE8DA9_F77B_4C0E_BC5A_0BDAE02CA68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "HTFHeader.h"


class HTFBitmap : public HTFHeader  
{
public:
	void load_image_data(FILE *fp);
	void write_file(FILE *fp);
	HTFBitmap();
	virtual ~HTFBitmap();

	BITMAPFILEHEADER bmp_file_header;
	BITMAPINFOHEADER bmp_info_header;

	char* image_date;

	

};

#endif // !defined(AFX_HTFBITMAP_H__B6BE8DA9_F77B_4C0E_BC5A_0BDAE02CA68A__INCLUDED_)
