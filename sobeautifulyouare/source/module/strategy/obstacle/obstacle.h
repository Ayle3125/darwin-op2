/*****************************
 *	For Fira2016.
 *
 ******************************/


#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <strategy.h>

enum ObstacleState{
    BEFORE1,
    BEFORE2,
    BEFORE3,
    LAST,
    TURN,
};

class Obstacle:public Strategist
{
    public:
        Obstacle();
        ~Obstacle();
    private:

        /*************Image****************/
        ImgProcResult *m_imgRes_line, *m_imgRes_color;
        ImgProc *m_imgProc_line, *m_imgProc_color;
        int m_pixel_num;
        int m_PixelJudgeNum;
        cv::RotatedRect m_obstacle_rect;/*center:x,y	
                                         *size:width,height
                                         *angle:The rotation angle in a clockwise direction. 
                                         *void points(Point2f pts[]):会把四个顶点放在pts[],左下cd？和motion冲突
                                         */
        cv::Point m_obstacle_pts[4];
        Point2D m_obstacle_center_2D;
		double m_ObstacleCenterNeed[2];
        double m_ObstacleDiff;
        Point2D m_line_center_2D;
        double m_line_theta;//the angle of the white track  /:negative  \:positive

        /*************Process****************/
        ObstacleState m_process_state;
        ObstacleState m_pre_state;
        int m_NolookMaxTime;
        int m_nolooktime;
        bool m_execute;
        int m_pre_action;// 1:move left  0:go straight  -1:move right  

        int LostDispose();
        int TurnAdjust(int direction);
        int CheckLine();
        int RLFixed();
        void ChangeObstacleColor();

        /*************Motion Order****************/
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
        int GetImageResult_obstacle(int result_type);//type: 0:line 1:obstacle

};

#endif // _OBSTACLE_H_
