//http://study.marearts.com
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
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

void main()
{
	Mat m = Mat::ones(3, 3, CV_64F);
	m = m * 3;
	cout << m << endl;

	double dm[3][3] = { { 1, 2, 1 },{ 0, 1, 1 },{ 1, 0, 0 } };
	Mat m2 = Mat(3, 3, CV_64F, dm);
	cout << m2 << endl;
	cout << m + m2 << endl;
	cout << m - m2 << endl;
	cout << m*m2 << endl;
	cout << m / m2 << endl;
	cout << m2.inv() << endl;
	cout << m2.t() << endl;


}