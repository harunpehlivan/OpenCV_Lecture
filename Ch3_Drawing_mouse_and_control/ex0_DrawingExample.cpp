//http://study.marearts.com/2016/07/opencv-drawing-example-line-circle.html

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

	
	///////////////////////////////////////////////////
	//line example
	cv::Point pt(300, 300);
	line(img, Point(10, 10), pt, CV_RGB(255, 0, 0), 2);
	line(img, Point(300, 10), Point(30, 300), Scalar(255, 0, 0), 2);
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//Circle example
	circle(img, Point(250, 250), 100, CV_RGB(0, 255, 0), 3);
	cv::Point center(400, 400);
	circle(img, center, 300, Scalar(255, 255, 0), 10);
	circle(img, Point(40, 40), 10, Scalar(255, 0, 0), -1);
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	//rectangle example
	rectangle(img, Rect(10, 10, 200, 200), CV_RGB(255, 0, 0), 2);
	rectangle(img, Rect(Point(40, 40), Point(400, 400)), Scalar(255, 0, 0), 10);
	///////////////////////////////////////////////////


	/////////////////////////////////////////////////// 
	//ellipse example 1
	ellipse(img, Point(100, 100), Size(100, 50), 0, 0, 360, CV_RGB(255, 0, 0));
	ellipse(img, Point(100, 100), Size(100, 50), 30, 0, 360, CV_RGB(0, 255, 0));
	ellipse(img, Point(100, 100), Size(100, 50), 60, 0, 360, CV_RGB(0, 0, 255));

	ellipse(img, Point(300, 300), Size(100, 50), 0, 0, 180, CV_RGB(255, 0, 0));
	ellipse(img, Point(300, 300), Size(100, 50), 30, 0, 270, CV_RGB(0, 255, 0));
	ellipse(img, Point(300, 300), Size(100, 50), 60, 0, 360, CV_RGB(0, 0, 255));
	///////////////////////////////////////////////////

	/////////////////////////////////////////////////// 
	//ellipse example 2
	RotatedRect rRect = RotatedRect(Point2f(300, 300), Size2f(300, 100), 30);
	ellipse(img, rRect, CV_RGB(255, 0, 0));

	//draw rect and inside rect in RotatedRect
	Point2f vertices[4];
	rRect.points(vertices);
	for (int i = 0; i < 4; i++)
		line(img, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));

	Rect brect = rRect.boundingRect();
	rectangle(img, brect, Scalar(255, 0, 0));
	///////////////////////////////////////////////////
	

	/*
	///////////////////////////////////////////////////
	//polylines example 1 
	vector< Point> contour;
	contour.push_back(Point(50, 50));
	contour.push_back(Point(300, 50));
	contour.push_back(Point(350, 200));
	contour.push_back(Point(300, 150));
	contour.push_back(Point(150, 350));
	contour.push_back(Point(100, 100));

	const Point *pts = (const cv::Point*) Mat(contour).data;
	int npts = Mat(contour).rows;

	std::cout << "Number of polygon vertices: " << npts << std::endl;
	// draw the polygon 
	polylines(img, &pts, &npts, 1, false, Scalar(0, 255, 0));

	//polylines example 2 
	contour.clear();
	contour.push_back(Point(400, 400));
	contour.push_back(Point(250, 250));
	contour.push_back(Point(50, 300));

	pts = (const cv::Point*) Mat(contour).data;
	npts = Mat(contour).rows;
	polylines(img, &pts, &npts, 1, true, Scalar(255, 0, 0));
	///////////////////////////////////////////////////
	*/


	/*
	///////////////////////////////////////////////////
	//fillConvexPoly example 1 
	cv::Point ptss[4];
	ptss[0] = cv::Point(100, 100);
	ptss[1] = cv::Point(150, 200);
	ptss[2] = cv::Point(300, 300);
	ptss[3] = cv::Point(400, 100);

	cv::fillConvexPoly(img, ptss, 4, cv::Scalar(0, 0, 200));
	///////////////////////////////////////////////////
	*/

	/*
	///////////////////////////////////////////////////
	//textout example 1
	char TestStr[100];
	sprintf_s(TestStr, "total time : %lf sec", 0.001);
	putText(img, TestStr, Point(10, 250), CV_FONT_NORMAL, 1, Scalar(0, 0, 0), 1, 1); //OutImg is Mat class;
	///////////////////////////////////////////////////
	*/

	
	imshow("show0", img);
	waitKey(0);

	return 0;
}