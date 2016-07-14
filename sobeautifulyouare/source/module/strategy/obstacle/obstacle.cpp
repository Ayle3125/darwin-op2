
#include "obstacle.h"
#define TILT (20)
Obstacle::Obstacle()
{
    imgRes = new ColorFindResult();
    imgProc = new ColorFind();

    m_pixel_num = 0;
    m_PixelJudgeNum[0] = 1000;
    m_PixelJudgeNum[1] = 100;
    m_PixelJudgeNum[2] = 100;//TODO
    m_obstacle_center.x =0;
    m_obstacle_center.y =0;
    m_ObstacleDiff = 10;
    m_ObstacleCenterNeed[0] = 310;
    m_ObstacleCenterNeed[1] = 30;
    m_ObstacleCenterNeed[2] = 210;
	m_TurnPan[0] = 50;


    m_execute = 1;
    m_pre_action = 0;
    m_process_state = BEFORE1;


    //TODO go straight first    
    m_FBstep = 10;
    m_FBstep_straight = 10;
    m_FBstep_goal = 0;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0;
    m_RLturn_straight = 0.425;
    m_RLturn_goal = 0;
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

int Obstacle::GetImageResult()
{
    while ( is_new_img == false ) usleep(8000);
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        if ( debug_print ) fprintf(stderr,"Can't find the Obstacle!\n");
        return -1;
    }
    else {
        m_pixel_num = tmp_result->area;
        m_obstacle_rect = tmp_result->rect;
        m_obstacle_center = tmp_result->center;
        if ( debug_print ) fprintf(stderr,"color leftup: %lf %lf \n",  tmp_result->leftUp.x,  tmp_result->leftUp.y);
        if ( debug_print ) fprintf(stderr,"pixle:%lf  color center: %lf %lf \n",m_pixel_num,m_obstacle_center.x,m_obstacle_center.y);
    }

    is_new_img = false;
    return 0;
}


void Obstacle::ThreadMotion()
{
    motion = new Motion();
    ChangeObstacleColor(0);

    motion->walk(m_FBstep_straight, m_RLstep_straight, m_RLturn_straight);
    int tmp_img_result=0, tmp_rlfix_result=0, tmp_turn_result=0, turn_flag = 0;
    double pan,tilt;
    double pan_range = Head::GetInstance()->GetLeftLimitAngle();  
	double unit_pan = 0.5;
    motion->poseInit();
    Walking::GetInstance()->Start();
    while (false){
        ChangeObstacleColor(1);	
        m_process_state = LAST;
        motion->walk(0,0,0);
            tmp_img_result = GetImageResult();
    }
    while ( m_execute ){//always true
        if ( debug_print ) fprintf(stderr,"state %d. FB:%lf.  RL:%lf\n",m_process_state,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);
        //Walking::GetInstance()->Start();
        motion->CheckStatus();
        if ( m_process_state == BEFORE1){
            Head::GetInstance()->MoveByAngle(0,TILT);
            tmp_img_result = GetImageResult();
            if ( tmp_img_result == -1 ){
                //TODO LostDispose();//need turn around  
            }
            else {
                if ( m_pixel_num > m_PixelJudgeNum[0] || turn_flag ){
                    turn_flag = 1;
                    tmp_turn_result = TurnAdjust(0); 
                    if ( tmp_turn_result == 0 ){
                        m_FBstep = m_FBstep_straight;
                        m_RLturn = m_RLturn_straight;
                        turn_flag = 0;
                        m_pre_state = BEFORE1;
                        if ( debug_print ) fprintf(stderr,"**************************************************state before1 to turn !\n");
                        m_process_state = TURN;
                    }
                    else {
                        motion->walk(m_FBstep,m_RLstep,m_RLturn);
                    }
                }
                else {
					motion->walk(m_FBstep_straight, m_RLstep_straight, m_RLturn_straight);
                }
            }
        }
        else if ( m_process_state == BEFORE2){
            Head::GetInstance()->MoveByAngle(0,TILT);
            tmp_img_result = GetImageResult();
            if ( tmp_img_result == -1 ){
                if ( debug_print ) fprintf(stderr,"Can't find the Obstacle!\n");
                //TODO LostDispose();//need turn around  
            }
            else {
                if ( m_pixel_num > m_PixelJudgeNum[1] || turn_flag ){
                    turn_flag = 1;
                    tmp_turn_result = TurnAdjust(1); 
                    if ( tmp_turn_result == 0 ){
                        m_FBstep = m_FBstep_straight;
                        m_RLturn = m_RLturn_straight;
                        turn_flag = 0;
                        m_pre_state = BEFORE2;
                        if ( debug_print ) fprintf(stderr,"**************************************************state before2 to turn!\n");
        Walking::GetInstance()->Stop();
        getchar();
        Walking::GetInstance()->Start();
                        m_process_state = TURN;
                    }
                    motion->walk(m_FBstep,m_RLstep,m_RLturn);
                }
            }
        }
        else if ( m_process_state == BEFORE3){

        }
        else if ( m_process_state == LAST){
            //TODO finishing line?
        }
        else if ( m_process_state == TURN ){
            tmp_img_result = GetImageResult();
            static int turn_count = 0;
            static const int TurnMaxCount = 500; //TODO
            if ( tmp_img_result == -1 ){
                if ( debug_print ) fprintf(stderr,"Can't find the Obstacle!\n");
                turn_count++;
                //TODO 
				if ( m_pre_state == BEFORE1 ){
		        	Head::GetInstance()->MoveByAngleOffset(-1*unit_pan,0);
                }
                else {
                	Head::GetInstance()->MoveByAngleOffset(unit_pan,0);
                }
            }
            else {
                HeadTracker(m_obstacle_center);
                pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
                if ( debug_print ) {
            	    tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
					fprintf(stderr,"pan:%lf  tilt:%lf!\n",pan,tilt);
				}
                if ( fabs(pan) > m_TurnPan[0] ){ //TODO ?
                    ChangeObstacleColor(1);
                    if ( debug_print ) fprintf(stderr,"**************************************************state turn to next!\n");
 /*                   Walking::GetInstance()->Stop();
                    getchar();
                    Walking::GetInstance()->Start();
                    m_process_state = TURNNEXT;*/
                }
                else {
                    turn_count++;
                }
				tmp_rlfix_result = RLFixed();
                if( tmp_rlfix_result == 0 ){
                    m_FBstep = m_FBstep_straight; m_RLstep = m_RLstep_straight; m_RLturn = m_RLturn_straight; 
                }
                
            }
            motion->walk(m_FBstep, m_RLstep, m_RLturn);
            if ( turn_count > TurnMaxCount ){
                ChangeObstacleColor(1);
                m_process_state = TURNNEXT;
            }
        }
        else if ( m_process_state == TURNNEXT){
            double LR = 1.0;// +L -R
            tmp_img_result = GetImageResult();
            if ( tmp_img_result == 0 ){
                if ( debug_print ) fprintf(stderr,"Find the next Obstacle!\n");
                HeadTracker(m_obstacle_center);
            }
            pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
            if ( pan < 0 ){
                LR *= -1;
                pan *= -1;
            }
            if ( pan < unit_pan && tmp_img_result==0 ){
                    if ( debug_print ) fprintf(stderr,"**************************************************state turn next to before!\n");
/*                    Walking::GetInstance()->Stop();
                    getchar();
                    Walking::GetInstance()->Start();*/
                    if ( m_pre_state == BEFORE1 ){
                        m_process_state = BEFORE2;
                    }
                    else {
                        m_process_state = BEFORE1;
                    }
             }
             else {
                    pan -= unit_pan;
             }
            Head::GetInstance()->MoveByAngle(LR*pan,TILT);
            if ( debug_print ) fprintf(stderr,"pan:%lf  tilt:%lf!\n",MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN),MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT));
            m_RLturn_goal = LR*pan*m_MAX_RLturn/pan_range;
            if ( debug_print ) fprintf(stderr,"RLturn_goal: %lf !\n",m_RLturn_goal);
            if(m_RLturn < m_RLturn_goal){
                m_RLturn += 0.3*m_unit_RLturn;
            }
            else{
                m_RLturn -= 0.3*m_unit_RLturn;
            }
            m_FBstep = 1.0;
            motion->walk(m_FBstep,m_RLstep,m_RLturn);
        }
    }
}

