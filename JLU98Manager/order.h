#pragma once
#pragma once
typedef struct Order_Node
{
	char time[30];//����ʱ��
	char customer[30];//����˿�
	char cst_num[10];//����˿͵ı��
	char drink[30];//������Ʒ����
	char srg_num[10];//������Ʒ�����
	char num[20];//��������
	char Sale_volume[15];//���۶�
	char profit[15];//����
	struct Order_Node* next;
}Odr_Node;
Odr_Node* Order_build();//����������¼����
void Order_show(Odr_Node* head,int *page);//չʾ������¼
Odr_Node* Order_deal(Odr_Node* head);//����ǰ����
void Order_search(Odr_Node* head); //��ѯ������¼
void Order_income(Odr_Node* head,int *page);//չʾ����
void Order_save(Odr_Node* head);//��������Ϣ���浽�ļ�����
void Order_free(Odr_Node* head);//�ͷ������ڴ�ռ�

void Ord_show(Odr_Node* head,int *page);//չʾ������¼����
void Ord_income(Odr_Node* head,int *page);//չʾ�������
void Ord_deal(Odr_Node* head);//����ǰ��������
void Ord_search(Odr_Node* head); //��ѯ������¼����

