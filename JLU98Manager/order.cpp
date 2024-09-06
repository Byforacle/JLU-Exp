#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"char2int.h"
#include"Fuzzy_search.h"
#include"Time.h"
#include"customer.h"
#include"Storage.h"
#include"order.h"
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<time.h>

Odr_Node* Order_build()//����������¼����
{
    Odr_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Order.txt", "r");
    if (fp == NULL||feof(fp))//���ļ�Ϊ�գ�������¼������
    {
        MessageBox(NULL, _T("������¼�ļ�Ϊ��"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return NULL; 
    }
    else
    {
        //������ͷ��Ϣ��ʼ��
        head = (Odr_Node*)malloc(sizeof(Odr_Node));
        fscanf(fp, "%s %s %s %s %s %s %s %s\n", head->time, head->customer, head->cst_num, head->drink, head->srg_num, head->num, head->Sale_volume, head->profit);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//��������������,ֱ���ļ�����
        {
            p = (Odr_Node*)malloc(sizeof(Odr_Node));
            fscanf(fp, "%s %s %s %s %s %s %s %s\n", p->time, p->customer, p->cst_num, p->drink, p->srg_num, p->num, p->Sale_volume, p->profit);
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
void Order_show(Odr_Node* head,int *page)//չʾ������¼
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("������¼������"), _T("չʾ������¼"), MB_SETFOREGROUND);
        return;
    }
    Odr_Node* p = head;
    Odr_Node* p1 = head;
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
    int position_x = 410;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("����ʱ��                ����˿� �˿ͱ��   ������Ʒ����    ��Ʒ��� �������� ���۶�   ����"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {
        if (count >= st && count <= en)
        {
            outtextxy(412, position_y, p->time);//��ʾ����ʱ��
            outtextxy(665, position_y, p->customer);//����˿�
            outtextxy(775, position_y, p->cst_num);//�˿ͱ��
            outtextxy(850, position_y, p->drink);//��Ʒ����
            outtextxy(1030, position_y, p->srg_num);//��Ʒ�����
            outtextxy(1130, position_y, p->num);//��������
            outtextxy(1200, position_y, p->Sale_volume);//���۶�
            outtextxy(1280, position_y, p->profit);//����
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
void Order_income(Odr_Node* head,int *page)//չʾ����
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("������¼������"), _T("չʾ������¼"), MB_SETFOREGROUND);
        return;
    }
    Odr_Node* p = head;
    Odr_Node* p1 = head;
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
    outtextxy(position_x, position_y, _T("����ʱ��                 ���۶�    ����"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {
        if (count >= st && count <= en)
        {
            outtextxy(474, position_y, p->time);//��ʾ����ʱ��
            outtextxy(740, position_y, p->Sale_volume);//���۶�
            outtextxy(840, position_y, p->profit);//����
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
Odr_Node* Order_deal(Odr_Node* head)//����ǰ����
{
    if (head == NULL)//���ͷ�ڵ�Ϊ��
    {
        head = (Odr_Node*)malloc(sizeof(Odr_Node));
        //����ͻ���Ϣ
        strcpy(head->time, Time_now());
        //InputBox(head->customer, 11, _T("������ͻ�����"));//�ͻ�����
        InputBox(head->cst_num, 11, _T("������ͻ����"));//�ͻ����
        InputBox(head->srg_num, 11, _T("�����빺�����Ʒ���"));//�������Ʒ���
        InputBox(head->num, 11, _T("�����빺������"));//��������
        /*�жϿ���Ƿ����*/
        Srg_Node* sghead = Storage_build();//�����˿�����
        Srg_Node* p1 = sghead;
        int flag1 = 0;
        while (p1 != NULL)
        {
            if (strcmp(p1->Num, head->srg_num) == 0)
            {
                flag1 = 1;
                break;
            }
            p1 = p1->next;
        }
        if (flag1 == 0)//�����ڴ˱�ſ��
        {
            MessageBox(NULL, _T("�����ڴ˱�ſ�棬��������ʧ�ܣ�"), _T("��������"), MB_SETFOREGROUND);
            return head;
        }
        if (Char_to_int(p1->complete_num) < Char_to_int(head->num))//��治��ʱ
        {
            MessageBox(NULL, _T("��治�㣬��������ʧ�ܣ�"), _T("��������"), MB_SETFOREGROUND);
            return head;
        }
        strcpy(head->drink, p1->name);//������ľ�ˮ����ŵ�������¼��
        //�ж��Ƿ������ǰ�˿�
        Cst_Node* cshead = Customer_build();//�����˿�����
        Cst_Node* p2 = cshead; Cst_Node* p5 = p2;
        int flag2 = 0;
        while (p2 != NULL)
        {
            if (strcmp(p2->num, head->cst_num) == 0)
            {
                flag2 = 1;
                strcpy(head->customer,p2->name);
                break;
            }
            p5 = p2;
            p2 = p2->next;
        }
        if (flag2 == 0)//�����ڴ˱�Ź˿ͣ��½�һ���˿�
        {
            MessageBox(NULL, _T("�˹˿�Ϊ�¹˿ͣ��벹ȫ�¹˿���Ϣ��"), _T("��������"), MB_SETFOREGROUND);
            Cst_Node* p3 = (Cst_Node*)malloc(sizeof(Cst_Node));
            strcpy(p3->num, head->cst_num);
            InputBox(p3->name, 11, _T("������ͻ�����"));//�ͻ�����
            strcpy(head->customer, p3->name);
            InputBox(p3->phone, 20, _T("�������¹˿͵绰����"));//�¹˿͵绰����
            InputBox(p3->sex, 11, _T("�������¹˿��Ա�"));//�¹˿��Ա�
            strcpy(p3->money, Int_to_char(Char_to_int(head->num) * Char_to_int(p1->price)));//�˿����ѽ��
            if (Char_to_int(p3->money) > 50000)
            {
                strcpy(p3->Isvip, "��");

            }
            else strcpy(p3->Isvip, "����");
            p5->next = p3;
            p3->next = NULL;
            p2 = p3;//��p2ָ��p3�������������
            MessageBox(NULL, _T("����¹˿���Ϣ�ɹ���"), _T("��������"), MB_SETFOREGROUND);
        }
        //�˹˿ʹ���ʱ���޸������ۼ����ѽ��
        if (strcmp(p2->Isvip, "����") == 0)//����˿Ͳ���VIP
        {
            strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + Char_to_int(head->num) * Char_to_int(p1->price)));
            strcpy(head->Sale_volume, Int_to_char(Char_to_int(head->num) * Char_to_int(p1->price)));//�����۶�洢
            if (Char_to_int(p2->money) > 50000)//�ٴ��ж��Ƿ�ﵽ��ΪVIP������
            {
                strcpy(p2->Isvip, "��");
            }
            else strcpy(p2->Isvip, "����");
            //���Ŀ����Ϣ
            strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(head->num)));
            //����Ӫ�ʽ��ʽ��޸�
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money += Char_to_int(head->num) * Char_to_int(p1->price);
            strcpy(head->profit, Int_to_char(Char_to_int(head->num) * (Char_to_int(p1->price) - Char_to_int(p1->cost_price))));//���������
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
        }
        else//�����VIP����������Ʒ����۲������������Ʒ��Ϊ��Ʒ����
        {
            MessageBox(NULL, _T("���ڸù˿���VIP�û�����Ʒ���ܾ����ۿ۲�������覴õ���Ʒ!"), _T("��������"), MB_SETFOREGROUND);
            strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)))));
            strcpy(head->Sale_volume, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)))));//�����۶�洢
            //���Ŀ����Ϣ
            strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(head->num)));
            strcpy(p1->loss_num, "0");
            //����Ӫ�ʽ��ʽ��޸�
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money += (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)));
            strcpy(head->profit, Int_to_char((int)(0.5 + (Char_to_int(head->num) * (Char_to_int(p1->price) * 0.9 - Char_to_int(p1->cost_price))))));//��������
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
        }
        Storage_save(sghead);//��������Ϣ���浽�ļ�����
        Storage_free(sghead);//�ͷ������ڴ�ռ�
        Customer_save(cshead);//��������Ϣ���浽�ļ�����
        Customer_free(cshead);//�ͷ������ڴ�ռ�
        MessageBox(NULL, _T("��������ɹ�!"), _T("��������"), MB_SETFOREGROUND);
        head->next = NULL;
        return head;
    }
    Odr_Node* p, * p0;
    p0 = p = head;
    while (p != NULL)
    {
        p0 = p;
        p = p->next;
    }
    p = (Odr_Node*)malloc(sizeof(Odr_Node));
    //����ͻ���Ϣ
    strcpy(p->time, Time_now());
    //InputBox(p->customer, 11, _T("������ͻ�����"));//�ͻ�����
    InputBox(p->cst_num, 11, _T("������ͻ����"));//�ͻ����
    InputBox(p->srg_num, 11, _T("�����빺�����Ʒ���"));//�������Ʒ���
    InputBox(p->num, 11, _T("�����빺������"));//��������
    /*�жϿ���Ƿ����*/
    Srg_Node* sghead = Storage_build();//�����������
    Srg_Node* p1 = sghead;
    int flag1 = 0;
    while (p1 != NULL)
    {
        if (strcmp(p1->Num, p->srg_num) == 0)
        {
            flag1 = 1;
            break;
        }
        p1 = p1->next;
    }
    if (flag1 == 0)//�����ڴ˱�ſ��
    {
        MessageBox(NULL, _T("�����ڴ˱�ſ�棬��������ʧ�ܣ�"), _T("��������"), MB_SETFOREGROUND);
        return head;
    }
    strcpy(p->drink, p1->name);//������Ŀ���¼��ŵ�������¼��
    if (Char_to_int(p1->complete_num) < Char_to_int(p->num))//��治��ʱ
    {
        MessageBox(NULL, _T("��治�㣬��������ʧ�ܣ�"), _T("��������"), MB_SETFOREGROUND);
        return head;
    }
    //�ж��Ƿ������ǰ�˿�
    Cst_Node* cshead = Customer_build();//�����˿�����
    Cst_Node* p2 = cshead; Cst_Node* p5 = p2;
    int flag2 = 0;
    while (p2 != NULL)
    {
        if (strcmp(p2->num, p->cst_num) == 0)
        {
            flag2 = 1;
            strcpy(p->customer,p2->name);
            break;
        }
        p5 = p2;
        p2 = p2->next;
    }
    if (flag2 == 0)//�����ڴ˱�Ź˿ͣ��½�һ���˿�
    {
        MessageBox(NULL, _T("�˹˿�Ϊ�¹˿ͣ��벹ȫ�¹˿���Ϣ��"), _T("��������"), MB_SETFOREGROUND);
        Cst_Node* p3 = (Cst_Node*)malloc(sizeof(Cst_Node));
        if (cshead == NULL) cshead = p3;
        strcpy(p3->num, p->cst_num);
        InputBox(p3->name, 11, _T("������ͻ�����"));//�ͻ�����
        strcpy(p->customer, p3->name);
        InputBox(p3->phone, 20, _T("�������¹˿͵绰����"));
        InputBox(p3->sex, 11, _T("�������¹˿��Ա�"));
        strcpy(p3->money, Int_to_char(Char_to_int(p->num) * Char_to_int(p1->price)));//�˿����ѽ��
        if (Char_to_int(p3->money) > 50000)
        {
            strcpy(p3->Isvip, "��");

        }
        else strcpy(p3->Isvip, "����");
        p5->next = p3;
        p3->next = NULL;
        p2 = p3;//��p2ָ��p3�������������
        MessageBox(NULL, _T("����¹˿���Ϣ�ɹ���"), _T("��������"), MB_SETFOREGROUND);
    }
    //�˹˿ʹ���ʱ���޸������ۼ����ѽ��
    if (strcmp(p2->Isvip, "����") == 0)//����˿Ͳ���VIP
    {
        strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + Char_to_int(p->num) * Char_to_int(p1->price)));
        strcpy(p->Sale_volume, Int_to_char(Char_to_int(p->num) * Char_to_int(p1->price)));//�����۶�洢
        if (Char_to_int(p2->money) > 50000)//�ٴ��ж��Ƿ�ﵽ��ΪVIP������
        {
            strcpy(p2->Isvip, "��");
        }
        else strcpy(p2->Isvip, "����");
        //���Ŀ����Ϣ
        strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(p->num)));
        //����Ӫ�ʽ��ʽ��޸�
        FILE* fp1 = fopen("Amount.txt", "r");
        int money;
        fscanf(fp1, "%d", &money);
        money += Char_to_int(p->num) * Char_to_int(p1->price);
        strcpy(p->profit, Int_to_char(Char_to_int(p->num) * (Char_to_int(p1->price) - Char_to_int(p1->cost_price))));//���������
        fclose(fp1);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
    }
    else//�����VIP����������Ʒ����۲������������Ʒ��Ϊ��Ʒ����
    {
        MessageBox(NULL, _T("���ڸù˿���VIP�û�����Ʒ���ܾ����ۿ۲�������覴õ���Ʒ!"), _T("��������"), MB_SETFOREGROUND);
        strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)))));
        strcpy(p->Sale_volume, Int_to_char((int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)))));//�����۶�洢
        //���Ŀ����Ϣ
        strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(p->num)));
        strcpy(p1->loss_num, "0");
        //����Ӫ�ʽ��ʽ��޸�
        FILE* fp1 = fopen("Amount.txt", "r");
        int money;
        fscanf(fp1, "%d", &money);
        money += (int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)));
        strcpy(p->profit, Int_to_char((int)(0.5 + (Char_to_int(p->num) * (Char_to_int(p1->price) * 0.9 - Char_to_int(p1->cost_price))))));//��������
        fclose(fp1);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
    }
    p0->next = p;//���˼�¼��������
    p->next = NULL;
    Storage_save(sghead);//��������Ϣ���浽�ļ�����
    Storage_free(sghead);//�ͷ������ڴ�ռ�
    Customer_save(cshead);//��������Ϣ���浽�ļ�����
    Customer_free(cshead);//�ͷ������ڴ�ռ�
    MessageBox(NULL, _T("��������ɹ���"), _T("��������"), MB_SETFOREGROUND);
    return head;
}
void Order_search(Odr_Node* head)//��ѯ������¼
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("������¼������"), _T("��ѯ������¼"), MB_SETFOREGROUND);
        return;
    }
    Odr_Node* p = head;
    int position_x = 410;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("����ʱ��                ����˿� �˿ͱ��   ������Ʒ����    ��Ʒ��� �������� ���۶�   ����"));//��ʾ����һ�б�ͷ
    position_y += 20;
    char choice[10];
    InputBox(choice, 11, _T("����������ѡ���������ʽ��1��������Ʒ�ؼ���    2�����չ���ʱ�䷶Χ"));
    if (strcmp(choice, "1") == 0)
    {
        char key[20];
        InputBox(key, 11, _T("�����빺�����Ʒ�ؼ���"));//��Ʒ�ؼ���
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->drink))
            {
                outtextxy(412, position_y, p->time);//��ʾ����ʱ��
                outtextxy(665, position_y, p->customer);//����˿�
                outtextxy(775, position_y, p->cst_num);//�˿ͱ��
                outtextxy(850, position_y, p->drink);//��Ʒ����
                outtextxy(1030, position_y, p->srg_num);//��Ʒ�����
                outtextxy(1130, position_y, p->num);//��������
                outtextxy(1200, position_y, p->Sale_volume);//���۶�
                outtextxy(1280, position_y, p->profit);//����
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("δ�ܲ�ѯ����ض�����¼��"), _T("��ѯ������¼"), MB_SETFOREGROUND);
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("��ѯ������¼"), MB_SETFOREGROUND);
        return;
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
        Odr_Node* p = head;
        int flag = 0;//�ж���û�ҵ�
        while (p != NULL)
        {
            if (Time_compare(p->time, time1) >= 0 && Time_compare(p->time, time2) <= 0)
            {
                outtextxy(412, position_y, p->time);//��ʾ����ʱ��
                outtextxy(665, position_y, p->customer);//����˿�
                outtextxy(775, position_y, p->cst_num);//�˿ͱ��
                outtextxy(850, position_y, p->drink);//��Ʒ����
                outtextxy(1030, position_y, p->srg_num);//��Ʒ�����
                outtextxy(1130, position_y, p->num);//��������
                outtextxy(1200, position_y, p->Sale_volume);//���۶�
                outtextxy(1280, position_y, p->profit);//����
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
//��������Ϣ���浽�ļ�����
void Order_save(Odr_Node* head)
{
    FILE* fp = fopen("Order.txt", "w");
    Odr_Node* p = head;
    while (p != NULL)
    {
        fprintf(fp, "%s %s %s %s %s %s %s %s\n", p->time, p->customer, p->cst_num, p->drink, p->srg_num, p->num, p->Sale_volume, p->profit);
        p = p->next;
    }
    fclose(fp);
}
void Order_free(Odr_Node* head)//�ͷ�����ռ�
{
    Odr_Node* p;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    return;
}