#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int saveVideo()
{
	VideoCapture capture("2.avi");
	VideoWriter writer("VideoTest.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(300, 200));
	Mat frame;
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	long frameNumber = 1.0;
	while (capture.read(frame))
	{
		resize(frame, frame, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		writer << frame;
		if (cvWaitKey(20) == 27)
		{
			break;
		}
		frameNumber++;
		cout << totalFrameNumber - frameNumber << endl;
	}
	return 0;
}
