#include "findline.h"
#include <cmath>
using namespace std;
using namespace cv;
#define PI 3.1415926535
double CalK(int x1, int y1, int x2, int y2)
{
    if(x1 != x2){
        return atan((y1 - y2) * 1.0 / (x1 - x2));
    }
    else return PI / 2;
}

FindLine::FindLine() :
    src(),
    dst(),
    cdst()
{
    erosion_size = 2;
    element = getStructuringElement(MORPH_ELLIPSE,
                                    Size(2*erosion_size + 1, 2*erosion_size+1),
                                    Point(erosion_size, erosion_size));
}

FindLine::~FindLine()
{

}

void FindLine::imageProcess(cv::Mat img, ImgProcResult *Result)
{
    src = img(Rect(0, img.rows / 2, img.cols, img.rows / 2));
    erode(src, src, element);
    dilate(src, src, element);
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);
    HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
    if(lines.size() > 0){
       Point begin(0, 0), end(0, 0);
       int cnt = 0;
       for( size_t i = 0; i < lines.size(); i++ ){
           //line( cdst, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255,0,0), 3, CV_AA);
           double k = CalK(lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
           if(fabs(k) > PI / 6){
            begin.x += lines[i][0];
            begin.y += lines[i][1];
            end.x += lines[i][2];
            end.y += lines[i][3];
            ++cnt;
           }
       }
       if(cnt != 0){
        begin.x /= cnt;
        begin.y /= cnt;
        end.x /= cnt;
        end.y /= cnt;
        //line( cdst, begin, end, Scalar(0,0,255), 3, CV_AA);
        dynamic_cast<FindLineResult*>(Result)->slope = CalK(begin.x, begin.y, end.x, end.y);
        dynamic_cast<FindLineResult*>(Result)->valid = true;
       }else{
        dynamic_cast<FindLineResult*>(Result)->valid = false;
       }
    }
#ifdef QT_NO_DEBUG
    namedWindow("source");
    namedWindow("detected lines");
    imshow("source", src);
    imshow("detected lines", cdst);
#endif
}
