
#include "marathon.h"

Marathon::Marathon(){
	//imgRes = new ImgProcResult();
	//imgProc = new ImgProc();
    
    execute = true;
    m_process_state = STRAIGHT;
//TODO
    m_NoLineMaxCount = 6;
    m_no_line_found = 0;
    m_CurveJudgeCount = 4;
    m_curve_count = 0;
    m_StraightJudgeCount = 5;
    m_straight_count = 0;
    m_line_center_2D;
    m_line_theta = 0;
    m_CurveTheta = 100;

    m_NolookMaxTime = 5;
    m_nolooktime = 0;

//TODO go straight first    
    m_FBstep = 10;
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

Marathon::~Marathon(){
}

void Marathon::ThreadMotion(){
    motion->poseInit();
    Walking::GetInstance()->Start();
    while ( execute ){//always true
        motion->CheckStatus();
        if ( m_process_state == STRAIGHT ){
            if ( m_nolooktime < m_NolookMaxTime ){
                m_nolooktime++;
                m_FBstep += m_unit_FBstep;
                motion->walk(m_FBstep, m_RLstep, m_RLturn);
            }
            else {
                if ( m_FBstep > 10 ) {
                    m_FBstep -= m_unit_FBstep;
                }
                while ( is_new_img == false ) usleep(8000);
                GetImageResult(frame);
                is_new_img = false;
                if (m_no_line_found > m_NoLineMaxCount ){
                    int _tmp = LostDispose();
                    if ( _tmp == 1 ){
                        if ( debug_print ) fprintf(stderr,"Back on track!\n");
                        m_no_line_found = 0;
                    }
                }
                else {
                    if ( ( m_line_theta>0 &&  m_line_theta < m_CurveTheta) || (m_line_theta<0 && m_line_theta> -1*m_CurveTheta) ){
                        m_curve_count++;
                        if ( m_curve_count > m_CurveJudgeCount ){
                            m_process_state = CURVE;
                        }
                    }
                    else {
                        m_curve_count = 0;
                        motion->walk(m_FBstep, m_RLstep, m_RLturn);
                    }
                }
            }
        }
        else if ( m_process_state == CURVE ){
            m_nolooktime = 0;
            while ( is_new_img == false ) usleep(8000);
            GetImageResult(frame);
            is_new_img = false;
            if ( ( m_line_theta>m_CurveTheta) || (m_line_theta<-1*m_CurveTheta) ){
                m_straight_count++;
                if ( m_straight_count > m_StraightJudgeCount ){
                    m_process_state = STRAIGHT;
                }
            }
            else {
                m_straight_count = 0;
               // motion->walk(m_FBstep, m_RLstep, m_RLturn);
            }
        }
    }
}

void Marathon::GetImageResult(cv::Mat &frame)
{

}

int Marathon::LostDispose()
{    
    
}