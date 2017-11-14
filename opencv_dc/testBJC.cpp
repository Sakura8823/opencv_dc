#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include<vector>
#include <fstream>//fstream�����������࣬����ʵ��c++���ļ��Ĳ���
#include <iomanip>

using namespace std;
using namespace cv;

int testBJC()
{
	Mat test1 = imread("test1.png");//����ͼƬ
	Mat background;//����
	Mat temp;   
	Mat result;

	VideoCapture capture("7.mp4");
	long totalFrameNumber= capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ��Ƶ����֡��
	int FrameCount = 0;//֡��
	if (!capture.isOpened())//�ж��Ƿ����Ƶ
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
	ofstream File;//ofstream��ʵ�����ļ�д����
	File.open("H:\\test\\test.xls", ios::_Noreplace);//ios::_Noreplace ��һ���ļ�ʱ������ļ������ڣ��������ļ�
	vector<int>ivec(totalFrameNumber);//�ɱ�����ivec����СΪ��֡��
	vector<int>::iterator iter = ivec.begin();//������ָ��ָ��ivec��Ԫ��
	while (capture.read(temp))//ѭ����ȡ��һ֡
	{
		FrameCount++;
		resize(temp, temp, Size(300, 200));//resizeΪ300*200��ͼ��ԭ����720*480
		cvtColor(temp, temp, CV_RGB2GRAY);//תΪ�Ҷ�ͼ
		absdiff(background, temp, result);//�ͱ�������,���result
		addWeighted(background, 0.95, temp, 1-0.95, 0, background);//������ͼƬ����
		int PixelCount = 0;//������
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
		*iter = PixelCount;//���������ŵ�ivec��
		++iter;//ָ�����
		cout << "������Ƶ��" << totalFrameNumber << "֡" << endl;
		cout <<"��ǰ�ǵ�"<<FrameCount<<"֡"<<endl;
		cout << "��ǰ������" << PixelCount << "��ǰ������" << endl;
		imshow("��ǰ��Ƶ",result);
		imshow("����ͼƬ",background);
	}
	//forѭ�����ivec�ﴢ�������������д��excel�����
	for (vector<int>::iterator iter = ivec.begin(); iter != ivec.end(); ++iter)
	{
		File << *iter << "\n";
	}
	File.close();//�ر��ļ�
	return 0;
}
