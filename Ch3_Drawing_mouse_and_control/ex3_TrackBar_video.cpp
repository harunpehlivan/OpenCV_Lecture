//http://study.marearts.com/2016/07/opencv-30-trackbar-simple-example-in.html


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

int g_slider; //slider pos value
int g_slider_max; //slider max value

void on_trackbar(int, void*)
{
	printf("%d\n", g_slider);
}


int main()
{
	Mat edges;
	VideoCapture cap = VideoCapture(0);

	if (!cap.isOpened()) return -1;
	//set
	g_slider = 0;
	g_slider_max = 255;
	namedWindow("edges", 1);

	//make trackbar call back
	createTrackbar("TrackbarName", "edges", &g_slider, g_slider_max, on_trackbar);

	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, CV_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, g_slider, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}
