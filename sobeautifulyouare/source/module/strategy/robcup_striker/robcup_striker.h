#ifndef _ROBCUP_STRIKER_H_
#define _ROBCUP_STRIKER_H_

#include <strategy.h>



class Robcup_striker:public Strategist
{
    public:
        Robcup_striker();
        ~Robcup_striker();
    private:

        enum StrikerState{
            FINDBALL,
            JUDGE,
			TURN,
            KICK,
        };

        BallTracker *tracker;
        BallFollower *follower;	


        /*************Process****************/
        bool m_execute;
        StrikerState m_process_state;

        int m_MAXTurnCount;

        int TurnGoal(bool count_reset);

        /*************Image*******************/
        ImgProcResult *m_imgRes_goal, *m_imgRes_ball;
        ImgProc *m_imgPro_goal, *m_imgPro_ball;
        cv::Point2f m_ball_center;
		Point2D m_ball_center_2D;
        cv::Point2f m_goal_center;

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
        int GetImageResult(int result_type);//0:ball 1:goal


};

#endif // _ROBCUP_STRIKER_H_
