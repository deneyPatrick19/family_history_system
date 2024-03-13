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
				printf("\n\t\t03 - 打印发票");
				printf("\n\t\t04 - 打印邮寄信息");
				printf("\n\t\t05 - 库存信息查看");
				printf("\n\t\t06 - 联系生产厂家");
				printf("\n\t\t07 - 生成已完成订单列表");
				printf("\n\t\t08 - 生成未付款订单列表");
				printf("\n\t\t09 - 生成未发货订单列表");
				printf("\n\t\t10 - 返回上一级");
				printf("\n\t\t--------------------");
				printf("\n\t\t   请选择(1-10): ");
				
				int option;
				  
				fflush(stdin); 
				scanf("%d",&option);
				
				switch (option)
				{
					case 1:
						TraversalOrder(order, customer_orderNum);
						break;
					case 2:
						break;
					case 3:
						break;
					case 4:
						break;
					case 5:
						ShowProduct(product);
						break;
					case 6:
						
						break;
					case 7:
						printf("\n\t\t已完成订单\n");
						ShowCompleteOrder(order, customer_orderNum);
						break;
					case 8:
						printf("\n\t\t未付款订单\n");
						ShowNotPay(order, customer_orderNum);
						break;
					case 9:
						printf("\n\t\t未发货订单\n");
						ShowNotTransport(order, customer, customer_orderNum);
						break;
					case 10:
						printf("\n\t\t");
						system("pause");
						return;
					default: continue;
				}
			}	
		}
		else if (flag == -1) /*密码错误*/
		{
			if (num == 5)
			{
				printf("\n\t\t您已输错5次密码，将自动为你退出");
				system("pause");
				
				return;
			}
			
			printf("\n\t\t密码错误，请重新输入");
		}	
	}
}

int EnterPassword(char password[]) /*输入密码函数*/
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


void ShowProduct(Product product[])
{
	int i;
	
	printf("\n\t\t编号  厂家编号  说明    单价");
	for (i=0; i<21; i++)
	{
		printf("\n\t\t%-6d%-10s%-8s%.1lf 元",product[i].category_num,product[i].factory_num,product[i].information,product[i].price);
	}	
	
	printf("\n\t\t");
	system("pause");
}

void ShowCompleteOrder(Order order[], int customer_orderNum[])
{
	int i;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].pay_flag == 1 && order[i].transport_flag == 1)
		{
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t运费:%.1lf",order[i].transport_pay);
			printf("\n\t\t数量:%.1lf",order[i].details.amount);
			printf("\n\t\t总金额:%.1lf",order[i].details.total_price);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
		}
	}
	
	printf("\n\t\t");
	system("pause");
}
void ShowNotPay(Order order[], int customer_orderNum[])
{
	int i;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].pay_flag == 0)
		{
			printf("\n\t\t订单号:%d",order[i].number);
			printf("\n\t\t顾客代码:%d",order[i].customer_num);
			printf("\n\t\t运费:%.1lf",order[i].transport_pay);\
			printf("\n\t\t数量:%.1lf",order[i].details.amount);
			printf("\n\t\t总金额:%.1lf",order[i].details.total_price);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
		}
	}
	
	printf("\n\t\t");
	system("pause");
}
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
			printf("\n\t\t运费:%.1lf",order[i].transport_pay);\
			printf("\n\t\t数量:%.1lf",order[i].details.amount);
			printf("\n\t\t总金额:%.1lf",order[i].details.total_price);
			printf("\n\t\t下单日期:%s",order[i].pay_date);
		}
	}
	
	printf("\n\t\t");
	system("pause");
}
