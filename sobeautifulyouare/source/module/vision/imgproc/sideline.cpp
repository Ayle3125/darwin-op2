#include<sideline.h>

sideline::sideline()
{
    MAX_GRAY_VALUE = 256;
    area = 0;
    MIN_GRAY_VALUE = 0;
    k_value = 0.0;
    line_type = 0;
    threshold_value = 120;
    threshold_type = 3;
    max_BINARY_value = 255;
    forbiddenline  = 0;
    erosion_elem = 0;
    erosion_size = 5;
    kvalue = 15;
    sidelines = 0;
    goal = false;
    center = Point(-1,-1);
    MAX_KERNEL_LENGTH = 31;
    side = false;
    //black = Mat(Size(320,240),CV_8SC1);
    gray_image = Mat(Size(320,240),CV_8UC1);
    //image = Mat(Size(320,240),CV_8UC1);
    //result = (Size(320,240),CV_8U,Scalar(0));
}

sideline::~sideline()
{

}

//void sideline::threshold()
//{
//    threshold( gray_image, thres, 160, max_BINARY_value,3 );
//}

void sideline::imageProcess(Mat source)
{   
    //source = imread("C:\\Users\\Think\\Desktop\\opencv\\397.jpg");
//    flip(source,source,-1);
//    imshow("source",source);
    src= Mat(Size(320,240),CV_8UC3);
    resize(source,src,Size(320,240),0,0,INTER_LINEAR);
   // namedWindow("src",WINDOW_AUTOSIZE);
   // imshow("src",src);
    gray_image.create(src.size(), src.type());
    cvtColor(src,gray_image,CV_BGR2GRAY);
    //imshow("gray image",gray_image);
    findside();
    Erosion(0, 0);
    blur( gray_image, thres, Size(3,3) );
    threshold( gray_image, thres,otsu(gray_image), max_BINARY_value,8 );
    thres.copyTo(gray_image);
    //namedWindow("thres",WINDOW_AUTOSIZE);
    //imshow("thres",thres);
    black.create(src.size(),src.type());
    black = Scalar::all(0);
    getgoal();
    black = Scalar::all(0);
    vector<Vec2f> lines;
    HoughLines(thres, lines, 0.5, CV_PI/360, 100);  // 返回直线坐标对
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
            if(c < 10)
           {
                line(black, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
           }
        }
        cvtColor(black,black2,CV_RGB2GRAY);
       // imshow("black2",black2);
        Contour();
        cout<<"sidelines: "<<sidelines<<" forbiddenline: "<<forbiddenline<<endl;
}

void sideline::findside()
{
    int sum = 0;
    for(int i = 0;i < gray_image.cols;i++)
       for(int j = 0;j < gray_image.rows;j++)
       {
           if((int)gray_image.at<uchar>(i,j) < 160 && (int)gray_image.at<uchar>(i,j) > 130)
           {
               sum++;
           }
           if(sum >= 400)
           {
               side = true;
               break;
           }
       }
}

int sideline::otsu(Mat dst){

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

 //   cout<<maxthread<<std::endl;
    return maxthread;
}

void sideline::gravity()
{
    int x0 = 0,y0 = 0;
    int a = 0;
        for (int i=0;i<black.rows;i++)
        {
            for(int j=0;j<black.cols;j++)
          {
             if((int)thres.at<uchar>(i,j) == 255)
           {
           a++;
           x0 += i;
           y0 += j;
          }
         }
        }

        center.x = y0/a;
        center.y = x0/a;
        cout<<"center"<<center.x<<"   "<<center.y<<endl;
}

void sideline::Erosion(int, void *)
{
    int erosion_type;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
    Mat element = getStructuringElement( erosion_type,
    Size( 2*erosion_size + 1, 2*erosion_size+1 ),
    Point( erosion_size, erosion_size ) );
    /// Apply the erosion operation
    erode( gray_image, gray_image, element );
}

