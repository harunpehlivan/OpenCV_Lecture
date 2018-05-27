//http://study.marearts.com/2018/05/video-frame-difference-frame.html

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

	Mat frame;
	Mat old_frame;
	Mat sub_frame;
	//Mat absdiff_frame;
	VideoCapture stream1(0);

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera 1";
		return 0;
	}

	while (1)
	{
		if (!(stream1.read(frame))) //get one frame form video   
			break;

		if (old_frame.empty())
		{
			old_frame = frame.clone();
			continue;
		}
		

		subtract(old_frame, frame, sub_frame);
		//absdiff(old_frame, frame, absdiff_frame);

		imshow("frame", frame);
		imshow("sub_frame", sub_frame);
		//imshow("absdiff_frame", absdiff_frame);

		//subtraction every frame
		old_frame = frame.clone(); 
		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}