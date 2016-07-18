
#include "golf.h"

Golf::Golf()
{
    m_imgRes_ball = new ColorFindResult();
    m_imgPro_ball = new ColorFind();
    m_imgRes_hole = new ColorFindResult();
    m_imgPro_hole = new ColorFind();

    m_execute = true;
    m_process_state = APPROACH;
    m_pre_action = 0;

    m_ball_center.x = 0; m_ball_center.y = 0;
    m_hole_center.x = 0; m_hole_center.y = 0;
    m_ball_radius = 0.0;

    m_ApproachBallTop = 200;
    m_AddressHoleCenter = 160;
    m_AddressDiff = 5;
    m_AddressBallCenter.x = 140;
    m_AddressBallCenter.y = 120;
    m_SwingBallCenter.x = 40;
    m_SwingBallCenter.y = 180;
    m_SwingDiff = 5;

    //TODO go straight first  
    unit_pan = 0.5;
    pan_range = Head::GetInstance()->GetLeftLimitAngle(); 
    tilt_min = Head::GetInstance()->GetBottomLimitAngle();
    tilt_range = Head::GetInstance()->GetTopLimitAngle() - tilt_min	;

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
    motion = new Motion();
    motion->poseInit();
    Head::GetInstance()->MoveByAngle(0,15);   
    Walking::GetInstance()->Start();

    int tmp_img_result=0, tmp_return_value =0, tmp_img_result2;
    double tmp_pan=0,tmp_tilt=-5;
    while(false){
        //scanf("%lf%lf", &tmp_pan, &tmp_tilt);
        //Head::GetInstance()->MoveByAngle(tmp_pan, tmp_tilt); 
        m_RLstep += m_unit_RLstep;
        motion->walk(1,m_RLstep,0);
		usleep(10*8000);
    }
    while(true)
    {
        motion->CheckStatus();

        if ( m_process_state == ADDRESS ){
            tmp_img_result = GetImageResult(0);
            tmp_img_result2 = GetImageResult(1);
            if ( tmp_img_result != -1 || tmp_img_result2 !=-1 ){ 
                tmp_return_value = AddressHole();   
                if(tmp_return_value == 1){
                    m_process_state = APPROACH;
                }
            }
        }
        else if( m_process_state == APPROACH ){
            tmp_img_result = GetImageResult(0);
            if ( tmp_img_result != -1 ){ 
                tmp_return_value = ApproachBall();
                if ( tmp_return_value == 1){
                    Walking::GetInstance()->Stop();
                    m_process_state = SWING;
                }
            }
        }
        else if ( m_process_state == SWING ){
            tmp_img_result = GetImageResult(0);
            if ( tmp_img_result != -1 ){ 
                tmp_return_value = Swing();
            }
        }
        motion->walk(m_FBstep,m_RLstep,m_RLturn);
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
        }
        else {
            m_ball_center = tmp_result->center;
            //m_ball_radius = tmp_result->radius;
        }
    }
    else {
        m_imgPro_hole->imageProcess(frame,m_imgRes_hole);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_hole);
        if ( tmp_result->valid == false ){
            return -1;
        }
        else {
            m_hole_center = tmp_result->center;
        }

    }
    is_new_img = false;
    return 0;
}

int Golf::ApproachBall()//I need the ball center xy function && check the valid of Tiny
{
    //HeadTracker(m_ball_center);
    //double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
    double tilt = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_TILT);
    double tilt_percent = (tilt - tilt_min)/tilt_range;
    double RLdiff = m_ball_center.x - m_SwingBallCenter.x;
    double Tiny = 1.0;
    if ( tilt_percent < 0 ){
        tilt_percent = -tilt_percent;
    }
    if(tilt <= (tilt_min + MX28::RATIO_VALUE2ANGLE) ){
        if ( m_ball_center.y > m_ApproachBallTop){
            return 1;    
        }
        else {
            Tiny=0.5;
        }
    }
    m_FBstep_goal = m_MAX_FBstep*tilt_percent;
    if(m_FBstep_goal < m_FBstep_ApproachMin && Tiny==0.0){
        m_FBstep_goal = m_FBstep_ApproachMin;
    }
    m_RLstep_goal = m_MAX_RLstep*RLdiff/IMG_WIDTH;
    if (m_FBstep < m_RLstep_goal){
        m_FBstep += Tiny*m_unit_FBstep;
    }
    else {
        m_FBstep -= Tiny*m_unit_FBstep;
    }
    if ( m_RLstep < m_RLstep_goal ){
        m_RLstep += Tiny*m_RLstep_goal;
    }
    else {
        m_RLstep -= Tiny*m_RLstep_goal;
    }
    m_RLturn = 0;

    return 0;
}

int Golf::AddressHole()//TODO move R, turn L
{
    double ball_diff = m_ball_center.x - m_AddressBallCenter.x;
    double hole_diff = m_hole_center.x - m_AddressHoleCenter;
    double diff = 0.7*ball_diff + 0.3*hole_diff;
    if ( fabs(diff) >  m_AddressDiff){
        m_FBstep = 1.0;
if (diff>0){
		m_RLstep_goal = m_MAX_RLstep*diff/IMG_WIDTH;
        if(m_RLstep < m_RLstep_goal){
            m_RLstep += m_unit_RLstep;
        }
        else{
            m_RLstep -= m_unit_RLstep;
        }
}
else {
        m_RLturn_goal = m_MAX_RLturn*diff/IMG_WIDTH;
        if(m_RLturn < m_RLturn_goal){
            m_RLturn += m_unit_RLturn;
        }
        else{
            m_RLturn -= m_unit_RLturn;
        }
    }
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
    if( RLdiff < m_SwingDiff || swing_flag){
        //swing_flag = 1;//TODO 多次击球？
        Action::GetInstance()->m_Joint.SetEnableBody(true, true);
        Action::GetInstance()->Start(81);
        //TODO Action::GetInstance()->m_Joint.SetEnableBody(true, true);
        Action::GetInstance()->Start(80);
    }
    else {
        if ( RLdiff > 0 ){
            //move right
        }
        else {
            //move left
        }
        //Walking->GetInstance()->Start();
        usleep(10*8000);
        Walking::GetInstance()->Stop();
    }
}

int Golf::HeadTracker(cv::Point2f pos)
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
        offset.X = pos.x - IMG_WIDTH/2;
        offset.Y = pos.y - IMG_HEIGHT/2;
        offset *= -1; // Inverse X-axis, Y-axis 
        offset.X *= (VIEW_H_ANGLE / IMG_WIDTH); // pixel per angle 
        offset.Y *= (VIEW_V_ANGLE / IMG_HEIGHT);
        Head::GetInstance()->MoveTracking(offset);
    }
}
