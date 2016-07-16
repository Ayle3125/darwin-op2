#ifndef _SPRINT_H_
#define _SPRINT_H_

#include <strategy.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240

class Sprint:public Strategist
{
public:
	Sprint();
	~Sprint();
private:

    BallTracker *tracker;
    BallFollower *follower;
    Motion *motion;
    //compass *compasspro;
    //findline *findline;

    bool m_is_checkstatus;

    /*******image process********/

    void CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D);
    int m_no_point_found;
    int m_NopointMaxCount;
    void LostDispose();

    /******motion**************/
    void SprintForward();

    int m_point_found;
    Point2D m_point_center_2D;

    double m_GoalFBStep;
    double m_GoalRLTurn;
    double m_FBStep;
    double m_RLTurn;
    double m_FBStep_straight;
    double m_RLTurn_straight;
    double m_RLTurn_left;
    double m_RLTurn_right;
    double m_RLturn_degree;
    double m_RLturn_max;
    double m_FitFBStep;
    double m_FitMaxRLTurn;
    double LRMoveAngle;
    int m_pre_action;

    double m_percent_CenterDiff;
    int m_Xoffset;
    int m_target_Xoffset;
    /*---------------------------*/
    int debug_print;

protected:
    virtual void ThreadMotion();
    virtual int GetImageResult();
};

#endif // _SPRINT_H_
