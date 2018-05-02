
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


//hsv histogram 2d
int main()
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	Mat srcA = Mat(500, 500, CV_8UC1);
	randn(srcA, 128, 20); //mean, variance

	Mat srcB = Mat(500, 500, CV_8UC1);
	randn(srcB, 128, 50); //mean, variance

	int aBin = 50, bBin = 50;
	int histSize[] = { aBin, bBin };

	float aranges[] = { 0, 256 };
	float branges[] = { 0, 256 };
	const float* ranges[] = { aranges, branges };

	MatND hist;
	int channels[] = { 0, 1 };

	Mat mat2ch[2];
	mat2ch[0] = srcA;
	mat2ch[1] = srcB;

	calcHist(mat2ch, 2, channels, Mat(), // do not use mask
		hist, 2, histSize, ranges,
		true, // the histogram is uniform
		false);
	double maxVal = 0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);

	int scale = 10;
	Mat histImg = Mat::zeros(aBin*scale, bBin * scale, CV_8UC3);

	for (int h = 0; h < aBin; h++)
	{
		for (int s = 0; s < bBin; s++)
		{
			float binVal = hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(histImg, Point(h*scale, s*scale),
				Point((h + 1)*scale - 1, (s + 1)*scale - 1),
				Scalar::all(intensity),
				CV_FILLED);
		}
	}

	namedWindow("SourceA", 1);
	imshow("SourceA", srcA);
	namedWindow("SourceB", 1);
	imshow("SourceB", srcB);


	namedWindow("AB Histogram", 1);
	imshow("AB Histogram", histImg);
	waitKey();

	return 0;



}
