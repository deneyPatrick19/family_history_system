#include "nodeheader.h"
#include<conio.h>

void AdministratorMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead, Factory* factory)
{	
/* 输入管理员密码方可进入 密码初始为123456  输入5次不成功返回主菜单*/
	char password[7] = "123456";
	int num = 0; /*密码输入次数*/
	int flag = 0; /*密码判断标志位*/
	
	while (1)
	{
		printf("\n请输入管理员密码:");
		flag = EnterPassword(password);  /*调用输入密码函数*/
		num++;
		
		if (flag == 1) /*密码正确*/
		{
			printf("\n密码正确!");
			printf("\n欢迎进入管理员界面\n");  /*管理员菜单 选择不同功能*/
			system("pause");
			while (1)
			{
				system("cls");
				printf("\n--------------------");
				printf("\n01 - 确认用户订单");
				printf("\n02 - 确认发货信息");
				printf("\n03 - 删除订单");
				printf("\n04 - 库存信息查看");
				printf("\n05 - 联系生产厂家");
				printf("\n06 - 生成已完成订单列表");
				printf("\n07 - 生成未付款订单列表");
				printf("\n08 - 生成未发货订单列表");
				printf("\n09 - 返回上一级");
				printf("\n--------------------");
				printf("\n   请选择(1-9): ");
				
				int option;
				int OrderNumber;/*订单号 用于查找、支付等功能*/
				  
				fflush(stdin); 
				scanf("%d",&option);
				
				switch (option)
				{
					case 1:
						/*显示所有的订单 若没有订单返回-1 显示提示信息*/
						if (TraversalOrder(OrNodeHead, CusNodeHead) == -1)
						{
							printf("\n没有任何订单");
						}
						break;
					case 2:
						/*对未配送订单进行是否发货操作 返回-1则没有可进行操作的订单*/
						if (CheckTransportInformation(OrNodeHead, CusNodeHead) == -1)
						{
							printf("\n没有可进行操作的订单");
						}
						break;
					case 3:
						/*输入订单号删除订单*/
						printf("\n请输入要删除的订单的订单号(0 退出功能):");
						
						fflush(stdin);
						scanf("%d",&OrderNumber);/*输入要删除的订单号*/
						
						/*若输入0返回上一界面  否则进行删除*/
						if (OrderNumber == 0)
						{
							break;
						}
						else
						{
							/*删除订单函数*/
							if (DeleteOrderByAdministrator(OrNodeHead, ProNodeHead, OrderNumber) == -1)
							{
								printf("\n删除失败");
							}
						}
						
						break;
					case 4:
						/*显示所有商品信息及库存量*/
						ShowProduct(ProNodeHead);
						break;
					case 5:
						/*联系生产厂家对商品进行补货*/
						ConnectFactory(ProNodeHead, factory);
						break;
					case 6:
						/*显示所有已经付款及配送的订单*/
						printf("\n已完成订单:\n");
						
						if (ShowCompleteOrder(OrNodeHead, CusNodeHead) == -1)
						{
							printf("\n没有符合条件的订单");
						}
						break;
					case 7:
						/*显示没有付款的订单*/
						printf("\n未付款订单:\n");
						
						if (ShowNotPay(OrNodeHead, CusNodeHead) == -1)
						{
							printf("\n没有符合条件的订单");
						}
						break;
					case 8:
						/*显示没有开始配送的订单*/
						printf("\n未发货订单:\n");
						
						if (ShowNotTransport(OrNodeHead, CusNodeHead) == -1)
						{
							printf("\n没有符合条件的订单");
						}
						break;
					case 9:
						return;
					default: continue;
				}
				printf("\n");
				system("pause");
			}
				
		}
		else if (flag == -1) /*密码错误*/
		{
			if (num == 5)/*5次输错密码*/
			{
				printf("\n您已输错5次密码，将自动为你退出\n");
				system("pause");
				
				return;
			}
			/*提示重新输入*/
			printf("\n密码错误，请重新输入");
		}	
	}
}

