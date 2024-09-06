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
#include <graphics.h>      // 引用图形库头文件
#include <conio.h>
#include<tchar.h>
#include<easyx.h>
#include<time.h>

Odr_Node* Order_build()//创建订单记录链表
{
    Odr_Node* head = NULL, * p = NULL, * tmp = NULL;
    FILE* fp = fopen("Order.txt", "r");
    if (fp == NULL||feof(fp))//读文件为空，订单记录不存在
    {
        MessageBox(NULL, _T("订单记录文件为空"), _T("酒水管理系统"), MB_SETFOREGROUND);
        return NULL; 
    }
    else
    {
        //将链表头信息初始化
        head = (Odr_Node*)malloc(sizeof(Odr_Node));
        fscanf(fp, "%s %s %s %s %s %s %s %s\n", head->time, head->customer, head->cst_num, head->drink, head->srg_num, head->num, head->Sale_volume, head->profit);
        head->next = NULL;
        tmp = head;
        while (!feof(fp))//创建链表拷贝数据,直到文件结束
        {
            p = (Odr_Node*)malloc(sizeof(Odr_Node));
            fscanf(fp, "%s %s %s %s %s %s %s %s\n", p->time, p->customer, p->cst_num, p->drink, p->srg_num, p->num, p->Sale_volume, p->profit);
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
void Order_show(Odr_Node* head,int *page)//展示订单记录
{
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("订单记录不存在"), _T("展示订单记录"), MB_SETFOREGROUND);
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
    int position_x = 410;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("购买时间                购买顾客 顾客编号   购买饮品名称    饮品编号 购买数量 销售额   利润"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {
        if (count >= st && count <= en)
        {
            outtextxy(412, position_y, p->time);//显示购买时间
            outtextxy(665, position_y, p->customer);//购买顾客
            outtextxy(775, position_y, p->cst_num);//顾客编号
            outtextxy(850, position_y, p->drink);//饮品名称
            outtextxy(1030, position_y, p->srg_num);//饮品库存编号
            outtextxy(1130, position_y, p->num);//购买数量
            outtextxy(1200, position_y, p->Sale_volume);//销售额
            outtextxy(1280, position_y, p->profit);//利润
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
void Order_income(Odr_Node* head,int *page)//展示收入
{
    if (head == NULL)//如果链表头空
    {
        MessageBox(NULL, _T("订单记录不存在"), _T("展示订单记录"), MB_SETFOREGROUND);
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
    int position_x = 476;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("购买时间                 销售额    利润"));//显示表格第一行表头
    position_y += 20;
    while (p != NULL)//打印链表内容
    {
        if (count >= st && count <= en)
        {
            outtextxy(474, position_y, p->time);//显示购买时间
            outtextxy(740, position_y, p->Sale_volume);//销售额
            outtextxy(840, position_y, p->profit);//利润
            position_y += 20;
        }
        p = p->next;
        count++;
    }
    return;
}
Odr_Node* Order_deal(Odr_Node* head)//处理当前订单
{
    if (head == NULL)//如果头节点为空
    {
        head = (Odr_Node*)malloc(sizeof(Odr_Node));
        //输入客户信息
        strcpy(head->time, Time_now());
        //InputBox(head->customer, 11, _T("请输入客户姓名"));//客户姓名
        InputBox(head->cst_num, 11, _T("请输入客户编号"));//客户编号
        InputBox(head->srg_num, 11, _T("请输入购买的饮品编号"));//购买的饮品编号
        InputBox(head->num, 11, _T("请输入购买数量"));//购买数量
        /*判断库存是否存在*/
        Srg_Node* sghead = Storage_build();//创建顾客链表
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
        if (flag1 == 0)//不存在此编号库存
        {
            MessageBox(NULL, _T("不存在此编号库存，订单处理失败！"), _T("订单处理"), MB_SETFOREGROUND);
            return head;
        }
        if (Char_to_int(p1->complete_num) < Char_to_int(head->num))//库存不足时
        {
            MessageBox(NULL, _T("库存不足，订单处理失败！"), _T("订单处理"), MB_SETFOREGROUND);
            return head;
        }
        strcpy(head->drink, p1->name);//将购买的酒水名存放到订单记录里
        //判断是否存在先前顾客
        Cst_Node* cshead = Customer_build();//创建顾客链表
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
        if (flag2 == 0)//不存在此编号顾客，新建一个顾客
        {
            MessageBox(NULL, _T("此顾客为新顾客，请补全新顾客信息！"), _T("订单处理"), MB_SETFOREGROUND);
            Cst_Node* p3 = (Cst_Node*)malloc(sizeof(Cst_Node));
            strcpy(p3->num, head->cst_num);
            InputBox(p3->name, 11, _T("请输入客户姓名"));//客户姓名
            strcpy(head->customer, p3->name);
            InputBox(p3->phone, 20, _T("请输入新顾客电话号码"));//新顾客电话号码
            InputBox(p3->sex, 11, _T("请输入新顾客性别"));//新顾客性别
            strcpy(p3->money, Int_to_char(Char_to_int(head->num) * Char_to_int(p1->price)));//顾客消费金额
            if (Char_to_int(p3->money) > 50000)
            {
                strcpy(p3->Isvip, "是");

            }
            else strcpy(p3->Isvip, "不是");
            p5->next = p3;
            p3->next = NULL;
            p2 = p3;//令p2指向p3方便接下来操作
            MessageBox(NULL, _T("添加新顾客信息成功！"), _T("订单处理"), MB_SETFOREGROUND);
        }
        //此顾客存在时，修改他的累计消费金额
        if (strcmp(p2->Isvip, "不是") == 0)//如果顾客不是VIP
        {
            strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + Char_to_int(head->num) * Char_to_int(p1->price)));
            strcpy(head->Sale_volume, Int_to_char(Char_to_int(head->num) * Char_to_int(p1->price)));//将销售额存储
            if (Char_to_int(p2->money) > 50000)//再次判断是否达到成为VIP的条件
            {
                strcpy(p2->Isvip, "是");
            }
            else strcpy(p2->Isvip, "不是");
            //更改库存信息
            strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(head->num)));
            //将运营资金资金修改
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money += Char_to_int(head->num) * Char_to_int(p1->price);
            strcpy(head->profit, Int_to_char(Char_to_int(head->num) * (Char_to_int(p1->price) - Char_to_int(p1->cost_price))));//将利润存入
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
        }
        else//如果是VIP，将所购商品打九折并将有破损的商品作为赠品赠送
        {
            MessageBox(NULL, _T("由于该顾客是VIP用户，商品享受九折折扣并赠送有瑕疵的商品!"), _T("订单处理"), MB_SETFOREGROUND);
            strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)))));
            strcpy(head->Sale_volume, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)))));//将销售额存储
            //更改库存信息
            strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(head->num)));
            strcpy(p1->loss_num, "0");
            //将运营资金资金修改
            FILE* fp1 = fopen("Amount.txt", "r");
            int money;
            fscanf(fp1, "%d", &money);
            money += (int)(0.5 + (0.9 * Char_to_int(head->num) * Char_to_int(p1->price)));
            strcpy(head->profit, Int_to_char((int)(0.5 + (Char_to_int(head->num) * (Char_to_int(p1->price) * 0.9 - Char_to_int(p1->cost_price))))));//存入利润
            fclose(fp1);
            FILE* fp2 = fopen("Amount.txt", "w");
            fprintf(fp2, "%d", money);
            fclose(fp2);
        }
        Storage_save(sghead);//将链表信息储存到文件当中
        Storage_free(sghead);//释放链表内存空间
        Customer_save(cshead);//将链表信息储存到文件当中
        Customer_free(cshead);//释放链表内存空间
        MessageBox(NULL, _T("订单处理成功!"), _T("订单处理"), MB_SETFOREGROUND);
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
    //输入客户信息
    strcpy(p->time, Time_now());
    //InputBox(p->customer, 11, _T("请输入客户姓名"));//客户姓名
    InputBox(p->cst_num, 11, _T("请输入客户编号"));//客户编号
    InputBox(p->srg_num, 11, _T("请输入购买的饮品编号"));//购买的饮品编号
    InputBox(p->num, 11, _T("请输入购买数量"));//购买数量
    /*判断库存是否存在*/
    Srg_Node* sghead = Storage_build();//创建库存链表
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
    if (flag1 == 0)//不存在此编号库存
    {
        MessageBox(NULL, _T("不存在此编号库存，订单处理失败！"), _T("订单处理"), MB_SETFOREGROUND);
        return head;
    }
    strcpy(p->drink, p1->name);//将购买的库存记录存放到订单记录里
    if (Char_to_int(p1->complete_num) < Char_to_int(p->num))//库存不足时
    {
        MessageBox(NULL, _T("库存不足，订单处理失败！"), _T("订单处理"), MB_SETFOREGROUND);
        return head;
    }
    //判断是否存在先前顾客
    Cst_Node* cshead = Customer_build();//创建顾客链表
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
    if (flag2 == 0)//不存在此编号顾客，新建一个顾客
    {
        MessageBox(NULL, _T("此顾客为新顾客，请补全新顾客信息！"), _T("订单处理"), MB_SETFOREGROUND);
        Cst_Node* p3 = (Cst_Node*)malloc(sizeof(Cst_Node));
        if (cshead == NULL) cshead = p3;
        strcpy(p3->num, p->cst_num);
        InputBox(p3->name, 11, _T("请输入客户姓名"));//客户姓名
        strcpy(p->customer, p3->name);
        InputBox(p3->phone, 20, _T("请输入新顾客电话号码"));
        InputBox(p3->sex, 11, _T("请输入新顾客性别"));
        strcpy(p3->money, Int_to_char(Char_to_int(p->num) * Char_to_int(p1->price)));//顾客消费金额
        if (Char_to_int(p3->money) > 50000)
        {
            strcpy(p3->Isvip, "是");

        }
        else strcpy(p3->Isvip, "不是");
        p5->next = p3;
        p3->next = NULL;
        p2 = p3;//令p2指向p3方便接下来操作
        MessageBox(NULL, _T("添加新顾客信息成功！"), _T("订单处理"), MB_SETFOREGROUND);
    }
    //此顾客存在时，修改他的累计消费金额
    if (strcmp(p2->Isvip, "不是") == 0)//如果顾客不是VIP
    {
        strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + Char_to_int(p->num) * Char_to_int(p1->price)));
        strcpy(p->Sale_volume, Int_to_char(Char_to_int(p->num) * Char_to_int(p1->price)));//将销售额存储
        if (Char_to_int(p2->money) > 50000)//再次判断是否达到成为VIP的条件
        {
            strcpy(p2->Isvip, "是");
        }
        else strcpy(p2->Isvip, "不是");
        //更改库存信息
        strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(p->num)));
        //将运营资金资金修改
        FILE* fp1 = fopen("Amount.txt", "r");
        int money;
        fscanf(fp1, "%d", &money);
        money += Char_to_int(p->num) * Char_to_int(p1->price);
        strcpy(p->profit, Int_to_char(Char_to_int(p->num) * (Char_to_int(p1->price) - Char_to_int(p1->cost_price))));//将利润存入
        fclose(fp1);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
    }
    else//如果是VIP，将所购商品打九折并将有破损的商品作为赠品赠送
    {
        MessageBox(NULL, _T("由于该顾客是VIP用户，商品享受九折折扣并赠送有瑕疵的商品!"), _T("订单处理"), MB_SETFOREGROUND);
        strcpy(p2->money, Int_to_char(Char_to_int(p2->money) + (int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)))));
        strcpy(p->Sale_volume, Int_to_char((int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)))));//将销售额存储
        //更改库存信息
        strcpy(p1->complete_num, Int_to_char(Char_to_int(p1->complete_num) - Char_to_int(p->num)));
        strcpy(p1->loss_num, "0");
        //将运营资金资金修改
        FILE* fp1 = fopen("Amount.txt", "r");
        int money;
        fscanf(fp1, "%d", &money);
        money += (int)(0.5 + (0.9 * Char_to_int(p->num) * Char_to_int(p1->price)));
        strcpy(p->profit, Int_to_char((int)(0.5 + (Char_to_int(p->num) * (Char_to_int(p1->price) * 0.9 - Char_to_int(p1->cost_price))))));//存入利润
        fclose(fp1);
        FILE* fp2 = fopen("Amount.txt", "w");
        fprintf(fp2, "%d", money);
        fclose(fp2);
    }
    p0->next = p;//将此记录存入链表
    p->next = NULL;
    Storage_save(sghead);//将链表信息储存到文件当中
    Storage_free(sghead);//释放链表内存空间
    Customer_save(cshead);//将链表信息储存到文件当中
    Customer_free(cshead);//释放链表内存空间
    MessageBox(NULL, _T("订单处理成功！"), _T("订单处理"), MB_SETFOREGROUND);
    return head;
}
void Order_search(Odr_Node* head)//查询订单记录
{
    if (head == NULL)
    {
        MessageBox(NULL, _T("订单记录不存在"), _T("查询订单记录"), MB_SETFOREGROUND);
        return;
    }
    Odr_Node* p = head;
    int position_x = 410;//“序号”横坐标
    int position_y = 92;//“序号”纵坐标
    setbkmode(TRANSPARENT);//设置字体背景为透明
    settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
    settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
    outtextxy(position_x, position_y, _T("购买时间                购买顾客 顾客编号   购买饮品名称    饮品编号 购买数量 销售额   利润"));//显示表格第一行表头
    position_y += 20;
    char choice[10];
    InputBox(choice, 11, _T("请输入您想选择的搜索方式：1、按照饮品关键字    2、按照购买时间范围"));
    if (strcmp(choice, "1") == 0)
    {
        char key[20];
        InputBox(key, 11, _T("请输入购买的饮品关键字"));//饮品关键字
        int flag = 0;//判断是否查找到
        while (p != NULL)
        {
            if (Fuzzy_Search(key, p->drink))
            {
                outtextxy(412, position_y, p->time);//显示购买时间
                outtextxy(665, position_y, p->customer);//购买顾客
                outtextxy(775, position_y, p->cst_num);//顾客编号
                outtextxy(850, position_y, p->drink);//饮品名称
                outtextxy(1030, position_y, p->srg_num);//饮品库存编号
                outtextxy(1130, position_y, p->num);//购买数量
                outtextxy(1200, position_y, p->Sale_volume);//销售额
                outtextxy(1280, position_y, p->profit);//利润
                position_y += 20;
                flag = 1;
            }
            p = p->next;
        }
        if (flag == 0)
        {
            MessageBox(NULL, _T("未能查询到相关订单记录！"), _T("查询订单记录"), MB_SETFOREGROUND);
        }
        else MessageBox(NULL, _T("查询成功！"), _T("查询订单记录"), MB_SETFOREGROUND);
        return;
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
        Odr_Node* p = head;
        int flag = 0;//判断找没找到
        while (p != NULL)
        {
            if (Time_compare(p->time, time1) >= 0 && Time_compare(p->time, time2) <= 0)
            {
                outtextxy(412, position_y, p->time);//显示购买时间
                outtextxy(665, position_y, p->customer);//购买顾客
                outtextxy(775, position_y, p->cst_num);//顾客编号
                outtextxy(850, position_y, p->drink);//饮品名称
                outtextxy(1030, position_y, p->srg_num);//饮品库存编号
                outtextxy(1130, position_y, p->num);//购买数量
                outtextxy(1200, position_y, p->Sale_volume);//销售额
                outtextxy(1280, position_y, p->profit);//利润
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
//将链表信息储存到文件当中
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
void Order_free(Odr_Node* head)//释放链表空间
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