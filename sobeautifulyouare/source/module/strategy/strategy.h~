#ifndef STRATEGIST_H
#define STRATEGIST_H
/*
#ifdef MX28_1024
#define MOTION_FILE_PATH    "../../../Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../../../Data/motion_4096.bin"
#endif

#define INI_FILE_PATH       "../../../Data/config.ini"
#define SCRIPT_FILE_PATH    "script.asc"

#define U2D_DEV_NAME0       "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

*/

#include <compass.h>
#include <StatusCheck.h>

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
#include <imgproc.h>
#include <ColorFind/ColorFind.h>
<<<<<<< HEAD
#include <FindLine/findline.h>
=======
>>>>>>> origin/zhoudongyang
#include <followball.h>
#include <goalpost.h>
#include <sideline.h>
#include <findrobot.h>
#include <motion.h>
#include <communication.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240
#define OPPONENTGOAL (0) // or 180 can not other now
enum ImgResultType{
    BALL,
    GOALPOST,
    GOALKEEPER,
    LINE,

};
class Strategist {
    public:
        Strategist();
        int run();
		int vision_exe;

    private:
        bool debug_print;

    protected:
        Motion *motion;
        compass *compasspro;
		bool is_cap;
		bool is_checkstatus;
		

        /*------------------thread--------------------*/
        pthread_t thread[2];
        pthread_mutex_t mut;
        pthread_cond_t cond;

        bool is_new_img;

        static void * InternalThreadVision(void * This) {
            ((Strategist *)This)->ThreadVision(); 
            return NULL;
        }
        static void * InternalThreadMotion(void * This) {
            ((Strategist *)This)->ThreadMotion(); 
            return NULL;
        }

        void ThreadVision();
        virtual void ThreadMotion() = 0; 
        void ThreadCreate();
        void ThreadWait(void);

        /*------------------Image---------------------*/
        cv::Mat frame;
		ImgProcResult *imgRes;
		ImgProc *imgProc;
        virtual int GetImageResult(){};
        void CVpointTo2Dpoint(cv::Point p_cv, Point2D &p_2D);

        /*------------------compass-------------------*/
        int CompassCheck();
        double m_angle_diff_opponentGoal;//angle from opponent goal
        double m_OpponentAngle;
        double m_DribbleRightAngle;
        double m_DribbleLeftAngle;
};

#endif // STRATEGIST_H

