
#include "ladder.h"

Ladder::Ladder()
{
	
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
        
    }

}

int Ladder::GetImageResult(cv::Mat &frame)
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {

    }
}

