
#include "shot.h"

Shot::Shot()
{
	
}

Shot::~Shot()
{
}



void Shot::ThreadMotion()
{
    motion = new Motion();
    
    
	motion->poseInit();

   
    while(true)
    {
	    motion->CheckStatus();
        
    }

}

int Shot::GetImageResult(cv::Mat &frame)
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {

    }
}

