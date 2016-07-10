
#include "marathon.h"

Marathon::Marathon()
{
	imgRes = new FindLineResult();
	imgProc = new FindLine();
    
    m_execute = true;
    m_process_state = STRAIGHT;
//TODO
    m_NoLineMaxCount = 6;
    m_no_line_found = 0;
    m_CurveJudgeCount = 3;
    m_curve_count = 0;
    m_StraightJudgeCount = 6;
    m_straight_count = 0;
    m_line_center_2D.X = -1;
    m_line_center_2D.Y = -1;
    m_CenterDiff = 30;
    m_line_theta = 0;
    m_CurveTheta = 1.3;//TODO

    m_NolookMaxTime = 5;
    m_nolooktime = 0;

//TODO go straight first    
    m_FBstep = 10;
    m_FBstep_straight = 10;
    m_unit_FBstep = 0.3;
    m_MAX_FBstep = 30; 
    m_RLturn = 0;
    m_RLturn_straight = 0;
    m_unit_RLturn = 1.0;
    m_MAX_RLturn = 35;
    m_RLstep_straight = 0;
    m_RLstep = 0;
    m_unit_RLstep = 0.3;
    m_MAX_RLstep = 30;

    debug_print = 1;
}

Marathon::~Marathon(){
}

void Marathon::ThreadMotion(){
	motion = new Motion();
    motion->poseInit();
    Walking::GetInstance()->Start();
    int tmp_img_result;
    while ( m_execute ){//always true
        motion->CheckStatus();
        if ( m_process_state == STRAIGHT ){
            if ( m_nolooktime < m_NolookMaxTime ){
                m_nolooktime++;
                m_FBstep += m_unit_FBstep;
                motion->walk(m_FBstep, m_RLstep, m_RLturn);
            }
            else {
                if ( m_FBstep > 10 ) {//TODO
                    m_FBstep -= m_unit_FBstep;
                }
                while ( is_new_img == false ) usleep(8000);
                tmp_img_result = GetImageResult(frame);
                is_new_img = false;
                if ( tmp_img_result == -1 ){
                    if ( debug_print ) fprintf(stderr,"Can't find the track!\n");
                    m_no_line_found++;
                    if (m_no_line_found > m_NoLineMaxCount ){
                        int _tmp = LostDispose();
                        if ( _tmp == 1 ){
                            if ( debug_print ) fprintf(stderr,"Back on track!\n");
                            m_no_line_found = 0;
                        }
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
                    }
       				RLFixed();
                    motion->walk(m_FBstep, m_RLstep, m_RLturn);
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
		            m_FBstep = m_FBstep_straight; m_RLstep = m_RLstep_straight; m_RLturn = m_RLturn_straight;			
                }
            }
            else {
                m_straight_count = 0;
				if ( m_line_theta > 0) {
					if ( debug_print ) fprintf(stderr,"I should turn right\n");
					m_RLturn = -10;
				}
				else {
					if ( debug_print ) fprintf(stderr,"I should turn left\n");
					m_RLturn = 10;
				} 
               motion->walk(m_FBstep, m_RLstep, m_RLturn);
            }
        }
    }
}

int Marathon::GetImageResult(cv::Mat &frame)
{
    imgProc->imageProcess(frame,imgRes);
    FindLineResult *tmp_result = dynamic_cast<FindLineResult *>(imgRes);//TODO
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {
		m_line_theta = tmp_result->slope;
        m_line_center_2D.X = tmp_result->center.x;
        m_line_center_2D.Y = tmp_result->center.y;
		if ( debug_print ) fprintf(stderr,"theta:%lf  line center: %lf %lf \n",m_line_theta,m_line_center_2D.X,m_line_center_2D.Y);
    }

}

int Marathon::LostDispose()
{    
    if ( debug_print ) fprintf(stderr,"I should dispose the lost\n");
}

void Marathon::RLFixed()
{
	double diff = m_line_center_2D.X - ( IMG_WIDTH/2 );
    if ( fabs ( diff  ) > m_CenterDiff ){
		m_RLstep =  m_MAX_RLstep * diff / ( IMG_WIDTH/2 );
        if ( diff > 0 ){
            m_RLstep *= -1;
        }
    }
}
