#ifndef _GOLF_H_
#define _GOLF_H_

#include <strategy.h>

class Golf:public Strategist
{
public:
	Golf();
	~Golf();
private:

    int debug_print;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult(cv::Mat &frame);
};

#endif // _GOLF_H_
