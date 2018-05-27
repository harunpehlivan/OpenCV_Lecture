//http://study.marearts.com/2017/04/otzu-binary-simple-example.html
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/cudaarithm.hpp"
#include <iostream>
#include <vector>

#ifdef _DEBUG               
#pragma comment(lib, "opencv_core331d.lib")       
#pragma comment(lib, "opencv_highgui331d.lib")    
#pragma comment(lib, "opencv_imgcodecs331d.lib")  
#pragma comment(lib, "opencv_objdetect331d.lib")  
#pragma comment(lib, "opencv_imgproc331d.lib")  
#pragma comment(lib, "opencv_videoio331d.lib")  
#pragma comment(lib, "opencv_cudaarithm331d.lib")  
#else       
#pragma comment(lib, "opencv_core331.lib")       
#pragma comment(lib, "opencv_highgui331.lib")    
#pragma comment(lib, "opencv_imgcodecs331.lib")    
#pragma comment(lib, "opencv_objdetect331.lib")  
#pragma comment(lib, "opencv_imgproc331.lib")  
#pragma comment(lib, "opencv_videoio331.lib")
#pragma comment(lib, "opencv_cudaarithm331.lib")
#endif        


using namespace std;
using namespace cv;


int main(int, char)
{

	namedWindow("img", 0);

	Mat img = imread("noise.jpg");

	Mat gray, binary, binary_th, binary_ad;
	cvtColor(img, gray, CV_RGB2GRAY);

	threshold(gray, binary_th, 128, 255, CV_THRESH_BINARY);
	adaptiveThreshold(gray, binary_ad, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 5);

	GaussianBlur(gray, gray, Size(7, 7), 0);
	threshold(gray, binary, 0, 255, CV_THRESH_BINARY + THRESH_OTSU);

	imshow("img", img);
	imshow("otsu", binary);
	imshow("binary_th", binary_th);
	imshow("binary_ad", binary_ad);

	waitKey(0);

	return 0;
}
