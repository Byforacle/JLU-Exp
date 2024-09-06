#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"char2int.h"
#include"Fuzzy_search.h"
#include"Purchase.h"
#include"Time.h"
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<Windows.h>
#include<time.h>

Pcs_Node* Purchase_build()//���������¼����
{
    Pcs_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Purchase.txt", "r");
    if (fp == NULL || feof(fp))//���ļ�Ϊ�գ������¼������
    {
        return NULL;
    }
    else
    {
        //������ͷ��Ϣ��ʼ��
        head = (Pcs_Node*)malloc(sizeof(Pcs_Node));
        fscanf(fp, "%s %s %s %s\n", head->time, head->drink, head->num, head->cost);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//��������������,ֱ���ļ�����
        {
            p = (Pcs_Node*)malloc(sizeof(Pcs_Node));
            fscanf(fp, "%s %s %s %s\n", p->time, p->drink, p->num, p->cost);
            tmp->next = p;
            tmp = p;
        }
        if (p != NULL)//���p���ǿ�ָ��Ļ�
        {
            p->next = NULL;
        }
        fclose(fp);//�ر��ļ�
        return head;//��������ͷ
    }
}
void Purchase_Moneyshow()//չʾ�����ʽ�
{
    FILE* fp = fopen("Amount.txt", "r");
    int money;
    fscanf(fp, "%d", &money);
    char money1[20];
    strcpy(money1, Int_to_char(money));
    fclose(fp);
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(120, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("�����ʽ�"));
    position_y += 120;
    outtextxy(position_x, position_y,money1);//��ʾ�����ʽ�
    return;
}

