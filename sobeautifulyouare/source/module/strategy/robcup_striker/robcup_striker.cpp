/*
 *  +- 40 10, 判断方向
 * 
 */
#include "robcup_striker.h"

Robcup_striker::Robcup_striker()
{
    m_imgRes_ball = new ColorFindResult();
    m_imgPro_ball = new ColorFind();
    m_imgRes_goal = new ColorFindResult();
    m_imgPro_goal = new ColorFind();

    m_execute = true;
    m_process_state = FINDBALL;

	m_MAXTurnCount = 200;

    m_ball_center.x = 0; m_ball_center.y = 0;
    m_goal_center.x = 0; m_goal_center.y = 0;


    unit_pan = 0.5;
    pan_range = Head::GetInstance()->GetLeftLimitAngle(); 
    tilt_min = Head::GetInstance()->GetBottomLimitAngle();
    tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min	;
    unit_tilt = 0.5;

    m_FBstep = 10;
    m_FBstep_straight = 10;
    m_FBstep_goal = 10;
    m_FBstep_ApproachMin = 5;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0;
    m_RLturn_goal = 0;
    m_RLturn_straight = 0.425;
    m_unit_RLturn = 0.15;	
    m_MAX_RLturn = 35;
    m_RLstep_straight = 0;
    m_RLstep_goal = 0;
    m_RLstep = 0;
    m_unit_RLstep = 0.3;	
    m_MAX_RLstep = 30;

    debug_print = 1;
}
Robcup_striker::~Robcup_striker()
{
}

void Robcup_striker::ThreadMotion() 
{
    fprintf(stderr,"Striker begin!\n");

    motion = new Motion();
    motion->poseInit();

    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_ball);
    tmp_proc->load("redbox.txt");
    tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_goal);
    tmp_proc->load("lanmen.txt");
    tracker = new BallTracker();
    follower = new BallFollower();

    int tmp_img_result=0, tmp_return_value =0, tmp_img_result2=0;

    while(0){if ( debug_print ) fprintf(stderr,"state %d. FB:%lf.  RLstep:%lf.  RLturn:%lf. \n",m_process_state,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->Y_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);
         m_RLstep_goal = 10;
         m_RLturn_goal = -5;

        if(m_RLstep < m_RLstep_goal){
            m_RLstep += 1.2*m_unit_RLstep;
        }
        else{
            m_RLstep -= m_unit_RLstep;
        }
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += m_unit_RLturn;
        }
        else{
            m_RLturn -= m_unit_RLturn;
        }
		m_FBstep = -1;
        motion->walk(m_FBstep,m_RLstep,m_RLturn);
  /*
        double tmp_pan=0,tmp_tilt=-5;
        scanf("%lf%lf", &tmp_pan, &tmp_tilt);
        Head::GetInstance()->MoveByAngle(tmp_pan, tmp_tilt); 
        GetImageResult(0);
        GetImageResult(1);
 */
        /*
           getchar();
           Walking::GetInstance()->Start();
           m_RLstep += m_unit_RLstep;
        //motion->walk(-1,m_RLstep,0);
        motion->walk(-1,0,m_RLstep);
        usleep(10*8000);
        Walking::GetInstance()->Stop();
        */
    }
   // Walking::GetInstance()->Start();

    Head::GetInstance()->MoveByAngle(0,25);
    while(m_execute){if ( debug_print ) fprintf(stderr,"state %d. FB:%lf.  RLstep:%lf.  RLturn:%lf. \n",m_process_state,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->Y_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);
   
        motion->CheckStatus();
        if ( m_process_state == FINDBALL ){
            tmp_img_result = GetImageResult(0);
            tmp_return_value = tracker->SearchAndTracking(m_ball_center_2D);
            if(tmp_return_value == 1)
            {
                follower->Process(tracker->ball_position);
                if(follower->IsClose != 0)
                {
                    motion->walk(0,0,0);
        	   Head::GetInstance()->MoveByAngle(0, 25); 
		    Head::GetInstance()->Initialize();
                    m_process_state = JUDGE;
                }
            }
            else if(tmp_return_value == -1)
            {
                motion->walk(-1,0,10);
            }
            else
            {
                motion->walk(-1,0,0);
            }
        }
        else if ( m_process_state == JUDGE ){
	    static int judge_count = 0;
            tmp_img_result = GetImageResult(1);
            if ( tmp_img_result != -1 ){
		judge_count++;
                if ( judge_count > 2 )
			m_process_state = KICK;
            }
            else {
		 judge_count = 0;
                tmp_return_value = tracker->Search(0);
		usleep(10000);
                if ( tmp_return_value == -1 ){
                    tracker->Search(1);
                    m_FBstep = -1; m_RLstep = 0; m_RLturn = 0;
                    m_process_state = TURN;
            		motion->walk(m_FBstep,m_RLstep,m_RLturn);
                }
            }
        }
        else if ( m_process_state == TURN ){//TODO
            tmp_img_result = GetImageResult(1);
            if ( tmp_img_result != -1 ){
                m_process_state = KICK;
            }
            else {
                tmp_return_value = TurnGoal(0);
                if(tmp_return_value == -1)
                {
                    TurnGoal(1);
                    m_FBstep = -1; m_RLstep = 0; m_RLturn = 0;
                    m_process_state = FINDBALL;
                }
            }
		m_FBstep = -2;
            motion->walk(m_FBstep,m_RLstep,m_RLturn);
        }
        else if ( m_process_state == KICK ){
            tmp_img_result = GetImageResult(0);
            tmp_return_value = tracker->SearchAndTracking(m_ball_center_2D);
            if(tmp_return_value == 1)
            {
                follower->Process(tracker->ball_position);
                if(follower->KickBall != 0)
                {
                    Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
                    Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

                    if(follower->KickBall == -1)
                    {
                        Action::GetInstance()->Start(12);   // RIGHT KICK
                        fprintf(stderr, "RightKick! \n");
                    }
                    else if(follower->KickBall == 1)
                    {
                        Action::GetInstance()->Start(13);   // LEFT KICK
                        fprintf(stderr, "LeftKick! \n");
                    }
    				while(Action::GetInstance()->IsRunning() == true) usleep(8000);
					Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
                }
            }
            else if(tmp_return_value == -1)
            {
                m_process_state = FINDBALL;
            }
            else
            {
                motion->walk(-1,0,0);
            }
        }

    }

    pthread_exit(NULL);
}

