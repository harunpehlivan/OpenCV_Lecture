//http://study.marearts.com/2017/12/calchist-for-rgb-image-opencv-histogram.html
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



int main()
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Mat imgA;
	imgA = imread(".\\goonies.jpg");
	imshow("img1", imgA);


	//variables preparing
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int hbins = 30; //histogram x axis size, that is histSize,
					//ex) 2 -> 0~128, 129~256, ex)16 -> 0 ~ 15, 16 ~ 31...,
	int channels[] = { 0 }; //index of channel
	int histSize[] = { hbins };
	float hranges[] = { 0, 180 }; //hue is 0~180
	const float* ranges[] = { hranges };

	Mat patch_HSV;
	MatND HistA, HistB;

	//cal histogram & normalization
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cvtColor(imgA, patch_HSV, CV_BGR2HSV);
	//Hue range is[0, 179], Saturation range is[0, 255] and Value range is[0, 255]

	calcHist(&patch_HSV, 1, channels, Mat(), //MaskForHisto, // // do use mask
		HistA, 1, histSize, ranges,
		true, // the histogram is uniform
		false);
	normalize(HistA, HistA, 0, 255, CV_MINMAX);

	//Mat for drawing
	Mat histimg = Mat::zeros(200, 320, CV_8UC3);
	int binW = histimg.cols / hbins;

	Mat buf(1, hbins, CV_8UC3);
	//Set RGB color
	for (int i = 0; i < hbins; i++)
		buf.at< Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hbins), 255, 255);
	cvtColor(buf, buf, CV_HSV2BGR);

	//drawing routine
	for (int i = 0; i < hbins; i++)
	{
		//int val = saturate_cast<int>(HistA.at< float>(i)*histimg.rows / 255);
		int val = HistA.at< float>(i) * histimg.rows / 255;
		rectangle(histimg, Point(i*binW, histimg.rows),
			Point((i + 1)*binW, histimg.rows - val),
			Scalar(buf.at< Vec3b>(i)), -1, 8);

		int r, g, b;
		b = buf.at< Vec3b>(i)[0];
		g = buf.at< Vec3b>(i)[1];
		r = buf.at< Vec3b>(i)[2];
		//show bin and RGB value
		printf("[%d] r=%d, g=%d, b=%d , bins = %d \n", i, r, g, b, val);
	}
	imshow("Histogram", histimg);
	waitKey(0);

	return 0;
}