#include <iostream>
#include <fstream>//fstream�����������࣬����ʵ��c++���ļ��Ĳ���
#include <iomanip>

using namespace std;

int WriteExcel()
{
	ofstream File;//ofstream��ʵ�����ļ�д����
	File.open("H:\\test\\test.xls", ios::_Noreplace);//ios::_Noreplace ��һ���ļ�ʱ������ļ������ڣ��������ļ�
	char chy[4] = { 'x' ,'a' ,'h','w' };
	int data[4] = { 1 , 3 , 6 ,9 };
	for (int i=0;i<=3;i++)//��26�����ּ�Ӣ����ĸд���ļ�
	{
		File <<chy[i]<<"\t"<<data[i]<<"\n";
	}
	File.close();//�ر��ļ�
	return 0;
}