#include "Manager.h"
#include"customer.h"
#include"storage.h"
#include"purchase.h"
#include"order.h"
#include"prediction.h"
//欢迎界面函数
void Welcome()
{
	loadimage(NULL, _T("welcome1.jpg"), 1366, 700);//加载图片
	/*下面进行鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 232 && msg.x < 498 && msg.y > 478 && msg.y < 543)//鼠标点击特定区域，即ENTER按钮所在区域
				{
					loadimage(NULL, _T("welcome_button1.jpg"), 1366, 700);//加载图片
					Sleep(100);//延时，降低CPU占用率，并且做到点击效果
					char password[12];//定义一个临时存储密码的字符数组
					char Password[12];
						/*输入密码模块*/
					FILE* fp = fopen("Password.txt", "r");
					if (fp == NULL)
					{
						MessageBox(NULL, _T("密码文件为空"), _T("酒水管理系统"), MB_SETFOREGROUND);

					}
					else fscanf(fp, "%s", &Password);
					while(1)
					{
						if(InputBox(password, 10, "请输入密码", NULL, NULL, 0, 0, false))
						{
							if (strcmp(password, Password) == 0)//密码符合 
							{
								MessageBox(NULL, _T("登录成功！"), _T("酒水管理系统"), MB_SETFOREGROUND);
								MainMenu();//调用一级主菜单选项函数
								break;
							}//结束密码输入模块 
							else
								MessageBox(NULL, _T("密码错误"), _T("酒水管理系统"), MB_ICONSTOP | MB_SETFOREGROUND);
						}//提示用户输入密码，输入给临时存储密码的字符数组
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
	loadimage(NULL, _T("main.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息1
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)
					Cus_manage();//调用顾客管理函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)
					Stock_manage();//调用库存管理函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)
					Money_manage();//调用财务管理函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)					
					Order_manage();//调用菜单修改函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)				
					Prediction();//调用回归预测函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 528 && msg.y < 597)				
					Password_change();//调用修改密码函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Welcome();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Cus_manage()//顾客管理函数
{
	loadimage(NULL, _T("cus_manage.jpg"), 1366, 700);//加载图片
	//loadimage(&Cus_manage1, L"cus_manage.jpg");//导入主界面
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Cst_Node* head = Customer_build();//创建链表
	int page = 1;
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击特定区域，即“顾客展示”按钮所在区域
					Cus_show(head,&page);//调用顾客展示函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击特定区域，即“VIP展示”按钮所在区域
					Cus_vipshow(head,&page);//调用VIP展示函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击特定区域，即“顾客修改”按钮所在区域
					Cus_change(head);//调用顾客修改函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//鼠标点击特定区域，即“增加顾客”按钮所在区域					
					Cus_add(head);//调用增加顾客函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)//鼠标点击特定区域，即“查询顾客”按钮所在区域					
					Cus_search(head);//调用查询顾客函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 528 && msg.y < 597)//鼠标点击特定区域，即“删除顾客”按钮所在区域					
					Cus_delete(head);//调用删除顾客函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Customer_save(head);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}     
void Stock_manage()//调用库存管理函数
{
	loadimage(NULL, _T("Stock_manage.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Srg_Node* head= Storage_build();//创建库存链表
	int page = 1;
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击特定区域，即“顾客展示”按钮所在区域
					Sto_show(head, &page);//调用展示库存函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击特定区域，即“VIP展示”按钮所在区域
					Sto_buy(head);//调用购入库存函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击特定区域，即“顾客修改”按钮所在区域
					Sto_change(head);//调用修改库存函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//鼠标点击特定区域，即“增加顾客”按钮所在区域					
					Sto_search(head);//调用搜索库存函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 436 && msg.y < 505)//鼠标点击特定区域，即“查询顾客”按钮所在区域					
					Sto_erase(head);//调用删除库存函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Storage_save(head);//保存文件
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Money_manage()//调用财务管理函数
{
	loadimage(NULL, _T("Mon_manage.jpg"), 1366, 700);//加载图片
	//loadimage(&Cus_manage1, L"cus_manage.jpg");//导入主界面
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Pcs_Node* head = Purchase_build();//创建购买记录链表
	int page = 1;
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击特定区域，即“顾客展示”按钮所在区域
					Pur_show(head,&page);//调用展示购买记录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击特定区域，即“VIP展示”按钮所在区域
					Pur_Moneyshow();//调用展示现有资金函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击特定区域，即“顾客修改”按钮所在区域
					Pur_search(head);;//调用查询购买记录函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Purchase_save(head);//保存购买记录文件
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Purchase_save(head);//保存购买记录文件
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Order_manage()//订单处理函数
{
	loadimage(NULL, _T("Ord_manage.jpg"), 1366, 700);//加载图片
/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Odr_Node* head=Order_build();//创建链表
	int page = 1;
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)
					Ord_show(head,&page);//调用订单记录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)
					Ord_income(head,&page);//调用收入记录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)
					Ord_deal(head);//调用处理订单函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)				
					Ord_search(head);//调用查询订单函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Order_save(head);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Order_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Ord_show(Odr_Node* head, int* page)//展示订单记录界面
{
	loadimage(NULL, _T("Ord_show.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Order_show(head, page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Order_save(head);//调用文件保存函数
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Order_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Ord_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Ord_show(head, page);
				}
			}
		}
	}
}
void Ord_income(Odr_Node* head, int* page)//展示收入界面
{
	loadimage(NULL, _T("Ord_income1.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Order_income(head, page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Order_save(head);//调用文件保存函数
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Order_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Ord_income(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Ord_income(head, page);
				}
			}
		}
	}
}
void Ord_deal(Odr_Node* head)//处理当前订单界面
{
	loadimage(NULL, _T("Ord_deal.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	head=Order_deal(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Order_save(head);//调用文件保存函数
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Order_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Ord_search(Odr_Node* head)//查询订单记录界面
{
	loadimage(NULL, _T("Ord_search.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Order_search(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Order_save(head);//调用文件保存函数
					Order_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Order_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Prediction()//回归分析函数
{
	loadimage(NULL, _T("Prediction.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息1
	float first, second;//接受回归分析变量
	Data_analysis(&first,&second);
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					MainMenu();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Sto_show(Srg_Node* head, int* page)//调用展示库存函数
{
	loadimage(NULL, _T("Sto_show.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Storage_show(head, page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Storage_save(head);;
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Sto_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Sto_show(head, page);
				}
			}
		}
	}
}
void Sto_buy(Srg_Node* head)//调用库存增加函数
{
	loadimage(NULL, _T("Sto_buy.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	head=Storage_add(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Storage_save(head);//调用文件保存函数
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Sto_change(Srg_Node* head)//调用库存修改函数
{
	loadimage(NULL, _T("Sto_change.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	Storage_change(head);
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Storage_save(head);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Sto_search(Srg_Node* head)//调用库存查询函数
{
	loadimage(NULL, _T("Sto_search.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Storage_search(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Sto_erase(Srg_Node* head)//调用库存删除函数
{
	loadimage(NULL, _T("Sto_erase.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	Storage_delete(head);
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Storage_save(head);
					Stock_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Storage_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Password_change()
{
	char password[12];
	InputBox(password, 11, _T("输入要修改的密码"));
	FILE* fp = fopen("Password.txt", "w");
	fprintf(fp,"%s",password);
	fclose(fp);
	MessageBox(NULL, _T("修改成功"), _T("酒水管理系统"), MB_SETFOREGROUND);
	Welcome();

}
void Cus_show(Cst_Node* head,int* page)//调用顾客展示函数
{
	loadimage(NULL, _T("Cus_show.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Customer_show(head,page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Customer_save(head);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Cus_show(head,page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Cus_show(head,page);
				}
			}
		}
	}
}
void Cus_vipshow(Cst_Node* head,int *page)//调用VIP展示函数
{
	loadimage(NULL, _T("Cus_showvip.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Customer_showvip(head,page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Cus_vipshow(head,page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Cus_vipshow(head,page);
				}
			}
		}
	}
}
void Cus_change(Cst_Node* head)//调用修改顾客函数
{
	loadimage(NULL, _T("Cus_change.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Customer_change(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Customer_save(head);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Cus_add(Cst_Node* head)//调用增加顾客函数
{
	loadimage(NULL, _T("Cus_add1.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	head = Customer_add(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Customer_save(head);//调用文件保存函数
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Cus_search(Cst_Node* head)//调用查询顾客函数
{
	loadimage(NULL, _T("Cus_search.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Customer_search(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Cus_delete(Cst_Node* head)
{
	loadimage(NULL, _T("Cus_delete.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	head = Customer_delete(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Customer_save(head);//调用文件保存函数
					Cus_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Customer_save(head);//调用文件保存函数
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Pur_show(Pcs_Node* head, int* page)//展示购买记录界面
{
	loadimage(NULL, _T("Pur_show.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Purchase_show(head, page);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Purchase_save(head);//保存购买记录文件
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Purchase_save(head);//保存购买记录文件
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“下一页”按钮所在区域
				{
					(*page)++;
					Pur_show(head, page);
				}
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//点击“上一页”按钮所在区域
				{
					(*page)--;
					Pur_show(head, page);
				}
			}
		}
	}
}
void Pur_Moneyshow()//展示现有资金界面
{
	loadimage(NULL, _T("Pur_showmoney.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Purchase_Moneyshow();
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
void Pur_search(Pcs_Node* head)//查询购买记录界面
{
	loadimage(NULL, _T("Pur_search.jpg"), 1366, 700);//加载图片
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	Purchase_search(head);
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{
					Sleep(100);
					Money_manage();
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					Purchase_save(head);//保存购买记录文件
					Sleep(100);
					loadimage(NULL, _T("end.jpg"), 1366, 700);//加载图片
				}
			}
		}
	}
}
