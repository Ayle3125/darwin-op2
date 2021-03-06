
#include "robcup_penalty.h"

Robcup_penalty::Robcup_penalty()
{
    is_new_img = false;

    m_process_state = 0;


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
Robcup_penalty::~Robcup_penalty()
{
}

int Robcup_penalty::run()
{	
    debug_print = 1;
    if ( debug_print ) printf( " robcup_penalty run\n");
    pthread_mutex_init(&mut,NULL);
    pthread_cond_init(&cond,NULL);
    thread_create();

    thread_wait();

    return 0;
}

void Robcup_penalty::ThreadVision() 
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
        if( debug_print) {
       		cv::imshow("cap", frame);		
        	cv::waitKey(30); 

		}
    }

    pthread_mutex_lock(&mut);


    pthread_mutex_unlock(&mut);
    sleep(2);

    pthread_exit(NULL);

}

void Robcup_penalty::ThreadMotion() 
{
    pthread_mutex_lock(&mut);
    motion = new Motion();
    tracker = new BallTracker();
    follower = new BallFollower();

    motion->poseInit();
 //   motion->walk_star();
    pthread_mutex_unlock(&mut);
	printf("Press the ENTER key to start ROBOCUP!\n");
    getchar();
    while (true)
    {

        pthread_mutex_lock(&mut);
        if( is_new_img == true){
            pthread_cond_signal(&cond);
        }
        is_new_img = false;
        pthread_mutex_unlock(&mut);

        motion->CheckStatus();
		usleep(8000);

    }

    pthread_exit(NULL);
}

void Robcup_penalty::thread_create() 
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

void Robcup_penalty::thread_wait(void) 
{
    if(thread[0] !=0)
        pthread_join(thread[0],NULL);
    if(thread[1] !=0) 
        pthread_join(thread[1],NULL);
}


void Robcup_penalty::GetImageResult(cv::Mat &frame, ImgResultType rs)
{
    if ( rs == BALL ){
        ballpro->imageProcess(frame);
        if( debug_print ) printf("ball center x:%d y:%d\n", ballpro->center.x,ballpro->center.y);
        CVpointTo2Dpoint( ballpro->center, m_ball_center_2D);
    }
    else if ( rs == GOALPOST ){

    }
    else if ( rs == LINE ){

    }
}

void Robcup_penalty::FindBall()
{
	
	static int no_ball_count = 0;
	static const int MaxNoBallCount = 5; 
	int KickPan = -10;
    
	if (m_ball_center_2D.X!=0 || m_ball_center_2D.Y!=0 ){
		tracker->Process(m_ball_center_2D); 
		double pan = MotionStatus::m_CurrentJoints.GetAngle(JointData::ID_HEAD_PAN);
		if ( pan > KickPan ){
			Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);   
            Action::GetInstance()->Start(130);   // Long shot
            fprintf(stderr, "Kick! \n");
		}
	}
	else {
		no_ball_count ++;
        m_FBstep = 0.0;
        m_RLturn = 0.0;
        motion->walk(m_FBstep, 0, m_RLturn);
	}
    
}


void Robcup_penalty::CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D)
{
    p_2D.X = p_cv.x;
    p_2D.Y = p_cv.y;
}

