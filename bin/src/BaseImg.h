#ifndef BASEIMG_H
#define BASEIMG_H

#include <string>
#include "Bmp.h"

class BaseImg : public Bmp {
	std::string tpl_path;
public:
	bool setImage(std::string s);	// arg
	bool setTplPath(std::string s);	// arg
	bool run();
	bool outputImage(std::string s);	// arg
private:
	bool Resize();
	bool dotDrawing();
};

#endif