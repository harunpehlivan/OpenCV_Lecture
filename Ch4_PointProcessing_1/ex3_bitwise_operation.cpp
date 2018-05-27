//http://study.marearts.com/2017/02/opencv-lecture-and-or-xor-not-example_14.html
//http://study.marearts.com/2017/02/opencv-lecture-and-or-xor-not-example.html


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
	//example 1
	Mat leftCircle = Mat(500, 1000, CV_8UC1);

	Mat rightCircle = Mat(500, 1000, CV_8UC1);
	leftCircle.setTo(0);
	rightCircle.setTo(0);

	circle(leftCircle, Point(1000 / 5 * 2, 500 / 2), 250, CV_RGB(255, 255, 255), CV_FILLED);
	circle(rightCircle, Point(1000 / 5 * 3, 500 / 2), 250, CV_RGB(255, 255, 255), CV_FILLED);

	//and, or, xor, not 
	Mat res;
	bitwise_and(leftCircle, rightCircle, res);     imshow("AND", res);
	bitwise_or(leftCircle, rightCircle, res);      imshow("OR", res);
	bitwise_xor(leftCircle, rightCircle, res);     imshow("XOR", res);
	bitwise_not(leftCircle, res);                    imshow("NOT", res);

	imshow("leftCircle", leftCircle);
	imshow("rightCircle", rightCircle);

	waitKey(0);



	/*
	example 2
	Mat img = imread("empireofthesun.jpg");
	Mat img_mask = img.clone(); // imread("empireofthesun_mask.jpg");
	img_mask.setTo(0);
	circle(img_mask, Point(1000 / 5 * 2, 500 / 2), 250, CV_RGB(255, 255, 255), CV_FILLED);

	Mat res;
	//bitwise_and(img, img_mask, res);     
	bitwise_and(img, img_mask, res);     imshow("AND", res);
	bitwise_or(img, img_mask, res);      imshow("OR", res);
	bitwise_xor(img, img_mask, res);     imshow("XOR", res);
	bitwise_not(img, res);               imshow("NOT", res);

	imshow("img_mask", img_mask);
	imshow("img", img);

	waitKey(0);
	*/


	

	return 0;
}