void sideline::getSizeContours(vector<vector<Point> > &contours)
{
    area = 0;
    int cmin = 100;   // 最小轮廓长度
    int cmax = 1000;   // 最大轮廓长度
    vector<vector<Point> >::iterator itc = contours.begin();
    while(itc != contours.end())
    {
        cout<<"area:  "<<itc->size()<<endl;

        if((itc->size()) < cmin || (itc->size()) > cmax)
        {
            itc = contours.erase(itc);
        }
        else {
            ++ itc;
            if(itc->size() > area)
            {
                area = itc->size();
            }
        }
    }

//   itc = contours.begin();
//    while(itc != contours.end())
//    {
////        if(itc->size() > 40000){
////            threshold_value = threshold_value + 10;
////            findline(src);
////            break;
////        }
//     if((itc->size()) > 2000){
//        itc = contours.erase(itc);
//    }
//     else ++ itc;
//    }
 //   cout<<"contours:  "<<contours.size()<<endl;
    if(contours.size() == 1 && side == true) {
        sidelines = 1;
        forbiddenline = 0;
        line_type = 1;
        gravity();
    } else if(side == false && contours.size() == 1)
     {
        sidelines = 0;
        forbiddenline = 1;
        line_type = 2;
    }else
    if( contours.size() == 2)
    {
     sidelines = 1;
     forbiddenline = 1;
     line_type = 2;
     gravity();
    }else if(goal == true)
    {
        sidelines = 1;
        forbiddenline = 1;
        line_type =2;
    }else
    {
        sidelines = 0;
        forbiddenline = 0;
        line_type =0;
    }

//    cout<<"all size:"<<contours.size()<<endl;
//    itc = contours.begin();
//    while(itc != contours.end())
//    {
//        cout<<"area:"<<itc->size()<<endl;
//        ++itc;
//    }
}

void sideline::getgoal()
{
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
        //imshow("black",black);
        //thres.copyTo(black2);
        cvtColor(black,black2,CV_RGB2GRAY);
        findContours(black2, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
        if(contours.size() == 1 || contours.size() == 2)
        goal = true;
}

void sideline:: Contour()
{
    findContours(black2, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
//    if(contours.size() >= 10){
//        threshold_value = threshold_value + 10;
//        findline(src);
//        //break;
//    }
    getSizeContours(contours);
   // cout<<"contour:  "<<contours.size()<<endl;

    result.create(black2.size(),black2.type());
    result = Scalar::all(0);
    drawContours(result,contours,-1,Scalar(255),2);
    //result = result<255;
    //result.copyTo(black2);
  //  namedWindow("result",WINDOW_AUTOSIZE);
  //  imshow("result",result);
    //cout<<contours.size()<<endl;
 //   black2 = Scalar::all(0);
//    drawContours(black2,contours,-1,Scalar(255),2);
    vector<Vec2f> lines2;
    HoughLines(result, lines2, 0.5, CV_PI/360, 100);  // 返回直线坐标对
        for (size_t i=0; i<lines2.size(); i++)
        {
            float rho = lines2[i][0];
            float theta = lines2[i][1];
            Point pt1,pt2;
            double a=cos(theta);
            double b=sin(theta);
            double c=a/b;
            double x0 = rho*a;
            double y0 = rho*b;
            pt1.x = cvRound(x0+1000*(-b));
            pt1.y = cvRound(y0+1000*a);
            pt2.x = cvRound(x0-1000*(-b));
            pt2.y = cvRound(y0-1000*a);

            if(abs(c) < 10)
           {
                line(black2, pt1, pt2, Scalar(255,255,255), 3, CV_AA);
              //  cout<<"xielv:"<<c<<endl;
           }
            if(abs(c) > abs(k_value)){
                k_value = c;
            }
            if(abs(k_value) < 0.01)
            {
                k_value = 0;
            }
        }
       // imshow("black2",black2);
       //cout<<"k-value"<<k_value<<endl;
}
