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

    bool m_is_checkstatus;
    double m_X_OFFSET ;
    double m_FB_Step;
    double m_RL_Turn;
    int debug_print;
    int m_upcnt;
    int m_max_upcnt;
    int m_flatcnt ;
    int m_max_flatcnt ;
    int m_downcnt ;
    int m_max_downcnt ;
    int m_flatcnttwo ;

    int m_ladder_flag;
    int m_up_time1;
    double m_up_offset1;
    int m_up_time2;
    double m_up_offset2;
    int m_up_time3;
    double m_up_offset3;

    int m_down_time1;
    double m_down_offset1;
    int m_down_time2;
    double m_down_offset2;
    int m_down_time3;
    double m_down_offset3;

    void moveupstair();
    void movedownstair();
    void findladder();
   /*-------------Vision---------------*/
    Point2D m_line_leftup;
    Point2D m_line_rightdown;

    int m_img_uplimit;
    int m_img_downlimit;
    int m_img_range;
    double m_img_area;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult();
};

#endif // _LADDER_H_
