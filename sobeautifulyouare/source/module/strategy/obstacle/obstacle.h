/*****************************
 *	For Fira2016.
 *
 ******************************/


#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <strategy.h>

enum ObstacleState{
    BEFOREODD,// 1,3
    BEFOREEVEN,// 2
    LAST,
    TURN,
    TURNNEXT,
};

class Obstacle:public Strategist
{
    public:
        Obstacle();
        ~Obstacle();
    private:

        /*************Image****************/
        double m_pixel_num;
        double m_PixelJudgeNum[3];
        cv::RotatedRect m_obstacle_rect;/*center:x,y	
                                         *size:width,height
                                         *angle:The rotation angle in a clockwise direction. 
                                         *void points(Point2f pts[]):会把四个顶点放在pts[],左下cd？和motion冲突
                                         */
        cv::Point m_obstacle_pts[4];
        cv::Point2f m_obstacle_center;
		double m_ObstacleCenterNeed[3];
		double m_TurnPan[3];
        double m_ObstacleDiff;

        /*************Process****************/
        ObstacleState m_process_state;
        ObstacleState m_pre_state;
        bool m_execute;
        int m_pre_action;// 1:move left  0:go straight  -1:move right 

	    int TURN_count; 

        int LostDispose();
		int HeadTracker(cv::Point2f);
        int TurnAdjust(int direction);
        int RLFixed();
        void ChangeObstacleColor(int number);

        /*************Motion Order****************/
		double pan,tilt;
		double pan_range; 
		double unit_pan;

        double m_FBstep_straight;
        double m_FBstep;
        double m_FBstep_goal;
        double m_unit_FBstep;
        double m_MAX_FBstep;

        double m_RLturn_straight;
        double m_RLturn;
        double m_RLturn_goal;
        double m_unit_RLturn;
        double m_MAX_RLturn;

        double m_RLstep_straight;
        double m_RLstep;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        /*------------------------------------*/
        int debug_print;

    protected:
        virtual void ThreadMotion();
		virtual int GetImageResult();
        int GetImageResult_obstacle(int result_type);//type: 0:line 1:obstacle //abandon= =

};

#endif // _OBSTACLE_H_
