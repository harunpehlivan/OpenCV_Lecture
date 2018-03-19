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
	Mat imgA, grayImg;
	imgA = imread(".\\goonies.jpg");
	imshow("img1", imgA);
	cvtColor(imgA, grayImg, CV_BGR2GRAY);

	//variables preparing
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int hbins = 255; //histogram x axis size, that is histSize, 
					 //ex) 2 -> 0~128, 129~256, ex)16 -> 0 ~ 15, 16 ~ 31..., 
	int channels[] = { 0 }; //index of channel
	int histSize[] = { hbins };
	float hranges[] = { 0, 255 };
	const float* ranges[] = { hranges };

	MatND Hist;

	vector<Mat> bgr_planes;
	split(imgA, bgr_planes);

	//cal histogram & normalization
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	calcHist(&grayImg, 1, channels, Mat(), //MaskForHisto, // // do use mask
		Hist, 1, histSize, ranges,
		true, // the histogram is uniform
		false);
	normalize(Hist, Hist, 0, 255, CV_MINMAX);

	// Draw the histograms for B, G and R
	int hist_w = 500; int hist_h = 255;
	int ratio = cvRound((double)hist_w / hbins);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	int x1, y1;
	int x2, y2;
	for (int i = 1; i < hbins; i++)
	{
		x1 = ratio*(i - 1);
		y1 = hist_h - cvRound(Hist.at<float>(i - 1));

		x2 = ratio*(i);
		y2 = hist_h - cvRound(Hist.at<float>(i));

		line(histImage, Point(x1, y1), Point(x2, y2),
			Scalar(255, 255, 255), 2, 8, 0);
	}

	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);
	waitKey(0);

	return 0;
}