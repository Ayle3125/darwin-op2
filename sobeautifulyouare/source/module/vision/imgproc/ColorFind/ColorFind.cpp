#include "ColorFind.h"
using namespace std;
using namespace cv;

void ColorFind::load(const string &file_path)
{
    filter.load(file_path);
}

void ColorFind::imageProcess(cv::Mat img, ImgProcResult &Result)
{
    filter.filt(img, filter_res);
    clear();
    cvtColor(filter_res, filter_res, CV_BGR2GRAY);
    equalizeHist(filter_res, filter_res);
    threshold(filter_res,filter_res,196,255,THRESH_BINARY_INV);
    blur(filter_res, filter_res, Size(3,3));
#ifdef QT_DEBUG
    namedWindow("filter_res");
    imshow("filter_res", filter_res);
#endif
    findContours(filter_res, contours,
                 CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE,
                 Point(1,1));
    minRect.resize(contours.size());
    contours_poly.resize(contours.size());
    boundRect.resize(contours.size());
    center.resize(contours.size());
    radius.resize(contours.size());

    for(unsigned i = 0; i < contours.size(); i++){
        minRect[i] = minAreaRect(Mat(contours[i]));
        approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
        boundRect[i] = boundingRect(Mat(contours_poly[i]));
        minEnclosingCircle(contours_poly[i], center[i], radius[i]);
    }
    most_possible = -1;
    float max = 0.0;

    for(unsigned i = 0; i< contours.size(); i++){
        if (radius[i] > max){
            most_possible = i;
            max = radius[i];
        }
    }
    if(most_possible == -1){
        MyResult.valid = false;
    }else{
        MyResult.radius = max;
        MyResult.center = center[most_possible];
        MyResult.rect = minRect[most_possible];
        MyResult.valid = true;
    }
    Result = MyResult;
#ifdef QT_DEBUG
    Mat ball_dis = Mat::zeros(filter_res.size(), CV_8UC3);
    if(most_possible != -1){
        drawResult(ball_dis);
        drawResult(out, 1);
    }
    namedWindow("ball_dis");
    imshow("ball_dis",ball_dis);
#endif
}

void ColorFind::drawResult(Mat &drawing, int Tag)
{
    if(Tag == 0)
        drawContours(drawing, contours_poly, most_possible,Scalar( 255, 255, 255 ), 1, 8, vector<Vec4i>(), 0, Point());
    rectangle(drawing, boundRect[most_possible].tl(), boundRect[most_possible].br(), Scalar(0, 255, 0), 2, 8, 0);
    Point2f rect_points[4]; minRect[most_possible].points( rect_points );
    for(int j = 0; j < 4; j++)
        line( drawing, rect_points[j], rect_points[(j+1)%4], Scalar(0, 0, 255), 1, 8 );
    circle(drawing, center[most_possible], (int)radius[most_possible], Scalar(255, 0, 0), 2, 8, 0);
    circle(drawing, center[most_possible],3, Scalar( 255, 0, 0 ), 2, 8, 0);
}
