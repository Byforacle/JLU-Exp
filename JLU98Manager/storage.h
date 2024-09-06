#pragma once
typedef struct Storage_Node {
    char Num[10];//���
    char  complete_num[10];//��Ʒ��������
    char  loss_num[10];//��Ʒ�������
    char name[30];//��Ʒ������ζ
    char   price[10];//�۸�
    char    cost_price[10];//�ɱ�
    char  Unit_capacity[20];//��Ʒ����
    char  Package_size[20];//��װ��С
    struct Storage_Node* next;
}Srg_Node;
Storage_Node* Storage_build();//�����������
void Storage_show(Storage_Node* head,int* page);//չʾ���п��
Storage_Node* Storage_add(Storage_Node* head);//���ӿ��
bool Storage_search(Storage_Node* head);//�������
void Storage_save(Storage_Node* head);//��������Ϣ���浽�ļ�����
void Storage_free(Srg_Node* head);//�ͷ������ڴ�ռ�
Storage_Node* Storage_change(Storage_Node* head);//�޸Ŀ����Ϣ
Storage_Node* Storage_delete(Storage_Node* head);//ɾ�����

void Sto_show(Srg_Node* head, int* page);//����չʾ��溯��
void Sto_buy(Srg_Node* head);//���ÿ�����Ӻ���
void Sto_change(Srg_Node* head);//���ÿ���޸ĺ���
void Sto_search(Srg_Node* head);//���ÿ���ѯ����
void Sto_erase(Srg_Node* head);//���ÿ��ɾ������
