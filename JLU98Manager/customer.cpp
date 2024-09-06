#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"customer.h"
#include<string.h>
#include<windows.h>
#include"char2int.h"
#include"Fuzzy_search.h"
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<Windows.h>
#include<time.h>
//�����˿�����
Cst_Node* Customer_build()
{
    Cst_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Customer.txt", "r");
    if (fp == NULL||feof(fp))//���ļ�Ϊ�գ��˿���Ϣ������
    {
        MessageBox(NULL, _T("�ļ�Ϊ�գ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return NULL;
    }
    else
    {
        //������ͷ��Ϣ��ʼ��
        head = (Cst_Node*)malloc(sizeof(Cst_Node));
        head->next = NULL;
        fscanf(fp, "%s %s %s %s %s %s\n", head->money, head->name, head->phone, head->num, head->sex, head->Isvip);
        tmp = head;
        while (!feof(fp))//��������������,ֱ���ļ�����
        {
            p = (Cst_Node*)malloc(sizeof(Cst_Node));
            fscanf(fp, "%s %s %s %s %s %s\n", p->money, p->name, p->phone, p->num, p->sex, p->Isvip);
            //������ѽ��ﵽ��1000�����ϣ���ΪVIP�û�
            if (Char_to_int(p->money) > 1000) strcpy(p->Isvip, "��");
            else strcpy(p->Isvip, "����");
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
//�ͷ�����ռ�
void Customer_free(Cst_Node* head)
{
    Cst_Node* p;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    return;
}
//չʾ�˿���Ϣ
void Customer_show(Cst_Node* head,int* page)
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("�˿���Ϣ�����ڣ�"), _T("VIPչʾ"), MB_SETFOREGROUND);
        return;
    }
    Cst_Node* p = head;
    Cst_Node* p1 = head;
    int count1 = 1;
    while (p1 != NULL)
    {
        p1 = p1->next;
        count1++;
    }
    if (*page < 1) *page = 1;
    if (*page > (count1 / 20) + 1) *page = (count1 / 20) + 1;
    int en = *page * 20,st=en-20+1;
    int count = 1;
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    //��ʾ���й˿���Ϣ
    outtextxy(position_x, position_y, _T("���    ����      �Ա�    �绰��      ���ѽ��     �Ƿ�ΪVIP"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {
        if (count >= st && count <= en)
        {
            outtextxy(494, position_y, p->num);//��ʾ���
            outtextxy(556, position_y, p->name);//����
            outtextxy(676, position_y, p->sex);//�Ա�
            outtextxy(730, position_y, p->phone);//�绰��
            outtextxy(870, position_y, p->money);//���ѽ��
            outtextxy(1016, position_y, p->Isvip);//VIP
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
void Customer_showvip(Cst_Node* head,int *page)
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("�˿���Ϣ�����ڣ�"), _T("VIPչʾ"), MB_SETFOREGROUND);
        return;
    }
    Cst_Node* p = head;
    Cst_Node* p1 = head;
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
    outtextxy(position_x, position_y, _T("���    ����      �Ա�    �绰��      ���ѽ��     �Ƿ�ΪVIP"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {
        if (strcmp(p->Isvip,"��")==0&& count >= st && count <= en)
        {
            outtextxy(494, position_y, p->num);//��ʾ���
            outtextxy(556, position_y, p->name);//����
            outtextxy(676, position_y, p->sex);//�Ա�
            outtextxy(730, position_y, p->phone);//�绰��
            outtextxy(870, position_y, p->money);//���ѽ��
            outtextxy(1016, position_y, p->Isvip);//VIP
            position_y += 20;
        }
        p = p->next;
    }
    return;
}
//���ӹ˿���Ϣ
Cst_Node* Customer_add(Cst_Node* head)
{
    Cst_Node* p;
    p = (Cst_Node*)malloc(sizeof(Cst_Node));
    //����ͻ���Ϣ
    InputBox(p->num, 11, _T("������ͻ����"));//�ͻ���� 
    InputBox(p->name, 11, _T("������ͻ�����"));//�ͻ�����
    InputBox(p->money, 11, _T("������ͻ��ۼ����ѽ��"));//�ۼ����ѽ��
    if (Char_to_int(p->money) > 50000)
    {
        strcpy(p->Isvip, "��");
    }
    else
        strcpy(p->Isvip, "����");
    InputBox(p->sex, 11, _T("������ͻ��Ա�"));//�ͻ��Ա� 
    InputBox(p->phone, 15, _T("������ͻ��绰����"));//�ͻ��绰����
    //��ӿͻ���Ϣ
    Cst_Node* p0 = head;
    if (head == NULL)
    {
        head = p;
        head->next = NULL;
    }
    else {
        while (p0 != NULL)//�ж��Ƿ��ظ����
        {
            if (strcmp(p->num, p0->num) == 0)
            {
                MessageBox(NULL, _T("������ظ������ʧ�ܣ�"), _T("��ӹ˿�"), MB_SETFOREGROUND);
                return head;
            }
            p0 = p0->next;
        }
        p0 = head;
        while (p0->next != NULL)
        {
            p0 = p0->next;
        }
        p0->next = p;
        p->next = NULL;

    }
    MessageBox(NULL, _T("�趨�ɹ���"), _T("��ӹ˿�"), MB_SETFOREGROUND);
    return head;
}
//�޸Ĺ˿���Ϣ
Cst_Node* Customer_change(Cst_Node* head)
{
    //����Ҫ�޸Ĺ˿͵ı��
    MessageBox(NULL, _T("������Ҫ�޸ĵĹ˿���Ϣ��"), _T("�޸Ĺ˿�"), MB_SETFOREGROUND);
    bool f=Customer_search(head);
    if (f)
    {
        char choice[10];
        InputBox(choice, 11, _T("����Ҫ�޸ĵı��"));
        Cst_Node* p = head; int flag = 0;
        while (p != NULL)
        {
            if (strcmp(p->num, choice) == 0)//��ѯ���˴˱�Ź˿�
            {
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag == 0)//�˹˿Ͳ�����
        {
            MessageBox(NULL, _T("�˱���û������ڣ�"), _T("�޸Ĺ˿�"), MB_SETFOREGROUND);
            return head;
        }
        //�޸Ŀͻ���Ϣ
        InputBox(p->name, 11, _T("����Ҫ�޸ĵĿͻ�����"));
        InputBox(p->money, 11, _T("����Ҫ�޸ĵĿͻ��ۼ����ѽ��"));
        if (Char_to_int(p->money) >50000)
        {
            strcpy(p->Isvip, "��");
        }
        else strcpy(p->Isvip, "����");
        InputBox(p->sex, 11, _T("����Ҫ�޸ĵĿͻ��Ա�"));
        InputBox(p->phone, 15, _T("����Ҫ�޸ĵĿͻ��绰����"));
        MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸Ĺ˿�"), MB_SETFOREGROUND);
        return head;
    }  
}
//��������Ϣ���浽�ļ�����
void Customer_save(Cst_Node* head)
{

    if (head == NULL)
    {
        remove("Customer.txt");
        return;
    }
    FILE* fp = fopen("Customer.txt", "w+");
    St_Cst temp;
    Cst_Node* p = head;
    while (p != NULL)
    {
        fprintf(fp, "%s %s %s %s %s %s\n", p->money, p->name, p->phone, p->num, p->sex, p->Isvip);
        p = p->next;
    }
    fclose(fp);
}

bool Customer_search(Cst_Node* head)//�����˿���Ϣ
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("�˿���Ϣ�����ڣ�"), _T("�����˿�"), MB_SETFOREGROUND);
        return false;
    }
    char choice[20];//ѡ���ѯ��ʽ
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("���    ����      �Ա�    �绰��      ���ѽ��     �Ƿ�ΪVIP"));//��ʾ����һ�б�ͷ
    position_y += 20;
    InputBox(choice, 11, _T("ѡ���ѯ��ʽ:1.�ؼ��ֲ���(������) 2.��Ų���"));//ѡ���ѯ��ʽ 
    if (strcmp(choice,"1")==0)//���չؼ��ֲ���
    {
        Cst_Node* p = head;
        char key[20];
        InputBox(key, 11, _T("����ؼ���"));
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->name))
            {
                outtextxy(494, position_y, p->num);//��ʾ���
                outtextxy(556, position_y, p->name);//����
                outtextxy(676, position_y, p->sex);//�Ա�
                outtextxy(730, position_y, p->phone);//�绰��
                outtextxy(870, position_y, p->money);//���ѽ��
                outtextxy(1016, position_y, p->Isvip);//VIP
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("�˿���Ϣ�����ڣ�"), _T("�����˿�"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("�����˿�"), MB_SETFOREGROUND);
        return true;
    }
    else if (strcmp(choice, "2")==0)
    {
        char key[10];
        InputBox(key, 11, _T("������"));
        Cst_Node* p = head;
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (strcmp(key, p->num) == 0)
            {
                outtextxy(494, position_y, p->num);//��ʾ���
                outtextxy(556, position_y, p->name);//����
                outtextxy(676, position_y, p->sex);//�Ա�
                outtextxy(730, position_y, p->phone);//�绰��
                outtextxy(870, position_y, p->money);//���ѽ��
                outtextxy(1016, position_y, p->Isvip);//VIP
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("�˿���Ϣ�����ڣ�"), _T("�����˿�"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("�����˿�"), MB_SETFOREGROUND);
        return true;
    }
    else
    {
        MessageBox(NULL, _T("��������"), _T("�����˿�"), MB_SETFOREGROUND);
        Customer_search(head);
        return false;
    }
}

Cst_Node* Customer_delete(Cst_Node* head)//ɾ���˿���Ϣ
{
    //����Ҫɾ���˿͵ı��
    MessageBox(NULL, _T("������Ҫɾ���Ĺ˿���Ϣ"), _T("ɾ���˿�"), MB_SETFOREGROUND);
    bool f=Customer_search(head);
    if(f)
    {
        char choice[10];
        InputBox(choice, 11, _T("����Ҫɾ���ı��"));
        Cst_Node* p = head; int flag = 0;
        Cst_Node* p0 = head;
        while (p != NULL)
        {
            if (strcmp(p->num, choice) == 0)//��ѯ���˴˱�Ź˿�
            {
                flag = 1;
                break;
            }
            p0 = p;
            p = p->next;
        }
        if (flag == 0)//�˹˿Ͳ�����
        {
            MessageBox(NULL, _T("�˱���û������ڣ�"), _T("�޸Ĺ˿�"), MB_SETFOREGROUND);
            return head;
        }
        //�޸Ŀͻ���Ϣ
        if (p->next == NULL)//���ɾ���˿���β�ڵ�
        {
            if (p == head)
            {
                free(p);
                p = NULL;
                p0->next = NULL;
                head = NULL;
            }
            free(p);
            p = NULL;
            p0->next = NULL;
        }
        else
        {
            p0->next = p->next;
            free(p);
            p = NULL;
        }
        MessageBox(NULL, _T("ɾ���ɹ�"), _T("ɾ���˿�"), MB_SETFOREGROUND);
        return head;
    }
}
