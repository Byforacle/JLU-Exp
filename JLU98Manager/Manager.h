#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<Windows.h>
#include<time.h>


/*欢迎界面函数*/
void Welcome();
/*一级主菜单函数*/
void MainMenu();
void Cus_manage();
void Stock_manage();
void Money_manage();
void Order_manage();//订单处理函数
void Prediction();//回归分析函数
void Password_change();
