#ifndef _ROBCUP_STRIKER_H_
#define _ROBCUP_STRIKER_H_

#include <strategy.h>


enum StrikerState{
    FINDBALL,
    DRIBBLE,
    KICK,
};

class Robcup_striker:public Strategist
{
    public:
        Robcup_striker();
        ~Robcup_striker();
    private:

        BallTracker *tracker;
        BallFollower *follower;	

        followball *ballpro; 
        goalpost *goalpro;
        sideline *linepro;
        findrobot *robotpro;


        StrikerState m_process_state;

        void FindBall();
        void Dribble();
        void KickAdjust();

        int FindGoal();// 0: no goal  1:goal found  -1:can't get two goalpost(close to goalpost)

        int m_is_dribble;


        /*********Process*******************/

        int m_ball_found;// 0: noball 1:found 2:found then lost -1:noball for long
        int m_NoBallMaxCount;
        int m_goal_found;// the number of goalpost
        int m_line_found;// 0:no 1:sideline 2:forbiddenline
        Point2D m_ball_center_2D;
        Point2D m_ball_center_angle;
        Point2D m_line_center_2D;//forbiddenline & sideline
        Point2D m_goalfoot1, m_goalfoot2;
        double m_line_Kvalue;

        double m_dribble_pan;

        double m_LongShotRightAngle;
        double m_LongShotLeftAngle;
        double m_LongShotTopAngle;

        double m_LineTopValue;

        int m_kick_ball_count;
        int m_KickBallMaxCount;

        /*---------------------------------------*/

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
		virtual void GetImageResult(cv::Mat &frame);


};

#endif // _ROBCUP_STRIKER_H_