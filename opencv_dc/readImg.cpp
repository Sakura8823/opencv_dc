#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; 
using namespace cv;

int readImg()
{
	//����ͼ�񣬲���֮תΪ��ͨ��ͼ�� 
	Mat im1 = imread("1.png", 0);
	if (im1.empty())
	{
		cout << "Can not load image." << endl;        
			return -1;
	}
	namedWindow("1");		// �ڴ�������ʾ��Ϸԭ��    
	imshow("1", im1);			// �ȴ�6000 ms�󴰿��Զ��ر�    
	waitKey(2000);
	return 0;
}