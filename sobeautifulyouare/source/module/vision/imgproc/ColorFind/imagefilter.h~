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

protected:
    bool setDetectObj(cv::Mat &_sample);
    cv::Mat sample_hist_hs;     //输入样本的h-s直方图
    cv::Mat sample_hist_rgb;    //输入样本的rgb直方图

    cv::Mat filted_img_rgb;     //rgb滤波结果
    cv::Mat filted_img_hs;      //h-s滤波结果
    cv::Mat filted_synthese;    //两者滤波综合结果

private:
    //进行滤波的参数
    int histsize_rgb[3],histsize_hs[2];
    float range[2];
    int channels_rgb[3], channels_hs[2];

    //滤波的功能函数
    void sampleHistExtract(cv::Mat &input);
    void colorFilter(cv::Mat &input);
//==============color filter===============
};



