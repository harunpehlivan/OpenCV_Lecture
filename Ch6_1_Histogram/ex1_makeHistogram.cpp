
#include "opencv2/opencv.hpp"
#include "opencv2\highgui.hpp"
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
	//image load
	Mat img = imread("./goonies.jpg"); // "./goonies.jpg"); //".\\lenna.jpg"

									   //rgb to gray
	Mat gray_img;
	cvtColor(img, gray_img, CV_RGB2GRAY);
	int width = img.cols;
	int height = img.rows;
	const int bufferSize = 256;

	//histogram buffer

	unsigned int Histogram_buffer[bufferSize];
	memset(Histogram_buffer, 0, sizeof(unsigned int) * bufferSize);

	//voting
	int maxValue = 0;
	for (int i = 0; i < gray_img.rows; ++i)
	{
		for (int j = 0; j < gray_img.cols; ++j)
		{
			//Vec3b means 'uchar 3ch'
			unsigned char v = gray_img.at<unsigned char>(i, j);
			Histogram_buffer[v] ++;

			if (maxValue < Histogram_buffer[v])
				maxValue = Histogram_buffer[v];
		}
	}

	//make histogram mat
	Mat histo = Mat::zeros(Size(bufferSize, maxValue + 1), CV_8U);

	//rect
	for (int i = 0; i< bufferSize; ++i)
	{
		for (int j = 0; j < Histogram_buffer[i]; ++j)
		{
			histo.at< unsigned char >(maxValue - j, i) = 255;
		}
	}

	//line
	for (int i = 1; i< bufferSize; ++i)
	{
		int y1 = maxValue - Histogram_buffer[i - 1];
		int x1 = i - 1;
		int y2 = maxValue - Histogram_buffer[i];
		int x2 = i;
		line(histo, Point(x1, y1), Point(x2, y2), CV_RGB(255, 255, 255), 1);
	}

	namedWindow("histo", 0);
	imshow("histo", histo);

	imshow("img", img);
	imshow("gray img", gray_img);
	waitKey(0);

	return 0;
}