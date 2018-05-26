//http://study.marearts.com/2017/01/opencv-trackbar-exmaple-source-code.html

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
	if (g_slider % 2 == 0)
		g_slider = g_slider + 1;

	printf("%d\n", g_slider);
}

int main()
{

	// Read image from file 
	Mat img = imread("anapji.jpg");
	Mat img2;

	//set
	g_slider = 0;
	g_slider_max = 21;

	//window name
	namedWindow("My Window", 1);

	//make trackbar call back
	createTrackbar("TrackbarName", "My Window", &g_slider, g_slider_max, on_trackbar);

	//show the image
	while (1)
	{
		Sobel(img, img2, CV_8U, 1, 0, g_slider);
		imshow("My Window", img2);
		// Wait until user press some key
		int r = waitKey(10);
		if (r > 0)
			break;
	}

	return 0;
}
