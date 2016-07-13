#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <ColorFind.h>
using namespace cv;
using namespace std;

int main()
{
    ColorFind find;
    VideoCapture cap(0);
    Mat img;
    ColorFindResult *tmp = new ColorFindResult;
    while(true){
        cap >> img;
        find.imageProcess(img, tmp);
	cout << tmp->area << endl;
        if(waitKey(30) != -1) break;
    }
    return 0;
}
