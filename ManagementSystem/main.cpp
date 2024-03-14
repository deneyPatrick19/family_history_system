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
	ReadFile(customer, order, product, customer_orderNum);
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
				WriteFile(customer, order, product, customer_orderNum);
				return 0;  /*退出系统*/
			default: continue;
		}
		printf("\n\t\t");
		system("pause");
	}
}

/*对商品进行赋值及定义*/
void DefineProduct(Product product[], Factory factory[])
{
	/*定义商品的编号、厂家编号、说明及单价*/
	int product_num[21] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}; 
	double price[21] = {3.5, 1.5, 4.0, 2.0, 3.0, 2.5, 4.0, 2.5, 3.0, 3.5, 5.0, 1.5, 4.5, 3.5, 3.5, 3.0, 4.0, 2.5, 3.5, 4.0, 1.5};
	char product_information[22][7] = {"牛肉","生菜","羊肉","豆腐","鱼丸","土豆片","鸭血","冬瓜","金针菇","鹌鹑蛋","方便面",
										"油条","魔芋丝","宽粉","可乐","橙汁","啤酒","花菜","山药","年糕","豆芽"};
	int i;/*迭代器*/
	
	for (i=0; i<21; i++) /*对商品各项数据类型进行赋值*/
	{
		product[i].category_num = product_num[i];
		product[i].price = price[i];
		strcpy(product[i].information, product_information[i]);
		product[i].amount = 50;
		
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

/*将客户信息及订单存储在硬盘上*/
void WriteFile(Customer customer[], Order order[], Product product[], int customer_orderNum[])
{
	FILE* fp = NULL;/*定义文件指针*/
	int i;/*迭代器*/
	
	/*客户*/
	fp = fopen("customer.txt", "wb");/*打开文件*/
	for (i=0; i< customer_orderNum[0]; i++)
	{
		fwrite(&customer[i], sizeof(Customer), 1, fp);/*写入数据*/
	}
	fclose(fp);/*关闭文件*/
	
	/*订单*/
	fp = fopen("order.txt", "wb");
	for (i=0; i<customer_orderNum[1]; i++)
	{
		fwrite(&order[i], sizeof(Order), 1, fp);
	}
	fclose(fp);
	
	/*库存量*/
	fp = fopen("productAmount.txt", "wb");
	for (i=0; i< 21; i++)
	{
		fwrite(&product[i].amount, sizeof(int), 1, fp);/*写入数据*/
	}
	fclose(fp);
}

/*将客户信息及订单从硬盘上读取内存中*/
void ReadFile(Customer customer[], Order order[], Product product[], int customer_orderNum[])
{
	FILE* fp = NULL;/*定义文件指针*/
	int i = 0;/*迭代器*/
	
	fp = fopen("customer.txt", "rb");/*打开文件*/
	if (fp == NULL)
	{
		return;
	}
	
	while (1)
	{
		int count = fread(&customer[i], sizeof(Customer), 1, fp);/*读取数据*/
		if (count == 0)/*若count == 0则文件读取完毕 退出循环*/
		{
			break;
		}
		
		i++;
		customer_orderNum[0]++;/*客户数量加1*/
	}
	fclose(fp);/*关闭文件*/
	
	
	i = 0;
	
	fp = fopen("order.txt", "rb");
	if (fp == NULL)
	{
		return;
	}
	
	while (1)
	{
		int count = fread(&order[i], sizeof(Order), 1, fp);
		if (count == 0)
		{
			break;
		}
		
		i++;
		customer_orderNum[1]++;
	}
	fclose(fp);
	
	i = 0;
	
	fp = fopen("productAmount.txt", "rb");
	if (fp == NULL)
	{
		return;
	}
	
	while (1)
	{
		int count = fread(&product[i].amount, sizeof(int), 1, fp);
		if (count == 0)
		{
			break;
		}
		
		i++;
	}
	fclose(fp);
}


