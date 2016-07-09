#include "bayes.h"
#include <cstring>
#include <fstream>
#include <set>

using namespace std;
using namespace cv;

Bayes::Bayes(int sup, int low):
    sup_Y(sup),
    low_Y(low),
    pixel_all(0),
    pixel_class(0),
    pixel_U_color_class(0),
    pixel_V_color_class(0),
    prb_class(0),
    prb_U_color_class(0),
    prb_V_color_class(0)
{
    memset(map_list, 0, sizeof(map_list));
}

void Bayes::train(
        //需要RGB格式
        const vector<Mat> &training_set,
        const vector<int> &label_set
        )
{
    set<int> tmp;
    //统计标签总数（要求标签连续）
    for(unsigned i = 0; i < label_set.size(); ++i){
        tmp.insert(label_set[i]);
    }
    size_t set_size = tmp.size();

    clear(set_size);
    count_pixel(training_set, label_set);
    cal_class_prb();
    cal_UV_prb();
    cal_map_list();
}

void Bayes::save(string &file_path)
{
    ofstream out(file_path.c_str(), ios::out);
    for(unsigned u = 0; u < 256; ++u){
        out << map_list[u][0];
        for(unsigned v = 1; v < 256; ++v){
            out << " " << map_list[u][v];
        }
        out << endl;
    }
    cout << "ok" << endl;
}

void Bayes::clear(unsigned set_size)
{
    memset(map_list, 0, sizeof(map_list));
    pixel_all = 0;
    pixel_class.assign(set_size, 0);
    pixel_U_color_class.assign(set_size, vector<int>(256, 0));
    pixel_V_color_class.assign(set_size, vector<int>(256, 0));
    prb_class.assign(set_size, 0.0);
    prb_U_color_class.assign(set_size, vector<long double>(256, 0.0));
    prb_V_color_class.assign(set_size, vector<long double>(256, 0.0));
}

void Bayes::count_pixel(
        const vector<Mat> &training_set,
        const vector<int> &label_set
        )
{
    size_t set_size = label_set.size();
    Mat YUV_tmp;
    for(unsigned i = 0; i < set_size; ++i){
        if(training_set[i].empty()){
            continue;
        }
        cvtColor(training_set[i], YUV_tmp, CV_BGR2YUV);

        int rows = YUV_tmp.rows;
        int cols = YUV_tmp.cols;
        int step = YUV_tmp.channels();

        for(int j = 0; j < rows; ++j){
            uchar* data = YUV_tmp.ptr<uchar>(j);
            for(int k = 0; k < cols * step; k += step){
                if(data[k + 0] > sup_Y || data[k + 0] < low_Y)
                    continue;
                ++pixel_all;
                ++pixel_class[label_set[i]];
                ++pixel_U_color_class[label_set[i]][data[k + 1]];
                ++pixel_V_color_class[label_set[i]][data[k + 2]];
            }
        }
    }
}

void Bayes::cal_class_prb()
{
    unsigned set_size = pixel_class.size();
    for(unsigned i = 0; i < set_size; ++i){
        prb_class[i] = pixel_class[i] * 1.0 / pixel_all;
    }
}

void Bayes::cal_UV_prb()
{
    unsigned set_size = pixel_class.size();
    for(unsigned i = 0; i < set_size; ++i){
        for(unsigned j = 0; j < 256; ++j){
            prb_U_color_class[i][j] =
                    pixel_U_color_class[i][j] * 1.0 / pixel_class[i];
            prb_V_color_class[i][j] =
                    pixel_V_color_class[i][j] * 1.0 / pixel_class[i];
        }
    }
}

void Bayes::cal_map_list()
{
    unsigned set_size = pixel_class.size();
    for(unsigned u = 0; u < 256; ++u){
        for(unsigned v = 0; v < 256; ++v){
            long double max = 0.0;
            long double tmp = 0.0;
            int maxi = -1;
            for(unsigned i = 0; i < set_size; ++i){
                tmp =
                    prb_U_color_class[i][u] * prb_V_color_class[i][v] * prb_class[i];
                if(tmp > max){
                    max = tmp;
                    maxi = i;
                }
            }
            map_list[u][v] = maxi;
        }
    }
}
