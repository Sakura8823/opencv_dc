#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; using namespace cv;

int readImg()
{
	//����ͼ�񣬲���֮תΪ��ͨ��ͼ�� 
	Mat im = imread("1.png", 0);
	if (im.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}
	//��ʾͼƬ
	namedWindow("1");		
	imshow("1", im);
	//�ȴ�����
	waitKey(2000);


	Mat result;
	//����Canny�����������������result 
	Canny(im, result, 50, 150);
	//��ʾͼƬ
	namedWindow("2");
	imshow("2", result);
	// �ȴ�����󴰿��Զ��ر�    
	waitKey(2000);
	//д��ͼƬ
	imwrite("2.png", result);
	return 0;
}
