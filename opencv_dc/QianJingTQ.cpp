#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#define threshold_diff 20

using namespace std;
using namespace cv;

int QianJingTQ()
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
	namedWindow("Extracted frame", 1);
	//����ÿһ֡��ͼ���Լ��ҶȻ����ͼ��
	Mat img_src1, img_src2, img_dst, gray1, gray2, gray_diff;
	//��ʾǰ����ȡ��Ĵ���
	namedWindow("foreground", 2);
	//��֡��ļ��ʱ��:
	int delay = 1000 / rate;
	//�˲����ĺ�
	int kernel_size = 3;
	Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
	//����forѭ����ȡ֡
	//��ǰ֡���趨�Ŀ�ʼ֡
	//currentFrame����ѭ�����п��ƶ�ȡ��ָ����֡��ѭ�������ı���
	for(long currentFrame = frameToStart;currentFrame<= frameToStop;currentFrame++)
	{
		//��ȡ��һ֡
		if (!capture.read(frame))
		{
			cout << "��ȡ��Ƶʧ��" << endl;
			return -1;
		}
		cout << "���ڶ�ȡ��" << currentFrame << "֡" << endl;
		imshow("Extracted frame", frame);
		//ǰ����ȡ
		//��ȡǰһ֡ͼ��
		capture >> img_src1;
		//�˲�
		filter2D(img_src1, img_src1, -1, kernel);
		//�ҶȻ�
		cvtColor(img_src1, gray1, CV_BGR2GRAY);
		//��̬ѧ����������ʴ�����ͣ��������㣩
		// ����ѽṹԪ������ΪMat()������Ĭ�ϵ�3*3�ľ��νṹԪ��
		Mat eroded;
		erode(gray1, eroded, Mat());
		Mat dilated;
		dilate(gray1, dilated, Mat());
		//����ṹԪ��
		Mat sa(5, 5, CV_8U, Scalar(1));
		Mat closed;
		morphologyEx(gray1, closed, MORPH_CLOSE, sa);
		Mat opened;
		morphologyEx(gray1, opened, MORPH_OPEN, sa);
		waitKey(5);
		//��ȡ��һ֡ͼ��
		capture >> img_src2;
		//�˲�
		filter2D(img_src2, img_src2, -1, kernel);
		//�ҶȻ�
		cvtColor(img_src2, gray2, CV_BGR2GRAY);
		//��̬ѧ����������ʴ�����ͣ��������㣩
		// ����ѽṹԪ������ΪMat()������Ĭ�ϵ�3*3�ľ��νṹԪ��
	    eroded;
		erode(gray2, eroded, Mat());
		dilated;
		dilate(gray2, dilated, Mat());
		// ����ṹԪ��
	    Mat sb(5, 5, CV_8U, Scalar(1));
		closed;
		morphologyEx(gray2, closed, MORPH_CLOSE, sb);
		opened;
		morphologyEx(gray2, opened, MORPH_OPEN, sb);
		waitKey(5);
		//�������һ֡��ǰһ֡�õ��ƶ�����
		subtract(gray1, gray2, gray_diff);
		for (int i = 0; i<gray_diff.rows; i++)
			for (int j = 0; j<gray_diff.cols; j++)
				if (abs(gray_diff.at<unsigned char>(i, j)) >= threshold_diff)//����ģ�����һ��Ҫ��unsigned char�������һֱ����
					gray_diff.at<unsigned char>(i, j) = 255;
				else gray_diff.at<unsigned char>(i, j) = 0;
				//������ֵ
				threshold(gray_diff, gray_diff, 255 * (0.5), 255, THRESH_BINARY);
				// �ٽ���һ����̬ѧ����
				eroded;
				erode(gray_diff, eroded, Mat());
				dilated;
				dilate(gray_diff, dilated, Mat());
				// ����ṹԪ��
				Mat sc(5, 5, CV_8U, Scalar(1));
				closed;
				morphologyEx(gray_diff, closed, MORPH_CLOSE, sc);
				opened;
				morphologyEx(gray_diff, opened, MORPH_OPEN, sc);
				//��ʾǰ������
				imshow("foreground", gray_diff);
				//ˢ��ͼ��	
				//waitKey(int delay=0)��delay �� 0ʱ����Զ�ȴ�����delay>0ʱ��ȴ�delay����
				waitKey(delay);
	}
	//�ر���Ƶ�ļ�
	capture.release();
	waitKey(0);
	return 0;
}