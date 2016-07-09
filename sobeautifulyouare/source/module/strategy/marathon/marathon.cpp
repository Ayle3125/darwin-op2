
#include "marathon.h"

Marathon::Marathon()
{
	//imgRes = new ImgProcResult();
	//imgProc = new ImgProc();

    m_process_state = STRAIGHT;
    theta = 0;
}

Marathon::~Marathon()
{
}

void Marathon::ThreadMotion(){
    
}

void Marathon::GetImageResult(cv::Mat &frame){

}
