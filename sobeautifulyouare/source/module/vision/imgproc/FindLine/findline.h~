#ifndef FINDLINE
#define FINDLINE

#include "imgproc.h"
#include <vector>
class FindLineResult : public ImgProcResult
{
public:
     double slope;
     bool valid;
     FindLineResult() : slope(0.0), valid(false) {}
     virtual void operator=(ImgProcResult &res)
     {
         FindLineResult *tmp = dynamic_cast<FindLineResult*>(&res);
         slope = tmp->slope;
         valid = tmp->slope;
     }
     void operator=(FindLineResult &res)
     {
         slope = res.slope;
         valid = res.slope;
     }
};

class FindLine : public ImgProc
{
public:
    FindLine();
    ~FindLine();
    virtual void imageProcess(cv::Mat img, ImgProcResult *Result);
private:
    int erosion_size;
    cv::Mat element;
    cv::Mat src, dst, cdst;
    std::vector<cv::Vec4i> lines;
};

#endif // FINDLINE

