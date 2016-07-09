#ifndef _MARATHON_H_
#define _MARATHON_H_

#include <strategy.h>

enum MarathonState{
    STRAIGHT,
    CURVE,
};
class Marathon:public Strategist
{
    public:
        Marathon();
        ~Marathon();
    private:
        MarathonState m_process_state;
        double theta;//the slope of the white track
    protected:
        virtual void ThreadMotion();
        virtual void GetImageResult(cv::Mat &frame);

};

#endif // _MARATION_H_
