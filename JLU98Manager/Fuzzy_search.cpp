#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//基于汉字的模糊搜索
int Fuzzy_Search(char* key, char* str)
{
	int i, j;
	int n = 0;
	for (i = 0; i < strlen(str); i += 2)
	{
		for (j = 0; j < strlen(key); j += 2)
		{
			if (str[i] == key[j] && str[i + 1] == key[j + 1])
				n++;//当相邻的两个字节都相等时，才自增一
		}
	}
	if (n == strlen(key) / 2)    //一个汉字占两个字节，所以要除以2
		return 1;
	else return 0;
}