/*输入密码函数*/
int EnterPassword(char* password) 
{
	char key[7];/*储存密码字符串*/
	int i;/*迭代器*/
	
	/*getch将输入字符隐藏 再输出*号 以达密码的效果*/
	for (i=0; i<6; i++)
	{
		key[i] = getch();
		printf("*");
	}
	
	/*判断是否比较成功 成功返回1 失败返回-1*/
	if (strcmp(key, password) == 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/*遍历显示订单链表所有订单*/
int TraversalOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead)
{
	OrderNode* p = OrNodeHead->next;
	CustomerNode* p_customer = NULL;
	int num = 0;
	
	while (p != NULL)
	{
		/*显示订单信息*/
		p_customer = FindCustomer(CusNodeHead, p->data.customer_num);
		printf("\n订单号:%d",p->data.number);
		printf("\n顾客代码:%d",p->data.customer_num);
		printf("\n顾客姓名:%s",p_customer->data.name);
		printf("\n订单费用:%.1lf 元",p->data.total_price);
		printf("\n运费:%.1lf 元",p->data.transport_pay);
		printf("\n总费用:%.1lf 元",p->data.total_price + p->data.transport_pay);
		printf("\n详细信息:%s",p->data.information);
		printf("\n数量:%.0lf",p->data.amount);
		printf("\n下单日期:%s",p->data.pay_date);
		/*若已经开始配送 显示配送日期*/
		if (p->data.transport_flag == 1)
		{
			printf("\n配送日期:%s",p->data.transport_date);
		}
		
		p = p->next;
		num++;
	}
	
	if (num == 0)
	{
		return -1;
	}
	return 1;
}

/*对未配送订单进行是否开始配送操作*/
int CheckTransportInformation(OrderNode* OrNodeHead, CustomerNode* CusNodeHead)
{
	char str_time[30] = {0};/*存储时间的字符串*/
	char *p_time; 			/*时间指针*/
	
	OrderNode* p_order = OrNodeHead->next;
	CustomerNode* p_customer = NULL;
	/*选项*/
	int option;
	int num = 0;
	
	/*遍历订单链表*/
	while (p_order !=NULL)
	{
		/*若已经付款但尚未开始配送 显示订单信息*/
		if (p_order->data.transport_flag == 0 && p_order->data.pay_flag == 1)
		{
			num++;
			/*查找顾客*/
			p_customer = FindCustomer(CusNodeHead, p_order->data.customer_num);	
			printf("\n订单号:%d",p_order->data.number);
			printf("\n顾客代码:%d",p_order->data.customer_num);
			printf("\n顾客姓名:%s",p_customer->data.name);
			printf("\n详细信息:%s",p_order->data.information);
			printf("\n配送地址:%s",p_customer->data.address);
			printf("\n联系电话:%s",p_customer->data.phone);
			printf("\n\n下单日期:%s",p_order->data.pay_date);
			
			/*进行配送选择*/
			printf("\n是否开始进行配送");
			printf("\n1 - 是\t2 - 否");
			printf("\n0 - 退出");/*输入 0 退出*/
			printf("\n请输入你的选择:");
			
			fflush(stdin);
			scanf("%d",&option);
			
			if (option == 1)
			{
				/*将订单设为已开始配送*/
				p_order->data.transport_flag = 1;
				
				/*获取开始配送时间并赋值给订单*/
				p_time = GetTime(str_time);
				strcpy(p_order->data.transport_date, p_time);
				
				printf("\n操作完成 已开始配送");
				
				return 0;
			}
			else if (option == 0)/*退出*/
			{
				return 0;
			}
			else
			{
				p_order = p_order->next;
				continue;
			}
		}
		
		p_order = p_order->next;
	}
	
	if (num == 0)
	{
		return -1;
	}
	return 0;
}

/*删除特定订单号的订单*/
int DeleteOrderByAdministrator(OrderNode* OrNodeHead, ProductNode* ProNodeHead, int number)
{
	OrderNode* p =OrNodeHead;
	OrderNode* pfollow = p->next;/*跟随指针*/
	
	while (pfollow != NULL)
	{
		if (p->next->data.number == number)/*当下一个节点的订单号相同时*/
		{
			p->next = pfollow->next;/*连接要删除节点的下一节点*/
			
			printf("\n删除成功");
			
			free(pfollow);/*释放要删除的节点的堆空间*/

			return 1;
		}
		
		/*两个指针移动*/
		p = p->next;
		pfollow = pfollow->next;
	}
	
	return -1;
}

/*显示所有商品具体信息及其库存量*/
void ShowProduct(ProductNode* ProNodeHead)
{
	ProductNode* p = ProNodeHead->next;
	
	printf("\n编号  厂家编号  说明    单价    库存量");
	
	while (p != NULL)
	{
		printf("\n%-6d%-10s%-8s%.1lf 元  %-3d 份", p->data.category_num, p->data.factory_num
											, p->data.information, p->data.price, p->data.amount);
		p = p->next;
	}
}

/*联系生产厂家对商品进行补货处理*/
void ConnectFactory(ProductNode* ProNodeHead, Factory* factory)
{
	int i;/*迭代器*/
	int option;/*商品选择选项*/
	int purchase_num;/*进货数量*/
	int choice;/*厂家选择选项*/
	
	ProductNode* p = ProNodeHead->next;
	ProductNode* p_product = NULL;
	
	while (1)
	{
		system("cls");
		p = ProNodeHead->next;
		printf("\n生产厂家:");
		/*打印厂家信息*/
		for (i=0; i<3;i++)
		{
			printf("\n%d    %s  %s",i+1, factory[i].num, factory[i].name);
		}
		
		printf("\n0    退出");
		printf("\n请输入需要联系的厂家(0-3):");
		
		/*选择厂家*/
		fflush(stdin);
		scanf("%d",&choice);
		
		/*根据选择显示各厂家的所有商品并选择商品进货*/
		switch (choice)
		{
			case 0:/*退出*/
				return;
			case 1:
				/*显示所有商品*/
				printf("\n编号  商品信息  库存量");
				for (i=0; i<7; i++)
				{
					printf("\n%-06d%-6s    %-3d",p->data.category_num, p->data.information, p->data.amount);
					p = p->next;
				}
				
				printf("\n请输入要进货的商品(输入0退出):");
				
				/*选择要进货的商品*/
				fflush(stdin);
				scanf("%d",&option);
								
				if (option>=1 && option<=7)/*若输入不为0 */
				{
					p_product = FindProduct(ProNodeHead, option);/*寻找商品在链表的节点*/
				
					printf("\n请输入要购入的数量:");
					
					/*输入要进货的数量*/
					fflush(stdin);
					scanf("%d",&purchase_num);
					
					/*库存量相应增加*/
					p_product->data.amount += purchase_num;
				}
				break;
			case 2:
				printf("\n编号  商品信息  库存量");
				for (i=0; i<7; i++)
				{
					printf("\n%-06d%-6s    %-3d",p->data.category_num, p->data.information, p->data.amount);
					p = p->next;
				}
				
				printf("\n请输入要进货的商品(输入0退出):");
				
				fflush(stdin);
				scanf("%d",&option);
				
				if (option>=8 && option<=14)
				{
					p_product = FindProduct(ProNodeHead, option);
				
					printf("\n请输入要购入的数量:");
					
					fflush(stdin);
					scanf("%d",&purchase_num);
					
					p_product->data.amount += purchase_num;
				}
				break;
			case 3:
				printf("\n编号  商品信息  库存量");
				for (i=0; i<7; i++)
				{
					printf("\n%-06d%-6s    %-3d",p->data.category_num, p->data.information, p->data.amount);
					p = p->next;
				}
				
				printf("\n请输入要进货的商品(输入0退出):");
				
				fflush(stdin);
				scanf("%d",&option);
								
				if (option>=15 && option<=21)
				{
					p_product = FindProduct(ProNodeHead, option);
				
					printf("\n请输入要购入的数量:");
					
					fflush(stdin);
					scanf("%d",&purchase_num);
					
					p_product->data.amount += purchase_num;
				}
				break;
		}
	}
}

/*显示所有已经付款及配送的订单*/
int ShowCompleteOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead)
{
	OrderNode* p = OrNodeHead->next;
	CustomerNode* p_customer = NULL;
	int num = 0;/*统计数*/
	
	/*遍历链表*/
	while (p != NULL)
	{
		p_customer = FindCustomer(CusNodeHead, p->data.customer_num);
		if (p->data.pay_flag == 1 && p->data.transport_flag == 1)/*订单已经付款及开始配送*/
		{
			p_customer = FindCustomer(CusNodeHead, p->data.customer_num);
			printf("\n订单号:%d",p->data.number);
			printf("\n顾客代码:%d",p->data.customer_num);
			printf("\n顾客姓名:%s",p_customer->data.name);
			printf("\n订单费用:%.1lf 元",p->data.total_price);
			printf("\n运费:%.1lf 元",p->data.transport_pay);
			printf("\n详细信息:%s",p->data.information);
			printf("\n数量:%.0lf",p->data.amount);
			printf("\n总金额:%.1lf 元",p->data.total_price + p->data.transport_pay);
			printf("\n下单日期:%s",p->data.pay_date);
			
			if (p->data.transport_flag == 1)
			{
				printf("\n配送日期:%s",p->data.transport_date);
			}
			
			num++;/*统计数加1*/
		}
		
		p = p->next;
	}
	
	if (num == 0)/*若统计数为0 则没有符合条件的订单 给出提示信息*/
	{
		return -1;
	}
	return 1;
}

