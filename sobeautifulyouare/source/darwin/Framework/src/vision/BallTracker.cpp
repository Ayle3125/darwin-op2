/*
 *   BallTracker.cpp
 *
 *   Author: ROBOTIS
 *
 */

#include <math.h>
#include "Head.h"
#include "Camera.h"
#include "ImgProcess.h"
#include "BallTracker.h"
#include "Walking.h"
#include "MotionStatus.h"

using namespace Robot;


BallTracker::BallTracker() :
    ball_position(Point2D(-1.0, -1.0))
{
    NoBallCount = 0;
	TiltTopLimit = 10;
	TiltBottomLimit = -5;
	PanLimit = 65;
	PanAmplitude = 5;
}

BallTracker::~BallTracker()
{
}

int BallTracker::Search(bool count_reset)
{
    static int count = 0;

    if(count_reset)
        count = 0;

    if(count > NotFoundMaxCount)
        return -1;
    else
    {
        count++;
        // Search
        Head::GetInstance()->InitTracking();

        double head_pan_angle = Head::GetInstance()->GetPanAngle();
        double head_tilt_angle =  Head::GetInstance()->GetTiltAngle();

        if((TiltTopLimit - head_tilt_angle) > (head_tilt_angle - TiltBottomLimit))//头部偏下
        {
            head_pan_angle -= PanAmplitude;
            if(head_pan_angle < ( -1.0*PanLimit ) ) //已经最右
                Head::GetInstance()->MoveByAngle( ( -1.0*PanLimit ), TiltTopLimit);// -> 最上
            else Head::GetInstance()->MoveByAngle(head_pan_angle, TiltBottomLimit);// -> 最下
        }
        else
        {
            head_pan_angle += PanAmplitude;
            if(head_pan_angle > PanLimit) // 已经最左
                Head::GetInstance()->MoveByAngle(PanLimit, TiltBottomLimit); // -> 最下
            else Head::GetInstance()->MoveByAngle(head_pan_angle, TiltTopLimit); //头部偏上 -> 最上左转
        }
    }

    return 0;
}

int BallTracker::SearchAndTracking(Point2D pos)
{
    /*
     * return
     * 0 : noball && NoBallCount < NotFoundMaxCount -> Search go on;
     * -1: no ball && NoBallCount > NotFoundMaxCount -> go straight;
     * 1 : find ball -> follow;
     * 2 : find ball then no ball, if_find == 1 && NoBallCount < -> go backward;
     */
    int debug_print = 1;
    static int          found_count     = 0;
    static int          not_found_count = 0;
    static bool         if_find = false;
    static int          bear_not_found_count = 7;
    static const int    max_found_count = 0;
    static const double max_x_offset    = 3.0;

    if(pos.X < 0 || pos.Y < 0)
    {
        // NOT Found
		found_count = 0;
        if( debug_print == 1) printf("noballcount %d\n", NoBallCount);
        ball_position.X = -1.0;
        ball_position.Y = -1.0;
	NoBallCount++;
        if(if_find && NoBallCount < bear_not_found_count)
        {
            //Head::GetInstance()->MoveTracking();
		return 0;
        }
        else
        {
	    if ( if_find ) {
			if_find = false;
			Head::GetInstance()->MoveBackTracking();
			return 2;
	     }
            if(NoBallCount > NotFoundMaxCount){
                NoBallCount = 0;
                return -1;
            }
            else{
                if( debug_print == 1) printf("head adjust\n");
                //
                // Search
                Head::GetInstance()->InitTracking();

                double head_pan_angle = Head::GetInstance()->GetPanAngle();
                double head_tilt_angle =  Head::GetInstance()->GetTiltAngle();

                if((TiltTopLimit - head_tilt_angle) > (head_tilt_angle - TiltBottomLimit))
                {
                    if( debug_print == 1) printf(" head_pan_angle -= 5;\n");
                    head_pan_angle -= PanAmplitude;
                    if(head_pan_angle < ( -1.0*PanLimit ) ) Head::GetInstance()->MoveByAngle( ( -1.0*PanLimit ), TiltTopLimit);
                    else Head::GetInstance()->MoveByAngle(head_pan_angle, TiltBottomLimit);
                }
                else
                {
                    if( debug_print == 1) printf(" head_pan_angle += 5;\n");
                    head_pan_angle += PanAmplitude;
                    if(head_pan_angle > PanLimit) Head::GetInstance()->MoveByAngle(PanLimit, TiltBottomLimit);
                    else Head::GetInstance()->MoveByAngle(head_pan_angle, TiltTopLimit);
                }
            }
        }
        return 0;
    }
    else
    {
        // Found
        if_find = true;
        NoBallCount = 0;
		found_count++;
		if(found_count > max_found_count){
//found_count = 0;
        Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
        Point2D offset = pos - center;
        offset *= -1; // Inverse X-axis, Y-axis
        offset.X *= (Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle
        offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
	double head_tilt_angle =  Head::GetInstance()->GetTiltAngle();//TODO
		
        ball_position = offset;
        Head::GetInstance()->MoveTracking(ball_position*0.2);
		return 1;
		}
		else {
        	return 0;
		}	
        /*
           double head_pan_angle = Head::GetInstance()->GetPanAngle();
           if((-max_x_offset < offset.X && offset.X < max_x_offset) ||
           (head_pan_angle == Head::GetInstance()->GetLeftLimitAngle() || head_pan_angle == Head::GetInstance()->GetRightLimitAngle()))
           {//头部处于最左/最右/球处于视野中心
        //fprintf(stderr, "[SearchAndTracking] FOUND!! \n");
        if(found_count > max_found_count)//Q:并不明白这里记录找到的次数做什么╮(╯▽╰)╭
        {
        found_count = 0;
        return 1;
        }
        else
        found_count++;
        }
        else
        found_count = 0;
        */
    }
}

void BallTracker::Process(Point2D pos)
{
    if(pos.X < 0 || pos.Y < 0)
    {
        ball_position.X = -1;
        ball_position.Y = -1;
        if(NoBallCount < NoBallMaxCount)
        {
            Head::GetInstance()->MoveTracking();
            NoBallCount++;
        }
        else
            Head::GetInstance()->InitTracking();
    }
    else
    {
        NoBallCount = 0;
        Point2D center = Point2D(Camera::WIDTH/2, Camera::HEIGHT/2);
        Point2D offset = pos - center;
        offset *= -1; // Inverse X-axis, Y-axis 如果图片中心为(0,0) 像素点左负右正、上负下正，实际角度相反
        offset.X *=(Camera::VIEW_H_ANGLE / (double)Camera::WIDTH); // pixel per angle // change by ayle
        offset.Y *= (Camera::VIEW_V_ANGLE / (double)Camera::HEIGHT); // pixel per angle
        ball_position = offset;
        //Head::GetInstance()->MoveTracking(ball_position);
    }
}

void BallTracker::ChangeLimit(int tiltTop, int tiltBottom, int panLimit, int mode)
{
		limit_mode = mode;
		TiltTopLimit = tiltTop; 
		TiltBottomLimit = tiltBottom; 
		PanLimit = panLimit;
}
