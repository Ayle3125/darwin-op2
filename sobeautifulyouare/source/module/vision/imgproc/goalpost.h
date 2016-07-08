#ifndef GOALPOST_H
#define GOALPOST_H
#include<iostream>
#include<opencv2/opencv.hpp>



using namespace std;
using namespace cv;

class goalpost
{
   private:
    int MAX_GRAY_VALUE;
    int MIN_GRAY_VALUE;
    int lowThreshold;
    int kernel_size;
    int threshold_value;
    int threshold_type;
    int max_BINARY_value;
    Mat gray_image;
    Mat thres;
    Mat src;
    Mat src2;
    Mat black;
    Mat black2;
    void Contour();
    Point tec_lu,tec_ru,tec_lb,tec_rb;
    Point tec_rb2,tec_lu2;
    vector< vector<Point> > contours;    //注意加空格
    void goal();
    void range();
    void goalfoot();
    void range2();
    void goalfoot2();
    int otsu(Mat dst);
    void getSizeContours(vector<vector<Point> > &contours);

   bool debug_print;
   public:
    int width;
    goalpost();
    ~goalpost();
    void imageProcess(Mat);
    Point center;
    Point goal_foot1;
    Point goal_foot2;
    int goal_number;
    bool left;
    bool right;
};

#endif // GOALPOST_H
