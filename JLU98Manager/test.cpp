#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>
void Welcome();

int main()
{
	initgraph(1366, 700);//���崰�ڴ�С
	Welcome();//����Welcome
	return 0;
}