
#include "ladder.h"

Ladder::Ladder()
{
    double m_X_OFFSET = -15;
    double m_FB_Step = 0;
    int m_upcnt = 0;
    int m_max_upcnt = 20;
    int m_flatcnt = 0;
    int m_flatcnttwo = 0;
    int m_max_flatcnt = 10;
    int m_downcnt = 0;
    int m_max_downcnt = 20;
}

Ladder::~Ladder()
{
}

void Ladder::ThreadMotion()
{
    motion = new Motion();
    
	motion->poseInit();

    while(true)
    {
	    motion->CheckStatus();

        Walking::GetInstance()->start();
        if(m_upcnt < m_max_upcnt)   //upstair
        {
            if(Walking::GetInstance()->X_OFFSET > -22)
            {
                Walking::GetInstance()->X_OFFSET -= 1;
            }
            motion->walk(22,0,0);
            usleep(20 * 8000);
            m_upcnt++;
        }
        else
        {
            if( m_flatcnt < m_max_flatcnt ) {//flat
                if(Walking::GetInstance()->X_OFFSET < -10)
                {
                    Walking::GetInstance()->X_OFFSET += 1;
                }
                motion->walk(22,0,0);
                usleep(20 * 8000);
                m_flatcnt++;
            }
            else if(m_downcnt < m_max_downcnt)//downstair
            {
                if(Walking::GetInstance()->X_OFFSET < 0)
                {
                    Walking::GetInstance()->X_OFFSET += 1;
                }
                motion->walk(22,0,0);
                usleep(20 * 8000);
                m_downcnt++;
            }
            else//flat
            {
                if( m_flatcnttwo < m_max_flatcnt ) {//flat
                    if(Walking::GetInstance()->X_OFFSET > -10)
                    {
                        Walking::GetInstance()->X_OFFSET -= 1;
                    }
                    motion->walk(22,0,0);
                    usleep(20 * 8000);
                    m_flatcnt++;
                }
            }
        }
    }

}

/*int Ladder::GetImageResult(cv::Mat &frame)
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {

    }
}*/

