#ifndef _IMG_PROC_H_
#define _IMG_PROC_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "frame.h"
#include "BlobResult.h"

using std::vector;

#define IMG_WIDTH	320
#define IMG_HEIGHT	240

class ImgProcResult{

public:
	ImgProcResult(){};
	~ImgProcResult(){};
	 virtual void operator=(ImgProcResult &res) = 0;
private:
protected:

};

class ImgProc{

public:
	ImgProc();
	~ImgProc();
	virtual void imageProcess(cv::Mat img, ImgProcResult *Result) =0;
private:
protected:
	ImgProcResult *res;

};


#endif // _IMG_PROC_H_