/*显示没有付款的订单*/
int ShowNotPay(OrderNode* OrNodeHead, CustomerNode* CusNodeHead)
{
	OrderNode* p = OrNodeHead->next;
	CustomerNode* p_customer = NULL;
	int num = 0;
	
	while (p != NULL)
	{
		if (p->data.pay_flag == 0)
		{
			p_customer = FindCustomer(CusNodeHead, p->data.customer_num);
			printf("\n订单号:%d",p->data.number);
			printf("\n顾客代码:%d",p->data.customer_num);
			printf("\n顾客姓名:%s",p_customer->data.name);
			printf("\n订单费用:%.1lf 元",p->data.total_price);
			printf("\n运费:%.1lf 元",p->data.transport_pay);
			printf("\n详细信息:%s",p->data.information);
			printf("\n数量:%.0lf",p->data.amount);
			printf("\n总金额:%.1lf 元",p->data.total_price + p->data.transport_pay);
			printf("\n下单日期:%s",p->data.pay_date);
			
			if (p->data.transport_flag == 1)
			{
				printf("\n配送日期:%s",p->data.transport_date);
			}
			
			num++;
		}
		
		p = p->next;
	}
	if (num == 0)
	{
		return -1;
	}
	return 1;
}

/*显示没有开始配送的订单*/
int ShowNotTransport(OrderNode* OrNodeHead, CustomerNode* CusNodeHead)
{
	OrderNode* p = OrNodeHead->next;
	CustomerNode* p_customer = NULL;
	int num = 0;
	
	while (p != NULL)
	{
		if (p->data.transport_flag == 0)
		{
			p_customer = FindCustomer(CusNodeHead, p->data.customer_num);
			printf("\n订单号:%d",p->data.number);
			printf("\n顾客代码:%d",p->data.customer_num);
			printf("\n顾客姓名:%s",p_customer->data.name);
			printf("\n订单费用:%.1lf 元",p->data.total_price);
			printf("\n运费:%.1lf 元",p->data.transport_pay);
			printf("\n详细信息:%s",p->data.information);
			printf("\n数量:%.0lf",p->data.amount);
			printf("\n总金额:%.1lf 元",p->data.total_price + p->data.transport_pay);
			printf("\n下单日期:%s",p->data.pay_date);
			
			if (p->data.transport_flag == 1)
			{
				printf("\n配送日期:%s",p->data.transport_date);
			}
			
			num++;
		}
		
		p = p->next;
	}
	if (num == 0)
	{
		return -1;
	}
	return 1;
}