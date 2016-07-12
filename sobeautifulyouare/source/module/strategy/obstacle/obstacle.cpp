
#include "obstacle.h"

Obstacle::Obstacle()
{
    m_pixel_num = 0;
    m_PixelJudgeNum = 3000;//TODO
    m_obstacle_center_2D.X =0;
    m_obstacle_center_2D.Y =0;
    m_line_center_2D.X =0;
    m_line_center_2D.Y =0;
	m_line_theta = 0;

    m_NolookMaxTime = 5;
    m_nolooktime = 0;

    m_execute = 1;
    m_pre_action = 0;


    //TODO go straight first    
    m_FBstep = 10;
    m_FBstep_straight = 10;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0;
    m_RLturn_straight = 0;
    m_unit_RLturn = 1.0;
    m_MAX_RLturn = 35;
    m_RLstep_straight = 0;
    m_RLstep = 0;
    m_unit_RLstep = 0.3;
    m_MAX_RLstep = 30;

    debug_print = 1;
}

Obstacle::~Obstacle()
{
}

int Obstacle::GetImageResult_obstacle(int result_type)
{
    while ( is_new_img == false ) usleep(8000);
    imgProc->imageProcess(frame,imgRes);
    if ( result_type == 0) {
        FindLineResult *tmp_result = dynamic_cast<FindLineResult *>(imgRes);
        if ( tmp_result->valid == false ){
            return -1;
        }
        else {
            m_line_theta = ( tmp_result->slope ) *180/3.141592;
            m_line_center_2D.X = tmp_result->center.x;
            m_line_center_2D.Y = tmp_result->center.y;
            if ( debug_print ) fprintf(stderr,"theta:%lf  line center: %lf %lf \n",m_line_theta,m_line_center_2D.X,m_line_center_2D.Y);
        }
    }
    else {

    }
    is_new_img = false;
    return 0;
}


void Obstacle::ThreadMotion()
{
    motion = new Motion();

    motion->poseInit();
    //Head::GetInstance()->MoveByAngle(0,10);
    Walking::GetInstance()->Start();
    int tmp_img_result, tmp_RL_return;
    while ( m_execute ){//always true
        motion->CheckStatus();
    }
}

int Obstacle::CheckLine()
{

}

int Obstacle::Turn(int direction)
{
	if ( direction %2 == 0) {

	}
	else {

	}
}

int Obstacle::LostDispose()
{

}
