#include <iostream> 
#include "opencv2/opencv.hpp" 

using namespace std; using namespace cv;
int readVideo()
{

	//����Ƶ�ļ� 
	VideoCapture cap("1.mp4");

	//����Ƿ�ɹ��� 
	if (!cap.isOpened())
	{
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}

	Mat edges;     //�������� 
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		//��cap�ж�һ֡���浽frame 
		cap >> frame;         
		//���δ����ͼ�� 
		if (frame.empty()) {
			break;
		}
		//��������ͼ��תΪ�Ҷ�ͼ 
		cvtColor(frame, edges, CV_BGR2GRAY);
		//���б�Ե��ȡ���� 
		Canny(edges, edges, 0, 123, 3);
		//��ʾ���       
		imshow("edges", edges);
		waitKey(100);

	}
	return 0;
}
