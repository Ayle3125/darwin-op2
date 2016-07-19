
#include "ladder.h"

Ladder::Ladder()
{
	 imgRes = new ColorFindResult;
	 imgProc = new ColorFind;

    m_is_checkstatus = true;
	m_X_OFFSET = -15;
    m_FB_Step = 30;
    m_RL_Turn = 0;
	m_upcnt = 0;
	m_max_upcnt = 17;
	m_downcnt = 0;
    m_max_downcnt = 15;
	m_flatcnt = 0;

    m_line_leftup.X = 0;
    m_line_leftup.Y = 0;
    m_line_rightdown.X = 0;
    m_line_rightdown.Y = 0;

    m_up_time1 = 0;
    m_up_offset1 = -36;
    m_up_time2 = 10;
    m_up_offset2 = -40;
    m_up_time3 = 15;
    m_up_offset3= -10;

    m_down_time1 = 2;
    m_down_offset1 = -8;
    m_down_time2 = 7;
    m_down_offset2 = -6;
    m_down_time3 = 12;
    m_down_offset3= -8;

    m_ladder_flag = 1;
	debug_print = 1;

    m_img_range = 25;
    m_img_area = 100;
}

Ladder::~Ladder()
{
}

void Ladder::ThreadMotion()
{
    motion = new Motion();
ColorFind *tmp_proc = dynamic_cast<ColorFind *>(imgProc);
tmp_proc->load("red.txt");
	motion->poseInit();
	/*Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
   	 MotionManager::GetInstance()->SetEnable(true);*/
//	Walking::GetInstance()->X_OFFSET = -10;
   	Walking::GetInstance()->Start();
	motion->walk(10,0,0);
	Walking::GetInstance()->Start();
    int tmp_img_result;

	while(true)
	{
        motion->CheckStatus();
        usleep(20*8000);
        if (  m_is_checkstatus ) {
            motion->CheckStatus();
        }

        if(m_ladder_flag == 1)//flat
        {
            findladder();
            motion->walk(5,0,0);
            Walking::GetInstance()->Start();
        }
        else if(m_ladder_flag == 2)//ladder
        {
            if(m_upcnt < m_max_upcnt)
            {
                if(debug_print)fprintf(stderr,"I 'm walking upstairs %d\n",Walking::GetInstance()->X_OFFSET);
                moveupstair();
                m_upcnt++;
            }
	    /*else if(m_downcnt == 0)
	    {
		   Walking::GetInstance()->Stop();
		   usleep(100 * 8000);
		   Walking::GetInstance()->Stop();
			m_downcnt++;
	    }*/
            else if(m_downcnt < m_max_downcnt)
            {
		Walking::GetInstance()->Start();
                if(debug_print)fprintf(stderr,"I 'm walking downstairs %d\n",Walking::GetInstance()->X_OFFSET);
                movedownstair();
                m_downcnt++;
            }
            else
            {
                m_ladder_flag == 3;
		Walking::GetInstance()->X_OFFSET = -10;
            }
        }
        else if(m_ladder_flag == 3)
        {
	    if(debug_print)fprintf(stderr,"I 'm walking flat %d\n",Walking::GetInstance()->X_OFFSET);
            if(debug_print)fprintf(stderr,"Walking already\n");
             motion->walk(10,0,0);
        }
    }
}

void Ladder::findladder()
{
        if(debug_print)fprintf(stderr,"Not found");

        usleep(50*8000);
        m_flatcnt ++;
        if(m_flatcnt == 4)
        {
            m_ladder_flag = 2;
            if(debug_print)fprintf(stderr,"Have found target");
        }
}

void Ladder::moveupstair()
{
    motion->walk(m_FB_Step,0,m_RL_Turn);

    if(m_upcnt == m_up_time1)
    {
        if(debug_print)fprintf(stderr,"I 'm walking upstairs changing the offset the first time");
        Walking::GetInstance()->X_OFFSET = m_up_offset1;
    }
    if(m_upcnt == m_up_time2)
    {
        if(debug_print)fprintf(stderr,"I 'm walking upstairs changing the offset the second time");
        Walking::GetInstance()->X_OFFSET = m_up_offset2;
    }
    if(m_upcnt == m_up_time3)
    {
        if(debug_print)fprintf(stderr,"I 'm walking upstairs changing the offset the third time");
        Walking::GetInstance()->X_OFFSET = m_up_offset3;
    }
}

void Ladder::movedownstair()
{
    motion->walk(m_FB_Step,0,m_RL_Turn);

    if(m_downcnt == m_down_time1)
    {
        if(debug_print)fprintf(stderr,"I 'm walking downstairs changing the offset the first time");
        Walking::GetInstance()->X_OFFSET = m_down_offset1;
    }
    if(m_downcnt == m_down_time2)
    {
        if(debug_print)fprintf(stderr,"I 'm walking downstairs changing the offset the second time");
        Walking::GetInstance()->X_OFFSET = m_down_offset2;
    }
    if(m_downcnt == m_down_time3)
    {
        if(debug_print)fprintf(stderr,"I 'm walking downstairs changing the offset the third time");
        Walking::GetInstance()->X_OFFSET = m_down_offset3;
    }

}


int Ladder::GetImageResult()
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {
        m_line_leftup.X = tmp_result->leftUp.x;
        m_line_leftup.Y = tmp_result->leftUp.y;
        m_line_rightdown.X = tmp_result->rightDown.x;
        m_line_rightdown.Y = tmp_result->rightDown.y;
	m_img_area = tmp_result->area;
        return 1;
    }
}
