//http://study.marearts.com
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
	//Declaration and at the same time created
	Mat mtx(3, 3, CV_32F); // make a 3x3 floating-point matrix
	Mat cmtx(10, 1, CV_64FC2); // make a 10x1 2-channel floating-point
							   // matrix (10-element complex vector)
	Mat img(Size(5, 3), CV_8UC3); // make a 3-channel (color) image
								  // of 1920 columns and 1080 rows.

								  //Created after the declaration
	Mat mtx2;
	mtx2 = Mat(3, 3, CV_32F);
	Mat cmtx2;
	cmtx2 = Mat(10, 1, CV_64FC1);

	//Create a point
	Mat* mtx3 = new Mat(3, 3, CV_32F);
	delete mtx3;

	//value set and print
	mtx.setTo(10);
	cout << mtx << endl;

	cmtx.setTo(11);
	cout << cmtx << endl;


}