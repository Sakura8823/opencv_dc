#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int saveVideo()
{
	VideoCapture capture("2.avi");
	int rate = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / rate;
	VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), rate, Size(300, 200),0);
	Mat frame;
	Mat background;
	Mat result;
	Mat mv[3];
	capture.read(background);
	resize(background, background, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
	cvtColor(background, background, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
	
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	long frameNumber = 1.0;
	while (capture.read(frame))
	{
		
		resize(frame, frame, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(frame, frame, CV_RGB2GRAY);//תΪ�Ҷ�ͼ

		split(frame, mv);
		writer << mv[0];

		cvNamedWindow("123123");
		imshow("123123", mv[0]);
		waitKey(delay);

		frameNumber++;
		cout << totalFrameNumber - frameNumber << endl;
	}
	return 0;
}