void Purchase_show(Pcs_Node* head,int *page)
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("�����¼�����ڣ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return;
    }
    Pcs_Node* p = head;
    Pcs_Node* p1 = head;
    int count1 = 1;
    while (p1 != NULL)
    {
        p1 = p1->next;
        count1++;
    }
    if (*page < 1) *page = 1;
    if (*page > (count1 / 20) + 1) *page = (count1 / 20) + 1;
    int en = *page * 20, st = en - 20 + 1;
    int count = 1;
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("����ʱ��                 ������Ʒ����         ��������    �ɱ�"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {

        if (count >= st && count <= en)
        {
            outtextxy(474, position_y, p->time);//��ʾ����ʱ��
            outtextxy(740, position_y, p->drink);//������Ʒ����
            outtextxy(980, position_y, p->num);//��������
            outtextxy(1060, position_y, p->cost);//�ɱ�
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
void Purchase_search(Pcs_Node* head)//��ѯ�����¼
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("�����¼�����ڣ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return;
    }
    Pcs_Node* p = head;
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("����ʱ��                 ������Ʒ����         ��������    �ɱ�"));//��ʾ����һ�б�ͷ
    position_y += 20;
    char choice[10];
    InputBox(choice, 11, _T("����������ѡ���������ʽ��1��������Ʒ�ؼ���    2�����չ���ʱ�䷶Χ"));

    if (strcmp(choice, "1") == 0)
    {
        char key[20];
        InputBox(key, 11, _T("����ؼ���"));
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->drink))
            {
                outtextxy(474, position_y, p->time);//��ʾ����ʱ��
                outtextxy(740, position_y, p->drink);//������Ʒ����
                outtextxy(980, position_y, p->num);//��������
                outtextxy(1060, position_y, p->cost);//�ɱ�
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("�����¼�����ڣ�"), _T("��ѯ�����¼"), MB_SETFOREGROUND);
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("��ѯ�����¼"), MB_SETFOREGROUND);
    }
    else if (strcmp(choice, "2") == 0)
    {
        char time1[25]; char time2[25];
        char year1[5]; 
        InputBox(year1, 11, _T("��������Ҫ��������ʼ���(����������)"));
        char month1[3]; 
        InputBox(month1, 11, _T("��������Ҫ��������ʼ�·�(����������,��ͷΪ0Ҳ����)"));
        char day1[3]; 
        InputBox(day1, 11, _T("��������Ҫ��������ʼ����(����������,��ͷΪ0Ҳ����)"));
        char hour1[3]; 
        InputBox(hour1, 11, _T("��������Ҫ��������ʼСʱ(����������,��ͷΪ0Ҳ����)"));
        char min1[3]; 
        InputBox(min1, 11, _T("��������Ҫ��������ʼ����(����������,��ͷΪ0Ҳ����)"));
        strcpy(time1, year1);
        strcpy((time1 + 4), "��");//4,5�±�Ϊ������
        strcpy(time1 + 6, month1);
        strcpy((time1 + 8), "��");//8 9�±�Ϊ������
        strcpy(time1 + 10, day1);
        strcpy((time1 + 12), "��");//12 13�±�Ϊ������
        strcpy(time1 + 14, hour1);
        strcpy((time1 + 16), "ʱ");//16 17Ϊ����ʱ
        strcpy(time1 + 18, min1);
        strcpy((time1 + 20), "��");//20 21Ϊ���ַ�
        time1[22] = '\0';
        char year2[5]; 
        InputBox(year2, 11, _T("��������Ҫ��������ʼ���(����������)"));
        char month2[3]; 
        InputBox(month2, 11, _T("��������Ҫ��������ʼ�·�(����������,��ͷΪ0Ҳ����)"));
        char day2[3]; 
        InputBox(day2, 11, _T("��������Ҫ��������ʼ����(����������,��ͷΪ0Ҳ����)"));
        char hour2[3]; 
        InputBox(hour2, 11, _T("��������Ҫ��������ʼСʱ(����������,��ͷΪ0Ҳ����)"));
        char min2[3];
        InputBox(min2, 11, _T("��������Ҫ��������ʼ����(����������,��ͷΪ0Ҳ����)"));
        strcpy(time2, year2);
        strcpy((time2 + 4), "��");//4,5�±�Ϊ������
        strcpy(time2 + 6, month2);
        strcpy((time2 + 8), "��");//8 9�±�Ϊ������
        strcpy(time2 + 10, day2);
        strcpy((time2 + 12), "��");//12 13�±�Ϊ������
        strcpy(time2 + 14, hour2);
        strcpy((time2 + 16), "ʱ");//16 17Ϊ����ʱ
        strcpy(time2 + 18, min2);
        strcpy((time2 + 20), "��");//20 21Ϊ���ַ�
        time2[22] = '\0';
        if (Time_compare(time1, time2) >= 0)
        {
            MessageBox(NULL, _T("���������ʼʱ����ڻ��ߴ�����ֹʱ�䣬��������"), _T("��ʱ���ѯ"), MB_SETFOREGROUND);
            return;
        }
        Pcs_Node* p = head;
        int flag = 0;//�ж���û�ҵ�
        while (p != NULL)
        {
            if (Time_compare(p->time, time1) >= 0 && Time_compare(p->time, time2) <= 0)
            {
                outtextxy(474, position_y, p->time);//��ʾ����ʱ��
                outtextxy(740, position_y, p->drink);//������Ʒ����
                outtextxy(980, position_y, p->num);//��������
                outtextxy(1060, position_y, p->cost);//�ɱ�
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("�����¼�����ڣ�"), _T("��ѯ�����¼"), MB_SETFOREGROUND);
            return;
        }
        MessageBox(NULL, _T("��ѯ�ɹ���"), _T("��ѯ�����¼"), MB_SETFOREGROUND);
        return;
    }
    else
    {
        MessageBox(NULL, _T("������������"), _T("��ѯ�����¼"), MB_SETFOREGROUND);
    }
    return;
}

void Purchase_save(Pcs_Node* head)
{
    FILE* fp = fopen("Purchase.txt", "w+");
    Pcs_Node* p = head;
    while (p != NULL)
    {
        fprintf(fp, "%s %s %s %s\n", p->time, p->drink, p->num, p->cost);
        p = p->next;
    }
    fclose(fp);
}

void Purchase_free(Pcs_Node* head)//�ͷ�����ռ�
{
    Pcs_Node* p;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    return;
}
