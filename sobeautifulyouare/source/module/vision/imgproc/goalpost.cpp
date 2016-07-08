#include<goalpost.h>

goalpost::goalpost(){
      MAX_GRAY_VALUE = 256;
      MIN_GRAY_VALUE = 0;
      lowThreshold = 30;
      kernel_size = 3;
      threshold_value = 160;
      threshold_type = 3;
      max_BINARY_value = 240;
      goal_number = 0;
      left = false;
      right = false;
      goal_foot1 = Point(-1,-1);
      goal_foot2 = Point(-1,-1);

      debug_print = false;
}

goalpost::~goalpost()
{

}

int goalpost::otsu(Mat dst){

    int i,j;
    int tmp;

    double u0,u1,w0,w1,u, uk;

    double cov;
    double maxcov=0.0;
    int maxthread=0;

    int hst[256]={0};
    double pro_hst[256]={0.0};

    int height=dst.cols;
    int width=dst.rows;




    //统计每个灰度的数量
    for( i =0 ; i<width; i++ ){
        for( j=0; j<height; j++){
            tmp=dst.at<uchar>(i,j);
            hst[tmp]++;
        }
    }

    //计算每个灰度级占图像中的概率
    for( i=MIN_GRAY_VALUE ; i<MAX_GRAY_VALUE; i++)
        pro_hst[i]=(double)hst[i]/(double)(width*height);


    //计算平均灰度值
    u=0.0;
    for( i=MIN_GRAY_VALUE; i<MAX_GRAY_VALUE; i++)
        u += i*pro_hst[i];

    double det=0.0;
    for( i= MIN_GRAY_VALUE; i< MAX_GRAY_VALUE; i++)
        det += (i-u)*(i-u)*pro_hst[i];

    //统计前景和背景的平均灰度值，并计算类间方差

    for( i=MIN_GRAY_VALUE; i<MAX_GRAY_VALUE; i++){

        w0=0.0; w1=0.0; u0=0.0; u1=0.0; uk=0.0;

        for( j=MIN_GRAY_VALUE; j < i; j++){

            uk += j*pro_hst[j];
            w0 += pro_hst[j];

        }
        u0=uk/w0;


        w1=1-w0;
        u1= (u - uk )/(1-w0);


        //计算类间方差
        cov=w0*w1*(u1-u0)*(u1-u0);

        if ( cov > maxcov )
        {
            maxcov=cov;
            maxthread=i;
        }
    }

//    cout<<maxthread<<std::endl;
    return maxthread;


}

