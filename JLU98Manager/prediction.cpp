#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include"order.h"
#include"char2int.h"
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<easyx.h>
#include<Windows.h>
#include"Time.h"
void Data_analysis(float* first, float* second)
{
	float x[10] = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0 };
	float y[10];

	//��������¼�е����ʮ������������ֵ�浽����y��
	Odr_Node* head = Order_build();
	Odr_Node* p = head;
	int num = 0;
	while (p != NULL)
	{
		num++;
		p = p->next;
	}
	if (num < 10)
	{
		MessageBox(NULL, _T("�ɹ����������ݲ���"), _T("�ع�Ԥ��"), MB_SETFOREGROUND);
		return;
	}
	int length = num - 10;
	p = head;
	while (length--)
	{
		p = p->next;
	}
	int cnt = 0;
	while (p != NULL)
	{
		int profit = Char_to_int(p->profit);
		y[cnt++] = profit;
		p = p->next;
	}
	Order_free(head);

	int n;//nΪ���ݸ���
	n = sizeof(x) / sizeof(x[0]);

	//a,b�ֱ�Ϊ���̵���������
	float a, b;
	//�ֱ�Ϊx��y�������ܺ�
	float sum_x, sum_y;
	//Numerator_xyΪ(X - X_ave)*(Y - Y_ave)�ĺͣ�Denominator_xyΪ(X - X_ave)*(X - X_ave)�ĺ�
	float Numerator_xy, Denominator_xy;

	a = b = sum_x = sum_y = Numerator_xy = Denominator_xy = 0.0;

	//���x��y��ƽ��ֵ
	for (int i = 0; i < n; i++)
	{
		sum_x += x[i];
		sum_y += y[i];
	}
	float x_ave = sum_x / n;
	float y_ave = sum_y / n;

	//���ݹ�ʽb=(X1 - X_ave)*(Y1-Y_ave)+...+(Xn-X_ave)*(Yn-Y_ave)/(X1 - X_ave)*(X1 - X_ave)+...+(Xn-X_ave)*(Xn-X_ave)���b
	for (int i = 0; i != n; i++)
	{
		Numerator_xy += (x[i] - x_ave) * (y[i] - y_ave);
		Denominator_xy += (x[i] - x_ave) * (x[i] - x_ave);
	}
	b = Numerator_xy / Denominator_xy;//б��

	//��x,y��ƽ��ֵ����a=Y_ave-X_ave*a���a
	a = y_ave - b * x_ave;//�ؾ�
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	//����x��
	setlinecolor(LIGHTRED);
	line(130, 540, 1150, 540);
	line(1150,540, 1120, 530);
	line(1150,540, 1120, 550);
	outtextxy(1150, 550, "x / ����");
	//����y��
	line(130, 540, 130, 80);
	line(130, 80, 120, 95);
	line(130, 80, 140, 95);
	outtextxy(140, 80, "y / ����");
	//ԭ��������
	setlinecolor(LIGHTBLUE);
	//int positionx[11] = { 230,330,430,530,630,730,830,930,1030,1130 };
	int positionx[11] = { 210,290,370,450,530,610,690,770,850,930 };
	for (int i = 0; i < 9; i++)
	{
		line(positionx[i],541-(y[i]/300), positionx[i + 1], 541 - (y[i+1] / 300));
	}
	for (int i = 0; i < 10; i++)
	{
		setfillcolor(BLACK); //�����ɫ
		fillcircle(positionx[i], 541 - (y[i] / 300),3); //�������Բ��Ϊ�յ�
		//outtextxy(positionx[i], 541 - (y[i] / 300)-10,"o");
	}
	outtextxy(positionx[0], 545, "1");
	outtextxy(positionx[1], 545, "2");
	outtextxy(positionx[2], 545, "3");
	outtextxy(positionx[3], 545, "4");
	outtextxy(positionx[4], 545, "5");
	outtextxy(positionx[5], 545, "6");
	outtextxy(positionx[6], 545, "7");
	outtextxy(positionx[7], 545, "8");
	outtextxy(positionx[8], 545, "9");
	outtextxy(positionx[9], 545, "10");
	line(130, 537, 120, 537);
	outtextxy(50, 527, "1000Ԫ");
	line(130, 523, 120, 523);
	outtextxy(50, 513, "5000Ԫ");
	line(130, 507, 120, 507);
	outtextxy(50, 497, "10000Ԫ");
	line(130, 475, 120, 475);
	outtextxy(50, 465, "20000Ԫ");
	line(130, 409, 120, 409);
	outtextxy(50, 399, "40000Ԫ");
	line(130, 340, 120, 340);
	outtextxy(50, 330, "60000Ԫ");
	line(130, 274, 120, 274);
	outtextxy(50, 264, "80000Ԫ");
	line(130, 207, 120, 207);
	outtextxy(40, 197, "100000Ԫ");
	line(130, 140, 120, 140);
	outtextxy(40, 130, "120000Ԫ");

	line(130, 540, positionx[0], 541 - (y[0] / 300));
	setlinecolor(LIGHTGREEN);
	line(130,541-(a/300),1130, (541 - (a / 300)-(10*(b/300))));
	outtextxy(1130, (541 - (a / 300) - (10 * (b / 300))+10), "�ع�Ԥ��ֱ��");
}
