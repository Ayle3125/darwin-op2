
#include "robcup_fullback.h"

Robcup_fullback::Robcup_fullback()
{
  
    debug_print = 1;

}
Robcup_fullback::~Robcup_fullback()
{
}

int Robcup_fullback::run()
{	
    if ( debug_print ) printf( " robcup_fullback run\n");
    pthread_mutex_init(&mut,NULL);
    pthread_cond_init(&cond,NULL);
    ThreadCreate();

    ThreadWait();

    return 0;
}

void Robcup_fullback::ThreadVision() 
{
    ballpro = new followball();
    cv::VideoCapture cap(0);
    if(!cap.isOpened())  // check if we succeeded
        fprintf(stderr,"Can not open the camera!\n");
    while (true)
    {
        pthread_mutex_lock(&mut);
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


void Robcup_fullback::ThreadMotion() 
{
   
}

void Robcup_fullback::ThreadCreate() 
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

void Robcup_fullback::ThreadWait(void) 
{
    if(thread[0] !=0)
        pthread_join(thread[0],NULL);
    if(thread[1] !=0) 
        pthread_join(thread[1],NULL);
}


void Robcup_fullback::GetImageResult(cv::Mat &frame, ImgResultType rs)
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

void Robcup_fullback::CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D)
{
    p_2D.X = p_cv.x;
    p_2D.Y = p_cv.y;
}

void Robcup_fullback::WalkForBall()
{
    

}

void Robcup_fullback::CloseToBall()
{

   
}


int Robcup_fullback::CompassCheck()
{// degree 0~360  -> -180~ 180
  
}

