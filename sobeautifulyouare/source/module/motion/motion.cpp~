#include "motion.h"

Motion::Motion()
{
    linux_cm730 = new LinuxCM730(U2D_DEV_NAME0);
    cm730 = new CM730(linux_cm730);
    tracker = new BallTracker();
    follower = new BallFollower();

    if(MotionManager::GetInstance()->Initialize(cm730) == false)
    {
        linux_cm730->SetPortName(U2D_DEV_NAME1);
        if(MotionManager::GetInstance()->Initialize(cm730) == false)
        {
            printf("Fail to initialize Motion Manager!\n");
            exit(0);
        }
    }

    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());

    LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
    motion_timer->Start();

    firm_ver = 0;
    if(cm730->ReadByte(JointData::ID_HEAD_PAN, MX28::P_VERSION, &firm_ver, 0)  != CM730::SUCCESS)
    {
        fprintf(stderr, "Can't read firmware version from Dynamixel ID %d!! \n\n", JointData::ID_HEAD_PAN);
        exit(0);
    }
    if(0 < firm_ver && firm_ver < 27)
    {
#ifdef MX28_1024
        Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
#else
        fprintf(stderr, "MX-28's firmware is not support 4096 resolution!! \n");
        fprintf(stderr, "Upgrade MX-28's firmware to version 27(0x1B) or higher.\n\n");
        exit(0);
#endif
    }
    else if(27 <= firm_ver)
    {
#ifdef MX28_1024
        fprintf(stderr, "MX-28's firmware is not support 1024 resolution!! \n");
        fprintf(stderr, "Remove '#define MX28_1024' from 'MX28.h' file and rebuild.\n\n");
        exit(0);
#else
        Action::GetInstance()->LoadFile((char*)MOTION_FILE_PATH);
#endif
    }
    else
        exit(0);

    Action::GetInstance()->m_Joint.SetEnableBody(true, true);
    MotionManager::GetInstance()->SetEnable(true);

    cm730->WriteByte(CM730::P_LED_PANNEL, 0x01|0x02|0x04, NULL);
    Action::GetInstance()->Start(15);
    /////////////////////////////////////////////////////////////////////
    /*
       int n = 0;
       int param[JointData::NUMBER_OF_JOINTS * 5];
       int wGoalPosition, wStartPosition, wDistance;

       for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
       {
       wStartPosition = MotionStatus::m_CurrentJoints.GetValue(id);
       wGoalPosition = Walking::GetInstance()->m_Joint.GetValue(id);
       if( wStartPosition > wGoalPosition )
       wDistance = wStartPosition - wGoalPosition;
       else
       wDistance = wGoalPosition - wStartPosition;

       wDistance >>= 2;
       if( wDistance < 8 )
       wDistance = 8;

       param[n++] = id;
       param[n++] = CM730::GetLowByte(wGoalPosition);
       param[n++] = CM730::GetHighByte(wGoalPosition);
       param[n++] = CM730::GetLowByte(wDistance);
       param[n++] = CM730::GetHighByte(wDistance);
       }
       cm730->SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);	
       */  
    /////////////////////////////////////////////////////////////////////////////
}

Motion::~Motion()
{
	Walking::GetInstance()->Stop();
    while(Walking::GetInstance()->IsRunning() == 1) usleep(8000);
	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	Action::GetInstance()->Start(15);
}

void Motion::Run(MyPointf *coorf)
{

    /////////////////////////////////////////////////////////////////////

    printf("Press the ENTER key to begin!\n");
    getchar();

    ///////////////////////////////////////////////////////////////////////
    while(1) {
        Point2D ball_pos;
        pt.X = coorf->x;
        pt.Y = coorf->y;

        usleep(1000);

        ball_pos = pt;
        //    	printf("ball_pos.X=%f, ball_pos.Y=%f\n", ball_pos.X, ball_pos.Y);
        tracker->Process(pt);
        //    	printf("coor.x=%f, coor.y=%f\n", coorf->x, coorf->y);
        //    	if(Action::GetInstance()->IsRunning() == 0) {
        Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
        Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
        follower->Process(tracker->ball_position);

        if(follower->KickBall != 0) {
            Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
            Action::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

            if(follower->KickBall == -1) {
                Action::GetInstance()->Start(12);   // RIGHT KICK
                fprintf(stderr, "RightKick! \n");
            }
            else if(follower->KickBall == 1) {
                Action::GetInstance()->Start(13);   // LEFT KICK
                fprintf(stderr, "LeftKick! \n");
            }
        }
        //        }
    }
}


