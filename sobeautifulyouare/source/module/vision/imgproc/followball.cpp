#include<followball.h>

followball::followball()
{
    findball = false;
    dilation_elem = 0;
    dilation_size = 1;
    kvalue = 15;
    what = false;
    MAX_KERNEL_LENGTH = 31;
    gray_image = Mat(Size(320,240),CV_8UC1);
    image = Mat(Size(320,240),CV_8UC1);
}
followball::~followball()
{

}

void followball::Dilation(int, void *)
{
    int dilation_type = MORPH_CROSS;
  //  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
 //   else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
 //   else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
    Mat element = getStructuringElement( dilation_type,
    Size( 2*dilation_size + 1, 2*dilation_size+1 ),
    Point( dilation_size, dilation_size ) );
    /// Apply the dilation operation
    Mat element2(5,5,CV_8U,cv::Scalar(255));
    dilate( gray_image, image, element );
    dilate( image, image, element2 );
    dilate( image, image, element );
    dilate( image, image, element );
    dilate( image, image, element2 );
    //erode( image, image, element );
    //namedWindow("image",WINDOW_AUTOSIZE);
    //imshow("image",image);
}

void followball::getSizeContours(vector<vector<Point> > &contours)
{

    int cmin = 100;    // 最小轮廓长度
    int cmax = 15000;   // 最大轮廓长度
    vector<vector<Point> >::iterator itc = contours.begin();
    while(itc != contours.end())
    {

        if((itc->size()) < cmin || (itc->size()) > cmax)
        {
            itc = contours.erase(itc);
        }
        else {
            ++ itc;
        }
    }
}

Mat followball:: Contour()
{
    findContours(image, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
//    if(contours.size() >= 10){
//        threshold_value = threshold_value + 10;
//        findline(src);
//        //break;
//    }
    getSizeContours(contours);
   // cout<<"contour:  "<<contours.size()<<endl;
    Mat result;
    result.create(gray_image.size(),gray_image.type());
    result = Scalar::all(0);
    drawContours(result,contours,-1,Scalar(255),2);
   // imshow("result",result);
    return result;
}

void followball:: imageProcess(Mat source)
{
    std::vector<Mat> hsv_channels;
    int s_threshold = 45;
    Mat src = Mat(Size(320,240),CV_8UC3);
    resize(source,src,Size(320,240),0,0,INTER_LINEAR);
   // imshow("src",src);
    cvtColor(src,src,CV_BGR2HSV);
    split(src,hsv_channels);
    threshold(hsv_channels[1],hsv_channels[1],s_threshold,255,1);
    hsv_channels[1].copyTo(gray_image);
//    imshow("hsv1",hsv_channels[1]);
//    hsv_channels[1].copyTo(source);
    //cvtColor(src,gray_image,CV_BGR2GRAY);
    Dilation(0,0);
    //Contour();
    //namedWindow("image",WINDOW_AUTOSIZE);
   // imshow("image",image);
    HoughCircles(Contour(), circles, CV_HOUGH_GRADIENT, 1.5, 20, 130, 30, 10, 50 );
 //   HoughLines(image, lines, 0.5, CV_PI/360, 240);  // 返回直线坐标对
   // cout<<"circles:  "<<circles.size()<<endl;
    //cout<<"Lines' size"<<lines.size()<<endl;
    if(circles.size() == 0) {
        center = Point(-1,-1);
        findball = false;
    }else if(circles.size() >= 6){
        center = Point(-1,-1);
        findball = false;
    }
    else{
    for( size_t i = 0; i < circles.size(); i++ )
    {
    center=Point(cvRound(circles[i][0]), cvRound(circles[i][1]));
    radius = cvRound(circles[i][2]);
    if(ball_rad < radius)
    {
    ball_rad = radius;
    ball_cir = i;
    }
    // draw the circle center
   // circle( gray_image, center,0, Scalar(0, 255, 0), -1, 8, 0);
     // draw the circle outline
  //  circle( gray_image, center, ball_rad, Scalar(0, 0, 255), 1, 8, 0);
    }
    center = Point(cvRound(circles[ball_cir][0]), cvRound(circles[ball_cir][1]));
    radius = ball_rad;
//   if(center.x != -1 && center.y != -1)
//    {
//        getarea(gray_image);
//    }

//    if(what == false)
//    {
//        center = Point(-1,-1);
//        findball = false;
//    }



//    if(radius <= 30 && radius > 150) {
//        center = Point(-1,-1);
//        findball = false;
//        }
    }
//    if(lines.size() <= 150)
//    {
//        Line = false;
//    }else{

//        Line = true;
//        getarea();
//        cout<<"getarea:  "<<area<<endl;
//    }
//    if(Line == true && area >= 1000)
//    {
//        sideline = true;
//        cout<<"sideline"<<endl;
//        turn();
//    }
  //  else
 //   {

    //qDebug()<<time.elapsed()/1000.0<<"s";
 //  }
  //else{
 //         center = Point(-1,-1);
 //   }
  //  namedWindow("circle",WINDOW_AUTOSIZE);
   // imshow("circle",gray_image);
    cout<<center.x<<"  "<<center.y<<endl;
}

void followball::getarea(Mat gray_image)
{
    int area = 0;
    if(center.x-10 > 0 && center.x+10 < 320 && center.y-10 > 0 && center.y+10 < 240)
    {
    for (int i = center.x-10; i<center.x+10; i++) {
        for (int j = center.x-10; j<center.x+10; j++) {
             if(gray_image.at<uchar>(i,j) < 100)
                    area++;
             if(area > 100){
                 what = true;
                 break;
             }
            }
        }
    }
    else{
        for (int i = center.x-5; i<center.x+5; i++) {
            for (int j = center.x-5; j<center.x+5; j++) {
                 if(gray_image.at<uchar>(i,j) < 100)
                        area++;
                 if(area > 20){
                     what = true;
                     break;
                 }
            }
        }
    }
}

//void followball::turn()
//{
//    //s1为第一象限,s2为第二象限,s3为第三象限,s4为第四象限
//    int s1 = 0;
//    for (int j = 0; j<black.rows/2; j=j+2) {
//          for (int i=black.cols/2; i<black.cols; i = i+2) {
//                if(black.at<Vec3b>(j,i)[0] != 0)
//                    s1++;
//            }
//      }
//    int s2 = 0;
//    for (int j = 0; j<black.rows/2; j=j+2) {
//        for (int i=0; i<black.cols/2; i = i+2) {
//             if(black.at<Vec3b>(j,i)[0] != 0)
//                    s2++;
//            }
//        }
//    int s3 = 0;
//    for (int j = black.rows/2; j<black.rows; j=j+2) {
//        for (int i=0; i<black.cols/2; i = i+2) {
//             if(black.at<Vec3b>(j,i)[0] != 0)
//                    s3++;
//            }
//        }
//    int s4 = 0;
//    for (int j = black.rows/2; j<black.rows; j=j+2) {
//        for (int i=black.cols/2; i<black.cols; i = i+2) {
//             if(black.at<Vec3b>(j,i)[0] != 0)
//                    s4++;
//            }
//        }
//              cout<<s1<<endl;
//              cout<<s2<<endl;
//              cout<<s3<<endl;
//              cout<<s4<<endl;
////      //判断是否为禁区线
////      if(s1+s2<s3+s4)
////          inside_box = true;
//      //判断是否为边线，且分析出机器人转向
//      if(s1+s2>s3+s4)
//      {
//      //    sideline = true;
//          if(s2>s1&&s4>s3)
//              turn_left = true;
//          if(s1>s2&&s3>s4)
//              turn_right = true;
//      }
//}
