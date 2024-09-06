#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"char2int.h"
#include"Fuzzy_search.h"
#include"Purchase.h"
#include"Time.h"
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<Windows.h>
#include<time.h>

Pcs_Node* Purchase_build()//创建购买记录链表
{
    Pcs_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Purchase.txt", "r");
    if (fp == NULL || feof(fp))//读文件为空，购买记录不存在
    {
        return NULL;
    }
    else
    {
        //将链表头信息初始化
        head = (Pcs_Node*)malloc(sizeof(Pcs_Node));
        fscanf(fp, "%s %s %s %s\n", head->time, head->drink, head->num, head->cost);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//创建链表拷贝数据,直到文件结束
        {
            p = (Pcs_Node*)malloc(sizeof(Pcs_Node));
            fscanf(fp, "%s %s %s %s\n", p->time, p->drink, p->num, p->cost);
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
void Purchase_Moneyshow()//展示现有资金
{
    FILE* fp = fopen("Amount.txt", "r");
    int money;
    fscanf(fp, "%d", &money);
    char money1[20];
    strcpy(money1, Int_to_char(money));
    fclose(fp);
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(120, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("现有资金："));
    position_y += 120;
    outtextxy(position_x, position_y,money1);//显示现有资金
    return;
}

void Purchase_show(Pcs_Node* head,int *page)
{
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("购买记录不存在！"), _T("酒水管理系统"), MB_SETFOREGROUND);
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
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("购买时间                 购买饮品名称         购买数量    成本"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {

        if (count >= st && count <= en)
        {
            outtextxy(474, position_y, p->time);//显示购买时间
            outtextxy(740, position_y, p->drink);//购买饮品名称
            outtextxy(980, position_y, p->num);//购买数量
            outtextxy(1060, position_y, p->cost);//成本
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
void Purchase_search(Pcs_Node* head)//查询购买记录
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("购买记录不存在！"), _T("酒水管理系统"), MB_SETFOREGROUND);
        return;
    }
    Pcs_Node* p = head;
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("购买时间                 购买饮品名称         购买数量    成本"));//显示表格第一行表头
    position_y += 20;
    char choice[10];
    InputBox(choice, 11, _T("请输入您想选择的搜索方式：1、按照饮品关键字    2、按照购买时间范围"));

    if (strcmp(choice, "1") == 0)
    {
        char key[20];
        InputBox(key, 11, _T("输入关键字"));
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->drink))
            {
                outtextxy(474, position_y, p->time);//显示购买时间
                outtextxy(740, position_y, p->drink);//购买饮品名称
                outtextxy(980, position_y, p->num);//购买数量
                outtextxy(1060, position_y, p->cost);//成本
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("购买记录不存在！"), _T("查询购买记录"), MB_SETFOREGROUND);
        }
        else MessageBox(NULL, _T("查询成功！"), _T("查询购买记录"), MB_SETFOREGROUND);
    }
    else if (strcmp(choice, "2") == 0)
    {
        char time1[25]; char time2[25];
        char year1[5]; 
        InputBox(year1, 11, _T("请输入您要搜索的起始年份(仅输入数字)"));
        char month1[3]; 
        InputBox(month1, 11, _T("请输入您要搜索的起始月份(仅输入数字,开头为0也输入)"));
        char day1[3]; 
        InputBox(day1, 11, _T("请输入您要搜索的起始日期(仅输入数字,开头为0也输入)"));
        char hour1[3]; 
        InputBox(hour1, 11, _T("请输入您要搜索的起始小时(仅输入数字,开头为0也输入)"));
        char min1[3]; 
        InputBox(min1, 11, _T("请输入您要搜索的起始分钟(仅输入数字,开头为0也输入)"));
        strcpy(time1, year1);
        strcpy((time1 + 4), "年");//4,5下标为汉字年
        strcpy(time1 + 6, month1);
        strcpy((time1 + 8), "月");//8 9下标为汉字月
        strcpy(time1 + 10, day1);
        strcpy((time1 + 12), "日");//12 13下标为汉字日
        strcpy(time1 + 14, hour1);
        strcpy((time1 + 16), "时");//16 17为汉字时
        strcpy(time1 + 18, min1);
        strcpy((time1 + 20), "分");//20 21为汉字分
        time1[22] = '\0';
        char year2[5]; 
        InputBox(year2, 11, _T("请输入您要搜索的起始年份(仅输入数字)"));
        char month2[3]; 
        InputBox(month2, 11, _T("请输入您要搜索的起始月份(仅输入数字,开头为0也输入)"));
        char day2[3]; 
        InputBox(day2, 11, _T("请输入您要搜索的起始日期(仅输入数字,开头为0也输入)"));
        char hour2[3]; 
        InputBox(hour2, 11, _T("请输入您要搜索的起始小时(仅输入数字,开头为0也输入)"));
        char min2[3];
        InputBox(min2, 11, _T("请输入您要搜索的起始分钟(仅输入数字,开头为0也输入)"));
        strcpy(time2, year2);
        strcpy((time2 + 4), "年");//4,5下标为汉字年
        strcpy(time2 + 6, month2);
        strcpy((time2 + 8), "月");//8 9下标为汉字月
        strcpy(time2 + 10, day2);
        strcpy((time2 + 12), "日");//12 13下标为汉字日
        strcpy(time2 + 14, hour2);
        strcpy((time2 + 16), "时");//16 17为汉字时
        strcpy(time2 + 18, min2);
        strcpy((time2 + 20), "分");//20 21为汉字分
        time2[22] = '\0';
        if (Time_compare(time1, time2) >= 0)
        {
            MessageBox(NULL, _T("您输入的起始时间等于或者大于终止时间，输入有误！"), _T("按时间查询"), MB_SETFOREGROUND);
            return;
        }
        Pcs_Node* p = head;
        int flag = 0;//判断找没找到
        while (p != NULL)
        {
            if (Time_compare(p->time, time1) >= 0 && Time_compare(p->time, time2) <= 0)
            {
                outtextxy(474, position_y, p->time);//显示购买时间
                outtextxy(740, position_y, p->drink);//购买饮品名称
                outtextxy(980, position_y, p->num);//购买数量
                outtextxy(1060, position_y, p->cost);//成本
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("购买记录不存在！"), _T("查询购买记录"), MB_SETFOREGROUND);
            return;
        }
        MessageBox(NULL, _T("查询成功！"), _T("查询购买记录"), MB_SETFOREGROUND);
        return;
    }
    else
    {
        MessageBox(NULL, _T("您的输入有误！"), _T("查询购买记录"), MB_SETFOREGROUND);
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

void Purchase_free(Pcs_Node* head)//释放链表空间
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
