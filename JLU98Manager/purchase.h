#pragma once
typedef struct Purchase_Node
{
	char time[30];//����ʱ��
	char drink[30];//������Ʒ����
	char num[20];//��������
	char cost[10];//�ɱ�
	struct Purchase_Node* next;
}Pcs_Node;

Pcs_Node* Purchase_build();//���������¼����
void Purchase_show(Pcs_Node* head,int* page);//չʾ�����¼
void Purchase_Moneyshow();//չʾ�����ʽ�
void Purchase_search(Pcs_Node* head);//��ѯ�����¼
void Purchase_save(Pcs_Node* head);//��������Ϣ���浽�ļ�����
void Purchase_free(Pcs_Node* head);//�ͷ������ڴ�ռ�

void Pur_show(Pcs_Node* head, int* page);//չʾ�����¼����
void Pur_Moneyshow();//չʾ�����ʽ����
void Pur_search(Pcs_Node* head);//��ѯ�����¼����