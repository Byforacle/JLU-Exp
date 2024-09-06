#pragma once
//构建顾客链表单元
typedef struct St_Customer {
    char num[10];//编号
    char name[10];//姓名为字符串 
    char sex[10]; //性别为单个字符
    char phone[20]; //电话号码
    char  money[10];//消费金额
    char Isvip[10];//是否为vip
}St_Cst;
typedef struct Customer_Node {
    char num[10];//编号
    char name[10];//姓名为字符串 
    char sex[10]; //性别为单个字符
    char phone[20]; //电话号码
    char  money[10];//消费金额
    char Isvip[10];//是否为vip
    struct Customer_Node* next;
}Cst_Node;
Cst_Node* Customer_build();//创建顾客链表
void Customer_show(Cst_Node* head,int* page);//展示所有顾客
void Customer_free(Cst_Node* head);//释放链表空间
Cst_Node* Customer_add(Cst_Node* head);//增加顾客信息
void Customer_showvip(Cst_Node* head, int* page);//展示vip顾客
Cst_Node* Customer_change(Cst_Node* head);//修改顾客信息
void Customer_save(Cst_Node* head);//将链表信息储存到文件当中
bool Customer_search(Cst_Node* head);//搜索顾客信息
Cst_Node* Customer_delete(Cst_Node* head);//删除顾客信息

void Cus_show(Cst_Node* head,int* page);//调用顾客展示函数
void Cus_vipshow(Cst_Node* head,int *page);//调用VIP展示函数
void Cus_change(Cst_Node* head);//调用顾客修改函数				
void Cus_add(Cst_Node* head);//调用增加顾客函数				
void Cus_search(Cst_Node* head);//调用查询顾客函数
void Cus_delete(Cst_Node* head);//调用删除顾客函数