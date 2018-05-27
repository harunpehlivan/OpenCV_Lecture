//http://study.marearts.com/2017/03/opencv-lecture-4-7-source-code-noise.html

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
	//image show./.
	Mat img = imread("jodie.jpg");
	namedWindow("img", 0);
	imshow("img", img);

	//gaussian generation example
	//test
	Mat Gnoise = Mat(5, 5, CV_8SC1);
	randn(Gnoise, 5, 10); //mean, variance
	cout << Gnoise << endl;
	//
	Mat Unoise = Mat(5, 5, CV_8SC1);
	randu(Unoise, 5, 10); //low, high
	cout << Unoise << endl;


	//noise adapt
	Mat Gaussian_noise = Mat(img.size(), img.type());
	double mean = 0;
	double std = 64;
	randn(Gaussian_noise, mean, std); //mean, std
	Mat colorNoise = img + Gaussian_noise;

	//another noise
	int rsize = 1000;
	//initialize random seed: 
	srand(time(NULL)); //#include <time.h>
	Mat imgD = img.clone();
	for (int i = 0; i < rsize; ++i)
	{
		//but x,y value will be duplicate
		int x = rand() % img.cols; //0 ~ img.cols-1
		int y = rand() % img.rows; //0 ~ img.rows-1

		//cout << x << " " << y << " / " << img.cols << " " << img.rows << endl;

		imgD.at< Vec3b >(y, x)[0] = 255;
		imgD.at< Vec3b >(y, x)[1] = 255;
		imgD.at< Vec3b >(y, x)[2] = 255;
	}

	namedWindow("img", 0);
	imshow("img", img);

	namedWindow("colorNoise", 0);
	imshow("colorNoise", colorNoise);

	namedWindow("Gaussian_noise", 0);
	imshow("Gaussian_noise", Gaussian_noise);

	namedWindow("imgD", 0);
	imshow("imgD", imgD);

	//normalize(result, result, 0.0, 1.0, CV_MINMAX, CV_64F);
	//minMaxIdx(plan[i],&minIm,&maxIm);

	Mat noiseGray = img.clone();
	cvtColor(noiseGray, noiseGray, CV_RGB2GRAY);
	Mat Gaussian_noise2 = Mat(noiseGray.rows, noiseGray.cols, CV_8UC1);
	double mean2 = 0;
	double std2 = 20;
	randn(Gaussian_noise2, mean2, std2); //mean, std
	double minV, maxV;
	minMaxIdx(Gaussian_noise2, &minV, &maxV);
	cout << "min : " << minV << " max :" << maxV << endl;
	threshold(Gaussian_noise2, Gaussian_noise2, (minV + maxV) / 2, 255, CV_THRESH_BINARY);

	noiseGray = noiseGray + Gaussian_noise2;

	namedWindow("Gaussian_noise2", 0);
	imshow("Gaussian_noise2", Gaussian_noise2);

	namedWindow("noiseGray", 0);
	imshow("noiseGray", noiseGray);

	waitKey(0);

	return 0;

}