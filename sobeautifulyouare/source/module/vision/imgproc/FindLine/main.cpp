#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <findline.h>
using namespace cv;
using namespace std;

int main()
{

    FindLine find;
    VideoCapture cap(0);
    Mat img;
    while(true){
        cap >> img;
        find.imageProcess(img, NULL);
        if(waitKey(30) != -1) break;
    }
    return 0;
}
