//http://study.marearts.com/2018/05/image-binary-simple-example-for-image.html

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
	VideoCapture stream1(0); //0:note book, 1:usb webcam

	Mat frame; //current frame
	Mat gray, binary_otsu, binary_th, binary_ad_m, binary_ad_g;

	namedWindow("img", 0);
	namedWindow("otsu", 0);
	namedWindow("binary_th", 0);
	namedWindow("binary_adaptive_mean", 0);
	namedWindow("binary_adaptive_gaussian", 0);

	//unconditional loop   
	while (true) {

		if (!(stream1.read(frame))) //get one frame form video   
			break;

		//printf("%d %d \n", frame.cols, frame.rows);
		resize(frame, frame, Size(frame.cols / 2, frame.rows / 2));
		cvtColor(frame, gray, CV_RGB2GRAY);

		threshold(gray, binary_th, 128, 255, CV_THRESH_BINARY);
		adaptiveThreshold(gray, binary_ad_m, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 9, 5);
		adaptiveThreshold(gray, binary_ad_g, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 9, 5);
		GaussianBlur(gray, gray, Size(7, 7), 0);
		threshold(gray, binary_otsu, 0, 255, CV_THRESH_BINARY + THRESH_OTSU);


		imshow("img", frame);
		imshow("otsu", binary_otsu);
		imshow("binary_th", binary_th);
		imshow("binary_adaptive_mean", binary_ad_m);
		imshow("binary_adaptive_gaussian", binary_ad_g);

		if (waitKey(10)> 0)
			break;
	}

	return 0;
}


