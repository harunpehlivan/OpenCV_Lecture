
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

int lookupEx();
int applyColorMapEx();
int LUTexample();

int main(int, char)
{
	//example 1
	//lookupEx();

	//example 2
	//applyColorMapEx();

	//example 3
	LUTexample();

}



//http://study.marearts.com/2018/05/opencv-lutlook-up-table-example-code.html
int LUTexample()
{

	Mat img = imread("AbyssCGI2.jpg");

	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	int factor = 256 / 5;
	for (int i = 0; i < 256; ++i)
	{
		p[i] = factor * (i / factor);
		printf("[%d] = %d \n", i, p[i]);
	}



	Mat reduced;
	LUT(img, lookUpTable, reduced);

	namedWindow("img", 0);
	imshow("img", img);
	namedWindow("reduced", 0);
	imshow("reduced", reduced);


	/*
	//////////////////// gray & color test!!
	Mat img2(1, 1, CV_8UC3);
	img2.setTo(Scalar(0, 128, 255));
	Mat im_color3;
	LUT(img2, lookUpTable, im_color3);
	cout << im_color3 << endl;
	//namedWindow("im_color3", 0);
	//imshow("im_color3", im_color3);

	//different result with color!!
	Mat img2_gray;
	cvtColor(img2, img2_gray, CV_BGR2GRAY);
	Mat im_color4;
	LUT(img2_gray, lookUpTable, im_color4);
	cout << im_color4 << endl;
	//namedWindow("im_color4", 0);
	//imshow("im_color4", im_color4);
	//////////////////////*/


	waitKey(0);


	return 0;

}

//http://study.marearts.com/2018/05/example-for-applycolormap-usage.html
int applyColorMapEx()
{
	
	//image show.
	Mat img = imread("AbyssCGI.jpg");

	namedWindow("img", 0);
	imshow("img", img);

	/////////////////applyColorMap
	//basic usage
	Mat im_color;
	applyColorMap(img, im_color, COLORMAP_JET);//COLORMAP_AUTUMN);
	namedWindow("im_color", 0);
	imshow("im_color", im_color);


	//what about gray?
	Mat img_gray;
	cvtColor(img, img_gray, CV_RGB2GRAY);
	Mat im_color2;
	applyColorMap(img_gray, im_color2, COLORMAP_AUTUMN);
	namedWindow("im_color2", 0);
	imshow("im_color2", im_color2);
	/////////////////////////////////////////
	

	/*
	//////////////////// gray & color test!!
	Mat img2(100, 100, CV_8UC3);
	img2.setTo(Scalar(0, 128, 255));
	Mat im_color3;
	applyColorMap(img2, im_color3, COLORMAP_JET);
	//cout << im_color3 << endl;
	namedWindow("im_color3", 0);
	imshow("im_color3", im_color3);

	//same with resutl of color
	Mat img2_gray;
	cvtColor(img2, img2_gray, CV_BGR2GRAY);
	Mat im_color4;
	applyColorMap(img2_gray, im_color4, COLORMAP_JET);
	//cout << im_color4 << endl;
	namedWindow("im_color4", 0);
	imshow("im_color4", im_color4);
	//////////////////////

	*/

	waitKey(0);

	return 0;
}


//http://study.marearts.com/2018/05/loop-lut-processing-time-compare.html
int lookupEx()
{
	unsigned long AAtime = 0, BBtime = 0;
	unsigned char O[1000][1000] = { 1, 2, };


	//very slow;
	AAtime = getTickCount();
	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 1000; ++j)
		{
			int t = O[i][j] * 1.14;
			t = (t > 255) ? 255 : t;
			O[i][j] = t;
		}
	}
	BBtime = getTickCount();
	printf("just loop %.5lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check speed

	//fast
	unsigned char LUT[256];
	AAtime = getTickCount();
	for (int i = 0; i < 256; ++i)
	{
		int t = i * 1.14;
		t = (t > 255) ? 255 : t;
		LUT[i] = t;
	}

	for (int i = 0; i < 1000; ++i)
	{
		for (int j = 0; j < 1000; ++j)
		{
			O[i][j] = LUT[O[i][j]];
		}
	}
	BBtime = getTickCount();
	printf("using lut %.5lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check speed

	return 0;
}



