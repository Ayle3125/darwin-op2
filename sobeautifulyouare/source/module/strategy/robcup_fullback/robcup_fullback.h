#ifndef _ROBCUP_FULLBACK_H_
#define _ROBCUP_FULLBACK_H_

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
#define WAITTIME (10*8000)


enum FullbackState{
    WALKFORBALL,
    CLOSETOBALL,
    LONGSHOT,
    BACK,
};//TODO 可以加倒下挡球 dive 的状态

class Robcup_fullback
{
    public:
        Robcup_fullback();
        ~Robcup_fullback();
        int run();
    private:

        BallTracker *tracker;
        BallFollower *follower;	
        Motion *motion;
        followball *ballpro; 
        goalpost *goalpro;
        sideline *linepro;
        findrobot *robotpro;
	    compass *compasspro;

        FullbackState m_process_state;

        void WalkForBall();
        void CloseToBall();
        void Longshot();
        void GoBack();

		
		//compass
		int CompassCheck();// check compass
        double m_angle_diff_opponentGoal;//angle from opponent goal
		double m_OpponentAngle;
        double m_DribbleRightAngle;
        double m_DribbleLeftAngle;
        

        /***************thread********************/
        pthread_t thread[2];
        pthread_mutex_t mut;
        pthread_cond_t cond;

        bool is_new_img;

        static void * InternalThreadVision(void * This) {
            ((Robcup_fullback *)This)->ThreadVision(); 
            return NULL;
        }
        static void * InternalThreadMotion(void * This) {
            ((Robcup_fullback *)This)->ThreadMotion(); 
            return NULL;
        }

        void ThreadVision();
        void ThreadMotion();
        void ThreadCreate();
        void ThreadWait(void);
        /*---------------------------------------*/

        /*********Image Process*******************/

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
	
        double m_LongShotRightAngle;
        double m_LongShotLeftAngle;
        double m_LongShotTopAngle;
        int m_kick_ball_count;
        int m_KickBallMaxCount;
        
        /*---------------------------------------*/

        /*************Motion Order****************/

        double m_FBstep;
        double m_unit_FBstep;
        double m_MAX_FBstep;

        double m_RLturn;
        double m_unit_RLturn;
        double m_MAX_RLturn;

        double m_RLstep;
        double m_unit_RLstep;
        double m_MAX_RLstep;
        
        /*---------------------------------------*/

        int debug_print;

    protected:

};

#endif // _ROBCUP_FULLBACK_H_
