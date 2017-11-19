#include <iostream>  
#include <opencv2/opencv.hpp>  


using namespace std;
using namespace cv;


int saveVideo2()
{
	Mat in_frame, out_frame;
	double fps = 30;
	char file_out[] = "recorded.avi";
	int i = 0;

	VideoCapture cap("2.mp4");//��Ĭ���������videocapture������������������Ƶ�ļ���VideoCapture(const string &filename)  
	if (!cap.isOpened())
	{
		cout << "Can not open a capture object." << endl;
		return -1;
	}

	//��ȡ������Ƶÿһ֡�Ŀ�Ⱥ͸߶�  
	int width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter recVid(file_out, VideoWriter::fourcc('M', 'P', '4', '2'), fps, Size(width, height),0);
	// MSVC��΢����Ƶ��������Windows�Ͻ���ʹ�ã�����ѡ��MJPG,PIM1��FLV1��  
	if (!recVid.isOpened())
	{
		cout << "Error!Video File is not open...\n";
	}

	while (cap.read(in_frame))
	{
		
		cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
		out_frame.convertTo(out_frame, CV_8U);
		recVid << out_frame; // ��ת����ĻҶ�ͼд����Ƶ�ļ�  
		cout << i++ <<endl;
	}
	cap.release();
	return 0;
}