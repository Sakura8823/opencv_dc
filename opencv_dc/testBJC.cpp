#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int testBJC()
{
	Mat img = imread("1.png");
	Mat test1 = imread("test1.png");
	Mat background;
	Mat temp;
	Mat result;
	resize(img, img, Size(300, 300));//resizeΪ300*300��ͼ��
	cvtColor(img, img, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
	imshow("grey1.png", img);

	//����ͼ�񣬶�ֵ������ֵΪ50
	for (int i = 0; i < img.rows; i++){
		for (int j = 0; j < img.cols; j++){
			if(img.at<uchar>(i, j)<50){
				img.at<uchar>(i, j) = 0;
			}
			else {
				img.at<uchar>(i, j) = 255;
			}
			
		}
	}
	imshow("gray_result", img);

	VideoCapture capture("7.mp4");
	capture.read(background);
	absdiff(background,test1,result);
	imshow("result",result);
	//Mat diff;
	//diff = absdiff(test1,ob��);
	//imshow("diff", diff);
	waitKey(0);
	return 0;
}