#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>
#include<iostream>
#include <sys/time.h>
#include <cstdlib>
#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#endif
using namespace  cv;
using namespace std;

int64_t getCurrentTime()       //时间获取
  {      struct timeval tv;  
         gettimeofday(&tv,NULL);   
         return tv.tv_sec * 1000 + tv.tv_usec / 1000; 
   } 

   

	
cv::Mat readRawDataImage2(std::string imageName, int rawDataHeight, int rawDataWidth)
{
    std::cout<<"nowTime2.00:"<<getCurrentTime()<<"\n";	
	FILE *filePointer;

	fopen_s(&filePointer, imageName.c_str(), "rb+");
	if (filePointer == NULL)
	{
		std::cout << "Can not open the raw data!\n";
		return cv::Mat();
	}
	cv::Mat rawData(rawDataHeight, rawDataWidth, CV_8UC1, cv::Scalar(0));
    std::cout<<"nowTime2.01:"<<getCurrentTime()<<"\n";
	// read imgae data
	for (int i = 0; i < rawDataHeight; i++)
	{
		uchar *pointer = rawData.ptr<uchar>(i);
		fread(pointer, 1, rawDataWidth, filePointer);
	}
    std::cout<<"nowTime2.02:"<<getCurrentTime()<<"\n";
    Mat rgbdata;
 	cvtColor(rawData,rgbdata,COLOR_YUV2RGB_NV12);
	cv::imwrite("test00.jpg", rawData);
	std::cout<<"nowTime2.03:"<<getCurrentTime()<<"\n";
	    vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);  //选择jpeg
	compression_params.push_back(1); //在这个填入你要的图片质量
	//CV_IMWRITE_PNG_COMPRESSION
	std::cout<<"nowTime2.031:"<<getCurrentTime()<<"\n";
	int64_t imgname;;
    imgname<<getCurrentTime();
	std::string wholename , timename;
    timename=std::to_string(getCurrentTime());
	wholename=timename+".png";
    cv::imwrite(wholename,rgbdata,compression_params);
	std::cout<<"nowTime2.04:"<<getCurrentTime()<<"\n";
	return rgbdata;
}

bool YV12ToBGR24_OpenCV(unsigned char* pYUV,unsigned char* pBGR24,int width,int height)
{
    if (width < 1 || height < 1 || pYUV == NULL || pBGR24 == NULL)
        return false;
    Mat dst(height,width,CV_8UC3,pBGR24);
    Mat src(height + height/2,width,CV_8UC1,pYUV);
    cvtColor(src,dst,CV_YUV2RGB_NV12);
    return true;
}

IplImage *src2;


int main()
{
	//int rawDataHeight = 1620;     //1920*1080
	//int rawDataWidth = 1920;
	
 int rawDataHeight = 1080;       //1280*720
 int rawDataWidth = 1280;
 cv::Mat rawImage;
 int toksi=0;
 int toks=0;
 while(toks==0){
 std::cout<<"nowTime1.00:"<<getCurrentTime()<<"\n";
 //system("v4l2-ctl --set-fmt-video=width=1920,height=1080,pixelformat=NV12  --stream-mmap  --stream-count=1 --stream-to=2.raw");//1920*1080 
 system(" v4l2-ctl -d /dev/video0 --set-fmt-video=width=1280,height=720,pixelformat=NV12 --stream-mmap --stream-skip=2  --stream-to=2.raw --stream-count=1         ");//1280*720
// Load image
 std::string imageName = "2.raw";
 std::cout<<"nowTime1.99:"<<getCurrentTime()<<"\n";
 rawImage = readRawDataImage2(imageName, rawDataHeight, rawDataWidth);
 std::cout<<"nowTime2.10:"<<getCurrentTime()<<"\n";
 cv::imshow("test", rawImage);
 /* IplImage imgnormal =rawImage.operator IplImage();
 std::cout<<"nowTime2.101:"<<getCurrentTime()<<"\n";
 IplImage *imgnormal2;
 jiaozheng(&imgnormal,imgnormal2); */
 toks=1;
//  cvShowImage("testbecleared", imgnormal);
  std::cout<<"nowTime2.11:"<<getCurrentTime()<<"\n";
 }
	  waitKey(80000);
	
	
}