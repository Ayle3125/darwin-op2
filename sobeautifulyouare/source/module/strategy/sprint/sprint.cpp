
#include "sprint.h"

Sprint::Sprint()
{
	 imgRes = new ColorFindResult;
	 imgProc = new ColorFind;

     m_is_checkstatus = true;
     m_point_center_2D.X = 0;
     m_point_center_2D.Y = 0;
     m_point_found = false;
     m_GoalFBStep = 0;
     m_GoalRLTurn = 0;
     m_FBStep = 10.0;
     m_RLTurn = 0;
    debug_print = 1; 

    m_FitFBStep = 3.0;
    m_FitMaxRLTurn = 35.0;

    m_FBStep_straight = 30.0;
    m_RLTurn_straight = 0;

    m_Xoffset = -10;
    m_target_Xoffset = -20;

    m_percent_CenterDiff = 0.01;
    m_no_point_found = 0;
    m_NopointMaxCount = 5;
    m_pre_action = 0;
    m_RLturn_degree = 0;
    m_RLturn_max = 10;
    m_RLTurn_left = 1;
    m_RLTurn_right = -1;
    LRMoveAngle = 3.0;
}

Sprint::~Sprint()
{
}

void Sprint::ThreadMotion()
{
    motion = new Motion();
    ColorFind *tmp_proc = dynamic_cast<ColorFind *>(imgProc);
    tmp_proc->load("redbox.txt");
    //compasspro = new compass();
    //findline = new findline();
    
	motion->poseInit();
    Head::GetInstance()->MoveByAngle(0, 50);
    usleep(1000*8000);
    Walking::GetInstance()->Start();
    Walking::GetInstance()->X_OFFSET = m_Xoffset;
    motion->walk(m_FBStep,0,0);
    Walking::GetInstance()->Start();
    
    int tmp_img_result;
    while(true)
    {
	    motion->CheckStatus();
        usleep(10*8000);
        if (  m_is_checkstatus ) {
            motion->CheckStatus();
        }
        tmp_img_result = GetImageResult();

        if( m_Xoffset > m_target_Xoffset)
        {
		if ( debug_print ) fprintf(stderr,"oFFset %d %d\n", m_Xoffset, m_target_Xoffset);
            m_Xoffset -= 2;
        }
	Walking::GetInstance()->X_OFFSET = m_Xoffset;
        if(m_FBStep < m_FBStep_straight)
        {
            m_FBStep += 2;
        }

        if(m_point_found != true)
        {
            if ( debug_print ) fprintf(stderr,"Can't find the track!\n");
            m_no_point_found++;
            m_point_found = false;
            if (m_no_point_found > m_NopointMaxCount ){
                LostDispose();
            }
        }
        else
        {
            if(m_pre_action == 0){
                SprintForward();
                if ( debug_print ) fprintf(stderr,"I'm walking foward!\n");
            }
            else if(m_pre_action == 1){
                motion ->walk(m_FBStep,0,m_RLTurn_left);   //haven't LostDispose but need turn easy left
                if ( debug_print ) fprintf(stderr,"I'm walking easy left! %d\n",m_RLTurn_left);
            }
            else if(m_pre_action == -1){
                motion ->walk(m_FBStep,0,m_RLTurn_right);   //haven't LostDispose but need turn easy right
                if ( debug_print ) fprintf(stderr,"I'm walking easy right!\n");
            }
        }

        m_percent_CenterDiff += 0.0002;
    }
}

void Sprint::SprintForward()
{
    if(debug_print) printf("SprintForward \n");
    if(  m_point_found == 1){//find point
        motion->walk(m_FBStep , 0,m_RLTurn );
    }

}


int Sprint::GetImageResult()
{
	while ( is_new_img == false ) usleep(8000);
    imgProc->imageProcess(frame,imgRes);
    ColorFindResult *tmp_result = dynamic_cast<ColorFindResult *>(imgRes);
    if ( tmp_result->valid == false ){
        return  -1;
    }
    else {
        m_point_found = true;
        m_point_center_2D.X = tmp_result->center.x;
        m_point_center_2D.Y = tmp_result->center.y;
        m_RLturn_degree = fabs((m_point_center_2D.X - 160.0) / 320.0);

        if(debug_print) fprintf(stderr,"Center %lf IMG_Center 160 degree %lf now %lf\n",m_point_center_2D.X,m_RLturn_degree,m_percent_CenterDiff);
        if(m_point_center_2D.X > 160.0&&  m_RLturn_degree > m_percent_CenterDiff ) {
            m_pre_action = -1;  //-1 point is on the right
        }
        else if(m_point_center_2D.X < 160.0&&  m_RLturn_degree >m_percent_CenterDiff ){
            m_pre_action = 1;   //1 point is on the left
        }
        else
        {
            m_pre_action = 0;
        }
        return 0;
    }
	is_new_img = false;
}

void Sprint::LostDispose()
{
    if(debug_print) fprintf(stderr,"I should dispose the lost\n");
    if(m_pre_action == -1)  //point is on the right
    {
        if ( debug_print ) fprintf(stderr,"Lost right!\n");
        motion->walk(5,8,0);    //pinyi right
    }
    else if(m_pre_action == 1)  //point is on the left
    {
		if ( debug_print ) fprintf(stderr,"Lost left!\n");
        motion->walk(5,-6,0);   //pinyi left
    }
	else
	{
        motion->walk(m_FBStep,0,0);
        Walking::GetInstance()->Start();
	}	
}