void goalpost::imageProcess(Mat source)
{
    //source = imread("C:\\Users\\Think\\Desktop\\opencv\\397.jpg");
   // flip(source,source,-1);
    src= Mat(Size(320,240),CV_8UC3);
    resize(source,src,Size(320,240),0,0,INTER_LINEAR);
  //  namedWindow("gray",WINDOW_AUTOSIZE);
  //  imshow("gray",src);
    gray_image.create(src.size(), src.type());
    cvtColor(src,gray_image,CV_BGR2GRAY);
    blur( gray_image, thres, Size(3,3) );
    thres.copyTo(gray_image);
    threshold( gray_image, thres, otsu(gray_image), max_BINARY_value,CV_THRESH_OTSU );
    if ( debug_print ){	 
    	namedWindow("thres",WINDOW_AUTOSIZE);
    	imshow("thres",thres);
    }
    black.create(src.size(),src.type());
    black = Scalar::all(0);
    vector<Vec2f> lines;
    HoughLines(thres, lines, 1,CV_PI/180, 100, 0, 0);  // 返回直线坐标对
        for (size_t i=0; i<lines.size(); i++)
        {
            float rho = lines[i][0];
            float theta = lines[i][1];
            Point pt1,pt2;
            double a=cos(theta);
            double b=sin(theta);
            double c=abs(a/b);
            double x0 = rho*a;
            double y0 = rho*b;
            pt1.x = cvRound(x0+1000*(-b));
            pt1.y = cvRound(y0+1000*a);
            pt2.x = cvRound(x0-1000*(-b));
            pt2.y = cvRound(y0-1000*a);
            if(c>50)
           {

                line(black, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
            }
        }
         if ( debug_print )  imshow("black",black);
        //thres.copyTo(black2);
        cvtColor(black,black2,CV_RGB2GRAY);
        Contour();
        //cout<<"contour"<<contours.size()<<endl;
        if(contours.size() == 2)
        {
            goal_number = 2;
          //  goal();
            range();
            goalfoot();
            range2();
            goalfoot2();

        }
        if(contours.size() == 1)
           {
            goal_number = 1;
            range();
            goalfoot();
            //width = tec_ru.y-tec_lu.y;
        }
        if(contours.size() > 2)
        {
            goal_number = 0;
        }
         if ( debug_print ) cout<<"goalnumber"<<goal_number<<"  goal1:"<<goal_foot1<<"  goal2:"<<goal_foot2<<endl;
}

void goalpost::goalfoot2()
{
    cout<<"goal2:"<<tec_lu2<<"  "<<tec_rb2<<endl;
   // for(int i = tec_lu2.x; i < tec_rb2.x;i++)
   // {
        for(int j = 0;j < 239;j++)
        {
            if((int)thres.at<uchar>(j,tec_lu2.x) == 0)
            {
                goal_foot2.x = tec_lu2.x;
                goal_foot2.y = j;
                break;
            }
        }
  //  }
}

void goalpost::range2()
{
    for(int j=black.cols;j>0;j--)
     {

            if(black.at<Vec3b>(1,j)[0] != 0)
          {
         tec_lu2.y = 1;
         tec_lu2.x = j;
         break;
         }
       }
    for(int j=black.cols-1;j > 0;j--)
     {

            if(black.at<Vec3b>(239,j)[0] != 0)
          {
         tec_rb2.x = j;
         tec_rb2.y = 239;
         break;
         }
       }



}

void goalpost::goalfoot()
{
    //cout<<tec_lu<<"  "<<tec_rb<<endl;
    for(int j = 0;j < 239;j++)
    {
        if((int)thres.at<uchar>(j,(tec_lu.x+tec_rb.x)/2) == 0)
        {
            goal_foot1.x = (tec_lu.x+tec_rb.x)/2;
            goal_foot1.y = j;
            break;
        }
    }

}

void goalpost::range()
{
    for(int i = 1, j=0;j<black.cols;j++)
     {

            if(black.at<Vec3b>(i,j)[0] != 0)// 0 is black, 255 is white
            {
         tec_lu.y = i;
         tec_lu.x = j;
         break;
         }
       }
    for(int i = 239, j=tec_lu.x;j<black.cols;j++)
     {

            if(black.at<Vec3b>(i,j)[0] == 0)
          {
         tec_rb.x = j;
         tec_rb.y = i;
         break;
         }
       }

}



void goalpost::getSizeContours(vector<vector<Point> > &contours)
{
    int cmin = 480;   // 最小轮廓长度
    int cmax = 10048;   // 最大轮廓长度
    vector<vector<Point> >::iterator itc = contours.begin();
    while(itc != contours.end())
    {
        //cout<<itc->size()<<endl;
        if((itc->size()) < cmin || (itc->size()) > cmax)
        {
            itc = contours.erase(itc);
        }
        else ++ itc;
    }
}

void goalpost:: Contour()
{
    findContours(black2, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
    getSizeContours(contours);
    Mat result(black2.size(),CV_8U,Scalar(0));
    drawContours(result,contours,-1,Scalar(255),2);
    //result = result<255;
    if ( debug_print ) imshow("result",result);
     if ( debug_print ) result.copyTo(black2);
    //cout<<contours.size()<<endl;
}

void goalpost::goal()
{
    int x0 = 0,y0 = 0;
    int a = 0;
        for (int i=0;i<black.rows;i++)
        {
            for(int j=0;j<black.cols;j++)
          {
             if(thres.at<Vec3b>(i,j)[0] == 0)
           {
           a++;
           x0 += i;
           y0 += j;
          }
         }
        }

        center.x = y0/a;
        center.y = x0/a;
      //  cout<<"center"<<center.x<<"   "<<center.y<<endl;
}
