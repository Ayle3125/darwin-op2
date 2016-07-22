/*
 *  100: 张开四肢  劈叉
 *  101: 劈叉恢复，15
 *  115: front lie down
 *  130: 大脚射门
 */
#include "robcup_goalkeeper.h"

Robcup_goalkeeper::Robcup_goalkeeper()
{
    is_new_img = false;

    m_ball_center_2D.X = -1; m_ball_center_2D.Y = -1;
    m_ball_center_angle.X = -1; m_ball_center_angle.Y = -1;
    m_line_center_2D.X = -1; m_line_center_2D.Y = -1;
    m_goalfoot1.X = -1; m_goalfoot1.Y = -1;
    m_goalfoot2.X = -1; m_goalfoot2.Y = -1;
    m_ball_found = 0;
    m_NoBallMaxCount = 10;
    m_goal_found = 0;
    m_line_found = 0;
    m_line_Kvalue = 0;

    m_process_state = FOLLOWBALL;
	m_dive_status = -1;
    
    m_is_checkstatus = true;
		
    m_DiveRightAngle = 10;
    m_DiveLeftAngle = -10;
    m_DiveTopAngle = 5;//TODO
}
Robcup_goalkeeper::~Robcup_goalkeeper()
{
}

int Robcup_goalkeeper::run()
{	
    debug_print = 1;
    if ( debug_print ) printf( " robcup_striker run\n");
    pthread_mutex_init(&mut,NULL);
    pthread_cond_init(&cond,NULL);
    thread_create();

    thread_wait();

    return 0;
}

void Robcup_goalkeeper::ThreadVision() 
{
    ballpro = new followball();
    linepro = new sideline();
    // robotpro = new findrobot();
    ballpro = new followball();
    goalpro = new goalpost();
    cv::VideoCapture cap(0);
    if(!cap.isOpened())  // check if we succeeded
        fprintf(stderr,"Can not open the camera!\n");
    while (true)
    {
        pthread_mutex_lock(&mut);//相当于模拟单线程，锁不锁也没关系
        while( is_new_img == true){
            pthread_cond_wait(&cond, &mut);
        }
        is_new_img = true;
        pthread_mutex_unlock(&mut);

        cap >> frame;
        flip(frame,frame,-1);
        if ( debug_print ){
            cv::imshow("cap", frame);		
            cv::waitKey(30); 
        }

    }
    pthread_exit(NULL);

}

void Robcup_goalkeeper::ThreadMotion() 
{
    
}

void Robcup_goalkeeper::thread_create() 
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

void Robcup_goalkeeper::thread_wait(void) 
{
    if(thread[0] !=0)
        pthread_join(thread[0],NULL);
    if(thread[1] !=0) 
        pthread_join(thread[1],NULL);
}


void Robcup_goalkeeper::GetImageResult(cv::Mat &frame, ImgResultType rs)
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


void Robcup_goalkeeper::CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D)
{
    p_2D.X = p_cv.x;
    p_2D.Y = p_cv.y;
}
