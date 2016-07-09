
#include "sprint.h"

Sprint::Sprint()
{
     m_is_checkstatus = true;
     m_point_center_2D.X = 0;
     m_point_center_2D.Y = 0;
     m_point_found = false;
     m_GoalFBStep = 0;
     m_GoalRLTurn = 0;
     m_FBStep = 0;
     m_RLTurn = 0;
    debug_print = 0; 

    m_FitFBStep = 3.0;
    m_FitMaxRLTurn = 35.0;

    m_FBStep_straight = 40.0;
    m_RLTurn_straight = 2.27;

    LRMoveAngle = 3.0;
}

Sprint::~Sprint()
{
}



void Sprint::ThreadMotion()
{
    motion = new Motion();
    tracker = new BallTracker();
    follower = new BallFollower();
    //compasspro = new compass();
    //findline = new findline();
    
	motion->poseInit();

   
    while(true)
    {
	    motion->CheckStatus();
        GetImageResult(frame);
        usleep(10*8000);
        if (  m_is_checkstatus ) {
            motion->CheckStatus();
        }

        SprintForward();
    }

}

/*void Robcup_goalkeeper::GetImageResult(cv::Mat &frame,ImgProcResult Result)      //In this part We have to visit the point.
{
    findline->imageProcess(frame,Result);
    CVpointTo2Dpoint(Result->point,m_point_center_2D);
}*/

void Sprint::SprintForward()
{
    if(debug_print) printf("SprintForward \n");
    if ( tracker->limit_mode != 2){
       tracker->ChangeLimit(12, -10, 50, 2);
    }
    m_point_found = tracker->SearchAndTracking(m_point_center_2D);
    tracker->Process(tracker->ball_position);   //tracker the point

    if(  m_point_found == 1)
    {
        double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
        double pan_range = Head::GetInstance()->GetLeftLimitAngle();
        double pan_percent = pan / pan_range;
        double tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
        double tilt_min = Head::GetInstance()->GetBottomLimitAngle();
        double tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min;
        double tilt_percent = (tilt - tilt_min) / tilt_range;

        if( pan < LRMoveAngle && pan > -1.0*LRMoveAngle){ //TODO LRMoveAngle以内不动
            m_RLTurn = m_RLTurn_straight;
            m_FBStep = m_FBStep_straight;
        }
        else if(pan >= LRMoveAngle)
        {
            m_FBStep = m_FBStep_straight;
            m_RLTurn=  m_FitMaxRLTurn * pan_percent;
        }
        else
        {
            m_FBStep = m_FBStep_straight;
            m_RLTurn=  m_FitMaxRLTurn * pan_percent;
        }
    }
    else{
        m_RLTurn = m_RLTurn_straight;
        m_FBStep = m_FBStep_straight;
    }
    motion->walk(m_FBStep , m_RLTurn, 0);
}


void Sprint::GetImageResult(cv::Mat &frame)
{

}

