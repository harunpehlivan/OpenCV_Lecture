//http://study.marearts.com/2018/05/opencv-integral-test-source-code.html

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
	
	Mat img = Mat(10, 10, CV_8UC1);
	randu(img, 0, 10);

	cout << "origin" << endl << img << endl;

	//int x=3, y=4, w=4, h=4;
	int x = 1, y = 1, w = 2, h = 2;

	int sum = 0;
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			sum = sum + img.at<unsigned char>((y + j), (x + i));
		}
	}

	printf("for loop : sum = %d \n", sum);


	///////////////////////////////////////////////////////////////////////

	Mat integralImg;
	integral(img, integralImg, CV_64F);

	cout << endl << "integral" << endl << integralImg << endl;

	double p1 = integralImg.at<double>((y), (x));
	double p2 = integralImg.at<double>((y), (x + w));
	double p3 = integralImg.at<double>((y + h), (x));
	double p4 = integralImg.at<double>((y + h), (x + w));

	printf("\n p1:%lf, p2:%lf, p3:%lf, p4:%lf\n", p1, p2, p3, p4);
	printf("integral : sum = %lf \n", (p1 + p4) - (p2 + p3));

	//////////////////////////////////////////////////////////////////////////
	

}