void Motion::poseInit()
{
	//static int m_old_btn = 0;
    printf("Press the ENTER key to stand up!\n");
/*	while(StatusCheck::m_is_started == 0)
	{
		if ( MotionStatus::BUTTON != m_old_btn ) {
			break;
		}
	}
*/
	getchar();
    Action::GetInstance()->m_Joint.SetEnableBody(true, true);  //!!!
    Action::GetInstance()->Start(9);  
    while(Action::GetInstance()->IsRunning() == true) usleep(8000);
    Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
    MotionManager::GetInstance()->ResetGyroCalibration();
    MotionManager::GetInstance()->SetEnable(true);
}

void Motion::tuner_ARM_SWING_GAIN(double value)
{
    Walking::GetInstance()->ARM_SWING_GAIN = value;
}

void Motion::init_motion()
{
    Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
    Head::GetInstance()->MoveByAngle(0.0,20.0);//max:40 home:10 min:-25
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
    MotionManager::GetInstance()->SetEnable(true);
}

void Motion::sprint_init()
{
    Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
    Head::GetInstance()->MoveByAngle(0.0,20.0);//max:40 home:10 min:-25
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
    MotionManager::GetInstance()->SetEnable(true);
}

void Motion::walk_x_move_amplitude(double FBStep)
{
    Walking::GetInstance()->X_MOVE_AMPLITUDE = FBStep;
}

void Motion::walk_a_move_amplitude(double RLTurn)
{
    Walking::GetInstance()->A_MOVE_AMPLITUDE = RLTurn;
}

void Motion::walk_h_move_amplitude(double HTStep)
{
    Walking::GetInstance()->Z_MOVE_AMPLITUDE = HTStep;
}

void Motion::walk_y_move_amplitude(double RLStep)
{
    Walking::GetInstance()->Y_MOVE_AMPLITUDE = RLStep;
}

void Motion::walk_star()
{
    Walking::GetInstance()->Start();
}

int Motion::get_walking_phrase()
{
    return Walking::GetInstance()->GetCurrentPhase();
}

void Motion::stop_walking()
{
    Walking::GetInstance()->Stop();
}

void Motion::walking(double ht, double fb, double al, double rl)
{
    int tmp_val = -1, tmp_old_val = -1;
    walk_h_move_amplitude(ht);
    walk_x_move_amplitude(fb);
    walk_a_move_amplitude(al);
    walk_y_move_amplitude(rl);

    walk_star();

    while(1) {
        walk_star();
        tmp_val = get_walking_phrase();
        if(tmp_old_val == 2 && tmp_val == 3) {
            stop_walking();
            break;
        }
        tmp_old_val = tmp_val;
    }
}

void Motion::set_walking_time(double t)
{
    Walking::GetInstance()->PERIOD_TIME = t;
}

void Motion::CheckStatus()
{
    if(MotionStatus::FALLEN != STANDUP )
    {
        Walking::GetInstance()->Stop();
        while(Walking::GetInstance()->IsRunning() == 1) usleep(8000);

        Action::GetInstance()->m_Joint.SetEnableBody(true, true);

        if(MotionStatus::FALLEN == FORWARD){
            printf("forward!\n");
            Action::GetInstance()->Start(10);   // FORWARD GETUP
        }
        else if(MotionStatus::FALLEN == BACKWARD){
            Action::GetInstance()->Start(11);   // BACKWARD GETUP
        }

        while(Action::GetInstance()->IsRunning() == 1) usleep(8000);
        while(Walking::GetInstance()->IsRunning() == 1) usleep(8000);
        Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
        Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
    }
}
void Motion::walk(double FBstep, double RLstep, double RLturn)
{
    if(FBstep == 0 && RLturn == 0 && RLstep == 0){
        if(Walking::GetInstance()->IsRunning() == true){
            Walking::GetInstance()->Stop();
        }
        else{
        }      
    }
    else {
        if(Walking::GetInstance()->IsRunning() == false){
            FBstep = 0;
            RLturn = 0;
            RLstep = 0;
            Walking::GetInstance()->X_MOVE_AMPLITUDE = FBstep;
            Walking::GetInstance()->A_MOVE_AMPLITUDE = RLturn;
            Walking::GetInstance()->Y_MOVE_AMPLITUDE = RLstep;
            Walking::GetInstance()->Start();			
        }
        else{
            Walking::GetInstance()->X_MOVE_AMPLITUDE = FBstep;
            Walking::GetInstance()->A_MOVE_AMPLITUDE = RLturn;
            Walking::GetInstance()->Y_MOVE_AMPLITUDE = RLstep;
        }
    }
}
void Motion::shutdown()
{
    for(int i=1;i<21;i++)
        cm730->WriteWord(i,MX28::P_TORQUE_ENABLE,0,0);
    linux_cm730->ClosePort();
}
