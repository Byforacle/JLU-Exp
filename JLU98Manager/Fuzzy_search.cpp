#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//���ں��ֵ�ģ������
int Fuzzy_Search(char* key, char* str)
{
	int i, j;
	int n = 0;
	for (i = 0; i < strlen(str); i += 2)
	{
		for (j = 0; j < strlen(key); j += 2)
		{
			if (str[i] == key[j] && str[i + 1] == key[j + 1])
				n++;//�����ڵ������ֽڶ����ʱ��������һ
		}
	}
	if (n == strlen(key) / 2)    //һ������ռ�����ֽڣ�����Ҫ����2
		return 1;
	else return 0;
}