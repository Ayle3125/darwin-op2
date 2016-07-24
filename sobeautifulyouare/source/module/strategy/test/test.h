#ifndef _TEST_H_
#define _TEST_H_

#include <strategy.h>



class Test:public Strategist
{
    public:
        Test();
        ~Test();
    private:

        enum {
            READY,
            VISION,
            VISION2,
            WALK,
            TURN,
            MAX_MODE
        };
        enum {
            BTN_MODE = 1,
            BTN_START = 2
        };

        BallTracker *tracker;
        BallFollower *follower;	


        /*************Process****************/
        bool m_execute;
        //TestState m_process_state;


        /*************Image*******************/
        ImgProcResult *m_imgRes_a, *m_imgRes_b;
        ImgProc *m_imgPro_a, *m_imgPro_b;
        cv::Point2f a_center;
        cv::Point2f b_center;

        /*************Motion Order*************/
        double pan_range; 
        double unit_pan;
        double tilt_min;		
        double tilt_range; 
        double unit_tilt;

        double m_FBstep_straight;
        double m_FBstep;
        double m_FBstep_ApproachMin;
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
        double m_RLstep_goal;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        /*------------------------------------*/

        int debug_print;
        static int m_old_btn;

    public:
        static int m_cur_mode;
        static int m_soccer_sub_mode;
        static int m_is_started;


    protected:
        virtual void ThreadMotion();
        //virtual int GetImageResult();
        int GetImageResult(int result_type);//0:ball 1:goal


};

#endif // _TEST_H_