int Obstacle::TurnAdjust(int direction) // OK return 0; else -1
{
    int tmp_return = 0;
    double diff = m_obstacle_center.x - m_ObstacleCenterNeed[direction];
    if ( fabs(diff) > m_ObstacleDiff ){
        tmp_return = -1;
        m_RLturn_goal = -1 * m_MAX_RLturn * diff /(IMG_WIDTH);
        if ( diff > 0 ){
            m_pre_action = -1;
        }
        else {
            m_pre_action = 1;
        }
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += 0.7*m_unit_RLturn;
        }
        else{
            m_RLturn -= 0.7*m_unit_RLturn;
        }
        m_FBstep = 1.0;
        if ( debug_print ) fprintf(stderr,"RLfix:turn: %lf\n", m_RLturn);
    }
    return tmp_return;
}

int Obstacle::LostDispose()
{

}


int Obstacle::RLFixed()
{
    int tmp_return = 0;
    static int LeftLimit = 10, RightLimit =310;
	if ( m_obstacle_center.x > RightLimit || m_obstacle_center.x <LeftLimit ){
		tmp_return = -1;
        int diff = 0;
	    if (m_obstacle_center.x > RightLimit ){
            diff = (-1)*(m_obstacle_center.x - RightLimit);
        }
        else {
            diff = LeftLimit - m_obstacle_center.x;
        }
        m_RLturn_goal = m_MAX_RLturn*diff/IMG_WIDTH;
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += 0.7*m_unit_RLturn;
        }
        else{
            m_RLturn -= 0.7*m_unit_RLturn;
        }
        m_FBstep = 1.0;
	}
    return tmp_return;
}

void Obstacle::ChangeObstacleColor(int number)
{
    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(imgProc);
    if ( number == 0 ){
        tmp_proc->load("redbox.txt");
    }
    else if ( number == 1) {
        tmp_proc->load("yellowbox.txt");
    }
    else if ( number == 2) {
		tmp_proc->load("redbox.txt");
    }
}

int Obstacle::HeadTracker(cv::Point2f pos)
{
    static int NoFindCount =0;
    static const int NoFindMaxCount = 4;
    if(pos.x < 0 || pos.y < 0)
    {
        if(NoFindCount < NoFindMaxCount)
        {
            Head::GetInstance()->MoveTracking();
            NoFindCount++;
        }
        else
            Head::GetInstance()->InitTracking();
    }
    else
    {
        NoFindCount = 0;
        Point2D offset;
        offset.X = pos.x - IMG_WIDTH/2;
        offset.Y = pos.y - IMG_HEIGHT/2;
        offset *= -1; // Inverse X-axis, Y-axis 
        offset.X *=0.5*(VIEW_H_ANGLE / IMG_WIDTH); // pixel per angle 
        // offset.Y *= 0.5*(VIEW_V_ANGLE / IMG_HEIGHT);
        offset.Y =10;
        Head::GetInstance()->MoveTracking(offset);
    }
}
