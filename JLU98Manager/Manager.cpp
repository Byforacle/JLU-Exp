#include "Manager.h"
#include"customer.h"
#include"storage.h"
#include"purchase.h"
#include"order.h"
#include"prediction.h"
//��ӭ���溯��
void Welcome()
{
	loadimage(NULL, _T("welcome1.jpg"), 1366, 700);//����ͼƬ
	/*���������꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 232 && msg.x < 498 && msg.y > 478 && msg.y < 543)//������ض����򣬼�ENTER��ť��������
				{
					loadimage(NULL, _T("welcome_button1.jpg"), 1366, 700);//����ͼƬ
					Sleep(100);//��ʱ������CPUռ���ʣ������������Ч��
					char password[12];//����һ����ʱ�洢������ַ�����
					char Password[12];
						/*��������ģ��*/
					FILE* fp = fopen("Password.txt", "r");
					if (fp == NULL)
					{
						MessageBox(NULL, _T("�����ļ�Ϊ��"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);

					}
					else fscanf(fp, "%s", &Password);
					while(1)
					{
						if(InputBox(password, 10, "����������", NULL, NULL, 0, 0, false))
						{
							if (strcmp(password, Password) == 0)//������� 
							{
								MessageBox(NULL, _T("��¼�ɹ���"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
								MainMenu();//����һ�����˵�ѡ���
								break;
							}//������������ģ�� 
							else
								MessageBox(NULL, _T("�������"), _T("��ˮ����ϵͳ"), MB_ICONSTOP | MB_SETFOREGROUND);
						}//��ʾ�û��������룬�������ʱ�洢������ַ�����
						else
						{
							Welcome();
						}
					} 
				}
			}
		}
	}
}
void MainMenu()
{
	loadimage(NULL, _T("main.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ1
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)
					Cus_manage();//���ù˿͹�����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)
					Stock_manage();//���ÿ�������
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)
					Money_manage();//���ò��������
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)					
					Order_manage();//���ò˵��޸ĺ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)				
					Prediction();//���ûع�Ԥ�⺯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 528 && msg.y < 597)				
					Password_change();//�����޸����뺯��
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Welcome();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Cus_manage()//�˿͹�����
{
	loadimage(NULL, _T("cus_manage.jpg"), 1366, 700);//����ͼƬ
	//loadimage(&Cus_manage1, L"cus_manage.jpg");//����������
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Cst_Node* head = Customer_build();//��������
	int page = 1;
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//������ض����򣬼����˿�չʾ����ť��������
					Cus_show(head,&page);//���ù˿�չʾ����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//������ض����򣬼���VIPչʾ����ť��������
					Cus_vipshow(head,&page);//����VIPչʾ����
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//������ض����򣬼����˿��޸ġ���ť��������
					Cus_change(head);//���ù˿��޸ĺ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//������ض����򣬼������ӹ˿͡���ť��������					
					Cus_add(head);//�������ӹ˿ͺ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)//������ض����򣬼�����ѯ�˿͡���ť��������					
					Cus_search(head);//���ò�ѯ�˿ͺ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 528 && msg.y < 597)//������ض����򣬼���ɾ���˿͡���ť��������					
					Cus_delete(head);//����ɾ���˿ͺ���
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Customer_save(head);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}     
void Stock_manage()//���ÿ�������
{
	loadimage(NULL, _T("Stock_manage.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Srg_Node* head= Storage_build();//�����������
	int page = 1;
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//������ض����򣬼����˿�չʾ����ť��������
					Sto_show(head, &page);//����չʾ��溯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//������ض����򣬼���VIPչʾ����ť��������
					Sto_buy(head);//���ù����溯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//������ض����򣬼����˿��޸ġ���ť��������
					Sto_change(head);//�����޸Ŀ�溯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//������ض����򣬼������ӹ˿͡���ť��������					
					Sto_search(head);//����������溯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)//������ض����򣬼�����ѯ�˿͡���ť��������					
					Sto_erase(head);//����ɾ����溯��
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Storage_save(head);//�����ļ�
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Money_manage()//���ò��������
{
	loadimage(NULL, _T("Mon_manage.jpg"), 1366, 700);//����ͼƬ
	//loadimage(&Cus_manage1, L"cus_manage.jpg");//����������
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Pcs_Node* head = Purchase_build();//���������¼����
	int page = 1;
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//������ض����򣬼����˿�չʾ����ť��������
					Pur_show(head,&page);//����չʾ�����¼����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//������ض����򣬼���VIPչʾ����ť��������
					Pur_Moneyshow();//����չʾ�����ʽ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//������ض����򣬼����˿��޸ġ���ť��������
					Pur_search(head);;//���ò�ѯ�����¼����
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Purchase_save(head);//���湺���¼�ļ�
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Purchase_save(head);//���湺���¼�ļ�
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Order_manage()//����������
{
	loadimage(NULL, _T("Ord_manage.jpg"), 1366, 700);//����ͼƬ
/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Odr_Node* head=Order_build();//��������
	int page = 1;
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)
					Ord_show(head,&page);//���ö�����¼����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)
					Ord_income(head,&page);//���������¼����
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)
					Ord_deal(head);//���ô���������
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)				
					Ord_search(head);//���ò�ѯ��������
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Order_save(head);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Order_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Ord_show(Odr_Node* head, int* page)//չʾ������¼����
{
	loadimage(NULL, _T("Ord_show.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Order_show(head, page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Order_save(head);//�����ļ����溯��
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Order_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Ord_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Ord_show(head, page);
				}
			}
		}
	}
}
void Ord_income(Odr_Node* head, int* page)//չʾ�������
{
	loadimage(NULL, _T("Ord_income1.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Order_income(head, page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Order_save(head);//�����ļ����溯��
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Order_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Ord_income(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Ord_income(head, page);
				}
			}
		}
	}
}
void Ord_deal(Odr_Node* head)//����ǰ��������
{
	loadimage(NULL, _T("Ord_deal.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	head=Order_deal(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Order_save(head);//�����ļ����溯��
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Order_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Ord_search(Odr_Node* head)//��ѯ������¼����
{
	loadimage(NULL, _T("Ord_search.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Order_search(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Order_save(head);//�����ļ����溯��
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Order_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Prediction()//�ع��������
{
	loadimage(NULL, _T("Prediction.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ1
	float first, second;//���ܻع��������
	Data_analysis(&first,&second);
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Sto_show(Srg_Node* head, int* page)//����չʾ��溯��
{
	loadimage(NULL, _T("Sto_show.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Storage_show(head, page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Storage_save(head);;
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Sto_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Sto_show(head, page);
				}
			}
		}
	}
}
void Sto_buy(Srg_Node* head)//���ÿ�����Ӻ���
{
	loadimage(NULL, _T("Sto_buy.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	head=Storage_add(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Storage_save(head);//�����ļ����溯��
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Sto_change(Srg_Node* head)//���ÿ���޸ĺ���
{
	loadimage(NULL, _T("Sto_change.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	Storage_change(head);
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Storage_save(head);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Sto_search(Srg_Node* head)//���ÿ���ѯ����
{
	loadimage(NULL, _T("Sto_search.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Storage_search(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Sto_erase(Srg_Node* head)//���ÿ��ɾ������
{
	loadimage(NULL, _T("Sto_erase.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	Storage_delete(head);
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Storage_save(head);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Storage_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Password_change()
{
	char password[12];
	InputBox(password, 11, _T("����Ҫ�޸ĵ�����"));
	FILE* fp = fopen("Password.txt", "w");
	fprintf(fp,"%s",password);
	fclose(fp);
	MessageBox(NULL, _T("�޸ĳɹ�"), _T("��ˮ����ϵͳ"), MB_SETFOREGROUND);
	Welcome();

}
void Cus_show(Cst_Node* head,int* page)//���ù˿�չʾ����
{
	loadimage(NULL, _T("Cus_show.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Customer_show(head,page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Customer_save(head);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Cus_show(head,page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Cus_show(head,page);
				}
			}
		}
	}
}
void Cus_vipshow(Cst_Node* head,int *page)//����VIPչʾ����
{
	loadimage(NULL, _T("Cus_showvip.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Customer_showvip(head,page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Cus_vipshow(head,page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Cus_vipshow(head,page);
				}
			}
		}
	}
}
void Cus_change(Cst_Node* head)//�����޸Ĺ˿ͺ���
{
	loadimage(NULL, _T("Cus_change.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Customer_change(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Customer_save(head);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Cus_add(Cst_Node* head)//�������ӹ˿ͺ���
{
	loadimage(NULL, _T("Cus_add1.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	head = Customer_add(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Customer_save(head);//�����ļ����溯��
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Cus_search(Cst_Node* head)//���ò�ѯ�˿ͺ���
{
	loadimage(NULL, _T("Cus_search.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Customer_search(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Cus_delete(Cst_Node* head)
{
	loadimage(NULL, _T("Cus_delete.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	head = Customer_delete(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Customer_save(head);//�����ļ����溯��
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Customer_save(head);//�����ļ����溯��
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Pur_show(Pcs_Node* head, int* page)//չʾ�����¼����
{
	loadimage(NULL, _T("Pur_show.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Purchase_show(head, page);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Purchase_save(head);//���湺���¼�ļ�
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Purchase_save(head);//���湺���¼�ļ�
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������һҳ����ť��������
				{
					(*page)++;
					Pur_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//�������һҳ����ť��������
				{
					(*page)--;
					Pur_show(head, page);
				}
			}
		}
	}
}
void Pur_Moneyshow()//չʾ�����ʽ����
{
	loadimage(NULL, _T("Pur_showmoney.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Purchase_Moneyshow();
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
void Pur_search(Pcs_Node* head)//��ѯ�����¼����
{
	loadimage(NULL, _T("Pur_search.jpg"), 1366, 700);//����ͼƬ
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	Purchase_search(head);
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{
					Sleep(100);
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					Purchase_save(head);//���湺���¼�ļ�
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//����ͼƬ
				}
			}
		}
	}
}
