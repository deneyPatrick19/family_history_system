#include"header.h"

/*客户模块的函数及菜单界面*/
void CustomerMenu(Customer customer[], Order order[], Product product[], int customer_orderNum[])	/*客户菜单 选择功能进行操作*/	
{	
	char name[16]; /*通过输入姓名进行登录系统*/
	
	printf("\n\t\t输入姓名登录或注册:"); /*登录*/
	fflush(stdin);
	gets(name);
	fflush(stdin);
	
	/*查找客户是否已使用过系统 flag为存在标志位 为-1则客户进行注册 否则就直接使用*/
	int flag;
	
	flag = SearchCustomer(customer, customer_orderNum, name); /*若不为0 则返回该客户在数组中的下标数*/
	if (flag == -1)
	{
		AddCustomer(customer, customer_orderNum, name); /*添加客户*/
	}
	
	/*功能选择菜单*/
	while (1)
	{
		system("cls");
		printf("\n\t\t--------------------");
		printf("\n\t\t01 - 订购商品");
		printf("\n\t\t02 - 请求发票");
		printf("\n\t\t03 - 提供支付信息");
		printf("\n\t\t04 - 修改客户信息");
		printf("\n\t\t05 - 返回上一级");
		printf("\n\t\t--------------------");
		printf("\n\t\t   请选择(1-5): ");  
		
		int option; 
		int order_number;
		 
		fflush(stdin); 
		scanf("%d",&option);/*输入选择*/
		
		switch (option)
		{
			case 1:
				PurchaseMenu(customer, order,customer_orderNum, product, name);/*购买商品菜单函数*/
				break;
			case 2:
				/*输入订单号进行查找*/
				printf("\n\t\t请输入订单号:");
				
				fflush(stdin);
				scanf("%d",&order_number);
				
				ShowReceipt(customer, order, order_number, customer_orderNum); /*打印发票*/
				break;
			case 3:
				/*输入订单号进行支付*/
				printf("\n\t\t请输入订单号:");
				
				fflush(stdin);
				scanf("%d",&order_number);
				
				Pay(order, customer_orderNum, order_number);/*支付订单*/
				break;
			case 4:
				flag = SearchCustomer(customer, customer_orderNum, name);
				ChangeCustomerInfor(customer, flag);
				break;
			case 5:
				/*返回上一界面*/
				return;
			default: continue;
		}
		printf("\n\t\t");
		system("pause");
	}
}

/*购买商品菜单函数*/
void PurchaseMenu(Customer customer[], Order order[], int customer_orderNum[], Product product[], char name[])
{
	int amount = 0; /*购买商品项数*/
	double cost = 0; /*存储总花费*/
	/*定义关于时间的变量，获取现在的时间*/
	char str_time[30] = {0};/*存储时间的字符串*/
	char *p_time; /*时间指针*/
	int i; /*迭代器*/
	
	char order_infor[100];
	int PurchaseItems[42] = {0}; /*用数组存储客户一次订单购买的商品及其数量,下标为偶数存储商品编号,下标为奇数存储购买的数量*/
	
	while (1)
	{
		system("cls");
		printf("\n\t\t请选择你要购买的商品");
		printf("\n\t\t--------------------");
		printf("\n\t\t01 -牛肉   -3.5 元");
		printf("\n\t\t02 -生菜   -1.5 元");
		printf("\n\t\t03 -羊肉   -4   元");
		printf("\n\t\t04 -豆腐   -2   元");
		printf("\n\t\t05 -鱼丸   -3   元");
		printf("\n\t\t06 -土豆片 -2.5 元");
		printf("\n\t\t07 -鸭血   -4   元");
		printf("\n\t\t08 -冬瓜   -2.5 元");
		printf("\n\t\t09 -金针菇 -3   元");
		printf("\n\t\t10 -鹌鹑蛋 -3.5 元");
		printf("\n\t\t11 -方便面 -5   元 ");
		printf("\n\t\t12 -油条   -1.5 元");
		printf("\n\t\t13 -魔芋丝 -4.5 元");
		printf("\n\t\t14 -宽粉   -3.5 元");
		printf("\n\t\t15 -可乐   -3.5 元 ");
		printf("\n\t\t16 -橙汁   -3   元");
		printf("\n\t\t17 -啤酒   -4   元");
		printf("\n\t\t18 -花菜   -2.5 元");
		printf("\n\t\t19 -山药   -3.5 元");
		printf("\n\t\t20 -年糕   -4.0 元");
		printf("\n\t\t21 -豆芽   -1.5 元");
		printf("\n\t\t22 -完成并返回上一界面");
		printf("\n\t\t--------------------");
		printf("\n\t\t请选择(1-22): "); 
		
		int option;
				
		fflush(stdin); /*输入选择*/
		scanf("%d",&option);
		
		switch (option)
		{
			case 22:
				int choice;/*确认是否完成订单 完成则生成订单 否则可以继续追加商品*/
				
				printf("\n\t\t是否完成订单(1-是 0-否):");
				
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice ==1)
				{
					AddOrder(order, customer, name, customer_orderNum, PurchaseItems);/*生成订单*/
					
					order[customer_orderNum[1] -1].total_price += cost; 
					order[customer_orderNum[1] -1].amount += amount;
					order[customer_orderNum[1] -1].pay_flag = 0; 		/*默认订单刚开始未付款*/
					order[customer_orderNum[1] -1].transport_flag = 0;	/*订单未开始配送*/
					order[customer_orderNum[1] -1].transport_pay = (rand()+1)*1.0/(RAND_MAX+2)*6 + 1;	/*随机生成1-7之间的浮点数作为运费*/
					
					p_time = GetTime(str_time);
					
					strcpy(order[customer_orderNum[1] -1].pay_date, p_time);
					strcpy(order[customer_orderNum[1] -1].information, AssignItems(product, PurchaseItems, order_infor) );
					
					printf("\n\t\t您的订单号为:%d",order[customer_orderNum[1] -1].number);/*给客户显示订单号 方便查找*/
				}
				else if (choice == 0)
				{
					continue;
				}
				
				return;
			default: 
				int num = 0; /*购买商品的数量*/ 
				
				printf("\n\t\t请输入你要选购的数量:"); /*输入数量*/
				
				fflush(stdin); 
				scanf("%d",&num);
				
				amount += num;
				cost += product[option-1].price * num; /*总价依据price数组中的数据增加*/
				product[option-1].amount -= num; /*库存量减少*/
				PurchaseItems[(option*2)-1] = num; /*选购商品数量存储在奇数位下标*/
				PurchaseItems[(option-1)*2] = option; /*商品编号存储在偶数位下标*/
		}
	}
}

