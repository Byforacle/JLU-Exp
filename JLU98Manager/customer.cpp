#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"customer.h"
#include<string.h>
#include<windows.h>
#include"char2int.h"
#include"Fuzzy_search.h"
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<Windows.h>
#include<time.h>
//创建顾客链表
Cst_Node* Customer_build()
{
    Cst_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Customer.txt", "r");
    if (fp == NULL||feof(fp))//读文件为空，顾客信息不存在
    {
        MessageBox(NULL, _T("文件为空！"), _T("酒水管理系统"), MB_SETFOREGROUND);
        return NULL;
    }
    else
    {
        //将链表头信息初始化
        head = (Cst_Node*)malloc(sizeof(Cst_Node));
        head->next = NULL;
        fscanf(fp, "%s %s %s %s %s %s\n", head->money, head->name, head->phone, head->num, head->sex, head->Isvip);
        tmp = head;
        while (!feof(fp))//创建链表拷贝数据,直到文件结束
        {
            p = (Cst_Node*)malloc(sizeof(Cst_Node));
            fscanf(fp, "%s %s %s %s %s %s\n", p->money, p->name, p->phone, p->num, p->sex, p->Isvip);
            //如果消费金额达到了1000及以上，则为VIP用户
            if (Char_to_int(p->money) > 1000) strcpy(p->Isvip, "是");
            else strcpy(p->Isvip, "不是");
            tmp->next = p;
            tmp = p;
        }
        if (p != NULL)//如果p不是空指针的话
        {
            p->next = NULL;
        }
        fclose(fp);//关闭文件
        return head;//返回链表头
    }
}
//释放链表空间
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
//展示顾客信息
void Customer_show(Cst_Node* head,int* page)
{
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("顾客信息不存在！"), _T("VIP展示"), MB_SETFOREGROUND);
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
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    //显示所有顾客信息
    outtextxy(position_x, position_y, _T("编号    姓名      性别    电话号      消费金额     是否为VIP"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {
        if (count >= st && count <= en)
        {
            outtextxy(494, position_y, p->num);//显示编号
            outtextxy(556, position_y, p->name);//姓名
            outtextxy(676, position_y, p->sex);//性别
            outtextxy(730, position_y, p->phone);//电话号
            outtextxy(870, position_y, p->money);//消费金额
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
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("顾客信息不存在！"), _T("VIP展示"), MB_SETFOREGROUND);
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
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("编号    姓名      性别    电话号      消费金额     是否为VIP"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {
        if (strcmp(p->Isvip,"是")==0&& count >= st && count <= en)
        {
            outtextxy(494, position_y, p->num);//显示编号
            outtextxy(556, position_y, p->name);//姓名
            outtextxy(676, position_y, p->sex);//性别
            outtextxy(730, position_y, p->phone);//电话号
            outtextxy(870, position_y, p->money);//消费金额
            outtextxy(1016, position_y, p->Isvip);//VIP
            position_y += 20;
        }
        p = p->next;
    }
    return;
}
//增加顾客信息
Cst_Node* Customer_add(Cst_Node* head)
{
    Cst_Node* p;
    p = (Cst_Node*)malloc(sizeof(Cst_Node));
    //输入客户信息
    InputBox(p->num, 11, _T("请输入客户编号"));//客户编号 
    InputBox(p->name, 11, _T("请输入客户姓名"));//客户姓名
    InputBox(p->money, 11, _T("请输入客户累计消费金额"));//累计消费金额
    if (Char_to_int(p->money) > 50000)
    {
        strcpy(p->Isvip, "是");
    }
    else
        strcpy(p->Isvip, "不是");
    InputBox(p->sex, 11, _T("请输入客户性别"));//客户性别 
    InputBox(p->phone, 15, _T("请输入客户电话号码"));//客户电话号码
    //添加客户信息
    Cst_Node* p0 = head;
    if (head == NULL)
    {
        head = p;
        head->next = NULL;
    }
    else {
        while (p0 != NULL)//判断是否重复编号
        {
            if (strcmp(p->num, p0->num) == 0)
            {
                MessageBox(NULL, _T("编号已重复，添加失败！"), _T("添加顾客"), MB_SETFOREGROUND);
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
    MessageBox(NULL, _T("设定成功！"), _T("添加顾客"), MB_SETFOREGROUND);
    return head;
}
//修改顾客信息
Cst_Node* Customer_change(Cst_Node* head)
{
    //搜索要修改顾客的编号
    MessageBox(NULL, _T("搜索您要修改的顾客信息！"), _T("修改顾客"), MB_SETFOREGROUND);
    bool f=Customer_search(head);
    if (f)
    {
        char choice[10];
        InputBox(choice, 11, _T("输入要修改的编号"));
        Cst_Node* p = head; int flag = 0;
        while (p != NULL)
        {
            if (strcmp(p->num, choice) == 0)//查询到了此编号顾客
            {
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag == 0)//此顾客不存在
        {
            MessageBox(NULL, _T("此编号用户不存在！"), _T("修改顾客"), MB_SETFOREGROUND);
            return head;
        }
        //修改客户信息
        InputBox(p->name, 11, _T("输入要修改的客户姓名"));
        InputBox(p->money, 11, _T("输入要修改的客户累计消费金额"));
        if (Char_to_int(p->money) >50000)
        {
            strcpy(p->Isvip, "是");
        }
        else strcpy(p->Isvip, "不是");
        InputBox(p->sex, 11, _T("输入要修改的客户性别"));
        InputBox(p->phone, 15, _T("输入要修改的客户电话号码"));
        MessageBox(NULL, _T("修改成功！"), _T("修改顾客"), MB_SETFOREGROUND);
        return head;
    }  
}
//将链表信息储存到文件当中
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

bool Customer_search(Cst_Node* head)//搜索顾客信息
{
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("顾客信息不存在！"), _T("搜索顾客"), MB_SETFOREGROUND);
        return false;
    }
    char choice[20];//选择查询方式
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("编号    姓名      性别    电话号      消费金额     是否为VIP"));//显示表格第一行表头
    position_y += 20;
    InputBox(choice, 11, _T("选择查询方式:1.关键字查找(仅汉字) 2.编号查找"));//选择查询方式 
    if (strcmp(choice,"1")==0)//按照关键字查找
    {
        Cst_Node* p = head;
        char key[20];
        InputBox(key, 11, _T("输入关键字"));
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->name))
            {
                outtextxy(494, position_y, p->num);//显示编号
                outtextxy(556, position_y, p->name);//姓名
                outtextxy(676, position_y, p->sex);//性别
                outtextxy(730, position_y, p->phone);//电话号
                outtextxy(870, position_y, p->money);//消费金额
                outtextxy(1016, position_y, p->Isvip);//VIP
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("顾客信息不存在！"), _T("搜索顾客"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("查询成功！"), _T("搜索顾客"), MB_SETFOREGROUND);
        return true;
    }
    else if (strcmp(choice, "2")==0)
    {
        char key[10];
        InputBox(key, 11, _T("输入编号"));
        Cst_Node* p = head;
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (strcmp(key, p->num) == 0)
            {
                outtextxy(494, position_y, p->num);//显示编号
                outtextxy(556, position_y, p->name);//姓名
                outtextxy(676, position_y, p->sex);//性别
                outtextxy(730, position_y, p->phone);//电话号
                outtextxy(870, position_y, p->money);//消费金额
                outtextxy(1016, position_y, p->Isvip);//VIP
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("顾客信息不存在！"), _T("搜索顾客"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("查询成功！"), _T("搜索顾客"), MB_SETFOREGROUND);
        return true;
    }
    else
    {
        MessageBox(NULL, _T("输入有误！"), _T("搜索顾客"), MB_SETFOREGROUND);
        Customer_search(head);
        return false;
    }
}

Cst_Node* Customer_delete(Cst_Node* head)//删除顾客信息
{
    //搜索要删除顾客的编号
    MessageBox(NULL, _T("搜索您要删除的顾客信息"), _T("删除顾客"), MB_SETFOREGROUND);
    bool f=Customer_search(head);
    if(f)
    {
        char choice[10];
        InputBox(choice, 11, _T("输入要删除的编号"));
        Cst_Node* p = head; int flag = 0;
        Cst_Node* p0 = head;
        while (p != NULL)
        {
            if (strcmp(p->num, choice) == 0)//查询到了此编号顾客
            {
                flag = 1;
                break;
            }
            p0 = p;
            p = p->next;
        }
        if (flag == 0)//此顾客不存在
        {
            MessageBox(NULL, _T("此编号用户不存在！"), _T("修改顾客"), MB_SETFOREGROUND);
            return head;
        }
        //修改客户信息
        if (p->next == NULL)//如果删除顾客是尾节点
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
        MessageBox(NULL, _T("删除成功"), _T("删除顾客"), MB_SETFOREGROUND);
        return head;
    }
}
