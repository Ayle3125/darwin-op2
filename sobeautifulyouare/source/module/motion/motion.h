#ifndef _MOTION_H_
#define _MOTION_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "frame.h"
#include "LinuxDARwIn.h"


#define SCRIPT_FILE_PATH    "script.asc"
#define U2D_DEV_NAME0       "/dev/ttyUSB0"
#define U2D_DEV_NAME1       "/dev/ttyUSB1"

#ifdef MX28_1024
#define MOTION_FILE_PATH    "../source/darwin/Data/motion_1024.bin"
#else
#define MOTION_FILE_PATH    "../source/darwin/Data/motion_4096.bin"
#endif

using namespace Robot;

class Motion{

    public:
        Motion();
        ~Motion();
        void init_motion();
        void sprint_init();
        void tuner_ARM_SWING_GAIN(double value);

        void walk_x_move_amplitude(double FBStep = 0.0);
        void walk_a_move_amplitude(double RLTurn = 0.0);
        void walk_h_move_amplitude(double HTStep = 40);
        void walk_y_move_amplitude(double RLStep = 0.0);
        void walk_star();
        int get_walking_phrase();
        void stop_walking();
        void walking(double ht, double fb, double al, double rl);
        void set_walking_time(double t);
        void walk(double FBstep, double RLstep, double RLturn);

        void CheckStatus();

        void shutdown();
    private:
        Point2D pt;

        BallTracker *tracker;
        BallFollower *follower;

        LinuxCM730 *linux_cm730;
        CM730 *cm730;

        int firm_ver;

    public:
        void Run(MyPointf *coorf);

    public:
        void poseInit();

};

#endif // _MOTION_H_
