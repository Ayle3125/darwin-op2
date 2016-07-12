/*****************************
 *	For Fira2016.
 *		imgResult&pro可以改用数组
 ******************************/


#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <strategy.h>

class Obstacle:public Strategist
{
    public:
        Obstacle();
        ~Obstacle();
    private:
        /*************Process****************/

        int m_pixel_num;
        int m_PixelJudgeNum;
        Point2D m_obstacle_center_2D;
        Point2D m_line_center_2D;
		double m_line_theta;//the angle of the white track  /:negative  \:positive

        int m_NolookMaxTime;
        int m_nolooktime;


        bool m_execute;
        int m_pre_action;// 1:move left  0:go straight  -1:move right  


        int LostDispose();
        int Turn(int direction);
        int CheckLine();
        /*************Motion Order****************/
        double m_FBstep_straight;
        double m_FBstep;
        double m_unit_FBstep;
        double m_MAX_FBstep;

        double m_RLturn_straight;
        double m_RLturn;
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
        int GetImageResult_obstacle(int result_type);

};

#endif // _OBSTACLE_H_
