/*
   Head 
   m_LeftLimit = 70;
   m_RightLimit = -70;
   m_TopLimit = 40; 
   m_BottomLimit = 40 - 65;

   Camera
   static const double VIEW_V_ANGLE = 46.0; //degree
   static const double VIEW_H_ANGLE = 58.0; //degree
   static int WIDTH = 320;
   static int HEIGHT = 240;
   */

#include "strategy.h"

Strategist::Strategist()
{
    vision_exe = 1;
    is_cap = true;
    is_new_img = false;

    m_angle_diff_opponentGoal = 0;
    m_OpponentAngle = OPPONENTGOAL;
    m_DribbleRightAngle = 40;
    m_DribbleLeftAngle = -40;//TODO

    debug_print = 1;
}

int Strategist::run()
{	
    if ( debug_print ) printf( "srategy run\n");
    pthread_mutex_init(&mut,NULL);
    pthread_cond_init(&cond,NULL);
    ThreadCreate();
    ThreadWait();

    return 0;
}

void Strategist::ThreadCreate() 
{
    if ( debug_print ) printf( "thread_create \n");
    int temp;
    memset(&thread, 0, sizeof(thread));

    if((temp = pthread_create(&thread[1], NULL, InternalThreadMotion, this)) != 0){
        if(debug_print) fprintf(stderr,"ThreadMotion failed!\n");
    }
    else{
        if(debug_print) fprintf(stderr,"ThreadMotion succ!\n");
    }

    if((temp = pthread_create(&thread[0], NULL, InternalThreadVision, this)) != 0){    
        if(debug_print) fprintf(stderr,"ThreadVision failed!\n");
    }
    else{
        if(debug_print) fprintf(stderr,"ThreadVision succ!\n");
    }

}

void Strategist::ThreadVision() 
{
    cv::VideoCapture cap(0);
    cap.set( CV_CAP_PROP_FRAME_WIDTH, IMG_WIDTH); 
    cap.set( CV_CAP_PROP_FRAME_HEIGHT, IMG_HEIGHT);
    if(!cap.isOpened())  // check if we succeeded
        fprintf(stderr,"Can not open the camera!\n");
    while (vision_exe)
    {
        /*pthread_mutex_lock(&mut);//相当于模拟单线程，锁不锁也没关系
          while( is_new_img == true){
          pthread_cond_wait(&cond, &mut);
          }
          is_new_img = true;
          pthread_mutex_unlock(&mut);*/
        if ( is_cap ){
            cap >> frame;
            is_new_img = true;
            flip(frame,frame,-1);
            if ( debug_print ){
                cv::imshow("cap", frame);		
                cv::waitKey(30); 
            }
        }

    }
    pthread_exit(NULL);

}

void Strategist::ThreadWait(void) 
{
    if(thread[0] !=0)
        pthread_join(thread[0],NULL);
    if(thread[1] !=0) 
        pthread_join(thread[1],NULL);
}
/*
   void Strategist::GetImageResult(cv::Mat &frame, ImgResultType rs)
   {


   if ( rs == BALL ){
   ballpro->imageProcess(frame);
   if( debug_print ) printf("ball center x:%d y:%d\n", ballpro->center.x,ballpro->center.y);
   CVpointTo2Dpoint( ballpro->center, m_ball_center_2D);
   }
   else if ( rs == GOALPOST ){
   goalpro->imageProcess(frame);
   m_goal_found = goalpro->goal_number;
   CVpointTo2Dpoint(goalpro->goal_foot1, m_goalfoot1);
   CVpointTo2Dpoint(goalpro->goal_foot2, m_goalfoot2);
   if( debug_print ) printf("gaol number: %d\n point1 %lf %lf  point2 %lf %lf ",m_goal_found,m_goalfoot1.X,m_goalfoot1.Y,m_goalfoot2.X,m_goalfoot2.Y);
   }
   else if ( rs == LINE ){
   linepro->imageProcess(frame);
   m_line_found = linepro->line_type;
   m_line_Kvalue = linepro->k_value;
   CVpointTo2Dpoint(goalpro->center, m_line_center_2D);
   }

   }
   */

int Strategist::CompassCheck()
{// degree 0~360  -> -180~ 180
    int check_time = 0;
    int check_result = 1;
    static int MaxCheckTime = 10; 
    m_angle_diff_opponentGoal = compasspro->GetAngle()  -  m_OpponentAngle;//任意角度还不行orz
    if ( m_angle_diff_opponentGoal  < 0 ){
        m_angle_diff_opponentGoal += 360;
    }//orz 开幕式太吵 只能啰嗦些

    if ( m_angle_diff_opponentGoal  > 180 ){
        m_angle_diff_opponentGoal = m_angle_diff_opponentGoal -360;
    }
    if ( debug_print ) printf("angle diff: %lf\n", m_angle_diff_opponentGoal);
    /*
       while ( abs(m_angle_diff_opponentGoal) > abs(m_DribbleLeftAngle)  ){
       check_time++;
       if ( check_time > MaxCheckTime ) {
       check_result = 0;
       break;
       }
       if (m_angle_diff_opponentGoal >m_DribbleRightAngle  ) {
       if ( debug_print == 1 ) printf("turn left \n");
       motion->walk(-5, 0, 25);
    //m_RLturn = m_MAX_RLturn *  m_angle_diff_opponentGoal /180.0;// turn left
    //m_RLstep = -10;//TODO
    }
    else {
    if ( debug_print == 1 ) printf("turn right \n");
    motion->walk(-5, 0, -25);
    //m_RLturn = m_MAX_RLturn * ( m_angle_diff_opponentGoal )/180.0;//turn right
    //m_RLstep = 5;//TODO
    }//TODO 绕球转
    m_FBstep = -10 * m_unit_FBstep;
    motion->walk(m_FBstep, m_RLstep, m_RLturn);

    int tmp = m_MAX_RLturn *  m_angle_diff_opponentGoal /180.0;
    //if ( debug_print == 1 ) printf("%lf   %lf   %lf  \n", m_FBstep, m_RLstep, m_RLturn);
    usleep( abs(tmp)*1000);
    }
    */
    return check_result;
}

void Strategist::CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D)
{
    p_2D.X = p_cv.x;
    p_2D.Y = p_cv.y;
}
