
#include "obstacle.h"

Obstacle::Obstacle()
{
    m_imgRes_line = new FindLineResult();
    m_imgProc_line = new FindLine();
	m_imgRes_color = new ColorFindResult();
    m_imgProc_color = new ColorFind();

    m_pixel_num = 0;
    m_PixelJudgeNum = 3000;//TODO
    m_obstacle_center_2D.X =0;
    m_obstacle_center_2D.Y =0;
    m_ObstacleDiff = 10;
    m_ObstacleCenterNeed[0] = 210;
    m_ObstacleCenterNeed[1] = 100;
    m_line_center_2D.X =0;
    m_line_center_2D.Y =0;
	m_line_theta = 0;

    m_NolookMaxTime = 5;
    m_nolooktime = 0;

    m_execute = 1;
    m_pre_action = 0;
    m_process_state = BEFORE1;


    //TODO go straight first    
    m_FBstep = 10;
    m_FBstep_straight = 10;
    m_FBstep_goal = 0;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0.425;
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

int Obstacle::GetImageResult_obstacle(int result_type)
{
    while ( is_new_img == false ) usleep(8000);
    
    if ( result_type == 0) {
	m_imgProc_line->imageProcess(frame,m_imgRes_line);
        FindLineResult *tmp_result = dynamic_cast<FindLineResult *>(m_imgRes_line);
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
    else if ( result_type == 1) {
	m_imgProc_color->imageProcess(frame,m_imgRes_color);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_color);
        if ( tmp_result->valid == false ){
            return -1;
        }
        else {
			//m_pixel_num =
	    m_obstacle_rect = tmp_result->rect;
            m_obstacle_center_2D.X = tmp_result->center.x;
            m_obstacle_center_2D.Y = tmp_result->center.y;
            if ( debug_print ) fprintf(stderr,"pixle:%d  line center: %lf %lf \n",m_pixel_num,m_obstacle_center_2D.X,m_obstacle_center_2D.Y);
        }
    }
    is_new_img = false;
    return 0;
}


void Obstacle::ThreadMotion()
{
    motion = new Motion();
    motion->poseInit();
    //is_cap = false;
    //Head::GetInstance()->MoveByAngle(0,10);
    Walking::GetInstance()->Start();
    motion->walk(m_FBstep_straight, m_RLstep_straight, m_RLturn_straight);
    int tmp_img_result=0, tmp_turn_result=0, turn_flag = 0;
    int tmp_count=0;
    while ( m_execute ){//always true
	if ( debug_print ) fprintf(stderr,"state %d\n",m_process_state);
        Walking::GetInstance()->Start();
        motion->CheckStatus();
        if ( m_process_state == BEFORE1){
            //is_cap = true;
            tmp_img_result = GetImageResult_obstacle(1);
            if ( tmp_img_result == -1 ){
                if ( debug_print ) fprintf(stderr,"Can't find the Obstacle!\n");
                //TODO LostDispose();//need turn around  
            }
            else {
				if ( m_pixel_num > m_PixelJudgeNum || turn_flag ){
                    turn_flag = 1;
                    tmp_turn_result = TurnAdjust(0); 
                    if ( tmp_turn_result == 0 ){
                        m_FBstep = m_FBstep_straight;
                        m_RLturn = m_RLturn_straight;
                        ChangeObstacleColor();
                        turn_flag = 0;
                        m_pre_state = BEFORE1;
                        m_process_state = TURN;
                    }
                    else {
                        motion->walk(m_FBstep,m_RLstep,m_RLturn);
                    }
                }
			}
        }
        else if ( m_process_state == BEFORE2){
            tmp_img_result = GetImageResult_obstacle(1);
            if ( tmp_img_result == -1 ){
                if ( debug_print ) fprintf(stderr,"Can't find the Obstacle!\n");
                //TODO LostDispose();//need turn around  
            }
            else {
				if ( m_pixel_num > m_PixelJudgeNum || turn_flag ){
                    turn_flag = 1;
                    tmp_turn_result = TurnAdjust(1); 
                    if ( tmp_turn_result == 0 ){
                        m_FBstep = m_FBstep_straight;
                        m_RLturn = m_RLturn_straight;
                        ChangeObstacleColor();
                        turn_flag = 0;
                        m_pre_state = BEFORE2;
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
        else if ( m_process_state == TURN ){//根据线的斜率和位置调整
            static double Line_check = 200;
            static double m_LineThetaNeed = 70; 
			static int turn_time = 0;
            tmp_img_result = GetImageResult_obstacle(0);
            if ( tmp_img_result == 1 ){
                if ( m_line_center_2D.X > Line_check ) {//TODO 感觉丢线可能很大
                    if ( fabs(m_line_theta) > m_LineThetaNeed ){//TODO
                        m_pre_state = TURN;
						turn_time = 0;
						if ( m_pre_state == BEFORE1 ){
							m_process_state = BEFORE2;
						}
						else {
                        	m_process_state = BEFORE1;
						}
                    }
                    else {
                        m_RLturn_goal = (m_LineThetaNeed - fabs(m_line_theta) )/90* m_MAX_RLturn;
                        if ( m_pre_state == BEFORE1 ){
                            m_RLturn_goal *= -1;
                        }
                        if(m_RLturn < m_RLturn_goal){
                            m_RLturn += m_unit_RLturn;
                        }
                        else{
                            m_RLturn -= m_unit_RLturn;
                        }
                        Walking::GetInstance()->A_MOVE_AMPLITUDE = m_RLturn;
                    }
                }
                else {
					turn_time ++;
					if ( turn_time > 500 ) {//没看到线不要走太远= =
						m_pre_state = TURN;
						turn_time = 0;
						if ( m_pre_state == BEFORE1 ){
							m_process_state = BEFORE2;
						}
						else {
                        	m_process_state = BEFORE1;
						}
					}
                    motion->walk(m_FBstep_straight,m_RLstep_straight,m_RLturn_straight);
                }
            }
            if ( tmp_count > 10) {
                tmp_count = 0;
                Walking::GetInstance()->Stop();
                getchar();
            }
            tmp_count++;
        }
    }
}

int Obstacle::CheckLine()
{

}
int Obstacle::TurnAdjust(int direction) // OK return 0
{
    int tmp_return = 0;
    double diff = m_obstacle_center_2D.X - m_ObstacleCenterNeed[direction];
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
            m_RLturn += 0.5*m_unit_RLturn;
        }
        else{
            m_RLturn -= 0.5*m_unit_RLturn;
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
/*
    double diff = m_line_center_2D.X - ( IMG_WIDTH/2 );
    if ( fabs ( diff  ) > m_CenterDiff ){
        tmp_return =1;
        m_RLturn_goal=  -1*m_MAX_RLturn * 0.5*diff / ( IMG_WIDTH/2 );//change Y
        if ( diff > 0 ){
            m_pre_action = -1;
        }
		else {
			m_pre_action = 1;
		}
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += 0.5*m_unit_RLturn;
        }
        else{
            m_RLturn -= 0.5*m_unit_RLturn;
        }
    }
    if ( debug_print ) fprintf(stderr,"RLfix:turn: %lf\n", m_RLturn);
*/
    return tmp_return;
}

void Obstacle::ChangeObstacleColor()
{

}
