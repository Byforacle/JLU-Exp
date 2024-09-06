#pragma once
typedef struct Storage_Node {
    char Num[10];//编号
    char  complete_num[10];//饮品完整数量
    char  loss_num[10];//饮品损耗数量
    char name[30];//饮品名及口味
    char   price[10];//价格
    char    cost_price[10];//成本
    char  Unit_capacity[20];//单品容量
    char  Package_size[20];//包装大小
    struct Storage_Node* next;
}Srg_Node;
Storage_Node* Storage_build();//创建库存链表
void Storage_show(Storage_Node* head,int* page);//展示所有库存
Storage_Node* Storage_add(Storage_Node* head);//增加库存
bool Storage_search(Storage_Node* head);//搜索库存
void Storage_save(Storage_Node* head);//将链表信息储存到文件当中
void Storage_free(Srg_Node* head);//释放链表内存空间
Storage_Node* Storage_change(Storage_Node* head);//修改库存信息
Storage_Node* Storage_delete(Storage_Node* head);//删除库存

void Sto_show(Srg_Node* head, int* page);//调用展示库存函数
void Sto_buy(Srg_Node* head);//调用库存增加函数
void Sto_change(Srg_Node* head);//调用库存修改函数
void Sto_search(Srg_Node* head);//调用库存查询函数
void Sto_erase(Srg_Node* head);//调用库存删除函数
