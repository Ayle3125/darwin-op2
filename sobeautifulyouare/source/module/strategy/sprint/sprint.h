#ifndef _SPRINT_H_
#define _SPRINT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <BlobResult.h>
#include <camera.h>
#include <imgproc.h>
#include <motion.h>
#include <communication.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240

class Sprint
{
public:
	Sprint();
	~Sprint();
private:

    BallTracker *tracker;
    BallFollower *follower;
    Motion *motion;
    compass *compasspro;
    findline *findline;

    bool m_is_checkstatus;

    int run();
    
    /*******image process********/
    void GetImageResult(cv::Mat &frame, ImgResultType rs);
    void CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D);

    /******motion**************/
    void SprintForward();

    int m_point_found;
    Point2D m_point_center_2D;

    double m_GoalFBStep;
    double m_GoalRLTurn;
    double m_FBStep;
    double m_RLTurn;
    const double m_FBStep_straight;
    const double m_RLTurn_straight;
    const double m_RLTurn_left;
    const double m_RLTurn_right;
    double m_FitFBStep;
    double m_FitMaxRLTurn;
    double LRMoveAngle;

    /*---------------------------*/
    int debug_print;

protected:
    virtual void ThreadMotion();
};

#endif // _SPRINT_H_
