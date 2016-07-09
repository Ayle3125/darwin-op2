/*
 *  +- 40 10, 判断方向
 * 
 */
#include "robcup_striker.h"

Robcup_striker::Robcup_striker()
{
	//imgRes = new ImgProcResult();//TODO
	//imgProc = new ImgProc();

    m_process_state = FINDBALL;

    m_ball_center_2D.X = -1; m_ball_center_2D.Y = -1;
    m_ball_center_angle.X = -1; m_ball_center_angle.Y = -1;
    m_line_center_2D.X = -1; m_line_center_2D.Y = -1;
    m_goalfoot1.X = -1; m_goalfoot1.Y = -1;
    m_goalfoot2.X = -1; m_goalfoot2.Y = -1;
    m_ball_found = 0;
    m_NoBallMaxCount = 5;
    m_goal_found = 0;
    m_line_found = 0;
    m_line_Kvalue = 0;

    m_dribble_pan = 10;
    m_is_dribble = 1;

    m_LongShotRightAngle = -10;
    m_LongShotLeftAngle = 0;
    m_LongShotTopAngle = -5;//TODO
    m_kick_ball_count = 0;
    m_KickBallMaxCount = 3;
    m_LineTopValue = 180;//TODO

    m_FBstep = 0;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0;
    m_unit_RLturn = 1.0;
    m_MAX_RLturn = 35;
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
    if(debug_print) fprintf(stderr,"striker begin!\n");

    linepro = new sideline();
    // robotpro = new findrobot();
    ballpro = new followball();
    goalpro = new goalpost();

    tracker = new BallTracker();
    follower = new BallFollower();
    /* //compasspro dbg
       compasspro->loadConfig();
       while ( false ){
       motion->walk(-5, 0, -25);
       double tmp = compasspro->GetAngle();
#include <iostream>
cout << tmp << endl;
}
*/

      motion->poseInit();

while ( false)
{
       /*
       pthread_mutex_lock(&mut);
       if( is_new_img == true){
       pthread_cond_signal(&cond);
       }
       is_new_img = false;
       pthread_mutex_unlock(&mut);
       */
    while( is_new_img == false) usleep(8000);

    motion->CheckStatus();
    usleep(5*8000);//TODO
    if( m_process_state == FINDBALL){
        if ( debug_print) printf("state :  FINDBALL\n");
        //GetImageResult(frame,BALL);
        	/*
           double tilt,pan;
           scanf("%lf%lf", &pan, &tilt);
           Head::GetInstance()->MoveByAngle(pan,tilt);
           GetImageResult(frame,GOALPOST);

           double x,y,a;
           scanf("%lf%lf%lf", &x, &y, &a);
           motion->walk(x,y,a);
           usleep(10*8000);
         	*/
        FindBall();
    }        
    if ( m_process_state == DRIBBLE ){
        usleep(5*8000);
        if ( debug_print) printf("state : DRIBBLE\n");
        //GetImageResult(frame,BALL);
        //motion->walk(0, 0, 0);
        Dribble();
        //m_process_state = KICK;
    }
    if ( m_process_state == KICK ){
        if ( debug_print) printf("state : KICK\n");
        //GetImageResult(frame,BALL);
        //GetImageResult(frame,LINE);
        KickAdjust();
    }
}

pthread_exit(NULL);
}

