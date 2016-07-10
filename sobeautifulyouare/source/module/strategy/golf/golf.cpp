
#include "golf.h"

Golf::Golf()
{
	
}

Golf::~Golf()
{
}



void Golf::ThreadMotion()
{
    motion = new Motion();
    
    
	motion->poseInit();

   
    while(true)
    {
	    motion->CheckStatus();
        
    }

}

int Golf::GetImageResult(cv::Mat &frame)
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {

    }
}

