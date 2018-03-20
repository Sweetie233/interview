/*本程序仅限于比较bmp图片文件
 *算法思想：
 *从图片的存储格式入手
 *1、判断图片类型
 *2、根据类型判断存储格式
 *3、读取图片图像数据到两个字符数组，然后在大数组中查找小数组，找到则包含，否则不包含
 **/
#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <iostream>
using namespace std;
#define LENGTH_PATH 200 //路径名最多200个字符
struct BmpPicture{//14个字节+40个字节
	//unsigned short type;//位图类型
	unsigned int size;//位图大小
	unsigned int reserved;//保留位
	unsigned int excursion;//图像偏移量
	unsigned int hesize;//header字节数
	unsigned int width;
	unsigned int height;
	unsigned short biPlanes;//位平面数，必须为1 
	unsigned short bitCount;//每像素位数
	unsigned int Compression;//压缩类型
	unsigned int SizeImage;//压缩图像大小字节数
	long XpelsPerMeter;//水平分辨率
	long YPerlsPerMeter;//垂直分辨率
	unsigned int ClrUsed;//实际用到的色彩数，调色板元素个数
	unsigned int ClrImportant;//重要色彩数
}info1, info2;

bool checkType(char *a, char *b,char*ext);//检查扩展名

int main(){
	char File1[LENGTH_PATH] = { 0 }, File2[LENGTH_PATH] = { 0 };//文件路径
	char ext[30] = { 0 };//扩展名
	char * imagedata1 = NULL,*imagedata2=NULL;
	cout << "请输入两个所要读取的文件名（如C:\\a.bmp）:" << endl;
	cin >> File1>>File2;
	if (!checkType(File2, File1,ext)){
		cout << "输入的两个图片文件不是同一种类型!" << endl;
		exit(1);
	}
	if (strcmp(ext, ".bmp") != 0){//检查扩展名是否是bmp文件
		cout << "转入" << ext << "图片处理程序。。。" << endl;
		exit(1);
	}
/******************bmp处理程序*********************/
	FILE *fpi1 = fopen(File1, "rb");
	FILE *fpi2 = fopen(File2, "rb");
	if (!fpi1 || !fpi2){//文件读取为空
		cout << "文件读取失败，请检查文件名后重新输入！" << endl;
		exit(1);
	}
	unsigned short type;//先读取文件类型
	fread(&type, 1, sizeof(short), fpi1);
	if (0x4d42 != type)
	{
		cout << "文件1非bmp文件!" << endl;
		exit(1);
	}
	fread(&type, 1, sizeof(short), fpi2);
	if (0x4d42 != type)
	{
		cout << "文件2非bmp文件!" << endl;
		exit(1);
	}
	// 读取bmp文件的文件头和信息头
	fread(&info1, 1, sizeof(BmpPicture), fpi1);
	fread(&info2, 1, sizeof(BmpPicture), fpi2);

	int width1 = info1.width;
	int height1 = info1.height;
	//图像每一行的字节数必须是4的整数倍  
	width1 = (width1 * sizeof(char) + 3) / 4 * 4;
	imagedata1 = (char*)malloc(width1 * height1);

	int width2 = info2.width;
	int height2 = info2.height;
	//图像每一行的字节数必须是4的整数倍  
	width2 = (width2 * sizeof(char) + 3) / 4 * 4;
	imagedata2 = (char*)malloc(width2 * height2);

	if (!imagedata1 || !imagedata2){
		cout << "内存空间分配错误。。。" << endl;
		exit(1);
	}
	//初始化原始图片的像素数组  
	for (int i = 0; i < height1; ++i)
		for (int j = 0; j < width1; ++j)
			*(imagedata1 + i * width1 + j) = 0;
	for (int i = 0; i < height2; ++i)
		for (int j = 0; j < width2; ++j)
			*(imagedata2 + i * width2 + j) = 0;

	//读出图片的数据  
	fread(imagedata1, sizeof(char) * width1, height1, fpi1);
	fclose(fpi1);
	fread(imagedata2, sizeof(char) * width2, height2, fpi2);
	fclose(fpi2);
	if (strlen(imagedata1) <= strlen(imagedata2)){
		if (!strstr(imagedata2, imagedata1)){
			cout << "两个图片不存在包含关系" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
		else{
			cout << "存在包含关系" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
	}
	else{
		if (!strstr(imagedata1, imagedata2)){
			cout << "两个图片不存在包含关系" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
		else{
			cout << "存在包含关系" << endl;
			free(imagedata1);
			free(imagedata2);
			return 0;
		}
	}
}

bool checkType(char *a, char *b,char *ext){//比较扩展名
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
	if (0 != strcmp(&a[start1], &b[start2]))//扩展名不同
		return false;
	strcpy(ext, &a[start1]);
	return true;
}