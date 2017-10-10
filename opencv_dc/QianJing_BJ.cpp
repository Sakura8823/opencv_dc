#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "cv.h"
#include <math.h>
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"
#include <opencv\ml.h>
#include <iostream>
#include "highgui.h"
#include <vector>
#include <string.h>
#include <fstream>

using namespace cv;
using namespace std;

void chao_thinimage(Mat &srcimage);

int QianJing_BJ() {
	IplImage* pFrame = NULL;//��Ƶ�н�ȡ��һ֡
	IplImage* pFrImg = NULL;//��ǰ֡�ĻҶ�ͼ
	IplImage* pBkImg = NULL;//��ǰ�����ĻҶ�ͼ
	IplImage* pFrameTemp = NULL;

	CvMat* pFrameMat = NULL;//��ǰ�ҶȾ���
	CvMat* pFrMat = NULL;//��ǰǰ��ͼ����
	CvMat* pBkMat = NULL;//��ǰ����ͼ����


						 //��̬ѧ����ʱ�ں˴�С
	IplConvKernel* Element = cvCreateStructuringElementEx(13, 13, 1, 1, CV_SHAPE_RECT, NULL);

	//������Ե��ȡʱ�Ĳ���
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;//�ɶ�̬����Ԫ������
	int mode = CV_RETR_EXTERNAL;//ֻ���������������

								//����Ƶ�л�������Ȥ������
	CvPoint pt1, pt2, pt3, pt4, pt5;//pt3,pt4Ϊ�����������������
	pt1.x = 292;//��Ƶ���µ�
	pt1.y = 100;
	pt2.x = 412;//��Ƶ���ϵ�
	pt2.y = 280;
	//��cvBoundingRect������Ӿ���ʱ��Ҫ�ľ���
	CvRect bndRect = cvRect(0, 0, 0, 0);
	//�˶�������������
	int avgX = 0;
	int avgY = 0;


	//��Ƶ����
	CvCapture* pCapture = NULL;
	//ͼ���֡��
	int nFramNum = 0;

	//��������
	cvNamedWindow("video", 1);
	cvNamedWindow("foreground", 1);
	cvMoveWindow("video", 30, 0);
	cvMoveWindow("foreground", 690, 0);

	pCapture = cvCaptureFromFile("7.mp4");
	//pFrame = cvQueryFrame(pCapture);


	pFrameTemp = cvQueryFrame(pCapture);
	pFrame = cvCreateImage(cvGetSize(pFrameTemp), 8, 3);//��С��pFrameTemp��ͬ��8Bit���3ͨ��ͼ��
	cvCopy(pFrameTemp, pFrame);//�������ɵ���ʱ֡���Ƶ�pFrame

							   //��֡��ȡ��Ƶ��cvQueryFrame������ͷ�����ļ���ץȡ������һ֡
	while (pFrameTemp = cvQueryFrame(pCapture)) {
		cvCopy(pFrameTemp, pFrame);
		nFramNum++;

		//����ǵ�һ֡�������ڴ沢��ʼ��
		if (nFramNum == 1) {
			pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);//8Bit��ȣ���ͨ��ͼ��
			pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
			pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);//CV_32FC1 ����32λ�����͵�ͨ������
			pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);//ת���ɵ�ͨ���Ҷ�ͼ
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			cvConvert(pFrImg, pFrameMat);//ת���ɾ���
			cvConvert(pFrImg, pFrMat);
			cvConvert(pFrImg, pBkMat);

		}

		else if (nFramNum >= 2) {
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			cvConvert(pFrImg, pFrameMat);
			//�ȸ�˹�˲�ƽ��ͼ��
			cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

			//����Ƶ�����ò���ROI����
			cvRectangle(pFrame, pt1, pt2, CV_RGB(255, 0, 0), 2, 8, 0);//�������ȣ�255,0,0��Ϊ��ɫ����ϸ2������8

																	  //��ǰ֡������ͼ������������������ľ���ֵ
			cvAbsDiff(pFrameMat, pBkMat, pFrMat);

			//��ֵ��ǰ��ͼ
			cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);//��ֵ����������ΪCV_THRESH_BINARY ��ֵ��

																	 //���Ͳ������ں�ΪElement
			cvDilate(pFrImg, pBkImg, Element, 1);

			//ͨ�����ұ߽��ҳ�ROI���������ڵ��˶�����
			cvFindContours(pBkImg, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE);//��ֵͼ����Ѱ������

																									   //����ǰ������ƶ����������ú���cvBoundingRect
			for (; contour != 0; contour = contour->h_next) {
				//����˶������ľ���
				bndRect = cvBoundingRect(contour, 0);
				//����˶�������ƽ��x����
				avgX = bndRect.x + (bndRect.width) / 2;
				avgY = bndRect.y + (bndRect.height) / 2;

				//����������ĵ���ROI�ڣ���ʾ
				if (avgX > 300 && avgX < 400 && avgY<280 && avgY>100) {
					pt3.x = bndRect.x;
					pt3.y = bndRect.y;
					pt4.x = bndRect.x + bndRect.width;
					pt4.y = bndRect.y + bndRect.height;

					//ȥ����С�ĸ��ž���
					if (bndRect.height>35 && 600<(bndRect.width*bndRect.height)<10000) {
						cvRectangle(pFrame, pt3, pt4, CV_RGB(255, 0, 0), 1, 8, 0);
					}
				}
			}//���ұ߽�for����

			 //���±���//////////////////////

			 //����ͼ�������-�����ۼӵ�ͼ�������-�ƶ�ƽ��ʱ��һ����image��ռ��Ȩ��-����������
			cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);//��pFrameMat�ۼӵ�pBkMat
													  //������ת����ͼ���ʽ��������ʾ
			cvConvert(pBkMat, pBkImg);

			//��ʾͼ��///////////////////////
			cvShowImage("video", pFrame);
			cvShowImage("foreground", pFrImg);
			cvShowImage("background", pBkImg);


			//����а�����������ȴ�
			if (cvWaitKey(2) >= 0)
				break;

		}
		waitKey(50);
	}//whileѭ������
	 //ɾ���ṹԪ��
	cvReleaseStructuringElement(&Element);
	//���ٴ���
	cvDestroyWindow("video");
	cvDestroyWindow("background");
	cvDestroyWindow("foreground");

	//�ͷ�ͼ��;���
	cvReleaseImage(&pFrImg);
	cvReleaseImage(&pBkImg);

	cvReleaseMat(&pFrameMat);
	cvReleaseMat(&pFrMat);
	cvReleaseMat(&pBkMat);
	return 0;
}