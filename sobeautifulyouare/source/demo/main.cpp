#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <BlobResult.h>
#include <camera.h>
#include <imgproc.h>
#include <motion.h>
#include <strategy.h>
#include <communication.h>
#include <obstacle.h>
#include <marathon.h>
#include <robcup_fullback.h>
#include <robcup_goalkeeper.h>
#include <robcup_penalty.h>
#include <robcup_striker.h>
#include <sprint.h>
#include <ladder.h>
#include <golf.h>
#include <fira_penalty.h>
#include <shot.h>
#include <test.h>

#define IMG_WIDTH 320
#define IMG_HEIGHT 240

// 以下宏定义对应于键盘上的0~9.
#define TEST			48
#define OBSTACLE		49
#define MARATHON		50
#define ROBCUP_STRIKER 		51
#define ROBCUP_FULLBACK		52
#define ROBCUP_GOALKEEPER	53
#define ROBCUP_PENALTY		54
#define SPRINT			55
#define LADDER			56
#define GOLF			57
#define SHOT			58
#define FIRA_PENALTY	59

void runObstacle();
void runMarathon();
void runRobcup_striker();
void runRobcup_fullback();
void runRobcup_goalkeeper();
void runRobcup_penalty();
void runSprint();
void runLadder();
void runGolf();
void runShot();
void runFira_penalty();
void runTest();


int main(int argc, char *argv[])
{	
    if(argc == 1)
        return 1;
    switch((int)argv[1][0]) {
        case TEST:
            runTest();
            break;
        case OBSTACLE:
            runObstacle();
            break;
        case MARATHON:
            runMarathon();
            break;
        case ROBCUP_STRIKER:
            runRobcup_striker();
            break;
        case ROBCUP_FULLBACK:
            runRobcup_fullback();
            break;
        case ROBCUP_GOALKEEPER:
            runRobcup_goalkeeper();
            break;
        case ROBCUP_PENALTY:
            runFira_penalty();
            break;
        case SPRINT:
            runSprint();
            break;
        case LADDER:
            runLadder();
            break;
        case GOLF:
            runGolf();
            break;
        case SHOT:
            runShot();
            break;
        case FIRA_PENALTY:
            runFira_penalty();
            break;
        default:
            printf("Please input the choice(e.g:sudo ./demo 1):\n");
            printf("%2d:obstacle,         %2d:Marathon,           %2d:Robcup_striker\n", OBSTACLE-48, MARATHON-48, ROBCUP_STRIKER-48);
            printf("%2d:Robcup_fullback,  %2d:Robcup_goalkeeper,  %2d:runRobcup_penalty\n", ROBCUP_FULLBACK-48, ROBCUP_GOALKEEPER-48, ROBCUP_PENALTY-48);
            printf("%2d:Sprint,           %2d:Ladder,             %2d:Golf\n", SPRINT-48, LADDER-48, GOLF-48);
            printf("%2d:Shot,             %2d:Fira_penalty:     \n", SHOT-48, FIRA_PENALTY-48);
            break;
    }

    return 0;
}
void runTest()
{
    Test *test = new Test();
    test->run();
}

void runObstacle()
{
    Obstacle *obstacle = new Obstacle();
    obstacle->run();
}

void runMarathon()
{
    Marathon *marathon = new Marathon();
    marathon->run();
}

void runRobcup_striker()
{
    Robcup_striker *robcup_striker = new Robcup_striker();
    robcup_striker->run();
}

void runRobcup_fullback()
{
    Robcup_fullback *robcup_fullback = new Robcup_fullback();
    robcup_fullback->run();
}

void runRobcup_goalkeeper()
{
    Robcup_goalkeeper *robcup_goalkeeper = new Robcup_goalkeeper();
    robcup_goalkeeper->run();
}

void runRobcup_penalty()
{
    Robcup_penalty *robcup_penalty = new Robcup_penalty();
    robcup_penalty->run();
}

void runSprint()
{
    Sprint *sprint = new Sprint();
    sprint->run();
}

void runLadder()
{
    Ladder *ladder = new Ladder();
    ladder->run();
}

void runGolf()
{
    Golf *golf = new Golf();
    golf->run();
}

void runShot()
{
    Shot *shot = new Shot();
    shot->run();
}

void runFira_penalty()
{
    Fira_penalty *fira_penalty = new Fira_penalty();
    fira_penalty->run();
}
