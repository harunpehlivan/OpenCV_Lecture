//http://study.marearts.com/2017/02/cvlecture-example-code-operation.html

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

	Mat img = imread("scret.jpg");
	Mat img2 = imread("scret2.jpg");


	Mat img_add;
	Mat img_wadd;
	Mat img_subtract;
	Mat img_mul;
	Mat img_div;

	//If the sizes of the two images are different, an error occurs.
	resize(img2, img2, Size(img.size().width, img.size().height));



	add(img, img2, img_add);
	//img_add = img + img2;
	//cuda::add(img_cuda, img2_cuda, img_add_cuda);

	subtract(img, img2, img_subtract);
	//img_subtract = img - img2;
	//cuda::subtract(img_cuda, img2_cuda, img_subtract_cuda);

	multiply(img, img2, img_mul);
	//img_mul = img * img2;
	//cuda::multiply(img_cuda, img2_cuda, img_mul_cuda);

	divide(img, img2, img_div);
	//img_div = img / img2;
	//cuda::divide(img_cuda, img2_cuda, img_div_cuda);



	//
	double alpha = 0.5;
	double beta;
	double input;

	cout << "Enter a real number between 0 and 1 : ";
	cin >> input;


	if (input < 0.0)
		input = 0;
	else if (input > 1.0)
		input = 1.0;

	alpha = input;

	beta = (1.0 - alpha);
	addWeighted(img, alpha, img2, beta, 0.0, img_wadd);

	
	imshow("img", img);
	imshow("img2", img2);
	imshow("img_add", img_add);
	imshow("img_subtract", img_subtract);
	imshow("img_mul", img_mul);
	imshow("img_div", img_div);
	imshow("img_wadd", img_wadd);
	

	for (float w = 0; w < 1; w += 0.05)
	{
		alpha = w;
		beta = (1.0 - alpha);

		addWeighted(img, alpha, img2, beta, 0.0, img_wadd);
		imshow("img_wadd", img_wadd);

		waitKey(200);
	}

	waitKey(0);

	return 0;
}