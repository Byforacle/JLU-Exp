#pragma once
#pragma once
typedef struct Order_Node
{
	char time[30];//购买时间
	char customer[30];//购买顾客
	char cst_num[10];//购买顾客的编号
	char drink[30];//购买饮品名称
	char srg_num[10];//购买饮品库存编号
	char num[20];//购买数量
	char Sale_volume[15];//销售额
	char profit[15];//利润
	struct Order_Node* next;
}Odr_Node;
Odr_Node* Order_build();//创建订单记录链表
void Order_show(Odr_Node* head,int *page);//展示订单记录
Odr_Node* Order_deal(Odr_Node* head);//处理当前订单
void Order_search(Odr_Node* head); //查询订单记录
void Order_income(Odr_Node* head,int *page);//展示收入
void Order_save(Odr_Node* head);//将链表信息储存到文件当中
void Order_free(Odr_Node* head);//释放链表内存空间

void Ord_show(Odr_Node* head,int *page);//展示订单记录界面
void Ord_income(Odr_Node* head,int *page);//展示收入界面
void Ord_deal(Odr_Node* head);//处理当前订单界面
void Ord_search(Odr_Node* head); //查询订单记录界面