void Robcup_striker::FindBall()
{
    static int no_ball_count = 0;
    static const int MaxNoBallCount = 5; 
    static int found_count = 0;
    static int MaxFoundCount = 200;
    if ( tracker->limit_mode != 0){
        tracker->ChangeLimit(20, -10, 30, 0);
    }


    m_ball_found = tracker->SearchAndTracking(m_ball_center_2D); 
    if ( debug_print == 1 ) printf("ballfound:%d \n", m_ball_found);
    no_ball_count = 0;
    if ( m_ball_found == 1){//found
        found_count++;
        if ( debug_print == 1 ){
            printf("\n*****************************%d\n",found_count);
        }
        if (  found_count >  MaxFoundCount) {
            MaxFoundCount = 10;
            found_count = 0;
            m_FBstep = 0.0;
            m_RLturn = 0.0;
            motion->walk(m_FBstep, 0, m_RLturn);
            usleep(80*8000);
            double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
            if ( pan > 0) {
                Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
                Action::GetInstance()->Start(140);   // Long shot
                fprintf(stderr, "LeftKick! \n");
            }
            else {
                Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
                Action::GetInstance()->Start(130);   // Long shot
                fprintf(stderr, "RightKick! \n");
            }
        }
        follower->Process(tracker->ball_position);
        //usleep(5*8000);
        if ( follower->IsClose == 1 ){
            if ( debug_print == 1 ){
                printf("kick ready");
                //	getchar();
            }
            /*
            //motion->walk(0, 0, 0);//stop to check compass
            if ( m_is_dribble == 1 ){
            m_process_state = DRIBBLE;
            }
            else {
            m_process_state = KICK;
            }
            */
        }//TODO !!! dirbble is not use now
    }
    else if ( m_ball_found == -1){// the area now can not find
        if ( debug_print == 1 ) printf("go straight\n");
        m_FBstep = 10.0;
        m_RLturn = 0.0;
        motion->walk(m_FBstep, 0, m_RLturn);
        //usleep(50*8000);
    }
    else if ( m_ball_found == 2){// found then lost
        if ( debug_print == 1 ) printf("go back\n");
        /*
           double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
           if ( pan > 0) {
           Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
           Action::GetInstance()->Start(130);   // Long shot
           fprintf(stderr, "RightKick! \n");
           }
           else {
           Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
           Action::GetInstance()->Start(130);   // Long shot
           fprintf(stderr, "RightKick! \n");
           }
           */

        m_FBstep = -10.0;
        m_RLturn = 0.0;
        motion->walk(m_FBstep, 0, m_RLturn);

        usleep(50*8000);
    }
    else{ //finding
        no_ball_count ++;
        //	if ( no_ball_count >MaxNoBallCount) {
        m_FBstep = 0.0;
        m_RLturn = 0.0;
        motion->walk(m_FBstep, 0, m_RLturn);
        //	}
    }
}

int Robcup_striker::FindGoal()
{
    int goal_result = 0; // 0: no goal  1:goal found  -1:can't get two goalpost(close to goalpost)
    static int one_goalpost_count = 0;
    const int MaxOnegoalCount = 1005;//TODO
    static int NoGoalCount = 0;
    static const int max_noGoalCount = 100;
    static const int m_dribble_pan = 30;
    if ( goalpro->goal_number == 0){//no goal //however i don't think it is useful...so maybe use in the future...201604Robocup
        /*
           if ( tracker->limit_mode != 1){
           tracker->ChangeLimit(20, 10, 30, 1);//TODO
           }
           NoGoalCount++;
           if ( NoGoalCount > max_noGoalCount ){//can not find, dribble first
           NoGoalCount = 0;
        // m_process_state = DRIBBLE;
        }
        else {
        tracker->Search(0);
        }
        */
        goal_result = 0;
    }
    else if ( m_goal_found == 2 ){
        one_goalpost_count = 0;
        Point2D mid_goalpost = ( m_goalfoot1 + m_goalfoot2)/2;
        tracker->Process(mid_goalpost);
        Head::GetInstance()->MoveTracking( tracker->ball_position );
        goal_result = 1;
    }
    else {
        one_goalpost_count++;
        if (  one_goalpost_count >  MaxOnegoalCount ){
            one_goalpost_count = 0;
            goal_result = -1;
        }
    }
    return goal_result;

}

