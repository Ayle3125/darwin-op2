#ifndef BAYES
#define BAYES

#include <vector>
#include <opencv2/opencv.hpp>
#include <string>

class Bayes
{

/************开放的接口函数*************/
public:
    Bayes(int sup = 256, int low = 0);//以指定阈值构造训练器
    ~Bayes(){} //默认析构
    void train(
            //需要RGB格式
            const std::vector<cv::Mat> &training_set,
            const std::vector<int> &label_set
            );      //使用给定的样本集生成特征文件
    void save(std::string &file_path); //将结果写入文件

/**********算法无关的工具函数************/
private:
    void clear(unsigned int set_size);//清理信息，初始化类的状态

/************像素数统计函数*************/
private:
    void count_pixel(
            const std::vector<cv::Mat> &training_set,
            const std::vector<int> &label_set
            ); //统计像素数

/**************Y阈值信息**************/
private:
    int sup_Y;  //超过此值的坐标将被抛弃
    int low_Y;  //低于此值的坐标将被抛弃

/**************像素数信息**************/
private:
    int pixel_all;         //样本集总像素数
    std::vector<int> pixel_class;   //每一类样本的总像素数
    /***用于计算P(Ci)***/
    std::vector<std::vector<int> > pixel_U_color_class;//每一类样本U坐标的像素总数
    std::vector<std::vector<int> > pixel_V_color_class;//每一类样本V坐标的像素总数
    /*用于计算P(ai|Ci)*/

/*********像素数向概率数转换函数**********/
private:
    void cal_class_prb();//计算P(Ci)
    void cal_UV_prb();   //计算P(ai|Ci)

/**************概率数信息**************/
private:
    std::vector<long double> prb_class; //每一类样本像素占总数的概率(P(Ci))
    //prb_class[i] = pixel_class[i] / pixel
    std::vector<std::vector<long double> > prb_U_color_class;//每一类样本U坐标的概率数
    //prb_U_color_class[i][j] = pixel_U_color_class[i][j] / pixel_class[i]
    std::vector<std::vector<long double> > prb_V_color_class;//每一类样本V坐标的概率数
    //prb_V_color_class[i][j] = pixel_V_color_class[i][j] / pixel_class[i]
    std::vector<int> label; //储存标签

/***************分类函数***************/
private:
    void cal_map_list();

/***************分类信息***************/
private:
    int map_list[256][256];//最终映射表

};

#endif // BAYES

