#pragma once
//�����˿�����Ԫ
typedef struct St_Customer {
    char num[10];//���
    char name[10];//����Ϊ�ַ��� 
    char sex[10]; //�Ա�Ϊ�����ַ�
    char phone[20]; //�绰����
    char  money[10];//���ѽ��
    char Isvip[10];//�Ƿ�Ϊvip
}St_Cst;
typedef struct Customer_Node {
    char num[10];//���
    char name[10];//����Ϊ�ַ��� 
    char sex[10]; //�Ա�Ϊ�����ַ�
    char phone[20]; //�绰����
    char  money[10];//���ѽ��
    char Isvip[10];//�Ƿ�Ϊvip
    struct Customer_Node* next;
}Cst_Node;
Cst_Node* Customer_build();//�����˿�����
void Customer_show(Cst_Node* head,int* page);//չʾ���й˿�
void Customer_free(Cst_Node* head);//�ͷ�����ռ�
Cst_Node* Customer_add(Cst_Node* head);//���ӹ˿���Ϣ
void Customer_showvip(Cst_Node* head, int* page);//չʾvip�˿�
Cst_Node* Customer_change(Cst_Node* head);//�޸Ĺ˿���Ϣ
void Customer_save(Cst_Node* head);//��������Ϣ���浽�ļ�����
bool Customer_search(Cst_Node* head);//�����˿���Ϣ
Cst_Node* Customer_delete(Cst_Node* head);//ɾ���˿���Ϣ

void Cus_show(Cst_Node* head,int* page);//���ù˿�չʾ����
void Cus_vipshow(Cst_Node* head,int *page);//����VIPչʾ����
void Cus_change(Cst_Node* head);//���ù˿��޸ĺ���				
void Cus_add(Cst_Node* head);//�������ӹ˿ͺ���				
void Cus_search(Cst_Node* head);//���ò�ѯ�˿ͺ���
void Cus_delete(Cst_Node* head);//����ɾ���˿ͺ���