#include"header.h"
#include<conio.h>
/*管理员模块的函数及菜单界面*/

void AdministratorMenu(Customer customer[], Order order[], Product product[], Factory factory[], int customer_orderNum[])
{
	/* 输入管理员密码方可进入 密码初始为123456  输入5次不成功返回主菜单*/
	char password[7] = "123456";
	int num = 0; /*密码输入次数*/
	int flag = 0; /*密码判断标志位*/
	
	while (1)
	{
		printf("\n\t\t请输入管理员密码:");
		flag = EnterPassword(password);  /*调用输入密码函数*/
		num++;
		
		if (flag == 1) /*密码正确*/
		{
			printf("\n\t\t密码正确!");
			printf("\n\t\t欢迎进入管理员界面");  /*管理员菜单 选择不同功能*/
			printf("\n\t\t");
			system("pause");
			while (1)
			{
				system("cls");
				printf("\n\t\t--------------------");
				printf("\n\t\t01 - 确认用户订单");
				printf("\n\t\t02 - 确认发货信息");
				printf("\n\t\t03 - 删除订单");
				printf("\n\t\t04 - 库存信息查看");
				printf("\n\t\t05 - 联系生产厂家");
				printf("\n\t\t06 - 生成已完成订单列表");
				printf("\n\t\t07 - 生成未付款订单列表");
				printf("\n\t\t08 - 生成未发货订单列表");
				printf("\n\t\t09 - 返回上一级");
				printf("\n\t\t--------------------");
				printf("\n\t\t   请选择(1-9): ");
				
				int option;
				  
				fflush(stdin); 
				scanf("%d",&option);
				
				switch (option)
				{
					case 1:
						TraversalOrder(order, customer_orderNum);
						break;
					case 2:
						CheckTransportInfor(order, customer, customer_orderNum);
						break;
					case 3:
						int var_number;
						int num;
						
						printf("\n\t\t请输入要删除的订单的订单号:");
						
						fflush(stdin);
						scanf("%d",&var_number);/*输入要删除的订单号*/
						
						num = DeleteOrder(order, customer_orderNum, var_number);/*删除订单函数*/
						if (num == -1)
						{
							printf("\n\t\t删除失败\n\t\t");
						}
						else
						{
							printf("\n\t\t删除成功\n\t\t");
						}
						system("pause");
						break;
					case 4:
						ShowProduct(product);
						break;
					case 5:
						ConnectFactory(factory, product);
						break;
					case 6:
						printf("\n\t\t已完成订单\n");
						ShowCompleteOrder(order, customer_orderNum);
						break;
					case 7:
						printf("\n\t\t未付款订单\n");
						ShowNotPay(order, customer_orderNum);
						break;
					case 8:
						printf("\n\t\t未发货订单\n");
						ShowNotTransport(order, customer, customer_orderNum);
						break;
					case 9:
						return;
					default: continue;
				}
			}
				
		}
		else if (flag == -1) /*密码错误*/
		{
			if (num == 5)
			{
				printf("\n\t\t您已输错5次密码，将自动为你退出\n\t\t");
				system("pause");
				
				return;
			}
			
			printf("\n\t\t密码错误，请重新输入");
		}	
	}
}

/*输入密码函数*/
int EnterPassword(char password[]) 
{
	char key[7];
	int i;
	
	for (i=0; i<6; i++)
	{
		key[i] = getch();
		printf("*");
	}
	
	if (strcmp(key, password) == 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

/*对订单进行配送处理*/
void CheckTransportInfor(Order order[], Customer customer[], int customer_orderNum[])
{
	int i;
	int j;
	int option;
	char str_time[30] = {0};/*存储时间的字符串*/
	char *p_time; /*时间指针*/
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].transport_flag == 0)
		{
			j = FindCustomer(customer, customer_orderNum, order[i].customer_num);	
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t顾客姓名:%s",customer[j].name);
			printf("\n\t\t详细信息:%s",order[i].information);
			printf("\n\t\t配送地址:%s",customer[j].address);
			printf("\n\t\t联系电话:%s",customer[j].phone);
			printf("\n\n\t\t下单日期:%s",order[i].pay_date);
			
			printf("\n\t\t是否开始进行配送");
			printf("\n\t\t1 - 是\t2 - 否");
			printf("\n\t\t请输入你的选择:");
			fflush(stdin);
			scanf("%d",&option);
			if (option == 1)
			{
				order[i].transport_flag = 1;
				p_time = GetTime(str_time);
				strcpy(order[i].transport_date, p_time);
				printf("\n\t\t操作完成 已开始配送");
			}
			else
			{
				continue;
			}
		}
	}
	printf("\n\t\t");
	system("pause");
}

/*删除对应订单号的订单*/
int DeleteOrder(Order order[], int customer_orderNum[], int var_number)
{
	int i;
	int j;
	
	i = FindOrder(order, customer_orderNum, var_number);
	if (i == -1)
	{
		return -1;
	}
	
	if (i != customer_orderNum[1] - 1)
	{
		for (j=i; j<customer_orderNum[1]; j++)
		{
			order[j] = order[j+1];
		}
	}
	customer_orderNum[1]--;
	return 0;
}

/*显示所有商品信息及其库存量*/
void ShowProduct(Product product[])
{
	int i;
	
	printf("\n\t\t编号  厂家编号  说明    单价    库存量");
	for (i=0; i<21; i++)
	{
		printf("\n\t\t%-6d%-10s%-8s%.1lf 元  %-3d 份", product[i].category_num, product[i].factory_num
											, product[i].information, product[i].price, product[i].amount);
	}	
	printf("\n\t\t");
	system("pause");
}

/*联系生产厂家并进货缺货的商品*/
void ConnectFactory(Factory factory[], Product product[])
{
	int i;/*迭代器*/
	int j;
	int option;/*商品选择选项*/
	int purchase_num;/*进货数量*/
	int num;/*厂家选择xuanxiang*/
	
	while (1)
	{
		system("cls");
		printf("\n\t\t生产厂家:");
		/*打印厂家信息*/
		for (i=0; i<3;i++)
		{
			printf("\n\t\t%d    %s  %s",i+1, factory[i].num, factory[i].name);
		}
		
		printf("\n\t\t0    退出");
		printf("\n\t\t请输入需要联系的厂家(0-3):");
		
		fflush(stdin);
		scanf("%d",&num);
		
		switch (num)
		{
			case 1:
				printf("\n\t\t编号  商品信息  库存量");
				for (j=0; j<7; j++)
				{
					printf("\n\t\t%-06d%-6s    %-3d",product[j].category_num, product[j].information, product[j].amount);
				}
				
				printf("\n\t\t请输入要进货的商品(输入0退出):");
				
				fflush(stdin);
				scanf("%d",&option);
				
				printf("\n\t\t请输入要购入的数量:");
				
				fflush(stdin);
				scanf("%d",&purchase_num);
				
				if (option>=1 && option<=7)
				{
					product[option -1].amount += purchase_num;
				}
				else
				{
					break;
				}
				break;
			case 2:
				printf("\n\t\t编号  商品信息  库存量");
				for (j=7; j<14; j++)
				{
					printf("\n\t\t%-06d%-6s    %-3d",product[j].category_num, product[j].information, product[j].amount);
				}
				
				printf("\n\t\t请输入要进货的商品(输入0退出):");
				
				fflush(stdin);
				scanf("%d",&option);
				
				printf("\n\t\t请输入要购入的数量:");
				
				fflush(stdin);
				scanf("%d",&purchase_num);
				
				if (option>=8 && option<=14)
				{
					product[option -1].amount += purchase_num;
				}
				else
				{
					break;
				}
				break;
			case 3:
				printf("\n\t\t编号  商品信息  库存量");
				for (j=14; j<21; j++)
				{
					printf("\n\t\t%-06d%-6s    %-3d",product[j].category_num, product[j].information, product[j].amount);
				}
				
				printf("\n\t\t请输入要进货的商品(输入0退出):");
				
				fflush(stdin);
				scanf("%d",&option);
				
				printf("\n\t\t请输入要购入的数量:");
				
				fflush(stdin);
				scanf("%d",&purchase_num);
				
				if (option>=15 && option<=21)
				{
					product[option -1].amount += purchase_num;
				}
				else
				{
					break;
				}
				break;
			case 0:
				return;
		}
	}
		
	printf("\n\t\t");
	system("pause");
}

/*显示已付款及已发货的订单*/
void ShowCompleteOrder(Order order[], int customer_orderNum[])
{
	int i;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].pay_flag == 1 && order[i].transport_flag == 1)
		{
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t运费:%.1lf 元",order[i].transport_pay);
			printf("\n\t\t详细信息:%s",order[i].information);
			printf("\n\t\t数量:%.1lf",order[i].amount);
			printf("\n\t\t总金额:%.1lf 元",order[i].total_price + order[i].transport_pay);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
			printf("\n\t\t配送日期:%s",order[i].transport_date);
		}
	}
	printf("\n\t\t");
	system("pause");
}

/*显示未付款的订单*/
void ShowNotPay(Order order[], int customer_orderNum[])
{
	int i;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].pay_flag == 0)
		{
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t运费:%.1lf 元",order[i].transport_pay);
			printf("\n\t\t详细信息:%s",order[i].information);
			printf("\n\t\t数量:%.1lf",order[i].amount);
			printf("\n\t\t总金额:%.1lf 元",order[i].total_price + order[i].transport_pay);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
			if (order[i].transport_flag == 1)
			{
			printf("\n\t\t发货日期:%s",order[i].transport_date);
			}
		}
	}
	printf("\n\t\t");
	system("pause");
}

/*显示未开始配送的订单*/
void ShowNotTransport(Order order[], Customer customer[], int customer_orderNum[])
{
	int i;
	int j;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].transport_flag == 0)
		{
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t运费:%.1lf 元",order[i].transport_pay);
			printf("\n\t\t详细信息:%s",order[i].information);
			printf("\n\t\t数量:%.1lf",order[i].amount);
			printf("\n\t\t总金额:%.1lf 元",order[i].total_price + order[i].transport_pay);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
		}
	}
	printf("\n\t\t");
	system("pause");
	
}
