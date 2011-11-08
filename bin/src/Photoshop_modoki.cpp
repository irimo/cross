#include <string>
#include "BaseImg.h"

int main(int argc, char *argv[]){
	printf("main start\n");
	// プログラムの引数検索
	std::string in_path, out_path,tpl_path;

	if(argc != 3){
		return 1;
	}
	in_path = argv[1];
	out_path = argv[2];

//	in_path = std::string("./test_kurage.bmp");	// もともとある
//	out_path = std::string("./test_out.bmp");	// 存在しない(作る)
	if(in_path.find(".bmp",0) == std::string::npos){
		return 1;
	}
	if(out_path.find(".bmp",0) == std::string::npos){
		return 1;
	}

	BaseImg *baseimg = new BaseImg();
//	Bmp *cross = new Bmp();
	baseimg->openBmp(in_path);
	baseimg->setTplPath("/home/mnlab/bin/cross");
//	cross->setImage(in_path);
	baseimg->run();
	baseimg->writeBmp(out_path);
//	cross->outputImage(out_path);
	delete baseimg;

	return 0;
}