/*输入顾客基本信息*/
Customer InputCustomer(Customer c, int customer_orderNum[], char name[]) 
{
	printf("\n\t\t请输入个人信息\n");
	
	c.num = 240300+customer_orderNum[0] + (rand()%100 +1) ;
	printf("\t\t昵称:"); gets(c.id);
	printf("\t\t姓名:%s\n",name); strcpy(c.name, name);
	printf("\t\t地址:"); gets(c.address);
	printf("\t\t邮编:"); gets(c.postcode);
	printf("\t\t电话:"); gets(c.phone);
	
	return c;
}

/*添加顾客并输入基本信息*/
void AddCustomer(Customer customer[], int customer_orderNum[], char name[]) 
{
	/*输入客户的代码、名称和姓名*/
	Customer cus;
	
	customer[customer_orderNum[0]] = InputCustomer(cus, customer_orderNum, name);
	
	/*顾客数加1*/
	customer_orderNum[0]++;
}

/*查找顾客是否已注册过系统 已注册则返回客户在数组的下标  返回-1则表示没有注册*/
int SearchCustomer(Customer customer[], int customer_orderNum[], char var_name[])
{
	int i;
	
	for (i=0; i<customer_orderNum[0]; i++)
	{
		if (strcmp(var_name, customer[i].name) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

/*添加订单并赋值基本信息*/
void AddOrder(Order order[], Customer customer[], char name[], int customer_orderNum[], int PurchaseItems[])
{
	int i;
	
	order[customer_orderNum[1]].number = 10100+customer_orderNum[1]+(rand()%100 + 1);  /*订单号*/
	/*确定订单人及其代码*/
	for (i=0; i<customer_orderNum[0]; i++)
	{
		if (strcmp(name, customer[i].name) == 0)
		{
			order[customer_orderNum[1]].customer_num = customer[i].num; 
		}
	}
	/*订单数加1*/
	customer_orderNum[1]++;
}

/*将所有购买的商品名及其数量赋值在订单的information中 方便客户查看*/
char* AssignItems(Product product[], int PurchaseItems[], char* information)
{
	int len = 0; /*字符串长度 用来移动字符串赋值初位置*/
	int j = 1; 
	int product_num; /*获取PurchaseItems里的商品编号，用于读取对应的商品名*/
	char product_name[7]; /*存取商品的名称*/
	char num[3];/*存取商品购买数量的字符串*/
	
	while (1)
	{
		if(j == 22)
		{
			break;
		}
		product_num = PurchaseItems[(j-1)*2]; /*获取购买商品的编号*/
		if (product_num == 0) /*若值为0 则表明未购买 直接检索下一商品*/
		{
			j++;
			continue;
		}
		else
		{
			strcpy(product_name, product[product_num-1].information); /*赋值商品名*/
			
			strcpy(information + len, product_name);/*将商品名赋值到information中*/
			len += strlen(product_name);
			
			strcpy(information + len, "*");/*赋值乘号*/
			len++;
			
			sprintf(num, "%d", PurchaseItems[(j*2)-1]);/*将购买商品的数量的int型转化为字符串型*/
			
			strcpy(information + len, num);/*赋值数量值*/
			len += strlen(num);
			
			strcpy(information + len, " ");/*赋值空格 用于隔开各商品*/
			len++;
			
			j++;
		}
	}
	return information;
}

/*遍历显示所有订单及其信息*/
void TraversalOrder(Order order[], int customer_orderNum[]) 
{
	int i;
	int j;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		printf("\n\t\t订单号:%d",order[i].number);
		printf("\n\t\t顾客代码:%d",order[i].customer_num);
		printf("\n\t\t订单费用:%.1lf 元",order[i].total_price);
		printf("\n\t\t运费:%.1lf 元",order[i].transport_pay);
		printf("\n\t\t总费用:%.1lf 元",order[i].total_price + order[i].transport_pay);
		printf("\n\t\t详细信息:%s",order[i].information);
		printf("\n\t\t数量:%.0lf",order[i].amount);
		printf("\n\t\t下单日期:%s",order[i].pay_date);
		if (order[i].transport_flag == 1)
		{
			printf("\n\t\t发货日期:%s",order[i].transport_date);
		}
	}
	printf("\n\t\t");
	system("pause");
}

/*遍历显示所有客户及其信息*/
void TraversalCustomer(Customer customer[], int customer_orderNum[])
{
	int i;
	
	for (i=0; i<customer_orderNum[0]; i++)
	{
		printf("\n\t\t代码:%d",customer[i].num);
		printf("\n\t\t昵称:%s",customer[i].id);
		printf("\n\t\t姓名:%s",customer[i].name);
		printf("\n\t\t地址:%s",customer[i].address);
		printf("\n\t\t邮编:%s",customer[i].postcode);
		printf("\n\t\t电话:%s",customer[i].phone);
	}
	printf("\n\t\t");
	system("pause");
}

/*获取现在的时间*/
char* GetTime(char* str_time) 
{
	int sec = 0;
	time_t* clock;
	
	//获取时间，保存到time_t结构体中。在time的返回值(sec)里面有全部秒数
    sec = time(clock);
    strcpy(str_time, ctime(clock)); //将time_t类型的结构体中的时间，按照一定格式保存成字符串，
	
	return str_time;
}

/*根据订单号查找订单在数组中的下标 若返回-1则表明未找到该订单*/
int FindOrder(Order order[], int customer_orderNum[], int var_number)
{
	int i;
	
	for (i=0; i<customer_orderNum[1]; i++)
	{
		if (order[i].number == var_number)
		{
			return i;
		}
	}
	
	return -1;
}

/*根据顾客代码查找顾客在数组中的下标 若返回-1则表明未找到该顾客*/
int FindCustomer(Customer customer[], int customer_orderNum[], int var_customernum)
{
	int i;
	
	for (i=0; i<customer_orderNum[0]; i++)
	{
		if (customer[i].num == var_customernum)
		{
			return i;
		}
	}
	
	return -1;
}

/*打印发票（客户及其查找的订单信息）*/
void ShowReceipt(Customer customer[], Order order[], int order_number, int customer_orderNum[])
{
	/*i,j 分别存储订单及顾客的下标*/
	int i;
	int j;
	
	/*函数查找*/
	i = FindOrder(order, customer_orderNum, order_number);
	j = FindCustomer(customer, customer_orderNum, order[i].customer_num);
	
	/*为-1则让顾客重新输入正确的订单号或购买商品*/
	if (i == -1)
	{
		printf("\n\t\t没有查询到该订单！ 请重新输入或购买商品");
		return;
	}
	
	if (order[i].pay_flag == 0) /*检查是否付款*/
	{
		printf("\n\t\t未付款 请尽快付款!");
	}
	else /*打印各项数据*/
	{
		system("cls");
		printf("\n\t  杨国福麻辣烫专用发票");
		printf("\n———————————————————————————————————————————");
		printf("\n订单号    %d",order_number);
		printf("\n\t  %s",order[i].customer_num);
		printf("\n客户      %s",customer[j].name);
		printf("\n客户昵称  %s",customer[j].id);
		printf("\n客户代码  %d",customer[j].num);
		printf("\n\n详细信息  %s",order[i].information);
		printf("\n\n配送地址  %s",customer[j].address);
		printf("\n邮政编码  %s",customer[j].postcode);
		printf("\n联系电话  %s",customer[j].phone);
		printf("\n订单费用  %.1lf 元",order[i].total_price);
		printf("\n共\t  %.0lf 项",order[i].amount);
		printf("\n运费      %.1lf 元",order[i].transport_pay);
		if (order[i].transport_flag == 0)
		{
			printf("\n\t  (尚未开始配送)");
		}
		else
		{
			printf("\n\t  (已开始配送)");
		}
		printf("\n\n总计\t  %.1lf 元",order[i].total_price + order[i].transport_pay);
		printf("\n\n\n下单日期  %s",order[i].pay_date);
		if (order[i].transport_flag == 1)
		{
			printf("\n发货日期  %s",order[i].transport_date);
		}
		printf("\n———————————————————————————————————————————");
	}
}

/*提供支付信息 让客户进行支付*/
void Pay(Order order[], int customer_orderNum[], int order_number)
{
	int num;
	
	num = FindOrder(order, customer_orderNum, order_number);
	if (num == -1)
	{
		printf("\n\t\t未找到该订单");
		return;
	}
		
	system("cls");
	if (order[num].pay_flag == 1) /*确认是否已付过款， 若已付过则给出提示信息*/
	{
		printf("\n\t\t您已支付 无需再次支付");
	}
	else
	{
		printf("\n\t\t订单号:%d",order[num].number);
		printf("\n\t\t你须支付共%.1lf 元",order[num].total_price + order[num].transport_pay);
		printf("\n\t\t其中运费为%.1lf 元",order[num].transport_pay);
		
		printf("\n\t\t请选择支付方式");
		printf("\n\t\t--------------------");
		printf("\n\t\t01 - 微信支付");
		printf("\n\t\t02 - 支付宝支付");
		printf("\n\t\t03 - 银联支付");
		printf("\n\t\t04 - 返回上一级");
		printf("\n\t\t--------------------");
		printf("\n\t\t请选择(1-4): ");  
		
		int option;
		int i;
		
		fflush(stdin);
		scanf("%d",&option);
		
		switch (option)
		{
			case 4:
				return;
			default:
				if (option >3 || option<1)
				{
					return;
				}
				printf("\n\t\t正在跳转");
				for (i=0; i<4; i++)
				{
					printf(" .");
					Sleep(700);
				}
				printf("\n\t\t请稍后");
				for (i=0; i<4; i++)
				{
					printf(" .");
					Sleep(950);
				}
				
				Sleep(1500);
				printf("\n\t\t支付成功！");
				order[num].pay_flag = 1;
		}
	}

}

/*修改客户的信息（昵称、姓名、地址等）*/
void ChangeCustomerInfor(Customer customer[], int flag)
{
	while(1)
	{
		system("cls");
		printf("\n\t\t代码:%d",customer[flag].num);
		printf("\n\t\t昵称:%s",customer[flag].id);
		printf("\n\t\t姓名:%s",customer[flag].name);
		printf("\n\t\t地址:%s",customer[flag].address);
		printf("\n\t\t邮编:%s",customer[flag].postcode);
		printf("\n\t\t电话:%s",customer[flag].phone);
		printf("\n\n\t\t请选择你想要修改的数据");
		printf("\n\t\t--------------------");
		printf("\n\t\t01 - 昵称");
		printf("\n\t\t02 - 姓名");
		printf("\n\t\t03 - 地址");
		printf("\n\t\t04 - 邮编");
		printf("\n\t\t05 - 电话");
		printf("\n\t\t06 - 返回上一级");
		printf("\n\t\t--------------------");
		printf("\n\t\t请选择(1-6): ");  
		
		int option;
		
		fflush(stdin);
		scanf("%d",&option);
		fflush(stdin);
		
		switch (option)
		{
			case 1:
				printf("\n\t\t请输入修改后的昵称:");
				gets(customer[flag].id);
				break;
			case 2:
				printf("\n\t\t请输入修改后的姓名:");
				gets(customer[flag].name);
				break;
			case 3:
				printf("\n\t\t请输入修改后的地址:");
				gets(customer[flag].address);
				break;
			case 4:
				printf("\n\t\t请输入修改后的邮编:");
				gets(customer[flag].postcode);
				break;
			case 5:
				printf("\n\t\t请输入修改后的电话:");
				gets(customer[flag].phone);
				break;
			case 6:
				return;
			default: continue;
		}
		printf("\n\t\t");
		system("pause");
	}
}

