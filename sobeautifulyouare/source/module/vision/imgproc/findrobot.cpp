#include<findrobot.h>

findrobot::findrobot()
{
    position = Point(-1,-1);
    keeperpositionl = Point(-1,-1);
    keeperpositionr = Point(-1,-1);
    image = Mat(Size(320,240),CV_8UC3);
    grayimage = Mat(Size(320,240),CV_8UC1);
}
findrobot::~findrobot()
{

}

void findrobot::findgoalkeeper(Mat source)
{
    resize(source,image,Size(320,240),0,0,INTER_LINEAR);
    imshow("image",image);
    for(int j = image.rows-2;j > 0;j--)
    {    for(int i = 0;i < image.cols;i++)
        {
            if( ((int)image.at<Vec3b>(j,i)[0] < 30)&&((int)image.at<Vec3b>(j,i)[1] < 30)&&((int)image.at<Vec3b>(j,i)[2] > 230))
            {
                //grayimage.at<uchar>(i,j) = 0;
                keeperpositionl.x = i;
                keeperpositionl.y = j;
                break;
            }
        }
        if(keeperpositionl.x > -1) break;
    }

    for(int j = keeperpositionl.y;j > 0;j--)
    {    for(int i = image.cols-1;i > keeperpositionl.x;i--)
        {
            if( ((int)image.at<Vec3b>(j,i)[0] > 230)&&((int)image.at<Vec3b>(j,i)[1] < 30)&&((int)image.at<Vec3b>(j,i)[2] > 230))
            {
                //grayimage.at<uchar>(i,j) = 0;
                keeperpositionr.x = i;
                keeperpositionr.y = j;
                break;
            }
        }
        if(keeperpositionr.x > -1) break;
    }

    cout<<"keeper:  "<<keeperpositionl.x<<keeperpositionl.y<<endl;
    cout<<"keeper:  "<<keeperpositionr.x<<keeperpositionr.y<<endl;
}

void findrobot::imageProcess(Mat source)
{
    resize(source,image,Size(320,240),0,0,INTER_LINEAR);
    cvtColor(image,grayimage,CV_BGR2GRAY);
    imshow("grayimage",grayimage);
    cout << "graysize"<<grayimage.rows<<"  "<<grayimage.cols<<endl;
    cout<<"channels:  "<<grayimage.channels()<<endl;
    for(int j = grayimage.rows-2;j > 0;j--)
    {    for(int i = 0;i < grayimage.cols;i++)
        {
          //  color = grayimage.at<int>(i,j);
            cout<<"gray:"<<(int)grayimage.at<uchar>(j,i)<<"    position:"<<j<<"  "<<i<<endl;
            if( (int)grayimage.at<uchar>(j,i) < 50)
            {
                //grayimage.at<uchar>(i,j) = 0;
                position.x = i;
                position.y = j;
                break;
            }
        }
        if(position.x > -1) break;
    }
    cout<<"position:"<<position.x<<" "<<position.y<<endl;
}
