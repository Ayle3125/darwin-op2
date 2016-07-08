#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define IMG_WIDTH	320
#define IMG_HEIGHT	240

class Communication {

public:
	Communication();
	~Communication();
	void Run(unsigned char *mat1, unsigned char *mat2, int pts[18]);
private:
	unsigned char *imgData;
	
	void *context;
	void *responder;
	
	unsigned char *MergeChars(unsigned char *mat1, unsigned char *mat2);
protected:

};

#endif // _COMMUNICATION_H_
