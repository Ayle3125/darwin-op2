/***********************************************************************
 * Compass
 * Universal Synchronous/Asynchronous Receiver/Transmitter (USART)
 * For Ayle
 * Author：Zcer
 * ^_^
 * 2016-04-22
 * 使用该代码时请将main函数删除，并将本文件名改为compass.h
 * 注意u转串连接达尔文时，默认端口要修改为 /dev/ttyUSB1
 * **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <time.h>

#define defaultBaudrate 19200  //默认波特率 记住修改后下面initPort函数也要改
#define defaultCompassPort "/dev/ttyUSB1"  //默认端口，darwin的应该为  /dev/ttyUSB1
#define configFileName "compassConfig.txt"
#define DirNum (4)
//#define DEBUG

class compass
{
    public:
        compass();
        ~compass();
        double GetAngle();
        void resetCompass();
        int loadConfig();

    private:
        int fd;
        int x0;
        int y0;
        int z0;
        double angle0;//初值
        int x;
        int y;
        int z;
        double angle;//当前值
        int initPort();//串口初始化
        int openPort();//打开串口
        int closePort();//关闭串口
        int updateData();//更新当前数据
        //int saveConfig();
        double AngleShift[8];//记录八个方向的angle值，校准转换
        char* rxdata();
};

