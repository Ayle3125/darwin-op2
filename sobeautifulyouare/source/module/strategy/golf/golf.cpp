
#include "golf.h"

Golf::Golf()
{
    m_imgRes_ball = new ColorFindResult();
    m_imgPro_ball = new ColorFind();
    m_imgRes_hole = new ColorFindResult();
    m_imgPro_hole = new ColorFind();

    m_execute = true;
    m_process_state = ADDRESS;
    m_pre_action = 0;

    m_ball_center.x = 0; m_ball_center.y = 0;
    m_hole_center.x = 0; m_hole_center.y = 0;
    m_ball_radius = 0.0;

    m_ApproachBallTop = 120;//TODO
    m_ApproachHoleTop = 95;
    m_AddressHoleCenter = 144.5;
    m_AddressDiff = 5;
    m_AddressBallCenter.x = 100;
    m_AddressBallCenter.y = 93;
    m_SwingBallCenter.x = 50;
    m_SwingBallCenter.y = 203;
    m_SwingDiff_X = 10;
    m_SwingDiff_Y = 16;

    //TODO go straight first  
    unit_pan = 0.5;
    pan_range = Head::GetInstance()->GetLeftLimitAngle(); 
    tilt_min = Head::GetInstance()->GetBottomLimitAngle();
    tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min;
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
    m_unit_RLturn = 5.0;
    m_MAX_RLturn = 35;
    m_RLstep_straight = 0;
    m_RLstep_goal = 0;
    m_RLstep = 0;
    m_unit_RLstep = 0.3;
    m_MAX_RLstep = 30;

    debug_print = 1;
}

Golf::~Golf()
{
}



void Golf::ThreadMotion()
{
//int cnt = 0;
    motion = new Motion();
    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_ball);
    tmp_proc->load("golf.txt");
    tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_hole);
    tmp_proc->load("golfgoal.txt");
    motion->poseInit();
    Head::GetInstance()->MoveByAngle(0,10);   
    //Walking::GetInstance()->Start();

    int tmp_img_result=0, tmp_return_value =0, tmp_img_result2=0;
    double tmp_pan=0,tmp_tilt=-5;


    while(0){if ( debug_print ) fprintf(stderr,"state %d. FB:%lf.  RLstep:%lf.  RLturn:%lf. \n",m_process_state,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->Y_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);
        scanf("%lf%lf", &tmp_pan, &tmp_tilt);
        Head::GetInstance()->MoveByAngle(tmp_pan, tmp_tilt); 
/*
getchar();
Walking::GetInstance()->Start();
        m_RLstep += m_unit_RLstep;
        //motion->walk(-1,m_RLstep,0);
		motion->walk(-1,0,m_RLstep);
        usleep(10*8000);
Walking::GetInstance()->Stop();
*/
        GetImageResult(0);
        GetImageResult(1);
    }

	//m_RLturn = 10.0;//turn left correct
    while(m_execute)
    {if ( debug_print ) fprintf(stderr,"state %d. FB:%lf.  RLstep:%lf.  RLturn:%lf. \n",m_process_state,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->Y_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);

        motion->CheckStatus();

        if ( m_process_state == ADDRESS ){
            tmp_img_result = GetImageResult(0);
            tmp_img_result2 = GetImageResult(1);
            if ( tmp_img_result != -1 || tmp_img_result2 !=-1 ){ 
                tmp_return_value = AddressHole(tmp_img_result,tmp_img_result2);   
                if(tmp_return_value == 1){if ( debug_print ) fprintf(stderr,"**************************************************state change !\n"); 
                    Walking::GetInstance()->Stop();
                    getchar(); 
                    Walking::GetInstance()->Start();
                    m_process_state = APPROACH;
					m_FBstep = 5.0; m_RLstep = 0.0; m_RLturn = 0.0;
                }
				else {
					m_FBstep =-2;
				}
            	motion->walk(m_FBstep,m_RLstep,m_RLturn);
            }
        }
        else if( m_process_state == APPROACH ){
			static int approach_count = 0;
            tmp_img_result = GetImageResult(1);
            if ( tmp_img_result != -1 ){ 
                tmp_return_value = ApproachBall();
                if ( tmp_return_value == 1){
					approach_count++;
					if ( debug_print ) fprintf(stderr,"***********************************approach_count:%d !\n",approach_count); 
					m_FBstep = 0.0; m_RLstep = 0.0; m_RLturn = 0.0;
					motion->walk(0,0,0);
					if ( approach_count>3){
						if ( debug_print ) fprintf(stderr,"**************************************************state change !\n"); 
                    Walking::GetInstance()->Stop();
                    getchar(); 
                    Walking::GetInstance()->Start();
					
					Head::GetInstance()->MoveByAngle(0,-20);
                   	motion->walk(0,0,0);
                    m_process_state = SWING;
					}
                }
				else {
					approach_count = 0;
				}
            }
            motion->walk(m_FBstep,m_RLstep,m_RLturn);
        }
        else if ( m_process_state == SWING ){
			static int swing_count = 0;
            tmp_img_result = GetImageResult(0);
            if ( tmp_img_result != -1 ){
                tmp_return_value = Swing();
				if ( tmp_return_value == 1){
					swing_count++;
					m_FBstep = 0.0; m_RLstep = 0.0; m_RLturn = 0.0;
					motion->walk(0,0,0);
					if ( debug_print ) fprintf(stderr,"***********************************swing_count:%d !\n",swing_count);  
if ( swing_count>1){
						if ( debug_print ) fprintf(stderr,"**************************************************Wow !\n"); 
	usleep(500 * 8000);
	
        Action::GetInstance()->m_Joint.SetEnableBody(true, true);
        Action::GetInstance()->Start(81);
		while ( Action::GetInstance()->IsRunning() ) usleep(8000);
        //Action::GetInstance()->m_Joint.SetEnableBody(true, true);
        Action::GetInstance()->Start(80);
}
				}
            }
			else {
				swing_count = 0;
				//TODO lost dispose: head track &| go back
				motion->walk(-5,0,0);
			}
        }
    }

}

