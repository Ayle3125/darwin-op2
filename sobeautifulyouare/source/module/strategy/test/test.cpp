#include "test.h"

int Test::m_cur_mode     = READY;
int Test::m_old_btn      = 0;
int Test::m_is_started   = 0;
Test::Test()
{
    m_imgRes_b = new ColorFindResult();
    m_imgPro_b = new ColorFind();
    m_imgRes_a = new ColorFindResult();
    m_imgPro_a = new ColorFind();

    m_execute = true;
    //m_process_state = VISION;


    b_center.x = 0; b_center.y = 0;
    a_center.x = 0; a_center.y = 0;


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
Test::~Test()
{
}

void Test::ThreadMotion() 
{
    fprintf(stderr,"Striker begin!\n");

    motion = new Motion();

    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_b);
    tmp_proc->load("redbox.txt");
    tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_a);
    tmp_proc->load("bluebox.txt");
    tracker = new BallTracker();
    follower = new BallFollower();

    int tmp_img_result=0, tmp_return_value =0, tmp_img_result2=0;
    // Walking::GetInstance()->Start();
    static int m_old_btn = 0;
    printf("Press the number & ENTER key to start Test!\n");
    //getchar();
    scanf("%d",&m_cur_mode);
    if ( m_cur_mode == 1 ){
        char filename[10];
        printf("Input the **(.txt) & ENTER key to color load!\n");
        scanf("%s",filename);
        ColorFind *tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_a);
        tmp_proc->load("redbox.txt");
    }
    else if ( m_cur_mode == 2 ){
        char filename[10];
        printf("Input the first **(.txt) & ENTER key to color load!\n");
        scanf("%s",filename);
        ColorFind *tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_a);
        tmp_proc->load("redbox.txt");
        printf("Input the second **(.txt) & ENTER key to color load!\n");
        scanf("%s",filename);
        tmp_proc = dynamic_cast<ColorFind *>(m_imgPro_b);
        tmp_proc->load("bluebox.txt");
    }
    motion->poseInit();

    while(m_execute){
        motion->CheckStatus();
        /*        m_old_btn = MotionStatus::BUTTON;
                  if(m_old_btn & BTN_MODE)
                  {
                  fprintf(stderr, "Mode button pressed.. \n");

                  if(m_is_started != 0)
                  {
                  m_is_started    = 0;
                  m_cur_mode      = READY;

                  Walking::GetInstance()->Stop();
                  Action::GetInstance()->m_Joint.SetEnableBody(true, true);

                  while(Action::GetInstance()->Start(15) == false) usleep(8000);
                  while(Action::GetInstance()->IsRunning() == true) usleep(8000);
                  }
                  else
                  {
                  m_cur_mode++;
                  if(m_cur_mode >= MAX_MODE) m_cur_mode = READY;
                  }

                  MotionManager::GetInstance()->SetEnable(false);
                  usleep(10000);

                  }

                  if(m_old_btn & BTN_START)
                  {
                  if(m_is_started == 0)
                  {
                  if ( m_cur_mode != READY ) {
                  m_is_started = 1;
                  motion->poseInit();
                  }

                  }
                  }
                  */
        m_is_started = 1;
        if ( m_is_started ){
            if ( debug_print ) fprintf(stderr,"mode %d. FB:%lf.  RLstep:%lf.  RLturn:%lf. \n",m_cur_mode,Walking::GetInstance()->X_MOVE_AMPLITUDE,Walking::GetInstance()->Y_MOVE_AMPLITUDE,Walking::GetInstance()->A_MOVE_AMPLITUDE);
            if ( m_cur_mode == VISION ){       
                double tmp_pan=0,tmp_tilt=-5;
                scanf("%lf%lf", &tmp_pan, &tmp_tilt);
                Head::GetInstance()->MoveByAngle(tmp_pan, tmp_tilt);
                GetImageResult(1);

            }
            else if ( m_cur_mode == VISION2 ){       
                double tmp_pan=0,tmp_tilt=-5;
                scanf("%lf%lf", &tmp_pan, &tmp_tilt);
                Head::GetInstance()->MoveByAngle(tmp_pan, tmp_tilt); 
                GetImageResult(0);
                GetImageResult(1);

            }
            else if ( m_cur_mode == WALK ){
                getchar();
                Walking::GetInstance()->Start();
                m_RLstep += m_unit_RLstep;
                //motion->walk(-1,m_RLstep,0);
                motion->walk(-1,0,m_RLstep);
                usleep(10*8000);
                Walking::GetInstance()->Stop();
            }
            else if ( m_cur_mode == TURN ){
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

            }
        }
    }

    pthread_exit(NULL);
}

int Test::GetImageResult(int result_type)
{
    static cv::Point2f not_found_p(-1,-1); 
    while ( is_new_img == false ) usleep(8000);
    if ( result_type == 0){
        m_imgPro_b->imageProcess(frame,m_imgRes_b);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_b);
        if ( tmp_result->valid == false ){
            b_center = not_found_p;
            // b_center_2D.X = -1;b_center_2D.Y = -1;
            if ( debug_print ) fprintf(stderr,"Can't find the ball!\n");
            return -1;
        }
        else {
            b_center = tmp_result->center;
            // b_center_2D.X = b_center.x;
            // b_center_2D.Y = b_center.y+28;
            if ( debug_print ) fprintf(stderr,"b_center:%lf %lf  \n",b_center.x,b_center.y);
        }
    }
    else if ( result_type == 1){
        m_imgPro_a->imageProcess(frame,m_imgRes_a);
        ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(m_imgRes_a);
        if ( tmp_result->valid == false ){
            a_center = not_found_p;
            if ( debug_print ) fprintf(stderr,"Can't find the hole!\n");
            return -1;
        }
        else {
            a_center = tmp_result->center;
            if ( debug_print ) fprintf(stderr,"a_center:%lf %lf  \n",a_center.x,a_center.y);
        }

    }
    is_new_img = false;
    return 0;

}
