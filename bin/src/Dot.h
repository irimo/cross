#ifndef DOT_H
#define DOT_H

#include "Bmp.h"

// クロスの1ドットの縦横
#define DOT_WIDTH 10
#define DOT_HEIGHT 10
// 何ドット並べてあるか
// 画像のサイズはDOT_x*MASK_x
#define MASK_WIDTH 50
#define MASK_HEIGHT 50

#define CLOTH_WIDTH 888
#define CLOTH_HEIGHT 665

#define NEW_W MASK_WIDTH*DOT_WIDTH
#define NEW_H MASK_HEIGHT*DOT_HEIGHT

#define MASK_L 193
#define MASK_T 80


class Dot{
public:
	unsigned char dot[DOT_HEIGHT][DOT_WIDTH];
	Dot();
	bool setDot();
};
class Mask{
	unsigned char _mask[CLOTH_HEIGHT][CLOTH_WIDTH];
public:
	Mask();
	bool setMask();
};
class Cloth : public Bmp {
	unsigned char _mask[CLOTH_HEIGHT][CLOTH_WIDTH];
public:
	bool setMaskImg(Bmp bmp);
};

#endif