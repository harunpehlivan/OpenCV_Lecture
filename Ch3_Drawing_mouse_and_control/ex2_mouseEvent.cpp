//http://study.marearts.com/2016/12/opencv-mouse-event-example-code.html

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


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{

	if (event == EVENT_LBUTTONDOWN)
	{
		printf("lLBUTTONDOWN down %d, %d \n", x, y);

		circle((*(Mat*)userdata), Point(x, y), 2, CV_RGB(255, 0, 0), 3);
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		printf("RBUTTONDOWN down %d, %d \n", x, y);
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		printf("MBUTTONDOWN down %d, %d \n", x, y);
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		printf("move %d, %d \n", x, y);
	}

	//imshow("img", (*(Mat*)userdata)); //show
}


int main(int, char)
{
	namedWindow("img", 0);
	Mat img = imread("gh.jpg");
	setMouseCallback("img", CallBackFunc, &img);

	while (1)
	{
		imshow("img", img); //show
		if (waitKey(10) > 0)
			break;
	}

	destroyAllWindows();

	return 0;
}
