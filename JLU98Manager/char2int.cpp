#include<stdio.h>
#include<string.h>
int Char_to_int(char str[])
{
	int ans = 0;
	int n = 1;
	int l = strlen(str);//获取字符串长度
	for (int i = l - 1; i >= 0; i--)
	{
		ans += (str[i] - '0') * n;
		n *= 10;
	}
	return ans;
}

char* Int_to_char(int x)
{
	char arr[25];
	for (int i = 0; i < 25; i++)
	{
		arr[i] = '\0';
	}
	if (x == 0)
	{
		arr[0] = '0';
		return arr;
	}
	int size = 0;
	int a;
	while (x)
	{
		a = x % 10;
		x /= 10;
		arr[size++] = '0' + a;
	}
	int left = 0;
	int right = size - 1;
	while (left < right)
	{
		char b = arr[left];
		arr[left] = arr[right];
		arr[right] = b;
		left++;
		right--;
	}
	return arr;
}