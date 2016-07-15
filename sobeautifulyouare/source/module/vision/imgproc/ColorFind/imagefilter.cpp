#include "imagefilter.h"
#include <fstream>

using namespace std;
using namespace cv;

void imageFilter::load(const string &file_path)
{
    ifstream in(file_path.c_str(), ios::in);
    for(int i = 0; i < 256; ++i){
        for(int j = 0; j < 256; ++j){
            in >> map_list[i][j];
	    
        }
    }
 histsize_rgb[0]=30;histsize_rgb[1]=30;histsize_rgb[2]=30; //rgb
    histsize_hs[0]=30;histsize_hs[1]=32;//hs
    channels_rgb[0]=0;channels_rgb[1]=1;channels_rgb[2]=2;
    channels_hs[0]=0;channels_hs[1]=1;
    range[0]=0; range[1]=255;

    string samplePath;
    in >> samplePath;
    Mat sample = imread(samplePath);

    setDetectObj(sample);
	
}

void imageFilter::filt(const cv::Mat &in, cv::Mat &out)
{
    img_res = in.clone();
    cvtColor(img_res, img_YUV, CV_BGR2YUV);
    int rows = img_YUV.rows;
    int cols = img_YUV.cols;
    int step = img_YUV.channels();
    for(int i = 0; i < rows; ++i){
        uchar* data = img_YUV.ptr<uchar>(i);
        uchar* dataBGR = img_res.ptr<uchar>(i);
        for(int j = 0; j < cols * step; j += step){
            if(map_list[data[j + 1]][data[j + 2]] != 0){
                dataBGR[j + 0] = 255;
                dataBGR[j + 1] = 255;
                dataBGR[j + 2] = 255;
            }
        }
    }
    int size_dilate = 2, size_erode = 2;
    Mat element_dilate =
            getStructuringElement(MORPH_RECT,
                                  Size(2 * size_dilate + 1, 2 * size_dilate + 1),
                                  Point(size_dilate, size_dilate));
    Mat element_erode =
            getStructuringElement(MORPH_RECT,
                                  Size(2 * size_erode + 1, 2 * size_erode + 1),
                                  Point(size_erode, size_erode));

    dilate(img_res, img_res, element_dilate);
    erode(img_res, img_res, element_erode);
    cvtColor(img_res, img_res, CV_BGR2GRAY);
    equalizeHist(img_res, img_res);
    threshold(img_res,img_res, 196,255,THRESH_BINARY_INV);
    blur(img_res, img_res, Size(3,3));
    Mat tmp = in.clone();

    colorFilter(tmp);

    img_res = filted_img_hs * 0.5 + filted_img_rgb * 0.5;
//threshold(img_res,img_res,128,255,THRESH_BINARY);
    out = img_res.clone();
}

//===============color filter===================
bool imageFilter::setDetectObj(Mat &_sample)
{
    sampleHistExtract(_sample);
    return true;
}

void imageFilter::sampleHistExtract(Mat &input)
{

    float h_range[2];
    float s_range[2];
    h_range[0] = 0;
    h_range[1] = 180;
    s_range[0] = 0;
    s_range[1] = 255;

    const float* ranges_rgb[] =
                              {range,range,range};
    calcHist(&input,1,channels_rgb,Mat(),sample_hist_rgb,
             2,histsize_rgb,ranges_rgb,true,false);

    normalize(sample_hist_rgb,sample_hist_rgb,
              0,255,NORM_MINMAX,-1,Mat());

    const float* ranges_hs[3] =
                              {h_range,s_range};
    cvtColor(input,input,CV_BGR2HSV);
    calcHist(&input,1,channels_hs,Mat(),sample_hist_hs,
             2, histsize_hs, ranges_hs, true, false);
    normalize(sample_hist_hs,sample_hist_hs, 0,255,NORM_MINMAX,-1,Mat());
}
void imageFilter::colorFilter(Mat &input)
{
    int _threshold = 55;
    int s_threshold = 15;
    float h_range[2];
    float s_range[2];
    h_range[0] = 0;
    h_range[1] = 180;
    s_range[0] = 0;
    s_range[1] = 255;
    std::vector<Mat> hsv_channels;
    const float* ranges_rgb[] = {range,range,range};

    //rbg
    calcBackProject(&input,1,channels_rgb,sample_hist_rgb,
                    filted_img_rgb,ranges_rgb,1,true);
    threshold(filted_img_rgb,filted_img_rgb,_threshold,255,cv::THRESH_BINARY);
    medianBlur(filted_img_rgb,filted_img_rgb,5);
    medianBlur(filted_img_rgb,filted_img_rgb,5);

    //hsv
    const float* ranges_hs[3] =
    {h_range,s_range};

    cvtColor(input,input,CV_BGR2HSV);
    split(input,hsv_channels);
    threshold(hsv_channels[1],hsv_channels[1],s_threshold,255,CV_THRESH_BINARY);
    filted_img_hs = Scalar::all(0);
    calcBackProject(&input,1,channels_hs,sample_hist_hs,
                    filted_img_hs,ranges_hs,1,true);
    bitwise_and(filted_img_hs,hsv_channels[1],filted_img_hs);
    //threshold(filted_img_hs,filted_img_hs,_threshold,255,CV_THRESH_BINARY);
    medianBlur(filted_img_hs,filted_img_hs,5);
    medianBlur(filted_img_hs,filted_img_hs,5);

    Mat element(7,7,CV_8U,cv::Scalar(1));
    dilate(filted_img_hs,filted_img_hs,element);

    //    cvtColor(filted_img_hs,filted_img_hs,CV_HSV2BGR);
    //    cvtColor(filted_img_hs,filted_img_hs,CV_BGR2GRAY);
    //    threshold(filted_img_hs,filted_img_hs,_threshold,255,cv::THRESH_BINARY);
    //    medianBlur(filted_img_hs,filted_img_hs,5);
    //    medianBlur(filted_img_hs,filted_img_hs,5);
    /******去掉饱和度低于某阈值的点**************/
    //    imshow("filted_img_hs",filted_img_hs);
    //    vector<Mat> v;
    //    split(input,v);
    //    threshold(v[1],v[1],190,255,THRESH_BINARY);
    //    bitwise_and(filted_img_hs,v[1],filted_img_hs);
    //    imshow("aws",filted_img_hs);
    //imshow("filted_img_synthese",filted_synthese);
}

