#ifndef IMAGEDISPOSE
#define IMAGEDISPOSE

#include <opencv2/opencv.hpp>
#include <vector>
#include "imagefilter.h"
#include "imgproc.h"

class ColorFindResult : public ImgProcResult
{
public:
    cv::Point2f center;
    cv::Point2f leftUp;
    cv::Point2f rightDown;
    cv::RotatedRect rect;
    double area;
    float radius;
    bool valid;
    
public:
    ColorFindResult() :
        center(),
        rect(),
        radius(0.0),
        valid(false)
    {}

    virtual void operator=(ImgProcResult &res)
    {
	ColorFindResult *tmp = dynamic_cast<ColorFindResult*>(&res);
        center = tmp->center;
        rect = tmp->rect;
        radius = tmp->radius;
	area = tmp->area;
	leftUp = tmp->leftUp;
	rightDown = tmp->rightDown;
	valid = tmp->valid;
    }
    void operator=(ColorFindResult &res)
    {
        center = res.center;
        rect = res.rect;
        radius = res.radius;
	area = res.area;
        leftUp = res.leftUp;
	rightDown = res.rightDown;
	valid = res.valid;
    }
};

class ColorFind : public ImgProc
{

/*******开放的接口********/
public:
    ColorFind() : filter(), MyResult(){filter.load("ball.txt");}
    ~ColorFind(){}
    void load(const std::string &file_path);
    virtual void imageProcess(cv::Mat img, ImgProcResult *Result);

private:
    void drawResult(cv::Mat &drawing, int Tag = 0);
    void clear()
    {
        contours.clear();
        contours_poly.clear();
        boundRect.clear();
        center.clear();
        radius.clear();
        minRect.clear();
    }

/*********滤波器*********/
private:
    imageFilter filter;

/******鹰眼数据空间*******/
private:
    std::vector<std::vector<cv::Point> > contours;
    std::vector<std::vector<cv::Point> > contours_poly;
    std::vector<cv::Rect> boundRect;
    std::vector<cv::Point2f>center;
    std::vector<float>radius;
    std::vector<cv::RotatedRect> minRect;
    int most_possible;
    ColorFindResult MyResult;

/*******图片数据空间*******/
private:
    cv::Mat filter_res;

};

#endif // IMAGEDISPOSE

