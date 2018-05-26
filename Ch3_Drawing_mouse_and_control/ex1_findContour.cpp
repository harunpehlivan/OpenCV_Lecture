//http://study.marearts.com/2018/05/find-contour-example-source-code.html

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <vector>

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

int main()
{
	Mat img(500, 500, CV_8UC3);
	img.setTo(255);

	cvtColor(img, img, CV_RGB2GRAY);
	img.setTo(0);
	rectangle(img, Rect(10, 10, 200, 200), CV_RGB(255, 255, 255), CV_FILLED);
	imshow("show1", img);

	Mat dst = Mat::zeros(img.rows, img.cols, CV_8UC3);
	vector< vector< Point> > contours;
	vector< Vec4i> hierarchy;

	findContours(img.clone(), contours, hierarchy,
		RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	// iterate through all the top-level contours,
	// draw each connected component with its own random color
	int idx = 0;
	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		//drawContours(dst, contours, idx, color, FILLED, 8, hierarchy);
		drawContours(dst, contours, idx, color, 1, 8, hierarchy);
	}

	imshow("show2", dst);

	waitKey(0);

	return 0;
}