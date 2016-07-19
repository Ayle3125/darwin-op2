#ifndef _FIRA_PENALTY_H_
#define _FIRA_PENALTY_H_

#include <strategy.h>

class Fira_penalty:public Strategist
{
public:
	Fira_penalty();
	~Fira_penalty();
private:

            BallTracker *tracker;
            BallFollower *follower;
            Motion *motion;

            int m_penalty_flag;
            int m_img_result;

            void Followball();
            void Adjustment();
            void Findcolumn();

            bool m_is_checkstatus;

            int m_NoBallMaxCount;
            int m_NoBallCount;
            double m_GoalFBStep;
            double m_GoalRLTurn;
            double m_FBStep;
            double m_RLTurn;
            double m_UnitFBStep;
            double m_UnitRLTurn;
            double m_forward_count;
            double m_forward_max;
            double m_UnitFBStep;
            double m_UnitRLTurn;

            double m_FollowMinFBStep;
            double m_FollowMaxFBStep;
            double m_FollowMaxRLTurn;
            int m_KickBallMaxCount;
            int m_KickBallCount;
            int KickBall;
		
	    int m_pan_angle;
	    int m_pan_max;
            /*--------------------Vision--------------------*/
            cv::Point2f m_point_center_2D;
            int debug_print;
            double m_percent_CenterDiff_X;
            double m_percent_CenterDiff_Y;
            int m_img_range;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult();
};

#endif // _FIRA_PENALTY_H_
