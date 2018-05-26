//http://study.marearts.com/2016/12/gpu-mat-cpu-mat-example-code-1.html

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/cudaarithm.hpp"

#include <iostream>


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

#pragma comment(lib, "opencv_cudaarithm331d.lib")  
#endif        


using namespace std;
using namespace cv;

int main()
{
	cuda::GpuMat gpuImg;
	Mat img = imread("ss.jpg");

	
	gpuImg.upload(img); //upload
	vector< cuda::GpuMat> rgbGpuMat(3);
	cuda::split(gpuImg, rgbGpuMat); //cuda processing

	Mat r, g, b;
	rgbGpuMat[0].download(b); //download
	rgbGpuMat[1].download(g);
	rgbGpuMat[2].download(r);


	namedWindow("r", 0); //make window
	imshow("r", r); //show
	namedWindow("g", 0); //make window
	imshow("g", g); //show
	namedWindow("b", 0); //make window
	imshow("b", b); //show
	waitKey(0);
	

	return 0;
}