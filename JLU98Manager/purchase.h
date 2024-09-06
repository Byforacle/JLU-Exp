#pragma once
typedef struct Purchase_Node
{
	char time[30];//购买时间
	char drink[30];//购买饮品名称
	char num[20];//购买数量
	char cost[10];//成本
	struct Purchase_Node* next;
}Pcs_Node;

Pcs_Node* Purchase_build();//创建购买记录链表
void Purchase_show(Pcs_Node* head,int* page);//展示购买记录
void Purchase_Moneyshow();//展示现有资金
void Purchase_search(Pcs_Node* head);//查询购买记录
void Purchase_save(Pcs_Node* head);//将链表信息储存到文件当中
void Purchase_free(Pcs_Node* head);//释放链表内存空间

void Pur_show(Pcs_Node* head, int* page);//展示购买记录界面
void Pur_Moneyshow();//展示现有资金界面
void Pur_search(Pcs_Node* head);//查询购买记录界面