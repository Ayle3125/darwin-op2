#ifndef _ROBCUP_GOALKEEPER_H_
#define _ROBCUP_GOALKEEPER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <strategy.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <BlobResult.h>
#include <camera.h>
#include <followball.h>
#include <goalpost.h>
#include <sideline.h>
#include <findrobot.h>
#include <motion.h>
#include <communication.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240


enum GoalkeeperState{
    FOLLOWBALL,
    AFTERDIVE,//扑倒后检查球
	RETURNFOLLOW,//调整返回球门
};
class Robcup_goalkeeper
{
    public:
        Robcup_goalkeeper();
        ~Robcup_goalkeeper();
        int run();
    private:
    private:

        BallTracker *tracker;
        BallFollower *follower;	
        Motion *motion;
        followball *ballpro; 
        goalpost *goalpro;
        sideline *linepro;
        findrobot *robotpro;
		compass *compasspro;
        
		bool m_is_checkstatus;
        GoalkeeperState m_process_state;
        int m_dive_status; // 0:lie down  1: split
        
        void FollowBall();
        void AfterDive();
		void ReturnFollow();

		
		//compass
		int CompassCheck();// check compass
        double m_angle_diff_opponentGoal;//angle from opponent goal
		double m_OpponentAngle;
        double m_DribbleRightAngle;
        double m_DribbleLeftAngle;
        

        /*************thread********************/
        pthread_t thread[2];
        pthread_mutex_t mut;
        pthread_cond_t cond;

        bool is_new_img;

        static void * InternalThreadVision(void * This) {
            ((Robcup_goalkeeper *)This)->ThreadVision(); 
            return NULL;
        }
        static void * InternalThreadMotion(void * This) {
            ((Robcup_goalkeeper *)This)->ThreadMotion(); 
            return NULL;
        }

        void ThreadVision();
        void ThreadMotion();
        void thread_create();
        void thread_wait(void);
        /******************************************/

        /*********Image Process*********************/

        cv::Mat frame;
        void GetImageResult(cv::Mat &frame, ImgResultType rs);
        void CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D);
        int m_ball_found;// 0: noball 1:found 2:found then lost -1:noball for long
        int m_NoBallMaxCount;
        int m_goal_found;// the number of goalpost
        int m_line_found;// 0:no 1:sideline 2:forbiddenline
        Point2D m_ball_center_2D;
        Point2D m_ball_center_angle;
        Point2D m_line_center_2D;//forbiddenline & sideline
        Point2D m_goalfoot1, m_goalfoot2;
		int m_line_Kvalue;


        double m_DiveRightAngle;
        double m_DiveLeftAngle;
        double m_DiveTopAngle;
        
        double m_LineTopValue;
        
        /*---------------------------------------*/

 		/**********Motion Order****************/
        double m_FBstep;
        double m_unit_FBstep;
        double m_MAX_FBstep;
        
        double m_RLturn;
        double m_unit_RLturn;
        double m_MAX_RLturn;

		double m_RLstep;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        /*------------------------------------*/
        int debug_print;

    protected:


};

#endif // _ROBCUP_GOALKEEPER_H_
