#ifndef _LADDER_H_
#define _LADDER_H_

#include <strategy.h>

enum LadderState{
    UPSTAIR,
    FLATWALKING,
    DOWNSTAIR,
};

class Ladder:public Strategist
{
public:
	Ladder();
	~Ladder();
private:

    double m_X_OFFSET ;
    double m_FB_Step;
    int debug_print;
    int m_upcnt;
    int m_max_upcnt;
    int m_flatcnt ;
    int m_max_flatcnt ;
    int m_downcnt ;
    int m_max_downcnt ;
    int m_flatcnttwo ;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult(cv::Mat &frame);
};

#endif // _LADDER_H_
