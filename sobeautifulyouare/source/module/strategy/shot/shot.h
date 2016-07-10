#ifndef _SHOT_H_
#define _SHOT_H_

#include <strategy.h>

class Shot:public Strategist
{
public:
	Shot();
	~Shot();
private:

    int debug_print;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult(cv::Mat &frame);
};

#endif // _GOLF_H_
