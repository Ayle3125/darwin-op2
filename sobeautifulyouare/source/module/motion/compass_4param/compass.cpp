#include "compass.h"

compass::compass()
{
    //初始化为0
    x0=0;
    y0=0;
    z0=0;
    angle0=0;
    x=0;
    y=0;
    z=0;
    angle=0;
    fd=-1;

}

compass::~compass()
{
    closePort();
}

int compass::initPort()
{
    fd=-1;
    fd=open(defaultCompassPort , O_RDWR | O_NOCTTY | O_NDELAY) ;
    if(fd==-1){
        perror("open failed!\n") ;
        return -1;
    }
    struct  termios options;
    tcgetattr(fd,&options);
    //   9600/19200/38400bps , 8n1
    options.c_cflag=B19200|CS8|CLOCAL|CREAD;//set Baudrate!
    options.c_iflag=IGNPAR;
    options.c_oflag=0;
    options.c_lflag=0;
    options.c_cc[VTIME]=0;
    options.c_cc[VMIN]=0;
    tcflush(fd,TCIFLUSH);

    tcsetattr(fd,TCSANOW,&options);

    close(fd);
    printf("Init succeed!\t Baudrate: %d\n ",defaultBaudrate);
    return 0;
}

int compass::openPort()
{
    fd=-1;

    fd=open(defaultCompassPort,O_RDWR | O_NOCTTY | O_NDELAY) ;

    if(fd==-1)
    {
        perror("open failed!\n") ;
        return fd;
    }
    return fd;
}

int compass::closePort()
{
    close(fd);
    return 0;
}

char* compass::rxdata()
{//从串口读取一个长字符串
    int rx_length=0;
    char* s=(char*)malloc(300*sizeof(char));

    if(fd==-1)
    {
        perror("Port is not open !\n") ;
        return NULL;
    }

    tcflush(fd,TCIFLUSH);
    usleep(200000);//micro_seconds   200ms
    rx_length	= read(fd,s,200);

#ifdef DEBUG
    printf("read succeed %d bytes\n",rx_length);
#endif
    if(rx_length<0)   printf("read failed!\n");

    return s;
}

int compass::updateData()
{//成功则更新数据，返回正值8。失败返回负值
    //一个串口数据示例: @x0: -528 y0: -201 z0: -366 angle0: 20.84 x: -533 y: -182 z: -363 angle: 18.85 #
    char* tmp=NULL;
    int s=0,e=0;
    int length;
    int returnvalue;
    char dataStr[100]="";

    tmp=rxdata();
#ifdef DEBUG
    printf("$%s$\n",tmp);
#endif
    length=strlen(tmp);
    if(length<52) return -1;
    for(s=0;s<length;++s){
        if(tmp[s]=='@') break;
    }
    for(e=s;e<length;++e){
        if(tmp[e]=='#') break;
    }
#ifdef DEBUG
    printf("%d %d\n",s,e);
#endif
    if(e-s<50) return -1;
    if(e-s>85) return -2;
    strncpy(dataStr, &tmp[s], e-s+1);
    dataStr[e-s+1]='\0';
#ifdef DEBUG
    printf("[%s]\n",dataStr);
#endif
    returnvalue = sscanf(dataStr," @x0: %d y0: %d z0: %d angle0: %lf x: %d y: %d z: %d angle: %lf",&x0,&y0,&z0,&angle0,&x,&y,&z,&angle);
#ifdef DEBUG
    printf("\n  Resault:  x0: %d y0: %d z0: %d angle0: %lf x: %d y: %d z: %d angle: %lf    \n",x0,y0,z0,angle0,x,y,z,angle);
#endif
    free(tmp);
    tmp=NULL;
    return returnvalue;
}

double compass::GetAngle()/////test!
{
    int tmpReturn;
    int tmpAngle;
    openPort();
    while( true ){
        if (  ( tmpReturn=updateData() ) != 8 ){
            printf("update failed%d\n",tmpReturn);
        }
        else {
            int i;
            //tmpAngle =(  (  ( int) ( angle - angle0 ) ) + 360 )%360;
            tmpAngle = angle;


            int minIndex=0;
            int maxIndex=0;
            for (  i = 1; i < DirNum; i++){
				if(AngleShift[i]<AngleShift[minIndex]) minIndex=i;
				if(AngleShift[i]>AngleShift[maxIndex]) maxIndex=i;
            }

            int tmpIndex,findIndex;
            tmpIndex=minIndex;
            findIndex=maxIndex;
            for (  i = 1; i < DirNum; i++, tmpIndex=(tmpIndex+1)%DirNum){
                if ( tmpAngle >= AngleShift[tmpIndex] && angle < AngleShift[(tmpIndex+1)%DirNum] ){
					findIndex=tmpIndex;
                    break;
                }
            }

            double pitchValue;
			double amplitude = (AngleShift[maxIndex]-AngleShift[minIndex])*4.0/3.0 ;
            pitchValue=tmpAngle-AngleShift[findIndex];
            if(pitchValue<0) pitchValue += amplitude;


            double blockLength;
            blockLength=AngleShift[(findIndex+1)%DirNum]-AngleShift[findIndex];
            if(blockLength<0) blockLength+= amplitude;
            printf ( "the angle from target is: %lf \n", findIndex*90+pitchValue/blockLength*90);
        }
        //getchar();
        //tmpReturn=CP.updateData();
        //usleep(10);
        //free(tmp);
    }
return 0;
}
 
void compass::resetCompass()
{

    initPort();
    openPort();
    AngleShift[0] = 0;
    printf("请沿着顺时针方向依次记录4个值（90度）：\n" );
    int tmpReturn;
    for (int i = 0; i < DirNum; i++){
	getchar();
        printf("确定第%d个方向后按Enter键：\n",i);
        getchar();
        //for ( int j = 0; j < 5; j++)
        while(true){
			usleep(500000);
			tmpReturn =updateData();// 5 times to ensure
			if ( tmpReturn !=8 ) {
				printf("请重新确定这个方向的角度值\n");
				continue;
			}
			printf("angle %lf\n" , angle);
			printf("确定输入y，重测输入n\n");
			if('y'==getchar()) break;
			else printf("重测中\n");

        }

        //AngleShift[i] =(  (  ( int) ( angle - angle0 ) ) + 360 )%360;
        AngleShift[i] = angle;
        //printf("angle0: %lf  angle%d: %lf\n" , angle0, i, AngleShift[i]);
    }

        /////////////////////////////
        FILE *configFile;

	configFile = fopen( configFileName ,"w");

	if(configFile!=NULL) {
		fprintf(configFile,"%lf %lf %lf %lf",AngleShift[0],AngleShift[1],AngleShift[2],AngleShift[3]);
		//fputs(s2,configFile);
		fclose(configFile);
		printf("Config Saved!\n");
	}else{
		printf("Open file filed!\n");
	}
}

int compass::loadConfig()
{
    initPort();
    openPort();
	FILE *configFile;
	configFile = fopen( configFileName ,"r");

	if(configFile!=NULL) {
		fscanf(configFile,"%lf %lf %lf %lf",&AngleShift[0],&AngleShift[1],&AngleShift[2],&AngleShift[3]);
		//fputs(s2,configFile);
		fclose(configFile);
		printf("Config loaded!\n");
		return true;
	}else{
		printf("Open file filed!\n");
		return false;
	}
}
///////////////////An Example//////////////////////////
int main()
{
    //char* tmp;
    compass CP;

    CP.resetCompass();
    //CP.loadConfig();
    CP.GetAngle();


    return 0;
}
