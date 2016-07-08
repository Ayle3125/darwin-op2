#ifndef _SPRINT_H_
#define _SPRINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <BlobResult.h>
#include <camera.h>
#include <imgproc.h>
#include <motion.h>
#include <communication.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240

class Sprint
{
public:
	Sprint();
	~Sprint();
	int run();
private:
	
protected:

};

#endif // _SPRINT_H_
