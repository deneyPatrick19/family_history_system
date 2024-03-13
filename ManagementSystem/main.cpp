#include"header.h"
#define CAPACITY 500

int main()
{
	Customer customer[CAPACITY];
	Order order[CAPACITY];
	Product product[21];
	Factory factory[3] = {{"180310","杨氏食品集团有限公司"},{"203397","国盛食品集团有限公司"},{"104534","家百乐食品集团有限公司"}};
	int customer_orderNum[3] = {0}; /*[0]存储客户数量，[1]存储订单数量*/
	srand(time(NULL));/*设置随机数种子*/
	
	DefineProduct(product, factory);/*商品定义函数*/
		
	/*主菜单  选择管理员模式或顾客订餐模式*/
	while (1)
	{
		system("cls");
		printf("\n\t\t欢迎来到杨国福麻辣烫管理系统");
		printf("\n\t\t--------------------");
		printf("\n\t\t01 - 我是顾客");
		printf("\n\t\t02 - 我是管理员");
		printf("\n\t\t03 - 退出系统");
		printf("\n\t\t--------------------");
		printf("\n\t\t   请选择(1-3): ");  
		int option;
		
		fflush(stdin);
		scanf("%d",&option);/*输入选择*/
		
		switch (option)
		{
			case 1:
				CustomerMenu(customer, order, product, customer_orderNum);  /*顾客菜单*/
				TraversalCustomer(customer, customer_orderNum);
				TraversalOrder(order, customer_orderNum);
				break;
			case 2:
				AdministratorMenu(customer, order, product, factory, customer_orderNum);  /*管理员菜单*/
				break;
			case 3:
				return 0;  /*退出系统*/
			default: continue;
		}
	}
}

void DefineProduct(Product product[], Factory factory[])
{
	/*定义商品的编号、厂家编号、说明及单价*/
	int product_num[21] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 201, 202, 203, 204, 301, 302, 303, 111, 112, 205, 113}; 
	double price[21] = {3.5, 1.5, 4.0, 2.0, 3.0, 2.5, 4.0, 2.5, 3.0, 3.5, 5.0, 1.5, 4.5, 3.5, 3.5, 3.0, 4.0, 2.5, 3.5, 4.0, 1.5};
	char product_information[22][7] = {"牛肉","生菜","羊肉","豆腐","鱼丸","土豆片","鸭血","冬瓜","金针菇","鹌鹑蛋","方便面",
										"油条","魔芋丝","宽粉","可乐","橙汁","啤酒","花菜","山药","年糕","豆芽"};
	int i;/*迭代器*/
	
	for (i=0; i<21; i++) /*对商品各项数据类型进行赋值*/
	{
		product[i].category_num = product_num[i];
		product[i].price = price[i];
		strcpy(product[i].information, product_information[i]);
		
		if (i<7 && i>=0)
		{
			strcpy(product[i].factory_num, factory[0].num);
		}
		else if (i>=7 && i<14)
		{
			strcpy(product[i].factory_num, factory[1].num);
		}
		else
		{
			strcpy(product[i].factory_num, factory[2].num);
		}
	}
}