#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Storage.h"
#include"char2int.h"
#include"Fuzzy_search.h"
#include"Purchase.h"
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<easyx.h>
#include<Windows.h>
#include"Time.h"
//�����������
Srg_Node* Storage_build()
{
    Srg_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Storage.txt", "r");
    if (fp == NULL || feof(fp))//���ļ�Ϊ�գ���ˮ��Ϣ������
    {
        MessageBox(NULL, _T("����ļ�Ϊ�գ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return NULL;
    }
    else
    {
        //������ͷ��Ϣ¼��
        head = (Srg_Node*)malloc(sizeof(Srg_Node));//������ͷ��Ϣ��ʼ��
        fscanf(fp, " %s %s %s %s %s %s %s %s\n", head->Num, head->name, head->complete_num, head->loss_num, head->price, head->cost_price, head->Unit_capacity, head->Package_size);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//��������������,ֱ���ļ�����
        {
            p = (Srg_Node*)malloc(sizeof(Srg_Node));
            fscanf(fp, "%s %s %s %s %s %s %s %s \n", p->Num, p->name, p->complete_num, p->loss_num, p->price, p->cost_price, p->Unit_capacity, p->Package_size);
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
void Storage_save(Storage_Node* head)//��������Ϣ���浽�ļ�����
{
    if (head == NULL)
    {
        remove("CStorage.txt");
        return;
    }
    FILE* fp = fopen("Storage.txt", "w+");
    Srg_Node* p = head;
    while (p != NULL)
    {
        fprintf(fp, "%s %s %s %s %s %s %s %s\n", p->Num, p->name, p->complete_num, p->loss_num, p->price, p->cost_price, p->Unit_capacity, p->Package_size);
        p = p->next;
    }
    fclose(fp);
}
//�ͷ�����ռ�
void Storage_free(Srg_Node* head)
{
    Srg_Node* p;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        free(p);
    }
    return;
}
void Storage_show(Srg_Node* head,int* page)
{
    if (head == NULL)//�������ͷ��
    {
        MessageBox(NULL, _T("���Ϊ�գ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return;
    }
    Srg_Node* p = head;
    Srg_Node* p1 = head;
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
    outtextxy(position_x, position_y, _T("���  ��Ʒ��     �����Ŀ  �����Ŀ  �ۼ�  �ɱ�  ��λ����    ��װ��С"));//��ʾ����һ�б�ͷ
    position_y += 20;
    while (p != NULL)//��ӡ��������
    {
        if (count >= st && count <= en)
        {
            outtextxy(494, position_y, p->Num);//��ʾ���
            outtextxy(530, position_y, p->name);//����
            outtextxy(650, position_y, p->complete_num);//�����Ŀ
            outtextxy(780, position_y, p->loss_num);//�����Ŀ
            outtextxy(840, position_y, p->price);//�ۼ�
            outtextxy(920, position_y, p->cost_price);//�ɱ�
            outtextxy(1000, position_y, p->Unit_capacity);//��λ����
            outtextxy(1080, position_y, p->Package_size);//��װ��С
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
Srg_Node* Storage_add(Srg_Node* head)//������
{
    if (head == NULL)//���ͷ�ڵ�Ϊ��
    {
        head = (Srg_Node*)malloc(sizeof(Srg_Node));
        head->next = NULL;
        //����ͻ���Ϣ
        InputBox(head->Num, 11, _T("��������"));//��� 
        InputBox(head->name, 11, _T("��������Ʒ��"));//��Ʒ
        InputBox(head->complete_num, 11, _T("��������Ʒ��������"));//��Ʒ��������
        InputBox(head->loss_num, 11, _T("��������Ʒ�������"));//��Ʒ������� 
        InputBox(head->price, 11, _T("��������Ʒ�ۼۣ������밢�������֣�"));//��Ʒ�ۼ�
        InputBox(head->cost_price, 11, _T("��������Ʒ�ɱ��������밢�������֣�"));//��Ʒ�ɱ�
        InputBox(head->Unit_capacity, 11, _T("�����뵥λ����"));//��λ����
        InputBox(head->Package_size, 11, _T("��������Ʒ��װ��С"));//��Ʒ��װ��С
        MessageBox(NULL, _T("��ӳɹ���"), _T("��ӿ��"), MB_SETFOREGROUND);
        //��������¼���浽������
        Pcs_Node* pchead = Purchase_build();
        Pcs_Node* pre = pchead;
        Pcs_Node* p1 = (Pcs_Node*)malloc(sizeof(Pcs_Node));
        if (pchead == NULL)
        {
            pchead = p1;
            p1->next = NULL;
        }
        else
        {
            while (pre->next != NULL)
            {
                pre = pre->next;
            }
            pre->next = p1;
            p1->next = NULL;
        }
        strcpy(p1->time,Time_now());
        strcpy(p1->drink, head->name);
        strcpy(p1->num, Int_to_char((Char_to_int(head->complete_num) + Char_to_int(head->loss_num))));
        strcpy(p1->cost, head->cost_price);
        //����Ӫ�ʽ��ʽ��޸�
        FILE* fp = fopen("Amount.txt", "r");
        int money;
        fscanf(fp, "%d", &money);
        money -= (Char_to_int(p1->num) * Char_to_int(p1->cost));
        fclose(fp);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
        //�������¼����
        Purchase_save(pchead);//��������Ϣ���浽�ļ�����
        Purchase_free(pchead);//�ͷ������ڴ�ռ�
        return head;
    }

    Srg_Node* p, * p0 = head;
    p = (Srg_Node*)malloc(sizeof(Srg_Node));
    //��������Ϣ
    InputBox(p->Num, 11, _T("��������"));//��� 
    while (p0 != NULL)//�ж��Ƿ��ظ����
    {
        if (strcmp(p->Num, p0->Num) == 0)
        {
            MessageBox(NULL, _T("�Ѵ��ڴ˱����Ʒ�����ڴ˱���Ͻ��й���"), _T("��ӿ��"), MB_SETFOREGROUND);
            char addcomplete[20] ;
            char addloss[20];
            InputBox(addcomplete, 11, _T("��������Ʒ��������"));//��Ʒ��������
            InputBox(addloss, 11, _T("��������Ʒ�������"));//��Ʒ������� 
            
            //��������¼���浽������
            Pcs_Node* pchead = Purchase_build();
            Pcs_Node* p2 = pchead;
            while (p2->next != NULL)
            {
                p2 = p2->next;
            }
            Pcs_Node* p3 = (Pcs_Node*)malloc(sizeof(Pcs_Node));
            strcpy(p3->time, Time_now());//ʱ��
            strcpy(p3->drink, p0->name);//��Ʒ��
            strcpy(p3->num, Int_to_char((Char_to_int(addcomplete) + Char_to_int(addloss))));//���������
            strcpy(p3->cost, p0->cost_price);//�ɱ�
            p2->next = p3;
            p3->next = NULL;
            //�޸Ŀ�������е�����
            strcpy(p0->complete_num, Int_to_char(Char_to_int(addcomplete)+ Char_to_int(p0->complete_num)));
            strcpy(p0->loss_num , Int_to_char(Char_to_int(addloss) + Char_to_int(p0->loss_num)));
            //����Ӫ�ʽ��ʽ��޸�
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money -= (Char_to_int(p3->num) * Char_to_int(p3->cost));
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
            //�������¼����
            Purchase_save(pchead);//��������Ϣ���浽�ļ�����
            Purchase_free(pchead);//�ͷ������ڴ�ռ�
            MessageBox(NULL, _T("��ӳɹ���"), _T("��ӿ��"), MB_SETFOREGROUND);
            return head;
        }
        p0 = p0->next;
    }
    p0 = head;
    InputBox(p->name, 11, _T("��������Ʒ��"));//��Ʒ
    InputBox(p->complete_num, 11, _T("��������Ʒ��������"));//��Ʒ��������
    InputBox(p->loss_num, 11, _T("��������Ʒ�������"));//��Ʒ������� 
    InputBox(p->price, 11, _T("��������Ʒ�ۼۣ������밢�������֣�"));//��Ʒ�ۼ�
    InputBox(p->cost_price, 11, _T("��������Ʒ�ɱ��������밢�������֣�"));//��Ʒ�ɱ�
    InputBox(p->Unit_capacity, 11, _T("�����뵥λ����"));//��λ����
    InputBox(p->Package_size, 11, _T("��������Ʒ��װ��С"));//��Ʒ��װ��С
    while (p0 != NULL)//�ж��Ƿ��ظ����
    {
        if (strcmp(p->name, p0->name) == 0 && strcmp(p->cost_price, p0->cost_price) == 0 && strcmp(p->Package_size, p0->Package_size) == 0 && strcmp(p->price, p0->price) == 0 && strcmp(p->Unit_capacity, p0->Unit_capacity) == 0)
        {
            MessageBox(NULL, _T("�Ѵ�����ͬ��棬���ʧ�ܣ�"), _T("��ӿ��"), MB_SETFOREGROUND);
            free(p);//�ͷ��ڴ�
            p = NULL;
            return head;
        }
        p0 = p0->next;
    }

    MessageBox(NULL, _T("��ӳɹ���"), _T("��ӿ��"), MB_SETFOREGROUND);
    Srg_Node* p1 = head;
    while (p1->next != NULL)
    {
        p1 = p1->next;
    }
    p1->next = p;
    p->next = NULL;
    //��������¼���浽������
    Pcs_Node* pchead = Purchase_build();
    Pcs_Node* p2 = (Pcs_Node*)malloc(sizeof(Pcs_Node));
    Pcs_Node* p3 = pchead;
    while (p3->next != NULL)
    {
        p3 = p3->next;
    }
    p3->next = p2;
    p2->next = NULL;
    strcpy(p2->time, Time_now());
    strcpy(p2->drink, p->name);
    strcpy(p2->num, Int_to_char((Char_to_int(p->complete_num) + Char_to_int(p->loss_num))));
    strcpy(p2->cost, p->cost_price);
    //����Ӫ�ʽ��ʽ��޸�
    FILE* fp = fopen("Amount.txt", "r");
    int money;
    fscanf(fp, "%d", &money);
    money -= (Char_to_int(p2->num) * Char_to_int(p2->cost));
    fclose(fp);
    FILE* fp1 = fopen("Amount.txt", "w");
    fprintf(fp1, "%d", money);
    fclose(fp1);
    //�������¼����
    Purchase_save(pchead);//��������Ϣ���浽�ļ�����
    Purchase_free(pchead);//�ͷ������ڴ�ռ�
    return head;
}
bool Storage_search(Srg_Node* head)//���������Ϣ
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("���Ϊ�գ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
        return false;
    }
    char choice[5];//ѡ���ѯ��ʽ
    int position_x = 476;//����š�������
    int position_y = 92;//����š�������
    setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
    settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
    settextstyle(20, 0, _T("����"));//���������С20����ʽ����
    outtextxy(position_x, position_y, _T("���  ��Ʒ��     �����Ŀ  �����Ŀ  �ۼ�  �ɱ�  ��λ����    ��װ��С"));//��ʾ����һ�б�ͷ
    position_y += 20;
    InputBox(choice, 11, _T("ѡ���ѯ��ʽ:1.�ؼ��ֲ���(������) 2.��Ų���"));//ѡ���ѯ��ʽ 
    if (strcmp(choice,"1")==0)//���չؼ��ֲ���
    {
        Srg_Node* p = head;
        char key[20];
        InputBox(key, 11, _T("����ؼ���"));
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->name))
            {
                outtextxy(494, position_y, p->Num);//��ʾ���
                outtextxy(530, position_y, p->name);//����
                outtextxy(650, position_y, p->complete_num);//�����Ŀ
                outtextxy(780, position_y, p->loss_num);//�����Ŀ
                outtextxy(840, position_y, p->price);//�ۼ�
                outtextxy(920, position_y, p->cost_price);//�ɱ�
                outtextxy(1000, position_y, p->Unit_capacity);//��λ����
                outtextxy(1080, position_y, p->Package_size);//��װ��С
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("����Ʒ�����ڣ�"), _T("��ѯ���"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("��ѯ���"), MB_SETFOREGROUND);
        return true;
    }
    else if (strcmp(choice, "2") == 0)
    {
        char key[10];
        InputBox(key, 11, _T("������"));
        Srg_Node* p = head;
        int flag = 0;//�ж��Ƿ���ҵ�
        while (p != NULL)
        {
            if (strcmp(key, p->Num) == 0)
            {
                outtextxy(494, position_y, p->Num);//��ʾ���
                outtextxy(530, position_y, p->name);//����
                outtextxy(650, position_y, p->complete_num);//�����Ŀ
                outtextxy(780, position_y, p->loss_num);//�����Ŀ
                outtextxy(840, position_y, p->price);//�ۼ�
                outtextxy(920, position_y, p->cost_price);//�ɱ�
                outtextxy(1000, position_y, p->Unit_capacity);//��λ����
                outtextxy(1080, position_y, p->Package_size);//��װ��С
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("����Ʒ�����ڣ�"), _T("��ѯ���"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("��ѯ�ɹ���"), _T("��ѯ���"), MB_SETFOREGROUND);
        return true;
    }
    else
    {
        MessageBox(NULL, _T("��������"), _T("�������"), MB_SETFOREGROUND);//��������
        Storage_search(head);
        return false;
    }
}
Srg_Node* Storage_delete(Srg_Node* head)//ɾ�����
{
    //����Ҫɾ�����ı��
    MessageBox(NULL, _T("������Ҫɾ���Ŀ����Ϣ��"), _T("ɾ�����"), MB_SETFOREGROUND);
    Storage_search(head);
    char choice[10];
    InputBox(choice, 11, _T("��������Ҫɾ���Ŀ����"));//����Ҫɾ���Ŀ����
    Srg_Node* p = head; int flag = 0;
    Srg_Node* p0 = head;
    while (p != NULL)
    {
        if (strcmp(p->Num, choice) == 0)//��ѯ���˴˱�Ź˿�
        {
            flag = 1;
            break;
        }
        p0 = p;
        p = p->next;
    }
    if (flag == 0)//�˿�治����
    {
        MessageBox(NULL, _T("�˱�ſ�治���ڣ�"), _T("ɾ�����"), MB_SETFOREGROUND);
        return head;
    }
    //�޸Ŀ����Ϣ
    if (p->next == NULL)//���ɾ�������β�ڵ�
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
    MessageBox(NULL, _T("ɾ���ɹ���"), _T("ɾ�����"), MB_SETFOREGROUND);
    return head;
}
Storage_Node* Storage_change(Storage_Node* head)//�޸Ŀ����Ϣ
{
    //����Ҫ�޸Ĺ˿͵ı��
    MessageBox(NULL, _T("������Ҫ�޸ĵĿ����Ϣ��"), _T("ɾ�����"), MB_SETFOREGROUND);
    bool f=Storage_search(head);
    if (f)
    {
        char choice[10];
        InputBox(choice, 11, _T("��������Ҫ�޸ĵĿ����"));//����Ҫ�޸ĵĿ����
        Srg_Node* p = head; int flag = 0;
        while (p != NULL)
        {
            if (strcmp(p->Num, choice) == 0)//��ѯ���˴˱�ſ��
            {
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag == 0)//�˿�治����
        {
            MessageBox(NULL, _T("�˱�ſ�治���ڣ�"), _T("�޸Ŀ��"), MB_SETFOREGROUND);
            return head;
        }
        //�޸Ŀ����Ϣ
        InputBox(p->name, 11, _T("�������޸ĺ���Ʒ��"));//��Ʒ
        InputBox(p->complete_num, 11, _T("�������޸ĺ���Ʒ��������"));//��Ʒ��������
        InputBox(p->loss_num, 11, _T("�������޸ĺ���Ʒ�������"));//��Ʒ������� 
        InputBox(p->price, 11, _T("�������޸ĺ���Ʒ�ۼۣ������밢�������֣�"));//��Ʒ�ۼ�
        InputBox(p->cost_price, 11, _T("�������޸ĺ���Ʒ�ɱ��������밢�������֣�"));//��Ʒ�ɱ�
        InputBox(p->Unit_capacity, 11, _T("�������޸ĺ�λ����"));//��λ����
        InputBox(p->Package_size, 11, _T("�������޸ĺ���Ʒ��װ��С"));//��Ʒ��װ��С
        MessageBox(NULL, _T("��ӳɹ���"), _T("��ӿ��"), MB_SETFOREGROUND);
    }
    return head;
}