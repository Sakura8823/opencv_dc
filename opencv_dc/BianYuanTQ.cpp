#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int BianYuanTQ()
{
	//����Ƶ�ļ�����ʵ���ǽ���һ��VideoCapture�ṹ
	VideoCapture capture("1.mp4");
	//����Ƿ�������:�ɹ���ʱ��isOpened����ture
	if (!capture.isOpened())
	{
		cout << "fail to open!" << endl;
		return -1;
	}
	//��ȡ����֡��
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "������Ƶ��" << totalFrameNumber << "֡" << endl;

	//���ÿ�ʼ֡()
	long frameToStart = 1;
	capture.set(CV_CAP_PROP_POS_FRAMES, frameToStart);
	cout << "�ӵ�" << frameToStart << "֡��ʼ��" << endl;

	//���ý���֡
	int frameToStop = 1270;

	if (frameToStop < frameToStart)
	{
		cout << "����֡С�ڿ�ʼ֡��������󣬼����˳���" << endl;
		return -1;
	}
	else
	{
		cout << "����֡Ϊ����" << frameToStop << "֡" << endl;
	}

	//��ȡ֡��
	double rate = capture.get(CV_CAP_PROP_FPS);
	cout << "֡��Ϊ:" << rate << endl;

	//����һ���������ƶ�ȡ��Ƶѭ�������ı���
	bool stop = false;
	//����ÿһ֡��ͼ��
	Mat frame;
	//��ʾÿһ֡�Ĵ���
	namedWindow("Extracted frame", 0);
	//����ÿһ֡��Ե��ȡ���ͼ��
	Mat edges;
	//��ʾ��Ե��ȡ��Ĵ���
	namedWindow("edges", 1);
	int delay = 1000 / rate;
	//�˲����ĺ�
	int kernel_size = 3;
	Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
	//����forѭ����ȡ֡
	//��ǰ֡���趨�Ŀ�ʼ֡
	//currentFrame����ѭ�����п��ƶ�ȡ��ָ����֡��ѭ�������ı���
	for (long currentFrame = frameToStart; currentFrame <= frameToStop; currentFrame++)
	{
		//��ȡ��һ֡
		if (!capture.read(frame))
		{
			cout << "��ȡ��Ƶʧ��" << endl;
			return -1;
		}
		//������˲�����
		imshow("Extracted frame", frame);
		filter2D(frame, frame, -1, kernel);
		imshow("after filter", frame);
		cout << "���ڶ�ȡ��" << currentFrame << "֡" << endl;
		//���б�Ե��ȡ���� 
		cvtColor(frame, edges, CV_BGR2GRAY);
		Canny(edges, edges, 0, 123, 3);
		//��ʾ��Ե��ȡ���       
		imshow("edges", edges);
		//ˢ��ͼ��	
		//waitKey(int delay=0)��delay �� 0ʱ����Զ�ȴ�����delay>0ʱ��ȴ�delay����
		waitKey(delay);
	}
	//�ر���Ƶ�ļ�
	capture.release();
	waitKey(0);
	return 0;
}