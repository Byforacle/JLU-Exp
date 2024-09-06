#define _CRT_SECURE_NO_WARNINGS
#include <time.h>   
#include<string.h>
#include<stdlib.h>
int Time_year()//��õ���ʱ������
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//����1900��1��1��00��00�����ڵ�����
	local = localtime(&t);
	a = local->tm_year + 1900;
	return a;
}
int Time_month()//��õ���ʱ����·�
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//����1900��1��1��00��00�����ڵ�����
	local = localtime(&t);
	a = local->tm_mon + 1;
	return a;
}
int Time_day()//��õ���ʱ�������
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//����1900��1��1��00��00�����ڵ�����
	local = localtime(&t);
	a = local->tm_mday;
	return a;
}
int Time_hour()//��õ���ʱ���Сʱ��
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//����1900��1��1��00��00�����ڵ�����
	local = localtime(&t);
	a = local->tm_hour;
	return a;
}
int Time_min()//��õ���ʱ��ķ�����
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//����1900��1��1��00��00�����ڵ�����
	local = localtime(&t);
	a = local->tm_min;
	return a;
}

char* Time_now()//���ص�ǰʱ���ַ���
{
	int Year = Time_year();
	int Month = Time_month();
	int Day = Time_day();
	int Hour = Time_hour();
	int Min = Time_min();
	char* Time = (char*)malloc(25);
	for (int i = 3; i >= 0; i--)//¼���� 0 1 2 3�±�
	{
		Time[i] = Year % 10 + 48;
		Year = Year / 10;
	}
	strcpy((Time + 4), "��");//4,5�±�Ϊ������
	for (int i = 7; i >= 6; i--)//¼���� 6 7�±�
	{
		Time[i] = Month % 10 + 48;
		Month = Month / 10;
	}
	strcpy((Time + 8), "��");//8 9�±�Ϊ������
	for (int i = 11; i >= 10; i--)//¼���� 10 11�±�
	{
		Time[i] = Day % 10 + 48;
		Day = Day / 10;
	}
	strcpy((Time + 12), "��");//12 13�±�Ϊ������
	for (int i = 15; i >= 14; i--)//¼��ʱ 15 14�±�
	{
		Time[i] = Hour % 10 + 48;
		Hour = Hour / 10;
	}
	strcpy((Time + 16), "ʱ");//16 17Ϊ����ʱ
	for (int i = 19; i >= 18; i--)//¼��� 18 19�±�
	{
		Time[i] = Min % 10 + 48;
		Min = Min / 10;
	}
	strcpy((Time + 20), "��");//20 21Ϊ����ʱ
	Time[22] = '\0';
	return Time;
}
int Time_compare(char* str1, char* str2)
{
	int ans = 0;
	int Year1 = 0, Year2 = 0;
	int n = 1;
	for (int i = 3; i >= 0; i--)//��ȡ���
	{
		Year1 += (str1[i] - '0') * n;
		Year2 += (str2[i] - '0') * n;
		n *= 10;
	}
	if (Year1 > Year2)
	{
		ans = 1;
		return ans;
	}
	else if (Year1 < Year2)
	{
		ans = -1;
		return ans;
	}
	n = 1;
	int Month1 = 0, Month2 = 0;
	for (int i = 7; i >= 6; i--)//��ȡ�·�
	{
		Month1 += (str1[i] - '0') * n;
		Month2 += (str2[i] - '0') * n;
		n *= 10;
	}
	if (Month1 > Month2)
	{
		ans = 1;
		return ans;
	}
	else if (Month1 < Month2)
	{
		ans = -1;
		return ans;
	}
	n = 1;
	int Day1 = 0, Day2 = 0;
	for (int i = 11; i >= 10; i--)//��ȡ��
	{
		Day1 += (str1[i] - '0') * n;
		Day2 += (str2[i] - '0') * n;
		n *= 10;
	}
	if (Day1 > Day2)
	{
		ans = 1;
		return ans;
	}
	else if (Day1 < Day2)
	{
		ans = -1;
		return ans;
	}
	n = 1;
	int Hour1 = 0, Hour2 = 0;
	for (int i = 15; i >= 14; i--)//��ȡʱ
	{
		Hour1 += (str1[i] - '0') * n;
		Hour2 += (str2[i] - '0') * n;
		n *= 10;
	}
	if (Hour1 > Hour2)
	{
		ans = 1;
		return ans;
	}
	else if (Hour1 < Hour2)
	{
		ans = -1;
		return ans;
	}
	n = 1;
	int Minute1 = 0, Minute2 = 0;
	for (int i = 19; i >= 18; i--)//��ȡʱ
	{
		Minute1 += (str1[i] - '0') * n;
		Minute2 += (str2[i] - '0') * n;
		n *= 10;
	}
	if (Minute1 > Minute2)
	{
		ans = 1;
		return ans;
	}
	else if (Minute1 < Minute2)
	{
		ans = -1;
		return ans;
	}
	else if (Minute1 == Minute2)//ȫ�����˵��ʱ��Ҳ���
	{
		ans = 0;
		return ans;
	}
}