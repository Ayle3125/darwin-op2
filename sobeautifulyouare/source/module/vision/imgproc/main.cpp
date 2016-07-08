#include "mainwindow.h"
#include <QApplication>
#include<goalpost.h>
#include<followball.h>
#include<sideline.h>
#include<QTime>
#include<QDebug>


int main(int argc, char *argv[])
{
    QTime time;
    Mat source;
   // Mat source2;
    source = imread("C:\\Users\\Think\\Desktop\\opencv\\123.jpg");
   // source2 = imread("C:\\Users\\Think\\Desktop\\opencv\\37.jpg");

   // while(1){
    time.start();
    sideline sd;
    sd.findline(source);

   // followball fb;
   // fb.imageProcess(source);
  //  cout<<"Center:"<<fb.center.x<<"   "<<fb.center.y<<"rad:  "<<fb.ball_rad<<endl;
   // cout<<"turn right:"<<sd.turn_right<<"   "<<"turn left:"<<sd.turn_left<<endl;
   // goalpost gp;
   // gp.findgoal(source);
   // cout<<"double:"<<gp.two_goal<<"   "<<"single:"<<gp.single_goal<<endl;
    qDebug()<<time.elapsed()/1000.0<<"s";
   // }
    waitKey(0);
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
}
