#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int testBJC()
{
	Mat test1 = imread("test1.png");
	Mat background;
	Mat temp;
	Mat result;
	
	int FrameCount = 0;
	VideoCapture capture("2.mp4");

	if (!capture.isOpened())
	{
		cout << "��ȡ��Ƶ����" << endl;
		return -1;
	}
	else
	{
		capture.read(background);
		resize(background, background, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(background, background, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
	}
	while (capture.read(temp))
	{
		int PixelCount = 0;
		FrameCount++;
		resize(temp, temp, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(temp, temp, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
		absdiff(background, temp, result);//�ͱ�������,���result
		addWeighted(background, 0.95, temp, 1-0.95, 0, background);

		//����ͼ�񣬶�ֵ������ֵΪ50
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				if (result.at<uchar>(i, j)<50) {
					result.at<uchar>(i, j) = 0;
				}
				else {
					PixelCount++;
					result.at<uchar>(i, j) = 255;
				}
			}
		}
		cout <<FrameCount<< "��ǰ������" << PixelCount << "��ǰ������"<<endl;
		imshow("��ǰ��Ƶ",result);
		imshow("����ͼƬ",background);
		waitKey(50);
	}
	waitKey(0);

	return 0;
}