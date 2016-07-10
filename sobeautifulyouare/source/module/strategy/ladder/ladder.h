#ifndef _LADDER_H_
#define _LADDER_H_

#include <strategy.h>

class Ladder:public Strategist
{
public:
	Ladder();
	~Ladder();
private:

    int debug_print;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult(cv::Mat &frame);
};

#endif // _LADDER_H_
