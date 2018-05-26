//http://study.marearts.com/2016/06/opencv-image-and-video-write.html
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>


#ifdef _DEBUG               
#pragma comment(lib, "opencv_core331d.lib")       
#pragma comment(lib, "opencv_highgui331d.lib")    
#pragma comment(lib, "opencv_imgcodecs331d.lib")  
#pragma comment(lib, "opencv_objdetect331d.lib")  
#pragma comment(lib, "opencv_imgproc331d.lib")  
#pragma comment(lib, "opencv_videoio331d.lib")    
#else       
#pragma comment(lib, "opencv_core331.lib")       
#pragma comment(lib, "opencv_highgui331.lib")    
#pragma comment(lib, "opencv_imgcodecs331.lib")    
#pragma comment(lib, "opencv_objdetect331.lib")  
#pragma comment(lib, "opencv_imgproc331.lib")  
#pragma comment(lib, "opencv_videoio331.lib")    
#endif        


using namespace std;
using namespace cv;

void main()
{
	Mat img = imread("ss.jpg");
	vector< Mat> rgbMat(3);
	cv::split(img, rgbMat);

	namedWindow("img", 0); //make window
	imshow("img", rgbMat[2]); //show
	waitKey(0);

	imwrite("r.jpg", rgbMat[2]);
	imwrite("g.bmp", rgbMat[1]);
	imwrite("b.tif", rgbMat[0]);
}