int Robcup_striker::GetImageResult(int result_type)
{
    static cv::Point2f not_found_p(-1,-1); 
    while ( is_new_img == false ) usleep(8000);
    if ( result_type == 0){
        m_imgPro_ball->imageProcess(frame,m_imgRes_ball);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_ball);
        if ( tmp_result->valid == false ){
            m_ball_center = not_found_p;
            m_ball_center_2D.X = -1;m_ball_center_2D.Y = -1;
            return -1;
            if ( debug_print ) fprintf(stderr,"Can't find the ball!\n");
        }
        else {
            m_ball_center = tmp_result->center;
            m_ball_center_2D.X = m_ball_center.x;
            m_ball_center_2D.Y = m_ball_center.y+28;
            if ( debug_print ) fprintf(stderr,"ball_center:%lf %lf  \n",m_ball_center.x,m_ball_center.y);
        }
    }
    else if ( result_type == 1){
        m_imgPro_goal->imageProcess(frame,m_imgRes_goal);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_goal);
        if ( tmp_result->valid == false ){
            m_goal_center = not_found_p;
            if ( debug_print ) fprintf(stderr,"Can't find the hole!\n");
            return -1;
        }
        else {
            m_goal_center = tmp_result->center;
            if ( debug_print ) fprintf(stderr,"goal_center:%lf %lf  \n",m_goal_center.x,m_goal_center.y);
        }

    }
    is_new_img = false;
    return 0;

}

int Robcup_striker::TurnGoal(bool count_reset)
{
    static int count = 0;
printf("   %d\n",count);
    if(count_reset)
        count = 0;
    else {
        if(count > m_MAXTurnCount)
            return -1;
        else
        {
            m_RLstep_goal = 20;
            m_RLturn_goal = -10;
	    count++;
        }
        if(m_RLstep < m_RLstep_goal){
            m_RLstep += m_unit_RLstep;
        }
        else{
            m_RLstep -= m_unit_RLstep;
			//m_RLstep = 0;
        }
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += m_unit_RLturn;
			//m_RLturn = 0;
        }
        else{
            m_RLturn -= 0.415*m_unit_RLturn;
        }
		m_FBstep = -1;
    }
    return 0;
}
