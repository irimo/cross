#include <iostream>
#include <math.h>

#include "Dot.h"
#include "BaseImg.h"

bool BaseImg::setImage(std::string s){
	openBmp(s);
	return true;
}
bool BaseImg::outputImage(std::string s){
	writeBmp(s);
	return true;
}
bool BaseImg::run(){
	Resize();
	dotDrawing();
	return true;
}
bool BaseImg::Resize(){
	DWORD w = this->getWidth();
	DWORD h = this->getHeight();
	DWORD after_w = MASK_WIDTH;
	DWORD after_h = MASK_HEIGHT;
	if(w < after_w && h < after_h){
		return true;
	}
	this->setWidth(after_w);
	this->setHeight(after_h);
	double w_per = (double)after_w / (double)w;
	double h_per = (double)after_h / (double)h;
	if(w_per > h_per){
		h_per = w_per;
	} else {
		w_per = h_per;
	}
	std::cout << w_per << "percent.\n" << std::endl;;
	unsigned char image_tmp[3][MASK_HEIGHT][MASK_WIDTH];
	for(DWORD y=0; y<after_h; y++){
		for(DWORD x=0; x<after_w; x++){
			DWORD tmp_x = (DWORD)floor(x / w_per);// 切捨て
			DWORD tmp_y = (DWORD)floor(y / h_per);
			image_tmp[RED][y][x] = image[RED][tmp_y][tmp_x];
			image_tmp[GREEN][y][x] = image[GREEN][tmp_y][tmp_x];
			image_tmp[BLUE][y][x] = image[BLUE][tmp_y][tmp_x];
		}
	}
	for(DWORD y=0; y<after_h;  y++){
		for(DWORD x=0; x<after_w; x++){
			for(int c=0; c<3; c++){
				image[c][y][x] = image_tmp[c][y][x];
			}
		}
	}
	return true;
}
bool BaseImg::dotDrawing(){
	Dot *dot = new Dot();

	unsigned char image_tmp[3][NEW_H][NEW_W];
	for(int y=0; y<MASK_HEIGHT; y++){
		for(int x=0; x<MASK_WIDTH; x++){
			for(int yi=0; yi<DOT_HEIGHT; yi++){
				for(int xi=0; xi<DOT_WIDTH; xi++){
					for(int c=0; c<3; c++){
						image_tmp[c][y*DOT_HEIGHT+yi][x*DOT_WIDTH+xi] = (unsigned char)floor((float)dot->dot[yi][xi]*(float)image[c][y][x]/255.0f);
					}
				}
			}
		}
	}
	this->setImage(tpl_path+"/cloth.bmp");
	Bmp *bmp_mask = new Bmp();
	bmp_mask->openBmp(tpl_path+"/mask.bmp");
	unsigned char mask = 0;
	unsigned char cloth = 0;
	for(int y=0; y<NEW_H;  y++){
		for(int x=0; x<NEW_W; x++){
			mask = bmp_mask->getPixelG(MASK_L+x,MASK_T+y);
			for(int c=0; c<3; c++){
				cloth = this->image[c][MASK_T+y][MASK_L+x];
				double cloth_percent =(double)mask * 100.0 / 255.0;
				image[c][MASK_T+y][MASK_L+x] = (100.0-cloth_percent)/100.0*(double)image_tmp[c][y][x] + cloth_percent/100.0*(double)cloth;
			}
		}
	}
	delete bmp_mask;
	return true;
}
bool BaseImg::setTplPath(std::string s){
	tpl_path = s;
	return true;
}