int Golf::GetImageResult(int result_type)
{
    while ( is_new_img == false ) usleep(8000);
    if ( result_type == 0){
        m_imgPro_ball->imageProcess(frame,m_imgRes_ball);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_ball);
        if ( tmp_result->valid == false ){
            return -1;
            if ( debug_print ) fprintf(stderr,"Can't find the ball!\n");
        }
        else {
            m_ball_center = tmp_result->center;
            //m_ball_radius = tmp_result->radius;
            if ( debug_print ) fprintf(stderr,"ball_center:%lf %lf  \n",m_ball_center.x,m_ball_center.y);
        }
    }
    else if ( result_type == 1){
        m_imgPro_hole->imageProcess(frame,m_imgRes_hole);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_hole);
        if ( tmp_result->valid == false ){
            if ( debug_print ) fprintf(stderr,"Can't find the hole!\n");
            return -1;
        }
        else {
            m_hole_center = tmp_result->center;
            if ( debug_print ) fprintf(stderr,"hole_center:%lf %lf  \n",m_hole_center.x,m_hole_center.y);
        }

    }
    is_new_img = false;
    return 0;
}

int Golf::ApproachBall()//I need the ball center xy function && check the valid of Tiny// But the hole is better
{
    //HeadTrackTilt(m_ball_center);
    //double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
    static double Tiny = 1.0;

    if ( m_hole_center.y > m_ApproachHoleTop ){
		return 1;        
		//Head::GetInstance()->MoveByAngleOffset(0,-1*unit_tilt);
    }
else {
/*
    double tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
    double tilt_percent = (tilt - tilt_min)/tilt_range;
    if ( tilt_percent < 0 ){
        tilt_percent = -tilt_percent;
    }
    if(tilt <= 0 ){
        return 1;    
    }
*/
    double RLdiff = m_hole_center.x - m_AddressHoleCenter;
	double FBdiff = m_ApproachBallTop - m_hole_center.y;

    m_FBstep_goal = m_MAX_FBstep*FBdiff/IMG_HEIGHT;
//    if(m_FBstep_goal < m_FBstep_ApproachMin && Tiny==1.0){
//        m_FBstep_goal = m_FBstep_ApproachMin;
//    }
    m_RLstep_goal = -m_MAX_RLstep*RLdiff/IMG_WIDTH;

    if ( debug_print ) fprintf(stderr,"address diff: FBstep_goal %lf  RLstep_goal %lf\n",m_FBstep_goal,m_RLstep_goal);
    if (m_FBstep < m_FBstep_goal){
        m_FBstep += m_unit_FBstep;
    }
    else {
        m_FBstep -= m_unit_FBstep;
    }
    if ( m_RLstep < m_RLstep_goal ){
        m_RLstep += m_unit_RLstep ;
    }
    else {
        m_RLstep -= 0.3*m_unit_RLstep ;
    }
    m_RLturn = 0;
}
    return 0;
}

