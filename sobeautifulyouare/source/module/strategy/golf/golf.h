#ifndef _GOLF_H_
#define _GOLF_H_

#include <strategy.h>

class Golf:public Strategist
{
    public:
        Golf();
        ~Golf();
    private:
        enum GolfState{
            ADDRESS,
            APPROACH,
            SWING,
        };
        /*************Process****************/
        bool m_execute;
        GolfState m_process_state;
        int m_pre_action;// 1:move left  0:go straight  -1:move right 

        int ApproachBall();//return 1:OK
        int AddressHole(int ball_valid, int hole_valid);//0:valid -1:invalid
        int Swing();

        /*************Image*******************/
        ImgProcResult *m_imgRes_hole, *m_imgRes_ball;
        ImgProc *m_imgPro_hole, *m_imgPro_ball;
        cv::Point2f m_ball_center;
        cv::Point2f m_hole_center;
        double m_ball_radius;

        double m_ApproachBallTop;
        double m_ApproachHoleTop;
        double m_AddressHoleCenter;
        double m_AddressDiff;
        double m_SwingDiff;
        cv::Point2f m_AddressBallCenter,m_SwingBallCenter;


        /*************Motion Order*************/
        double pan_range; 
        double unit_pan;
        double tilt_min;		
        double tilt_range; 
        double unit_tilt;

        double m_FBstep_straight;
        double m_FBstep;
        double m_FBstep_ApproachMin;
        double m_FBstep_goal;
        double m_unit_FBstep;
        double m_MAX_FBstep;

        double m_RLturn_straight;
        double m_RLturn;
        double m_RLturn_goal;
        double m_unit_RLturn;
        double m_MAX_RLturn;

        double m_RLstep_straight;
        double m_RLstep;
        double m_RLstep_goal;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        /*------------------------------------*/

        int debug_print;

    protected:
        virtual void ThreadMotion();
        //virtual int GetImageResult();
        int GetImageResult(int result_type);//0:ball 1:hole
};

#endif // _GOLF_H_
