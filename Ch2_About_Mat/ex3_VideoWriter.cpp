//http://study.marearts.com/2013/09/opencv-video-writer-example-source-code.html

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

int main()
{
	VideoCapture capture("rhinos.avi");
	Mat frame;

	//Set properties
	int askFileTypeBox = 0; //-1 is show box of codec
	int Color = 1;
	Size S = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));

	//make output video file
	VideoWriter outVideo;
	//save video file by origin paramers
	outVideo.open(".\\outVideo.avi", askFileTypeBox, capture.get(CV_CAP_PROP_FPS), S, Color);

	double fps = capture.get(CV_CAP_PROP_FPS);
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
		//Sobel(frame, frame, frame.depth(), 1, 0);

		////////////////////
		//outVideo.write(frame);
		outVideo << frame;
		//display and delay
		imshow("w", frame);

		//delay by origin fps
		if (waitKey((1 / fps) * 1000) > 0)
			break;

	}

	return 0;
}