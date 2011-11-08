#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>
#include "Bmp.h"

	Bmp::Bmp(){
		std::cout << "Bmp construct\n";
	}
	Bmp::~Bmp(){
		std::cout << "Bmp destruct\n";
	}

	bool Bmp::openBmp(std::string s){

		std::cout << "openBmp(file:" << s.c_str() << ").....\n";
		openFile = s;

		const char *file = s.c_str();

		FILE *fp;
		fp = fopen(file, "rb");
		if(fp == NULL){
			std::cout << "fp error!\n";
			return false;
		}
		readHeader(fp);

		size = getFileSize() - sizeof(bmfh) - sizeof(bmih);
		std::cout << "remaining " << size << "byte\n";
	    BYTE* buf = new BYTE[size];
	    if (fread(buf, size, 1, fp) == false) {
			std::cout << "Error file!\n" << std::endl;
			return false;
	    }
		fclose(fp);

		int w = getWidth();
		int h = getHeight();
		std::cout << "width:" << w << " heiht:" << h << "\n";
		int padding = getPadding();
		int foward = 0;
		int i = 0;
		for (int y=0; y<h; y++){
			for (int x=0; x<w; x++) {
				for (int c=0; c<3; c++) {
					image[c][y][x] = *buf++;
					foward++;
				}
			}
			int count = 0;
			while(count < padding){
				buf++;
				count++;
				foward++;
			}
			
		}
		buf -= foward;
		delete [] buf;
		std::cout << "completed.\n";
		return true;
		
	}
	bool Bmp::openBmp(){
		return openBmp(openFile);
	}
	bool Bmp::writeBmp(std::string s){
		std::cout << "writeBmp(file:" << s.c_str() << ").....\n";
		writeFile = s;
		const char *file = s.c_str();
		FILE *fp;
		
		if ((fp = fopen(file, "wb"))==NULL) {
			std::cout << "writeBmp Error!\n";
			return false;
		} else {
			std::cout << "open success.\n";
		}

		writeHeader(fp);

		int w = getWidth();
		int h = getHeight();
		int padding = getPadding();
		unsigned char null_val= 0;
		for (int y=0; y<h; y++){
			for (int x=0; x<w; x++) {
				for (int c=0; c<3; c++) {
					fwrite(&image[c][y][x], 1 , 1, fp);
				}
			}
			int count = 0;
			while(count < padding){
				fwrite(&null_val, 1, 1, fp);
				count++;
			}

		}
		fclose(fp);
		std::cout << "completed.\n";

		return true;

	}
	bool Bmp::writeBmp(){
		return writeBmp(writeFile);
	}
	
	bool Bmp::copyBmp(Bmp *bmp){
		bmfh = bmp->bmfh;
		bmih = bmp->bmih;
		DWORD w = bmp->getWidth();
		DWORD h = bmp->getHeight();
		if(w > MAX_WIDTH){
			return false;
		}
		if(h > MAX_HEIGHT){
			return false;
		}

		for(int c=0; c<3; c++){
			for(int y=0; y<h; y++){
				for(int x=0; x<w; x++){
					image[c][y][x] = bmp->image[c][y][x];
				}
			}
		}
		setWidth(w);
		setHeight(h);

		return true;
	}
	bool Bmp::readHeader(FILE *fp){
		fread(&bmfh.bfType, sizeof(WORD), 1, fp);
		fread(&bmfh.bfSize, sizeof(DWORD), 1, fp);
		fread(&bmfh.bfReserved1, sizeof(WORD), 1, fp);
		fread(&bmfh.bfReserved2, sizeof(WORD), 1, fp);
		fread(&bmfh.bfOffBits, sizeof(DWORD), 1, fp);

		fread(&bmih.biSize, sizeof(DWORD), 1, fp);
		fread(&bmih.biWidth, sizeof(DWORD), 1, fp);
		fread(&bmih.biHeight, sizeof(DWORD), 1, fp);
		fread(&bmih.biPlanes, sizeof(WORD), 1, fp);
		fread(&bmih.biBitCount, sizeof(WORD), 1, fp);
		fread(&bmih.biCompression, sizeof(DWORD), 1, fp);
		fread(&bmih.biSizeImage, sizeof(DWORD), 1, fp);
		fread(&bmih.biXPelsPerMet1er, sizeof(DWORD), 1, fp);
		fread(&bmih.biYPelsPerMeter, sizeof(DWORD), 1, fp);
		fread(&bmih.biClrUsed, sizeof(DWORD), 1, fp);
		fread(&bmih.biClrImportant, sizeof(DWORD), 1, fp);

		if(bmfh.bfType != *((WORD*)"BM")){
			std::cout << "not BM file\n";
			return false;
		}
		std::cout << bmih.biBitCount << "bit file.\n";
		if(bmih.biBitCount <= 8){
			std::cout << "BitCountが8bit以下は読み込めない仕様\n";
			return false;
		}
		return true;
	}
	bool Bmp::writeHeader(FILE *fp){
		fwrite(&bmfh.bfType, sizeof(WORD), 1, fp);
		fwrite(&bmfh.bfSize, sizeof(DWORD), 1, fp);
		fwrite(&bmfh.bfReserved1, sizeof(WORD), 1, fp);
		fwrite(&bmfh.bfReserved2, sizeof(WORD), 1, fp);
		fwrite(&bmfh.bfOffBits, sizeof(DWORD), 1, fp);

		fwrite(&bmih.biSize, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biWidth, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biHeight, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biPlanes, sizeof(WORD), 1, fp);
		fwrite(&bmih.biBitCount, sizeof(WORD), 1, fp);
		fwrite(&bmih.biCompression, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biSizeImage, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biXPelsPerMet1er, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biYPelsPerMeter, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biClrUsed, sizeof(DWORD), 1, fp);
		fwrite(&bmih.biClrImportant, sizeof(DWORD), 1, fp);

		return true;
	}

	bool Bmp::setOpenFile(std::string s){
		if(typeid(s).name() != "std::string"){
			return false;
		}
		openFile = s;
		return true;
	}

	bool Bmp::setWriteFile(std::string s){
		if(typeid(s).name() != "std::string"){
			return false;
		}

		openFile = s;
		return true;
	}

	UINT Bmp::getFileSize(){
		fpos_t fsize = 0;
		const char *file = openFile.c_str();

		FILE *fp = fopen(file,"rb"); 
	 
		/* ファイルサイズを調査 */ 
		fseek(fp,0,SEEK_END); 
		fgetpos(fp,&fsize); 
	 
		fclose(fp);
	 
		return (UINT)fsize;
	}
	DWORD Bmp::getWidth(){
		return bmih.biWidth;
	}
	DWORD Bmp::getHeight(){
		return bmih.biHeight;
	}
	DWORD Bmp::getPadding(){
		DWORD w = getWidth();
		int depth = bmih.biBitCount;
		int rw = getDIBxmax(w,depth);
		long add = rw-w*depth/8;
		return add;
	}
int Bmp::getDIBxmax(int mx,int dep)
{
	switch(dep) {
	case 32:
		return mx*4;
	case 24:
		//return mx;
		return ((mx*3)+3)/4*4;
		break;
	case 16:
		return (mx+1)/2*2;
		break;
	case 8:
		return (mx+3)/4*4;
		break;
	case 4:
		return (((mx+1)/2)+3)/4*4;
		break;
	case 1:
		return (((mx+7)/8)+3)/4*4;
	}
	return mx;
}

	bool Bmp::setWidth(DWORD w){
		bmih.biWidth = w;
		return true;
	}
	bool Bmp::setHeight(DWORD h){
		bmih.biHeight = h;
		return true;
	}
	unsigned char Bmp::getPixelG(int x, int y){
		return image[GREEN][y][x];
	}