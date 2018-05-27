//http://study.marearts.com/2018/05/adaptivethreshold-test-code-in-opencv.html

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
	namedWindow("threshold", 0);
	namedWindow("mean_thres", 0);
	namedWindow("gauss_thres", 0);


	Mat img = imread("otzu.jpg");

	Mat gray, binary, binary1, binary2;
	cvtColor(img, gray, CV_RGB2GRAY);

	threshold(gray, binary, 128, 255, CV_THRESH_BINARY);
	adaptiveThreshold(gray, binary1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 5);
	adaptiveThreshold(gray, binary2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 5);


	imshow("img", img);

	imshow("threshold", binary);
	imshow("mean_thres", binary1);
	imshow("gauss_thres", binary2);


	waitKey(0);

	return 0;
}

