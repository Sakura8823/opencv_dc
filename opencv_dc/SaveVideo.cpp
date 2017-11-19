#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int saveVideo()
{
	VideoCapture capture("2.mp4");
	int rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;
	VideoWriter writer("VideoTest.avi", VideoWriter::fourcc('M', 'P', '4', '2'), rate, Size(300, 200),0);
	Mat frame;
	Mat background;
	Mat result;
	Mat mv[3];
	capture.read(background);
	resize(background, background, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
	cvtColor(background, background, COLOR_BGR2GRAY);//תΪ�Ҷ�ͼ
	
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	long frameNumber = 1.0;
	while (capture.read(frame))
	{
		resize(frame, frame, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(frame, frame, COLOR_BGR2GRAY);//תΪ�Ҷ�ͼ

		absdiff(background, frame, result);//�ͱ�������,���result

			//����ͼ�񣬶�ֵ������ֵΪ50
		for (int i = 0; i < result.rows; i++) {
			for (int j = 0; j < result.cols; j++) {
				if (result.at<uchar>(i, j) < 50) {
					result.at<uchar>(i, j) = 0;
				}
				else {
					result.at<uchar>(i, j) = 255;
				}
			}
		}

		result.convertTo(result, CV_8U);
		writer << result;

		frameNumber++;
		cout << totalFrameNumber - frameNumber << endl;
	}
	capture.release();
	return 0;
}
