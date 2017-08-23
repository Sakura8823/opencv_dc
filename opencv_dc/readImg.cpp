#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; using namespace cv;

int readImg()
{
	//����ͼ�񣬲���֮תΪ��ͨ��ͼ�� 
	Mat im = imread("1.png");
	Mat im1;
	if (im.empty())
	{
		cout << "Can not load image." << endl;
		return -1;
	}
	//��ʾͼƬ
	namedWindow("1");		
	imshow("1", im);
	cvtColor(im, im1, CV_BGR2GRAY);
	namedWindow("2");
	imshow("2", im1);
	//������ֵ
	threshold(im1, im1, 255 * (0.5), 255, THRESH_BINARY);
	// ��̬ѧ����
	// ����ѽṹԪ������ΪMat()������Ĭ�ϵ�3*3�ľ��νṹԪ��
	Mat eroded;
    erode(im1, eroded, Mat());
	Mat dilated;
    dilate(im1, dilated, Mat());
	// ����ṹԪ��
	Mat closed, opened;
	Mat se(5, 5, CV_8U, Scalar(1));
	morphologyEx(im1, closed, MORPH_CLOSE, se);
	morphologyEx(im1, opened, MORPH_OPEN, se);
	namedWindow("xintaixue");
	imshow("xintaixue", im1);
	//�ȴ�����
	waitKey(2000);

	Mat result;
	//����Canny�����������������result 
	Canny(im1, result, 50, 150);
	//��ʾͼƬ
	namedWindow("3");
	imshow("3", result);
	// �ȴ�����󴰿��Զ��ر�    
	waitKey(5000);
	//д��ͼƬ
	imwrite("2.png", result);
	return 0;
}
