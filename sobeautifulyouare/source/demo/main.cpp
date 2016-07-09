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

#define IMG_WIDTH 320
#define IMG_HEIGHT 240

// 以下宏定义对应于键盘上的0~9.
#define STOP			48
#define OBSTACLE		49
#define MARATHON		50
#define ROBCUP_STRIKER 		51
#define ROBCUP_FULLBACK		52
#define ROBCUP_GOALKEEPER	53
#define ROBCUP_PENALTY		54
#define SPRINT			55

void runObstacle();
void runMarathon();
void runRobcup_striker();
void runRobcup_fullback();
void runRobcup_goalkeeper();
void runRobcup_penalty();
void runSprint();

int main(int argc, char *argv[])
{	
	if(argc == 1)
		return 1;
	switch((int)argv[1][0]) {
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
		runRobcup_penalty();
		break;
	case SPRINT:
		runSprint();
		break;
	default:
		break;
	}

	return 0;
}

void runObstacle()
{
	Obstacle *obstacle = new Obstacle();
	// Here is for Obstacle
	obstacle->run();
}

void runMarathon()
{
	Marathon *marathon = new Marathon();
	// Here is for Marathon
	marathon->run();
}

void runRobcup_striker()
{
	//Robcup_striker *robcup_striker = new Robcup_striker();
	// Here is for Robcup_striker
	//robcup_striker->run();
	Strategist *strategy = new Robcup_striker();
	strategy->run();
}

void runRobcup_fullback()
{
	Robcup_fullback *robcup_fullback = new Robcup_fullback();
	// Here is for Robcup_fullback
	robcup_fullback->run();
}

void runRobcup_goalkeeper()
{
	Robcup_goalkeeper *robcup_goalkeeper = new Robcup_goalkeeper();
	// Here is for Robcup_goalkeeper
	robcup_goalkeeper->run();
}

void runRobcup_penalty()
{
	Robcup_penalty *robcup_penalty = new Robcup_penalty();
	// Here is for Robcup_penalty
	robcup_penalty->run();
}

void runSprint()
{
	Sprint *sprint = new Sprint();
	// Here is for Sprint
	sprint->run();
}