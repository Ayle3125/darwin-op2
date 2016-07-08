#ifndef FOLLOWBALL_H
#define FOLLOWBALL_H


#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>


using namespace std;
using namespace cv;

class followball{
private:
        void getSizeContours(vector<vector<Point> > &contours);
        Mat Contour();
        vector< vector<Point> > contours;    //注意加空格
        int MAX_KERNEL_LENGTH;
        int dilation_elem ;
        int dilation_size ;
        int kvalue;
        int most_possible;
        int ball_cir;
        Mat gray_image;
        Mat image;
        Mat dil;
        Mat black;
        Mat source;
        bool what;
        int radius;
        vector<Vec3f> circles;
        void getarea(Mat gray_image);
        void Dilation(int, void *);
public:
        bool findball;
        int ball_rad;
        Point center;
        followball();
        ~followball();
        void imageProcess(Mat source);
};


#endif // FOLLOWBALL_H
