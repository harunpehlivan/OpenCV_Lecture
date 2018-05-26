//http://study.marearts.com/2016/06/opencv-mat-copyto-clone-roi-example-code.html

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

	Rect r(img.cols / 4, img.rows / 4, img.cols / 4 * 2, img.rows / 4 * 2);

	//clone #1
	Mat img2 = img.clone();
	bitwise_not(img2, img2);

	//clone #2
	Mat img5 = img(r).clone();


	//copyTo #1
	Mat cimg;
	img.copyTo(cimg);

	//copyTo #2
	Mat cimg2;
	img(r).copyTo(cimg2);

	//copyTo #3
	Mat cimg3(Size(img.cols * 2, img.rows), img.type());
	cimg3.setTo(255);
	img.copyTo(cimg3(Range::all(), Range(0, img.cols)));
	img2.copyTo(cimg3(Range::all(), Range(img2.cols, img2.cols * 2)));

	//set roi
	Mat roi(img, r);
	//invert color
	bitwise_not(roi, roi);


	namedWindow("img2", 0); //make window
	imshow("img2", cimg); //show
	namedWindow("img3", 0); //make window
	imshow("img3", cimg2); //show
	namedWindow("img4", 0); //make window
	imshow("img4", cimg3); //show
	namedWindow("img5", 0); //make window
	imshow("img5", img5); //show
	namedWindow("img", 0); //make window
	imshow("img", img); //show

	waitKey(0);


}