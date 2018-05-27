//http://study.marearts.com/2017/01/opencv-add-subtract-multiply-divide.html

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


//TBB need for using this
class Parallel_process : public cv::ParallelLoopBody
{

private:
	cv::Mat& inImg;
	cv::Mat& outImg;
	int widthStep;
	//int m_stride;
	cv::Scalar scalar; //B,G,R

public:
	Parallel_process(cv::Mat& inputImgage, Mat& outImage, Scalar& inScalar)
		: inImg(inputImgage), outImg(outImage), scalar(inScalar) {

		widthStep = inputImgage.size().width * 3;
		//m_stride = inputImgage.size().width * 2;


	}

	virtual void operator()(const cv::Range& range) const
	{
		//thread
		for (int i = range.start; i < range.end; i++)
		{

			int s1 = i*widthStep;

			for (int iw = 0; iw< inImg.size().width; iw++)
			{
				int s2 = iw * 3;
				int mc = s1 + s2;

				unsigned char B1 = (unsigned char)(inImg.data[mc + 0]);
				unsigned char G1 = (unsigned char)(inImg.data[mc + 1]);
				unsigned char R1 = (unsigned char)(inImg.data[mc + 2]);

				int B2 = B1 + scalar[0];
				int G2 = G1 + scalar[1];
				int R2 = R1 + scalar[2];

				if (B2 > 255)
					B2 = 255;
				if (G2 > 255)
					G2 = 255;
				if (R2 > 255)
					R2 = 255;

				if (B2 < 0)
					B2 = 0;
				if (G2 < 0)
					G2 = 0;
				if (R2 < 0)
					R2 = 0;


				outImg.data[mc + 0] = B2;
				outImg.data[mc + 1] = G2;
				outImg.data[mc + 2] = R2;


			}
		}
	}
};





int main(int, char)
{

	Mat img = imread("scret.jpg");
	Mat img_add;
	Mat img_absdiff;
	Mat img_subtract;
	Mat img_mul;
	Mat img_div;
	Mat img_parallel;

	unsigned long AAtime = 0, BBtime = 0; //check processing time   


										  //cpu add
	AAtime = getTickCount();
	add(img, Scalar(200, 200, 200), img_add); //Value is between 0 and 255
											  //img_add = img + Scalar(200, 200, 200);
	BBtime = getTickCount();
	printf("add cpu %.2lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   


																			//cpu subtraction
	AAtime = getTickCount();
	subtract(img, Scalar(200, 200, 200), img_subtract); //Value is between 0 and 255
														//img_subtract = img - Scalar(200, 200, 200)
	BBtime = getTickCount();
	printf("subtract %.2lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   


																			 //cpu absdiff
	AAtime = getTickCount();
	absdiff(img, Scalar(200, 200, 200), img_absdiff); //Value is between 0 and 255
	BBtime = getTickCount();
	printf("absdiff %.5lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   


																			//cpu *, /
	multiply(img, 20, img_mul);
	divide(img, 20, img_div);
	//img_mul = img * 20; 
	//img_div = img / 20; 




	cuda::GpuMat gimg;
	cuda::GpuMat gout1, gout2;

	gimg.upload(img);
	//gpu add
	AAtime = getTickCount();
	cuda::absdiff(gimg, Scalar(200, 200, 200), gout1);
	BBtime = getTickCount();
	printf("gpu absdiff %.2lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   

	AAtime = getTickCount();
	cuda::add(gimg, Scalar(-200, -200, -200), gout2);
	BBtime = getTickCount();
	printf("gpu add %.5lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   



																			//tbb
	AAtime = getTickCount();
	img_parallel = Mat(img.size(), img.type());
	cv::parallel_for_(cv::Range(0, img.rows), Parallel_process(img, img_parallel, Scalar(-200, -200, -200)));
	BBtime = getTickCount();
	printf("parallel %.2lf sec \n", (BBtime - AAtime) / getTickFrequency()); //check processing time   


	imshow("img", img);
	imshow("img_add", img_add);
	imshow("img_absdiff", img_absdiff);
	imshow("img_subtract", img_subtract);
	imshow("img_mul", img_mul);
	imshow("img_div", img_div);
	imshow("img_parallel", img_parallel);


	waitKey(0);


	return 0;
}
