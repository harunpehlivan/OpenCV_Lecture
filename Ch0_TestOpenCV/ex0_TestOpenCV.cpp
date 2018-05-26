//http://study.marearts.com/2013/09/opencv-video-file-load-and-display.html?showComment=1501765724458
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

//gray histogram without opencv fuction
int main(int, char)
{
	//file load
	VideoCapture capture("rhinos.avi");
	Mat frame;

	//check
	if (!capture.isOpened())
	{
		printf("AVI file can not open.\n");
		return 0;
	}

	//create window
	namedWindow("w");

	while (1)
	{
		//grab frame from file & throw to Mat
		capture >> frame;
		if (frame.empty()) //Is video end?
			break;

		//processing example
		Sobel(frame, frame, frame.depth(), 1, 0);
		////////////////////

		//display and delay
		imshow("w", frame);
		if (waitKey(10) > 0)
			break;
	}

	return 0;
}