void Robcup_striker::Dribble()
{
    static int no_ball_count = 0;
    const static int CheckTime = 10;//TODO
    static int dribble_ball_count = 0;
    m_ball_found = tracker->SearchAndTracking(m_ball_center_2D); 
    m_ball_center_angle = tracker->ball_position;
    if ( debug_print == 1 ) printf("ballfound:%d \n", m_ball_found);
    if ( m_ball_found == 1){//found
        no_ball_count = 0;
        follower->Process(tracker->ball_position);
        CompassCheck();
        dribble_ball_count++;
        if ( dribble_ball_count > CheckTime ){
           // GetImageResult(frame,GOALPOST);
            dribble_ball_count = 0;
            int tmp = FindGoal();
            if ( tmp == 2 ){
                double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
                double pan_range = Head::GetInstance()->GetLeftLimitAngle(); 
                double pan_percent = pan / pan_range;
                if ( pan >-1*m_dribble_pan ){
                    if ( debug_print == 1 ) printf("绕球左转\n");
                    motion->walk(-5, 25, -5);//TODO
                }
                else  if  ( pan > m_dribble_pan ){
                    if ( debug_print == 1 ) printf("绕球右转\n");
                    motion->walk(-5, 30, 8);
                }
                int tmp = 100*pan_percent;
                usleep( abs(tmp)*8000);//TODO
            }
            else if (tmp == -1 ){
                m_is_dribble = 0;
                m_process_state = KICK;
            }
        }
        motion->walk(10, 0, 0);//dribble param
    }
    else {
        no_ball_count++;
        if (  no_ball_count > m_NoBallMaxCount){
            no_ball_count = 0;
            m_process_state = FINDBALL;
        }
    }
}

void Robcup_striker::KickAdjust()
{
    static int adjust_time = 0;
    static const int MaxAdjustTime = 100;
    if ( tracker->limit_mode != 4){
        tracker->ChangeLimit(10, -5, 30, 4);
    }
    adjust_time++;
    double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
    double pan_range = Head::GetInstance()->GetLeftLimitAngle(); 
    double pan_percent = pan / pan_range;
    double tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
    double tilt_min = Head::GetInstance()->GetBottomLimitAngle();		
    double tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min;
    double tilt_percent = (tilt - tilt_min) / tilt_range;

    static int no_ball_count = 0;


    m_ball_found = tracker->SearchAndTracking(m_ball_center_2D); 
    m_ball_center_angle = tracker->ball_position;
    if ( debug_print == 1 ) printf("ballfound:%d \n", m_ball_found);
    if ( m_ball_found == 1){//found
        no_ball_count = 0; 
        follower->Process(tracker->ball_position);
        if ( follower->IsClose == 1 ){

            if ( (adjust_time > MaxAdjustTime ) && ( m_line_found == 2 && m_line_center_2D.Y < m_LineTopValue ) ){

                if ( m_ball_center_angle.Y < m_LongShotTopAngle ){
                    if (m_kick_ball_count > m_KickBallMaxCount ){
                        Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
                        Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
                        Action::GetInstance()->Start(130);   // Long shot
                        fprintf(stderr, "RightKick! \n");
                    }
                    else {
                        m_kick_ball_count++;
                        if ( debug_print == 1 ) 
                            printf("kick ball count:%d \n", m_kick_ball_count);
                    }
                }
                else {
                    m_kick_ball_count = 0;
                    m_FBstep = m_unit_FBstep;
                    m_RLturn = m_MAX_FBstep * pan_percent;
                    motion->walk(m_FBstep, m_RLstep, m_RLturn);
                    if ( debug_print == 1 ) 
                        printf("FB:unit RL:%lf \n", m_RLturn);
                }
            }
            else {

            }
        }
    }
    else {
        no_ball_count++;
        if (  no_ball_count > m_NoBallMaxCount){
            adjust_time = 0;
            no_ball_count = 0;
            m_process_state = FINDBALL;
        }
    }
}

void Robcup_striker::GetImageResult(cv::Mat &frame)
{
	
}