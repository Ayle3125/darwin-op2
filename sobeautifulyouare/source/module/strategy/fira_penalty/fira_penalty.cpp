
#include "fira_penalty.h"

Fira_penalty::Fira_penalty()
{
	
}

Fira_penalty::~Fira_penalty()
{
}



void Fira_penalty::ThreadMotion()
{
    motion = new Motion();
    
    
	motion->poseInit();

   
    while(true)
    {
	    motion->CheckStatus();
        
    }

}

int Fira_penalty::GetImageResult()
{
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return -1;
    }
    else {

    }
}

