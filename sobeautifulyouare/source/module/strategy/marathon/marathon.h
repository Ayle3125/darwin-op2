#ifndef _MARATHON_H_
#define _MARATHON_H_

#include <strategy.h>

enum MarathonState{
    STRAIGHT,
    CURVE,
};
class Marathon:public Strategist{
    public:
        Marathon();
        ~Marathon();
    private:
        BallTracker *tracker;
        /*************Process****************/
        bool m_execute;
        MarathonState m_process_state;

        int m_NoLineMaxCount;
        int m_no_line_found;
        int m_CurveJudgeCount;
        int m_curve_count;
        int m_StraightJudgeCount;
        int m_straight_count;
        Point2D m_line_center_2D;
        double m_line_theta;//the angle of the white track
        double m_CurveTheta;

        int m_NolookMaxTime;
        int m_nolooktime;

        int LostDispose();//return 1 back to line, can't judge the direction

        /*************Motion Order****************/
        double m_FBstep;
        double m_unit_FBstep;
        double m_MAX_FBstep;

        double m_RLturn;
        double m_unit_RLturn;
        double m_MAX_RLturn;

        double m_RLstep;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        /*------------------------------------*/
        int debug_print;
    protected:
        virtual void ThreadMotion();
        virtual int GetImageResult(cv::Mat &frame);

};

#endif // _MARATION_H_
