#ifndef SIDELINE_H
#define SIDELINE_H

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace  cv;

class sideline{

private:
    int area;
    int MAX_GRAY_VALUE;
    int MIN_GRAY_VALUE;
    Mat result;
    int threshold_value;
    int threshold_type;
    int max_BINARY_value;
    bool  goal;
    bool side;
    void getarea();
    void gravity();
    void getSizeContours(vector<vector<Point> > &contours);
    void Contour();
    void findside();
    void getgoal();
    void Erosion(int, void *);
    int otsu(Mat dst);
    vector< vector<Point> > contours;    //注意加空格
    vector<Vec2f> lines;
    int MAX_KERNEL_LENGTH;
    int erosion_elem ;
    int erosion_size ;
    int kvalue;
    int most_possible;
    int ball_cir;
    Mat gray_image;
    Mat image;
    Mat src;
    Mat thres;
    Mat black;
    Mat black2;
    Mat source;
public:
    double k_value;
    int line_type;
    int forbiddenline;
    int sidelines;
    Point center;
    void imageProcess(Mat source);
    sideline();
    ~sideline();
};

#endif // SIDELINE_H
