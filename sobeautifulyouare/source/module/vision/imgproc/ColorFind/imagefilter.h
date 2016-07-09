#include <opencv2/opencv.hpp>

class imageFilter
{
/*******开放的接口********/
public:
    imageFilter(){}
    ~imageFilter(){}
    void load(const std::string &file_path);
    void filt(const cv::Mat &in, cv::Mat &out);

/******工作内存空间*******/
private:
    int map_list[256][256];
    cv::Mat img_res;
    cv::Mat img_YUV;
};



