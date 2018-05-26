//http://study.marearts.com/2013/09/opencv-video-capture-using-videocapture.html
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
	VideoCapture stream1(0);   //0 is the id of video device.0 if you have only one camera

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera";
		return;
	}

	namedWindow("Processing");
	namedWindow("Origin");

	//unconditional loop
	while (true) {
		Mat cameraFrame;
		stream1.read(cameraFrame); //get one frame form video
		imshow("Origin", cameraFrame);

		Sobel(cameraFrame, cameraFrame, CV_8U, 1, 0); //sobel processing
		imshow("Processing", cameraFrame);

		if (waitKey(30) >= 0)
			break;
	}

	destroyAllWindows();


}