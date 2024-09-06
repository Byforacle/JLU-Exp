#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Storage.h"
#include"char2int.h"
#include"Fuzzy_search.h"
#include"Purchase.h"
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<easyx.h>
#include<Windows.h>
#include"Time.h"
//创建库存链表
Srg_Node* Storage_build()
{
    Srg_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Storage.txt", "r");
    if (fp == NULL || feof(fp))//读文件为空，酒水信息不存在
    {
        MessageBox(NULL, _T("库存文件为空！"), _T("酒水管理系统"), MB_SETFOREGROUND);
        return NULL;
    }
    else
    {
        //将链表头信息录入
        head = (Srg_Node*)malloc(sizeof(Srg_Node));//将链表头信息初始化
        fscanf(fp, " %s %s %s %s %s %s %s %s\n", head->Num, head->name, head->complete_num, head->loss_num, head->price, head->cost_price, head->Unit_capacity, head->Package_size);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//创建链表拷贝数据,直到文件结束
        {
            p = (Srg_Node*)malloc(sizeof(Srg_Node));
            fscanf(fp, "%s %s %s %s %s %s %s %s \n", p->Num, p->name, p->complete_num, p->loss_num, p->price, p->cost_price, p->Unit_capacity, p->Package_size);
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
void Storage_save(Storage_Node* head)//将链表信息储存到文件当中
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
//释放链表空间
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
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("库存为空！"), _T("酒水管理系统"), MB_SETFOREGROUND);
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
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("编号  饮品名     完好数目  损耗数目  售价  成本  单位容量    包装大小"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {
        if (count >= st && count <= en)
        {
            outtextxy(494, position_y, p->Num);//显示编号
            outtextxy(530, position_y, p->name);//名称
            outtextxy(650, position_y, p->complete_num);//完好数目
            outtextxy(780, position_y, p->loss_num);//损耗数目
            outtextxy(840, position_y, p->price);//售价
            outtextxy(920, position_y, p->cost_price);//成本
            outtextxy(1000, position_y, p->Unit_capacity);//单位容量
            outtextxy(1080, position_y, p->Package_size);//包装大小
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
Srg_Node* Storage_add(Srg_Node* head)//购入库存
{
    if (head == NULL)//如果头节点为空
    {
        head = (Srg_Node*)malloc(sizeof(Srg_Node));
        head->next = NULL;
        //输入客户信息
        InputBox(head->Num, 11, _T("请输入编号"));//编号 
        InputBox(head->name, 11, _T("请输入饮品名"));//饮品
        InputBox(head->complete_num, 11, _T("请输入饮品完整数量"));//饮品完整数量
        InputBox(head->loss_num, 11, _T("请输入饮品损耗数量"));//饮品损耗数量 
        InputBox(head->price, 11, _T("请输入饮品售价（仅输入阿拉伯数字）"));//饮品售价
        InputBox(head->cost_price, 11, _T("请输入饮品成本（仅输入阿拉伯数字）"));//饮品成本
        InputBox(head->Unit_capacity, 11, _T("请输入单位容量"));//单位容量
        InputBox(head->Package_size, 11, _T("请输入饮品包装大小"));//饮品包装大小
        MessageBox(NULL, _T("添加成功！"), _T("添加库存"), MB_SETFOREGROUND);
        //将进货记录保存到链表中
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
        //将运营资金资金修改
        FILE* fp = fopen("Amount.txt", "r");
        int money;
        fscanf(fp, "%d", &money);
        money -= (Char_to_int(p1->num) * Char_to_int(p1->cost));
        fclose(fp);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
        //将购买记录保存
        Purchase_save(pchead);//将链表信息储存到文件当中
        Purchase_free(pchead);//释放链表内存空间
        return head;
    }

    Srg_Node* p, * p0 = head;
    p = (Srg_Node*)malloc(sizeof(Srg_Node));
    //输入库存信息
    InputBox(p->Num, 11, _T("请输入编号"));//编号 
    while (p0 != NULL)//判断是否重复编号
    {
        if (strcmp(p->Num, p0->Num) == 0)
        {
            MessageBox(NULL, _T("已存在此编号饮品，请在此编号上进行购入"), _T("添加库存"), MB_SETFOREGROUND);
            char addcomplete[20] ;
            char addloss[20];
            InputBox(addcomplete, 11, _T("请输入饮品完整数量"));//饮品完整数量
            InputBox(addloss, 11, _T("请输入饮品损耗数量"));//饮品损耗数量 
            
            //将进货记录保存到链表中
            Pcs_Node* pchead = Purchase_build();
            Pcs_Node* p2 = pchead;
            while (p2->next != NULL)
            {
                p2 = p2->next;
            }
            Pcs_Node* p3 = (Pcs_Node*)malloc(sizeof(Pcs_Node));
            strcpy(p3->time, Time_now());//时间
            strcpy(p3->drink, p0->name);//饮品名
            strcpy(p3->num, Int_to_char((Char_to_int(addcomplete) + Char_to_int(addloss))));//购买的数量
            strcpy(p3->cost, p0->cost_price);//成本
            p2->next = p3;
            p3->next = NULL;
            //修改库存链表中的数据
            strcpy(p0->complete_num, Int_to_char(Char_to_int(addcomplete)+ Char_to_int(p0->complete_num)));
            strcpy(p0->loss_num , Int_to_char(Char_to_int(addloss) + Char_to_int(p0->loss_num)));
            //将运营资金资金修改
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money -= (Char_to_int(p3->num) * Char_to_int(p3->cost));
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
            //将购买记录保存
            Purchase_save(pchead);//将链表信息储存到文件当中
            Purchase_free(pchead);//释放链表内存空间
            MessageBox(NULL, _T("添加成功！"), _T("添加库存"), MB_SETFOREGROUND);
            return head;
        }
        p0 = p0->next;
    }
    p0 = head;
    InputBox(p->name, 11, _T("请输入饮品名"));//饮品
    InputBox(p->complete_num, 11, _T("请输入饮品完整数量"));//饮品完整数量
    InputBox(p->loss_num, 11, _T("请输入饮品损耗数量"));//饮品损耗数量 
    InputBox(p->price, 11, _T("请输入饮品售价（仅输入阿拉伯数字）"));//饮品售价
    InputBox(p->cost_price, 11, _T("请输入饮品成本（仅输入阿拉伯数字）"));//饮品成本
    InputBox(p->Unit_capacity, 11, _T("请输入单位容量"));//单位容量
    InputBox(p->Package_size, 11, _T("请输入饮品包装大小"));//饮品包装大小
    while (p0 != NULL)//判断是否重复库存
    {
        if (strcmp(p->name, p0->name) == 0 && strcmp(p->cost_price, p0->cost_price) == 0 && strcmp(p->Package_size, p0->Package_size) == 0 && strcmp(p->price, p0->price) == 0 && strcmp(p->Unit_capacity, p0->Unit_capacity) == 0)
        {
            MessageBox(NULL, _T("已存在相同库存，添加失败！"), _T("添加库存"), MB_SETFOREGROUND);
            free(p);//释放内存
            p = NULL;
            return head;
        }
        p0 = p0->next;
    }

    MessageBox(NULL, _T("添加成功！"), _T("添加库存"), MB_SETFOREGROUND);
    Srg_Node* p1 = head;
    while (p1->next != NULL)
    {
        p1 = p1->next;
    }
    p1->next = p;
    p->next = NULL;
    //将进货记录保存到链表中
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
    //将运营资金资金修改
    FILE* fp = fopen("Amount.txt", "r");
    int money;
    fscanf(fp, "%d", &money);
    money -= (Char_to_int(p2->num) * Char_to_int(p2->cost));
    fclose(fp);
    FILE* fp1 = fopen("Amount.txt", "w");
    fprintf(fp1, "%d", money);
    fclose(fp1);
    //将购买记录保存
    Purchase_save(pchead);//将链表信息储存到文件当中
    Purchase_free(pchead);//释放链表内存空间
    return head;
}
bool Storage_search(Srg_Node* head)//搜索库存信息
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("库存为空！"), _T("酒水管理系统"), MB_SETFOREGROUND);
        return false;
    }
    char choice[5];//选择查询方式
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("编号  饮品名     完好数目  损耗数目  售价  成本  单位容量    包装大小"));//显示表格第一行表头
    position_y += 20;
    InputBox(choice, 11, _T("选择查询方式:1.关键字查找(仅汉字) 2.编号查找"));//选择查询方式 
    if (strcmp(choice,"1")==0)//按照关键字查找
    {
        Srg_Node* p = head;
        char key[20];
        InputBox(key, 11, _T("输入关键字"));
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->name))
            {
                outtextxy(494, position_y, p->Num);//显示编号
                outtextxy(530, position_y, p->name);//名称
                outtextxy(650, position_y, p->complete_num);//完好数目
                outtextxy(780, position_y, p->loss_num);//损耗数目
                outtextxy(840, position_y, p->price);//售价
                outtextxy(920, position_y, p->cost_price);//成本
                outtextxy(1000, position_y, p->Unit_capacity);//单位容量
                outtextxy(1080, position_y, p->Package_size);//包装大小
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("该商品不存在！"), _T("查询库存"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("查询成功！"), _T("查询库存"), MB_SETFOREGROUND);
        return true;
    }
    else if (strcmp(choice, "2") == 0)
    {
        char key[10];
        InputBox(key, 11, _T("输入编号"));
        Srg_Node* p = head;
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (strcmp(key, p->Num) == 0)
            {
                outtextxy(494, position_y, p->Num);//显示编号
                outtextxy(530, position_y, p->name);//名称
                outtextxy(650, position_y, p->complete_num);//完好数目
                outtextxy(780, position_y, p->loss_num);//损耗数目
                outtextxy(840, position_y, p->price);//售价
                outtextxy(920, position_y, p->cost_price);//成本
                outtextxy(1000, position_y, p->Unit_capacity);//单位容量
                outtextxy(1080, position_y, p->Package_size);//包装大小
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("该商品不存在！"), _T("查询库存"), MB_SETFOREGROUND);
            return false;
        }
        else MessageBox(NULL, _T("查询成功！"), _T("查询库存"), MB_SETFOREGROUND);
        return true;
    }
    else
    {
        MessageBox(NULL, _T("输入有误！"), _T("搜索库存"), MB_SETFOREGROUND);//输入有误
        Storage_search(head);
        return false;
    }
}
Srg_Node* Storage_delete(Srg_Node* head)//删除库存
{
    //搜索要删除库存的编号
    MessageBox(NULL, _T("搜索您要删除的库存信息！"), _T("删除库存"), MB_SETFOREGROUND);
    Storage_search(head);
    char choice[10];
    InputBox(choice, 11, _T("请输入您要删除的库存编号"));//输入要删除的库存编号
    Srg_Node* p = head; int flag = 0;
    Srg_Node* p0 = head;
    while (p != NULL)
    {
        if (strcmp(p->Num, choice) == 0)//查询到了此编号顾客
        {
            flag = 1;
            break;
        }
        p0 = p;
        p = p->next;
    }
    if (flag == 0)//此库存不存在
    {
        MessageBox(NULL, _T("此编号库存不存在！"), _T("删除库存"), MB_SETFOREGROUND);
        return head;
    }
    //修改库存信息
    if (p->next == NULL)//如果删除库存是尾节点
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
    MessageBox(NULL, _T("删除成功！"), _T("删除库存"), MB_SETFOREGROUND);
    return head;
}
Storage_Node* Storage_change(Storage_Node* head)//修改库存信息
{
    //搜索要修改顾客的编号
    MessageBox(NULL, _T("搜索您要修改的库存信息！"), _T("删除库存"), MB_SETFOREGROUND);
    bool f=Storage_search(head);
    if (f)
    {
        char choice[10];
        InputBox(choice, 11, _T("请输入您要修改的库存编号"));//输入要修改的库存编号
        Srg_Node* p = head; int flag = 0;
        while (p != NULL)
        {
            if (strcmp(p->Num, choice) == 0)//查询到了此编号库存
            {
                flag = 1;
                break;
            }
            p = p->next;
        }
        if (flag == 0)//此库存不存在
        {
            MessageBox(NULL, _T("此编号库存不存在！"), _T("修改库存"), MB_SETFOREGROUND);
            return head;
        }
        //修改库存信息
        InputBox(p->name, 11, _T("请输入修改后饮品名"));//饮品
        InputBox(p->complete_num, 11, _T("请输入修改后饮品完整数量"));//饮品完整数量
        InputBox(p->loss_num, 11, _T("请输入修改后饮品损耗数量"));//饮品损耗数量 
        InputBox(p->price, 11, _T("请输入修改后饮品售价（仅输入阿拉伯数字）"));//饮品售价
        InputBox(p->cost_price, 11, _T("请输入修改后饮品成本（仅输入阿拉伯数字）"));//饮品成本
        InputBox(p->Unit_capacity, 11, _T("请输入修改后单位容量"));//单位容量
        InputBox(p->Package_size, 11, _T("请输入修改后饮品包装大小"));//饮品包装大小
        MessageBox(NULL, _T("添加成功！"), _T("添加库存"), MB_SETFOREGROUND);
    }
    return head;
}