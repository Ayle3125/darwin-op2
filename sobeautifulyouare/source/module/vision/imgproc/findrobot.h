#ifndef FINDROBOT_H
#define FINDROBOT_H

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class findrobot
{
public:
    findrobot();
    ~findrobot();
    Point position;
    Point keeperpositionl;
    Point keeperpositionr;
    void findgoalkeeper(Mat source);
    void imageProcess(Mat source);
private:
    Mat image;
    Mat grayimage;
};

#endif // FINDROBOT_H
