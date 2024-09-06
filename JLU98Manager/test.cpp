#include <graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>
void Welcome();

int main()
{
	initgraph(1366, 700);//定义窗口大小
	Welcome();//调用Welcome
	return 0;
}