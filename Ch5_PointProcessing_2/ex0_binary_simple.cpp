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

	namedWindow("img", 0);
	namedWindow("binary", 0);

	Mat img = imread("book.jpg");

	Mat gray, binary;
	cvtColor(img, gray, CV_RGB2GRAY);
	threshold(gray, binary, 128, 200, CV_THRESH_BINARY);


	imshow("img", img);
	imshow("binary", binary);

	waitKey(0);

	return 0;
}