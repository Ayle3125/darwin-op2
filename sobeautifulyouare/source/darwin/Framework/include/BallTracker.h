/*
 *   BallTracker.h
 *
 *   Author: ROBOTIS
 * 
 * ------- 20160420 by Ayle ------
 * 为方便策略使用：
 * 0.这里将DarwIn源代码中的const常量TiltTopLimit, TiltBottomLimit, PanLimit 改成可变常量。Head中会再次checkLimit
 * 1.将Process中改变头部动作的代码注释，如有需要显式调用。
 * 
 */

#ifndef _BALL_TRACKER_H_
#define _BALL_TRACKER_H_

#include <string.h>

#include "Point.h"
#include "minIni.h"

namespace Robot
{
	class BallTracker
	{
	private:
		int NoBallCount;
		static const int NoBallMaxCount = 15, NotFoundMaxCount = 50;
        double TiltTopLimit, TiltBottomLimit, PanLimit ;

	public:
        Point2D     ball_position;
		int limit_mode;// 0: striker_findball  1:striker_findgoal 2:goalkeeper 3:fullback
		 int PanAmplitude;
		 
		BallTracker();
		~BallTracker();

		int  Search(bool count_reset);
        int  SearchAndTracking(Point2D pos);
        void ChangeLimit(int tiltTop, int tiltBottom, int panLimit, int mode){};
        void Process(Point2D pos);

	};
}

#endif