int Golf::AddressHole(int ball_valid, int hole_valid)//TODO move R, turn L
{
    //HeadTrackTilt(m_ball_center);
    double ball_diff=0, hole_diff=0; 
    if ( ball_valid==0)
        ball_diff = m_ball_center.x - m_AddressBallCenter.x;
    if ( hole_valid==0)
        hole_diff = m_hole_center.x - m_AddressHoleCenter;
    if ( debug_print ) fprintf(stderr,"address diff: ball %lf  hole %lf\n",ball_diff,hole_diff);
    if ( fabs(ball_diff) >  m_AddressDiff || fabs(hole_diff) >  0.5*m_AddressDiff){

        m_RLstep_goal = -1*m_MAX_RLstep*ball_diff/IMG_WIDTH;
        if(m_RLstep < m_RLstep_goal){
            m_RLstep += m_unit_RLstep;
			//m_RLstep = 0;
        }
        else{
            m_RLstep -= m_unit_RLstep;
        }
		double RL_Tiny = 0.3;
        m_RLturn_goal = -1*m_MAX_RLturn*hole_diff/IMG_WIDTH;
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += m_unit_RLturn;
        }
        else{
            m_RLturn -= m_unit_RLturn;
			//m_RLturn = 0.0;
        }
    if ( ball_valid!=0)
         m_RLstep = 0;
    if ( hole_valid!=0)
		 m_RLturn = 0;
    }
    else {
        return 1;
    }
    return 0;
}

int Golf::Swing()//check the light move
{
    static bool swing_flag = 0;
    double RLdiff = m_ball_center.x - m_SwingBallCenter.x;
    double FBdiff = m_ball_center.y - m_SwingBallCenter.y;
    if ( debug_print ) fprintf(stderr,"swing diff: RL %lf  FB %lf\n",RLdiff,FBdiff);
    if( ( fabs(RLdiff) < m_SwingDiff_X || m_ball_center.x <(m_SwingBallCenter.x+RLdiff) ) && fabs(FBdiff) < m_SwingDiff_Y){
        //swing_flag = 1;//TODO 多次击球？
		return 1;
    }
    else {
        m_RLstep_goal = -1*m_MAX_RLstep*RLdiff/IMG_WIDTH;
        m_FBstep_goal = -1*m_MAX_FBstep*FBdiff/IMG_HEIGHT;
        if (m_FBstep < m_FBstep_goal){
            m_FBstep += 0.3*m_unit_FBstep;
        }
        else {
            m_FBstep -= m_unit_FBstep;
        }
        if ( m_RLstep < m_RLstep_goal ){
            m_RLstep += m_unit_RLstep ;
        }
        else {
            m_RLstep -= m_unit_RLstep ;
        }
  //      Walking::GetInstance()->Start();
        motion->walk(m_FBstep,m_RLstep,m_RLturn);
        //usleep(50*8000);
    //    Walking::GetInstance()->Stop();
		//usleep(50*8000);
//getchar();
    }
}

int Golf::HeadTrackTilt(cv::Point2f pos)
{
    static int NoFindCount = 0;
    static const int NoFindMaxCount =4;
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
        Point2D offset;
        //offset.X = pos.x - IMG_WIDTH/2;
        offset.Y = pos.y - IMG_HEIGHT/2;
        if ( offset.Y > 0 ){
            offset *= -1; // Inverse X-axis, Y-axis 
            //offset.X *= (VIEW_H_ANGLE / IMG_WIDTH); // pixel per angle
            offset.X = 0; 
            offset.Y *= (VIEW_V_ANGLE / IMG_HEIGHT);
            Head::GetInstance()->MoveTracking(offset);
        }
    }
}
