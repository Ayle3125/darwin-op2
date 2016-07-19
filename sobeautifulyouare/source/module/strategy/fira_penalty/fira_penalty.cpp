
#include "fira_penalty.h"

Fira_penalty::Fira_penalty()
{
    imgRes = new ColorFindResult;
    imgProc = new ColorFind;

    m_is_checkstatus = true;
    m_point_center_2D.x = 0;
    m_point_center_2D.y = 0;

    m_penalty_flag = 1;//1 followball ;2 findcolumn ;3 adjustment
    m_img_result = 0;

    m_NoBallMaxCount = 10;
    m_NoBallCount = m_NoBallMaxCount;
    m_GoalFBStep = 0;
    m_GoalRLTurn = 0;
    m_FBStep = 0;
    m_RLTurn = 0;
    m_UnitFBStep = 1.0;
    m_UnitRLTurn = 0.3;
    m_forward_count  = 0;
    m_forward_max = 5;
    m_KickBallMaxCount = 10;
    m_KickBallCount = 0;
    m_img_range = 5;
    m_pan_angle = 10;
    m_pan_max = -25;
    KickBall = 0;

    debug_print = 1;
}

Fira_penalty::~Fira_penalty()
{
}



void Fira_penalty::ThreadMotion()
{
    motion = new Motion();
    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(imgProc);
    tmp_proc->load("hongqiu.txt");
    motion -> poseInit();
    Head::GetInstance() -> MoveByAngle(0,m_pan_angle);
   motion -> walk(10,0,0);
    Walking::GetInstance()->Start();

	/*while(true)
{
 m_img_result = GetImageResult();
usleep(5*8000);
}*/
    while(true)
    {
        Walking::GetInstance()->Start();
        motion->CheckStatus();
        usleep(10*8000);
        if (  m_is_checkstatus ) {
            motion->CheckStatus();
        }

        m_img_result = GetImageResult();

       if(m_penalty_flag == 1)
        {
            if(debug_print) fprintf(stderr,"I 'm following the ball\n");
            Followball();
        }
        else if(m_penalty_flag == 2)
        {
            if(debug_print) fprintf(stderr,"I 'm finding the column\n");
            Findcolumn();
        }
        else if(m_penalty_flag == 3)
        {
            if(debug_print) fprintf(stderr,"I 'm adjusting to kick the ball \n");
            Adjustment();
        }
    }

}

void Fira_penalty::Followball()
{
    if(m_img_result == -1)
    {
       KickBall = 0;    //No ball
       if(m_NoBallCount > m_NoBallMaxCount)
       {// can not find a ball
           m_GoalFBStep = 0;
           m_GoalRLTurn = 0;
           Head::GetInstance()->MoveToHome();
           if(debug_print)fprintf(stderr, "[NO BALL]\n");
       }
       else
       {
           m_NoBallCount++;
           if(debug_print)fprintf(stderr, "[NO BALL COUNTING(%d / %d)]\n", m_NoBallCount, m_NoBallMaxCount);
       }
    }
    else
    {
        m_NoBallCount = 0;
        if(m_pan_angle > m_pan_max)
        {
            if(debug_print)fprintf(stderr,"pan angle : %d\n",m_pan_angle);
            m_pan_angle -= 1;
                Head::GetInstance() -> MoveByAngle(0,m_pan_angle);
        }
        if(m_forward_count < m_forward_max)
        {
            if(debug_print)fprintf(stderr,"I' m walking straight forward~\n");
            m_forward_count++;
            motion ->walk(5,0,0);
            usleep(50 * 8000);
        }
        else
        {
                /*if(m_point_center_2D.y > 120 + m_img_range)
                {
                    if(debug_print)fprintf(stderr,"I' m adjusting back\n");
                    m_GoalFBStep += m_UnitFBStep;
                }
                else if(m_point_center_2D.y < 120 - m_img_range)
                {
                    if(debug_print)fprintf(stderr,"I' m adjusting straight\n");
                    m_GoalFBStep  += m_UnitFBStep;
                }
                usleep(100*8000);
	            if(m_point_center_2D.x > 160 + m_img_range)
	            {
	                if(debug_print)fprintf(stderr,"I' m walking right~\n");
                    m_GoalRLTurn -= m_UnitRLTurn;
	            }
	            else if(m_point_center_2D.x < 160 - m_img_range)
	            {
	                if(debug_print)fprintf(stderr,"I' m walking left~\n");
                    m_GoalRLTurn -=m_UnitRLTurn;
                }*/
	         if(m_point_center_2D.x <=  160 + m_img_range && m_point_center_2D.x >= 160 - m_img_range && 
                    m_point_center_2D.y >= 120 - m_img_range && m_point_center_2D.y <= 120 + m_img_range){

	                    m_KickBallCount++;
                }
             else
             {
                 m_GoalFBStep = m_FollowMaxFBStep * m_percent_CenterDiff_Y;
                 if(m_GoalFBStep < m_FollowMinFBStep)
                     m_GoalFBStep = m_FollowMinFBStep;
                 m_GoalRLTurn = m_FollowMaxRLTurn *  m_percent_CenterDiff_X;
                 if(DEBUG_PRINT == true)
                     fprintf(stderr, "[FOLLOW(P:%.2f T:%.2f>%.2f]", pan, tilt, tilt_min);

             }

             if(m_FBStep < m_GoalFBStep)
                 m_FBStep += m_UnitFBStep;
             else if(m_FBStep > m_GoalFBStep)
                 m_FBStep = m_GoalFBStep;

             if(m_RLTurn < m_GoalRLTurn)
                m_RLTurn += m_UnitRLTurn;
             else if(m_RLTurn > m_GoalRLTurn)
                m_RLTurn -= m_UnitRLTurn;

             if(DEBUG_PRINT == true)
                fprintf(stderr, " (FB:%.1f RL:%.1f)", m_FBStep, m_RLTurn);
            motion -> walk(m_FBStep,0,m_RLTurn);
            Walking::GetInstance()->Stop();
            usleep(100*8000);
         }
    }

    if(m_KickBallCount >= m_KickBallMaxCount)
    {
        m_penalty_flag = 2;
        if(debug_print)fprintf(stderr,"I have arrived at following target~\n\n");
    }
}

void Fira_penalty::Findcolumn()
{
    Walking::GetInstance()->Stop();
    usleep(1000*8000);
}

void Fira_penalty::Adjustment()
{

}

int Fira_penalty::GetImageResult()
{
if(debug_print)fprintf(stderr,"X %lf Y %lf diffX %lf diffY %lf \n",m_point_center_2D.x,m_point_center_2D.y, m_percent_CenterDiff_X, m_percent_CenterDiff_Y);
   
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {
      m_point_center_2D.x = tmp_result->center.x;
        m_point_center_2D.y = tmp_result->center.y;
        m_percent_CenterDiff_X = fabs(m_point_center_2D.x - 160) / 320;
        m_percent_CenterDiff_Y = fabs(m_point_center_2D.y - 120) / 240;

        return 0;
    }
}

