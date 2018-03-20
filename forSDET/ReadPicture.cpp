/*����������ڱȽ�bmpͼƬ�ļ�
 *�㷨˼�룺
 *��ͼƬ�Ĵ洢��ʽ����
 *1���ж�ͼƬ����
 *2�����������жϴ洢��ʽ
 *3����ȡͼƬͼ�����ݵ������ַ����飬Ȼ���ڴ������в���С���飬�ҵ�����������򲻰���
 **/
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <iostream>
using namespace std;
#define LENGTH_PATH 200 //·�������200���ַ�
struct BmpPicture{//14���ֽ�+40���ֽ�
	//unsigned short type;//λͼ����
	unsigned int size;//λͼ��С
	unsigned int reserved;//����λ
	unsigned int excursion;//ͼ��ƫ����
	unsigned int hesize;//header�ֽ���
	unsigned int width;
	unsigned int height;
	unsigned short biPlanes;//λƽ����������Ϊ1 
	unsigned short bitCount;//ÿ����λ��
	unsigned int Compression;//ѹ������
	unsigned int SizeImage;//ѹ��ͼ���С�ֽ���
	long XpelsPerMeter;//ˮƽ�ֱ���
	long YPerlsPerMeter;//��ֱ�ֱ���
	unsigned int ClrUsed;//ʵ���õ���ɫ��������ɫ��Ԫ�ظ���
	unsigned int ClrImportant;//��Ҫɫ����
}info1, info2;

bool checkType(char *a, char *b,char*ext);//�����չ��

int main(){
	char File1[LENGTH_PATH] = { 0 }, File2[LENGTH_PATH] = { 0 };//�ļ�·��
	char ext[30] = { 0 };//��չ��
	char * imagedata1 = NULL,*imagedata2=NULL;
	cout << "������������Ҫ��ȡ���ļ�������C:\\a.bmp��:" << endl;
	cin >> File1>>File2;
	if (!checkType(File2, File1,ext)){
		cout << "���������ͼƬ�ļ�����ͬһ������!" << endl;
		exit(1);
	}
	if (strcmp(ext, ".bmp") != 0){//�����չ���Ƿ���bmp�ļ�
		cout << "ת��" << ext << "ͼƬ������򡣡���" << endl;
		exit(1);
	}
/******************bmp�������*********************/
	FILE *fpi1 = fopen(File1, "rb");
	FILE *fpi2 = fopen(File2, "rb");
	if (!fpi1 || !fpi2){//�ļ���ȡΪ��
		cout << "�ļ���ȡʧ�ܣ������ļ������������룡" << endl;
		exit(1);
	}
	unsigned short type;//�ȶ�ȡ�ļ�����
	fread(&type, 1, sizeof(short), fpi1);
	if (0x4d42 != type)
	{
		cout << "�ļ�1��bmp�ļ�!" << endl;
		exit(1);
	}
	fread(&type, 1, sizeof(short), fpi2);
	if (0x4d42 != type)
	{
		cout << "�ļ�2��bmp�ļ�!" << endl;
		exit(1);
	}
	// ��ȡbmp�ļ����ļ�ͷ����Ϣͷ
	fread(&info1, 1, sizeof(BmpPicture), fpi1);
	fread(&info2, 1, sizeof(BmpPicture), fpi2);

	int width1 = info1.width;
	int height1 = info1.height;
	//ͼ��ÿһ�е��ֽ���������4��������  
	width1 = (width1 * sizeof(char) + 3) / 4 * 4;
	imagedata1 = (char*)malloc(width1 * height1);

	int width2 = info2.width;
	int height2 = info2.height;
	//ͼ��ÿһ�е��ֽ���������4��������  
	width2 = (width2 * sizeof(char) + 3) / 4 * 4;
	imagedata2 = (char*)malloc(width2 * height2);

	if (!imagedata1 || !imagedata2){
		cout << "�ڴ�ռ������󡣡���" << endl;
		exit(1);
	}
	//��ʼ��ԭʼͼƬ����������  
	for (int i = 0; i < height1; ++i)
		for (int j = 0; j < width1; ++j)
			*(imagedata1 + i * width1 + j) = 0;
	for (int i = 0; i < height2; ++i)
		for (int j = 0; j < width2; ++j)
			*(imagedata2 + i * width2 + j) = 0;

	//����ͼƬ������  
	fread(imagedata1, sizeof(char) * width1, height1, fpi1);
	fclose(fpi1);
	fread(imagedata2, sizeof(char) * width2, height2, fpi2);
	fclose(fpi2);
	if (strlen(imagedata1) <= strlen(imagedata2)){
		if (!strstr(imagedata2, imagedata1)){
			cout << "����ͼƬ�����ڰ�����ϵ" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
		else{
			cout << "���ڰ�����ϵ" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
	}
	else{
		if (!strstr(imagedata1, imagedata2)){
			cout << "����ͼƬ�����ڰ�����ϵ" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
		else{
			cout << "���ڰ�����ϵ" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
	}
}

bool checkType(char *a, char *b,char *ext){//�Ƚ���չ��
	int fi = strlen(a);
	int se = strlen(b);
	if (!fi || !se)
		return false;
	int start1=0, start2=0;
	for (int i = fi - 1; i > -1; i--){
		if (a[i] == '.'){
			start1 = i;
			break;
		}
	}
	for (int i = se - 1; i > -1; i--){
		if (b[i] == '.'){
			start2 = i;
			break;
		}
	}
	if (0 != strcmp(&a[start1], &b[start2]))//��չ����ͬ
		return false;
	strcpy(ext, &a[start1]);
	return true;
}