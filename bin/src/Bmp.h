#ifndef BMP_H
#define BMP_H

#include <string>

// "x or y <= 10000(about)" --->array size over.
// true 'Photoshop' show message,"over 30000 hasn't compatibility".
// !caution:a part(Bmp.h/cpp) use magic number.
const long MAX_WIDTH = 1600;
const long MAX_HEIGHT = 1400;

const short RED = 2;
const short GREEN = 1;
const short BLUE = 0;

typedef long LONG;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef unsigned int UINT;

typedef struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD	biSize;		// この構造体のサイズ
	DWORD	biWidth;		// 幅（ピクセル単位）
	DWORD	biHeight;		// 高さ（ピクセル単位）
	WORD	biPlanes;		// 常に1
	WORD	biBitCount;	// 1ピクセルあたりのカラービットの数
	DWORD	biCompression;	// BI_RGB, BI_RLE8, BI_RLE4のいずれか
	DWORD	biSizeImage;	// イメージの全バイト数
	DWORD	biXPelsPerMet1er;	// 0または水平解像度
	DWORD	biYPelsPerMeter;	// 0または垂直解像度
	DWORD	biClrUsed;	// 通常は0、biBitCount以下のカラー数に設定可能
	DWORD	biClrImportant;	// 通常は0
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
    	BYTE	rgbBlue;		// 青の輝度(0～255)
    	BYTE	rgbGreen;		// 緑の輝度(0～255)
    	BYTE	rgbRed;		// 赤の輝度(0～255)
    	BYTE	rgbReserved;	// 予約値。0にする
} RGBQUAD;
typedef struct tagBITMAPINFO {
    	BITMAPINFOHEADER	bmiHeader;
    	RGBQUAD		bmiColors[1];
} BITMAPINFO;


class Bmp{
public:
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	UINT size;
	unsigned char image[3][MAX_HEIGHT][MAX_WIDTH];
	std::string openFile;
	std::string writeFile;

public:
	Bmp();
	~Bmp();
	bool openBmp(std::string s);
	bool openBmp();
	bool writeBmp(std::string s);
	bool writeBmp();
	bool copyBmp(Bmp *bmp);
	DWORD getWidth();
	DWORD getHeight();
	DWORD getPadding();
	bool readHeader(FILE *fp);
	bool writeHeader(FILE *fp);
	bool setOpenFile(std::string s);
	bool setWriteFile(std::string s);
	UINT getFileSize();
	int getDIBxmax(int mx,int dep);
	bool setWidth(DWORD w);
	bool setHeight(DWORD h);
	unsigned char getPixelG(int x, int y);
};

#endif
