#define _CRT_SECURE_NO_WARNINGS
#include <time.h>   
#include<string.h>
#include<stdlib.h>
int Time_year()//获得当下时间的年份
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//距离1900年1月1日00：00到现在的秒数
	local = localtime(&t);
	a = local->tm_year + 1900;
	return a;
}
int Time_month()//获得当下时间的月份
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//距离1900年1月1日00：00到现在的秒数
	local = localtime(&t);
	a = local->tm_mon + 1;
	return a;
}
int Time_day()//获得当下时间的日期
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//距离1900年1月1日00：00到现在的秒数
	local = localtime(&t);
	a = local->tm_mday;
	return a;
}
int Time_hour()//获得当下时间的小时数
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//距离1900年1月1日00：00到现在的秒数
	local = localtime(&t);
	a = local->tm_hour;
	return a;
}
int Time_min()//获得当下时间的分钟数
{
	struct tm* local;
	time_t t;
	int a;
	t = time(NULL);//距离1900年1月1日00：00到现在的秒数
	local = localtime(&t);
	a = local->tm_min;
	return a;
}

char* Time_now()//返回当前时间字符串
{
	int Year = Time_year();
	int Month = Time_month();
	int Day = Time_day();
	int Hour = Time_hour();
	int Min = Time_min();
	char* Time = (char*)malloc(25);
	for (int i = 3; i >= 0; i--)//录入年 0 1 2 3下标
	{
		Time[i] = Year % 10 + 48;
		Year = Year / 10;
	}
	strcpy((Time + 4), "年");//4,5下标为汉字年
	for (int i = 7; i >= 6; i--)//录入月 6 7下标
	{
		Time[i] = Month % 10 + 48;
		Month = Month / 10;
	}
	strcpy((Time + 8), "月");//8 9下标为汉字月
	for (int i = 11; i >= 10; i--)//录入日 10 11下标
	{
		Time[i] = Day % 10 + 48;
		Day = Day / 10;
	}
	strcpy((Time + 12), "日");//12 13下标为汉字日
	for (int i = 15; i >= 14; i--)//录入时 15 14下标
	{
		Time[i] = Hour % 10 + 48;
		Hour = Hour / 10;
	}
	strcpy((Time + 16), "时");//16 17为汉字时
	for (int i = 19; i >= 18; i--)//录入分 18 19下标
	{
		Time[i] = Min % 10 + 48;
		Min = Min / 10;
	}
	strcpy((Time + 20), "分");//20 21为汉字时
	Time[22] = '\0';
	return Time;
}
int Time_compare(char* str1, char* str2)
{
	int ans = 0;
	int Year1 = 0, Year2 = 0;
	int n = 1;
	for (int i = 3; i >= 0; i--)//获取年份
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
	for (int i = 7; i >= 6; i--)//获取月份
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
	for (int i = 11; i >= 10; i--)//获取日
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
	for (int i = 15; i >= 14; i--)//获取时
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
	for (int i = 19; i >= 18; i--)//获取时
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
	else if (Minute1 == Minute2)//全都相等说明时间也相等
	{
		ans = 0;
		return ans;
	}
}