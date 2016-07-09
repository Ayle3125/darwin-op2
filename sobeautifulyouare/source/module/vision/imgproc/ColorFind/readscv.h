#ifndef READSCV
#define READSCV

#include <opencv.hpp>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

void readcsv(const std::string &fileName, std::vector<cv::Mat>& images,std::vector<int>& labels,char separator = ';')
{
    std::ifstream file(fileName.c_str(),std::ifstream::in);    //以读入的方式打开文件
    std::string line,path,label;
    while (std::getline(file,line))                       //从文本文件中读取一行字符，未指定限定符默认限定符为“/n”
    {
        std::stringstream lines(line);
        std::getline(lines,path,separator);               //根据指定分割符进行分割，分为“路径+标号”
        std::getline(lines,label);

        if (!path.empty()&&!label.empty())           //如果读取成功，则将图片和对应标签压入对应容器中
        {
            images.push_back(cv::imread(path));        //读取训练样本
            labels.push_back(atoi(label.c_str()));   //读取训练样本标号
        }
    }
}
#endif // READSCV

