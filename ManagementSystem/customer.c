#include "nodeheader.h"

/*客户模块的函数及菜单界面*/
void CustomerMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead)	/*客户菜单 选择功能进行操作*/	
{			
	/*通过输入姓名进行登录系统*/
	char name[16]; 
	
	printf("\n输入姓名登录或注册:"); /*输入姓名登录*/
	
	fflush(stdin);/*清除输入缓存*/
	gets(name);/*输入姓名*/
	fflush(stdin);
	
	/*查找客户是否已使用过系统 flag为存在标志位 为-1则客户进行注册 否则就直接使用*/
	int flag;
	
	flag = SearchCustomer(CusNodeHead, name); 
	
	if (flag == -1)
	{
		/*添加客户*/
		CusNodeHead = AddCustomer(CusNodeHead, name); 
	}

	/*顾客功能选择菜单*/
	while (1)
	{
		/*清屏*/
		system("cls");
		printf("\n--------------------");
		printf("\n01 - 订购商品");
		printf("\n02 - 查看个人订单");
		printf("\n03 - 取消订单");
		printf("\n04 - 请求发票");
		printf("\n05 - 提供支付信息");
		printf("\n06 - 修改客户信息");
		printf("\n07 - 返回上一级");
		printf("\n--------------------");
		printf("\n   请选择(1-7): ");  
		
		int option; /*选项*/
		int OrderNumber;/*订单号 用于查找、支付等功能*/
		
		fflush(stdin); 
		scanf("%d",&option);/*输入选择*/
		
		switch (option)
		{
			case 1:
				/*进入购买菜单*/
				PurchaseMenu(CusNodeHead, OrNodeHead, ProNodeHead, name);
				break;
			case 2:
				/*显示顾客自己所有的订单*/
				if(TraversalCustomerOrders(OrNodeHead, CusNodeHead, name) == -1)
				{
					printf("\n您没有任何订单");
				}
				break;
			case 3:
				/*输入订单号取消订单*/
				printf("\n请输入要取消的订单的订单号(0 退出功能):");
				
				fflush(stdin);
				scanf("%d",&OrderNumber);/*输入要取消的订单号*/
				
				/*若输入0返回上一界面  否则进行取消*/
				if (OrderNumber == 0)
				{
					break;
				}
				else
				{
					if (DeleteOrderByCustomer(OrNodeHead, ProNodeHead, OrderNumber) == -1)/*取消订单函数*/
					{
						printf("\n取消失败 是否输入错误的订单号");
					}
				}
				break;
			case 4:
				/*输入订单号进行查找*/
				printf("\n请输入订单号(输入 0 退出功能):");
				
				fflush(stdin);
				scanf("%d",&OrderNumber); /*输入订单号*/
				
				/*若输入0返回上一界面  否则显示发票*/
				if (OrderNumber == 0)
				{
					break;
				}
				else
				{
					ShowReceipt(CusNodeHead, OrNodeHead, OrderNumber);/*显示发票*/
				}
				break;
			case 5:
				/*输入订单号进行支付*/
				printf("\n请输入订单号(输入 0 退出功能):");
				
				fflush(stdin);
				scanf("%d",&OrderNumber);
				
				if (OrderNumber == 0)
				{
					break;
				}
				else
				{
					Pay(OrNodeHead, OrderNumber);/*支付订单*/
				}
				break;
			case 6:
				/*修改当前顾客的信息*/
				ChangeCustomer(CusNodeHead, name);
				break;
			case 7:
				/*返回上一界面*/
				return;
			default: continue;
		}
		printf("\n\n");
		system("pause");/*程序暂停*/
	}
}

/*购买商品界面*/
void PurchaseMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead, char *name)
{
	int amount = 0; /*购买商品项数*/
	double cost = 0; /*订单总花费*/
	
	/*定义关于时间的变量，获取现在的时间*/
	char str_time[30] = {0};/*存储时间的字符串*/
	char *p_time; /*时间指针*/
	int i; /*迭代器*/
	
	OrderNode* p_order = OrNodeHead;
	ProductNode* p_product = NULL;
	
	char OrderInformation[100];  /*用于存储订单详细信息*/
	
	/*购买商品细则数组 用数组存储客户一次订单购买的商品及其数量,下标为偶数存储商品编号,下标为奇数存储购买的数量 初始均为0*/
	int PurchaseItems[42] = {0}; 
	
	/*商品选择菜单*/
	while (1)
	{
		system("cls");
		printf("\n请选择你要购买的商品");
		printf("\n--------------------");
		printf("\n01 - 牛肉   - 3.5 元");
		printf("\n02 - 生菜   - 1.5 元");
		printf("\n03 - 羊肉   - 4   元");
		printf("\n04 - 豆腐   - 2   元");
		printf("\n05 - 鱼丸   - 3   元");
		printf("\n06 - 土豆片 - 2.5 元");
		printf("\n07 - 鸭血   - 4   元");
		printf("\n08 - 冬瓜   - 2.5 元");
		printf("\n09 - 金针菇 - 3   元");
		printf("\n10 - 鹌鹑蛋 - 3.5 元");
		printf("\n11 - 方便面 - 5   元 ");
		printf("\n12 - 油条   - 1.5 元");
		printf("\n13 - 魔芋丝 - 4.5 元");
		printf("\n14 - 宽粉   - 3.5 元");
		printf("\n15 - 可乐   - 3.5 元 ");
		printf("\n16 - 橙汁   - 3   元");
		printf("\n17 - 啤酒   - 4   元");
		printf("\n18 - 花菜   - 2.5 元");
		printf("\n19 - 山药   - 3.5 元");
		printf("\n20 - 年糕   - 4.0 元");
		printf("\n21 - 豆芽   - 1.5 元");
		printf("\n22 - 完成并返回上一界面");
		printf("\n23 - 直接返回上一界面");
		printf("\n--------------------");
		printf("\n     请选择(1-23): ");
		
		int option;/*选项*/
				
		fflush(stdin); 
		scanf("%d",&option);/*输入选择*/
		
		switch (option)
		{
			case 23:
				return;/*直接返回上一界面*/
			case 22:/*若输入22 则生成订单 但顾客可以反悔继续购买商品*/
				int choice;
				/*确认是否完成订单 完成则生成订单 否则可以继续追加商品*/
				printf("\n是否完成订单(1-是 0-否):");
				
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice ==1)
				{
					p_order = AddOrder(p_order, CusNodeHead, name);/*生成订单*/
					
					/*订单各项数据进行赋值*/
					p_order->data.total_price += cost; 	/*订单总花费*/
					p_order->data.amount += amount;		/*订单购买商品项数*/	
					p_order->data.pay_flag = 0; 		/*默认订单刚开始未付款*/
					p_order->data.transport_flag = 0;	/*订单未开始配送*/
					p_order->data.transport_pay = (rand()+1)*1.0/(RAND_MAX+2)*6 + 1;	/*随机生成1-7之间的浮点数作为运费*/
					
					p_time = GetTime(str_time); /*获取当前时间作为下单时间*/
					
					strcpy(p_order->data.pay_date, p_time);/*将时间赋值*/
					
					/*将订单具体购买商品及其购买数量作为字符串赋为订单的详细信息(如 "生菜*2 啤酒*1 ")*/
					strcpy(p_order->data.information, AssignItems(ProNodeHead, PurchaseItems, OrderInformation) );
					
					printf("\n您的订单号为:%d",p_order->data.number);/*给客户显示订单号 方便查找*/
				}
				else if (choice == 0)/*不返回上一界面 可以继续追加商品*/
				{
					continue;
				}
				
				return;
			default: /*输入商品编号时 选择购买商品数量*/
				int num = 0; /*购买商品的数量*/ 
				
				printf("\n请输入你要选购的数量(输入 0 取消购买该商品):"); /*输入数量*/
				
				fflush(stdin);
				scanf("%d",&num);
				
				p_product = FindProduct(ProNodeHead, option);/*根据输入的商品编号寻找商品在链表的位置*/
				
				if (p_product == NULL)/*若未找到商品 则返回上一界面(通常输入错误的编号)*/
				{
					continue;	
				}
				
				amount += num;							/*订单总项数增加*/
				cost += p_product->data.price * num; 	/*总价依据商品价格增加*/
				p_product->data.amount -= num; 			/*商品库存量减少*/
				PurchaseItems[(option*2)-1] += num; 	/*选购商品数量存储在奇数位下标*/
				PurchaseItems[(option-1)*2] = option; 	/*商品编号存储在偶数位下标*/
		}
	}
}

/*将订单具体购买商品及其购买数量作为 字符串 赋为订单的详细信息(如 "生菜*2 啤酒*1 ")*/
char* AssignItems(ProductNode* ProNodeHead, int* PurchaseItems, char* information)
{
	int len = 0; 			/*字符串长度 用来移动字符串赋值初位置*/
	int j = 1; 				/*奇偶数迭代器*/
	int product_num; 		/*获取PurchaseItems里的商品编号，用于获取对应的商品名*/
	char product_name[100];	/*获取商品名称*/
	int purchase_num;		/*购买商品数量*/
	char num[3];			/*存取商品购买数量的字符串*/
	ProductNode* p = NULL;	/*商品链表指针*/
	
	while (1)
	{
		if(j == 22)/*当迭代器超过21 表明所有商品已检查完毕 退出*/
		{
			break;
		}
		
		product_num = PurchaseItems[(j-1)*2]; 			/*获取偶数位购买商品的编号*/
		purchase_num = PurchaseItems[(j*2)-1];			/*获取奇数位购买商品的数量*/
		
		if (product_num == 0 || purchase_num == 0) 		/*若购买数量为0 则表明未购买 直接检索下一商品*/
		{
			j++;
			continue;
		}
		else
		{
			p = FindProduct(ProNodeHead, product_num);	/*根据编号查找商品在链表的位置*/
			
			strcpy(product_name, p->data.information);
			strcpy(information + len, product_name);	/*将商品名赋值到information中*/
			len += strlen(product_name);				/*len加相对应的长度 使得下次赋值information移动到末尾*/
			
			strcpy(information + len, "*");				/*末尾赋值乘号*/
			len++;										/*长度加1*/
			
			sprintf(num, "%d", PurchaseItems[(j*2)-1]);	/*将购买商品的数量的int型转化为字符串型*/
			
			strcpy(information + len, num);				/*末尾赋值数量值*/
			len += strlen(num);
			
			strcpy(information + len, " ");				/*末尾赋值空格 用于隔开各商品信息*/
			len++;
			
			j++;										/*迭代器加1*/
		}
	}
	
	return information;	/*返回订单详细信息*/
	
}

/*查找客户是否已使用过系统 flag为存在标志位 为-1则客户进行注册 否则就直接使用*/
int	SearchCustomer(CustomerNode* CusNodeHead, char* name)
{
	CustomerNode* p = CusNodeHead->next;
	
	while (p != NULL)
	{
		if (strcmp(p->data.name, name) == 0) /*若链表中姓名与输入姓名相同 则表明该顾客已注册*/
		{
			return 0;
		}
		p = p->next;
	}
	
	return -1;/*未注册则返回-1*/
}

/*输入顾客信息*/
Customer InputCustomer(char* name) 
{
	Customer customer;/*定义一个顾客变量*/
	
	printf("\n请输入个人信息\n");
	
	fflush(stdin);
	
	customer.num = 240300 + (rand()%200 +1);/*随机产生数作为顾客代码*/
	
	printf("昵称:"); /*输入昵称*/
	gets(customer.id);
	
	printf("姓名:%s\n",name);/*姓名 顾客不管是否注册 都已输入一个姓名 直接使用*/
	strcpy(customer.name, name);
	
	printf("地址:"); /*地址*/
	gets(customer.address);
	
	printf("邮编:"); /*邮编*/
	gets(customer.postcode);
	
	printf("电话:"); /*电话*/
	gets(customer.phone);
	
	return customer;/*返回顾客*/
}

/*增加顾客节点并输入顾客信息*/
CustomerNode* AddCustomer(CustomerNode* CusNodeHead, char* name)
{
	CustomerNode* p = CusNodeHead;
	
	/*将指针移动到链表尾节点*/
	while (p->next != NULL)
	{
		p = p->next;
	}
	
	/*增加新节点并连接*/
	CustomerNode* pnew = (CustomerNode*)malloc(sizeof(CustomerNode));
	pnew->next = NULL;
	pnew->data = InputCustomer(name);/*输入顾客信息*/
	p->next = pnew;
	
	return CusNodeHead;
}

/*赋值基本订单信息*/
Order InputOrder(CustomerNode* CusNodeHead, char* name)
{
	Order order;
	
	CustomerNode* p = CusNodeHead->next;
	
	order.number = 10100 + (rand()%200 + 1);/*随机产生1-200数作为订单号*/
	
	while (p != NULL)
	{
		if (strcmp(p->data.name, name) == 0 )/*查找当前顾客在链表的节点位置*/
		{
			order.customer_num = p->data.num;/*以当前顾客的顾客代码作为订单的顾客代码*/
			
			return order;
		}
		p = p->next;						/*移动*/
	}
	return order;
}

/*增加订单链表节点并赋值基本信息*/
OrderNode* AddOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead, char* name)
{
	OrderNode* p = OrNodeHead;
	
	/*移动到链表尾节点*/
	while (p->next != NULL)
	{
		p = p->next;
	}
	
	/*增加新节点并连接*/
	OrderNode* pnew = (OrderNode*)malloc(sizeof(OrderNode));
	pnew->next = NULL;
	pnew->data = InputOrder(CusNodeHead, name);/*赋值订单基本信息*/
	p->next = pnew;
	p = pnew;
	
	return p;
}

/*依据特定顾客代码查找顾客在链表的节点位置 并返回该节点*/
CustomerNode* FindCustomer(CustomerNode* CusNodeHead, int number)
{
	CustomerNode* p = CusNodeHead->next;
	 
	while (p != NULL)
	{
		if (p->data.num == number)
		{
			return p;
		}
		p = p->next;
	}
	
	return NULL;/*若未找到则返回NULL*/
}

/*依据特定订单号查找订单在链表的节点位置 并返回该节点*/
OrderNode* FindOrder(OrderNode* OrNodeHead, int number)
{
	OrderNode* p = OrNodeHead->next;
	 
	while (p != NULL)
	{
		if (p->data.number == number)
		{
			return p;
		}
		p = p->next;
	}
	
	return NULL;/*若未找到则返回NULL*/
}

/*依据特定商品编号查找商品在链表的节点位置 并返回该节点*/
ProductNode* FindProduct(ProductNode* ProNodeHead, int option)
{
	ProductNode* p = ProNodeHead->next;
	
	while (p != NULL)
	{
		if (p->data.category_num == option)
		{
			return p;
		}
		p = p->next;
	}
	
	return NULL;/*若未找到则返回NULL*/
}

/*显示当前顾客的所有订单信息*/
int TraversalCustomerOrders(OrderNode* OrNodeHead, CustomerNode* CusNodeHead, char* name)
{
	CustomerNode* p_customer = CusNodeHead->next;
	OrderNode* p_order = OrNodeHead->next;
	int num = 0;/*统计数*/
	
	/*查找顾客在链表的节点位置*/
	while (p_customer != NULL)
	{
		if (strcmp(p_customer->data.name, name) == 0)
		{
			break;
		}
		p_customer = p_customer->next;
	}
	
	/*遍历订单链表 若顾客代码相同 则显示订单信息*/
	while (p_order != NULL)
	{
		if (p_order->data.customer_num == p_customer->data.num)/*判断顾客代码是否相同*/
		{
			printf("\n\n订单号:%d",p_order->data.number);
			printf("\n顾客代码:%d",p_order->data.customer_num);
			printf("\n顾客姓名:%s",p_customer->data.name);
			printf("\n订单费用:%.1lf 元",p_order->data.total_price);
			printf("\n运费:%.1lf 元",p_order->data.transport_pay);
			printf("\n详细信息:%s",p_order->data.information);
			printf("\n数量:%.0lf",p_order->data.amount);
			printf("\n总金额:%.1lf 元",p_order->data.total_price + p_order->data.transport_pay);
			
			/*若该订单未付款显示提示信息*/
			if (p_order->data.pay_flag == 0)
			{
				printf("\n(未付款)");
			}
			else
			{
				printf("\n(已付款)");
			}
			
			printf("\n下单日期:%s",p_order->data.pay_date);
			
			/*若该订单未开始配送显示提示信息*/
			if (p_order->data.transport_flag == 0)
			{
				printf("\n(尚未开始配送)");
			}
			else
			{
				printf("\n(已开始配送)");
				printf("\n发货日期:%s",p_order->data.transport_date);/*否则显示开始配送时间*/
			}
			
			num++;/*统计数加1*/
		}
		p_order = p_order->next;/*移动*/
	}
	
	if (num == 0)/*若统计数为0 则没有符合条件的订单 给出提示信息*/
	{
		return -1;
	}
	return 1;
}

/*取消特定订单号的订单*/
int DeleteOrderByCustomer(OrderNode* OrNodeHead, ProductNode* ProNodeHead, int number)
{
	OrderNode* p =OrNodeHead;
	OrderNode* pfollow = p->next;/*跟随指针*/
	
	while (pfollow != NULL)
	{
		if (p->next->data.number == number)/*当下一个节点的订单号相同时*/
		{
			p->next = pfollow->next;/*连接要取消节点的下一节点*/
			
			/*若该订单未付款 商品库存将回到下单前的值*/
			if (pfollow->data.pay_flag == 0)
			{
				ResumeCustomerAmount(pfollow->data.information, ProNodeHead);/*将商品库存量变成订单前的值*/
			}
			
			if (pfollow->data.pay_flag == 1)/*若已支付 不返还商品库存量 显示提示信息*/
			{
				printf("\n取消成功");
				printf("\n已原路返还付款");
			}
			else
			{
				printf("\n取消成功");			
			}
			
			free(pfollow);/*释放要取消的节点的堆空间*/
			
			return 1;
		}
		
		/*两个指针移动*/
		p = p->next;
		pfollow = pfollow->next;
	}
	
	return -1;/*取消失败*/
}

/*通过将订单的详细信息转化为商品名及数量来返回购买商品消耗的库存量*/
void ResumeCustomerAmount(char* information, ProductNode* ProNodeHead)
{
	/*例如 "生菜*2 啤酒*1 可乐*12 "*/
	
	int purchase_num;			/*获取商品购买数量的整形*/
	char name[7];				/*获取商品信息*/
	char num[3];				/*获取商品购买数量的字符串*/
	/*迭代器*/
	int i;
	int j;
	/*下标值*/
	int index = 0;
	ProductNode* p = ProNodeHead->next;
	
	/*从详细信息开头开始获取商品信息*/
	for (i=0; i<strlen(information); i++)
	{
		name[index] = information[i];  /*获取商品名称*/
		
		if (information[i+1] == '*')	/*若下一位为 *号*/
		{
			i = i + 2;					/*跳过 *号位 */
			while (1)
			{
				j = 0;
				num[j] = information[i];/*获取购买商品的数量*/
				if (information[i+1] == ' ')/*若下一位为空格(商品购买数量有可能为两位)*/
				{
					i = i + 1;				/*下标移至空格处并退出 i进入下一个for循环时加i++ 下标跳过空格 到下一个商品信息*/
					break;
				}
				j++;						/*若数量为两位数 迭代器加1 获取第二位数量*/
				i++;
			}
			purchase_num = atoi(num);		/*将商品数量的字符串转化为整形*/
			
			while (p != NULL)/*遍历商品链表 当商品名称相同时 该商品库存量加上购买数量*/
			{
				if (strcmp(name, p->data.information) == 0)
				{
					p->data.amount += purchase_num;  /*加上购买数量*/
					break;
				}
				p = p->next;/*移动*/
			}
			
			index = 0;						/*下标置0 name重新赋值*/
			memset(name, 0, sizeof(name));	/*name 清除字符串内容*/
			memset(num, 0, sizeof(name));	/*num 清除内容*/
			p = ProNodeHead->next;			/*商品指针重新指向第一个商品*/
		}
		else
		{
			index++;   						/*若下一位不为 *号 则继续赋值(必为商品名称)*/
		}
	}
}


/*显示特定订单号的发票信息*/
void ShowReceipt(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, int number)
{
	OrderNode* p_order = FindOrder(OrNodeHead, number);/*根据订单号查找订单节点*/
	if (p_order == NULL)/*若未找到给出提示信息并退出*/
	{
		printf("\n没有查询到该订单！ 请重新输入或购买商品");
		return;
	}
	CustomerNode* p_customer = FindCustomer(CusNodeHead, p_order->data.customer_num);/*根据顾客嗲吗查早顾客节点*/
	
	if (p_order->data.pay_flag == 0) /*检查是否付款*/
	{
		printf("\n未付款 请尽快付款!");
	}
	else/*显示发票信息*/
	{
		system("cls");
		printf("\n\t  杨国福麻辣烫专用发票");
		printf("\n———————————————————————————————————————————");
		printf("\n订单号    %d",number);
		printf("\n\n客户      %s",p_customer->data.name);
		printf("\n客户昵称  %s",p_customer->data.id);
		printf("\n客户代码  %d",p_customer->data.num);
		printf("\n\n详细信息  %s",p_order->data.information);
		printf("\n\n配送地址  %s",p_customer->data.address);
		printf("\n邮政编码  %s",p_customer->data.postcode);
		printf("\n联系电话  %s",p_customer->data.phone);
		printf("\n订单费用  %.1lf 元",p_order->data.total_price);
		printf("\n共\t  %.0lf 项",p_order->data.amount);
		printf("\n运费      %.1lf 元",p_order->data.transport_pay);
		if (p_order->data.transport_flag == 0)
		{
			printf("\n\t  (尚未开始配送)");
		}
		else
		{
			printf("\n\t  (已开始配送)");
		}
		printf("\n\n总计\t  %.1lf 元",p_order->data.total_price + p_order->data.transport_pay);
		printf("\n\n\n下单日期  %s",p_order->data.pay_date);
		if (p_order->data.transport_flag == 1)
		{
			printf("\n发货日期  %s",p_order->data.transport_date);
		}
		printf("\n———————————————————————————————————————————");
	}
}

/*支付特定订单号的订单费用*/
void Pay(OrderNode* OrNodeHead, int number)
{
	OrderNode* p = FindOrder(OrNodeHead, number);/*根据订单号查找订单节点*/
	if (p == NULL)
	{
		printf("\n未找到该订单");
		return;
	}
	
	/*判断是否已支付*/
	if (p->data.pay_flag == 1)
	{
		printf("\n您已支付 无需再次支付");
	}
	else
	{
		/*给出支付费用信息*/
		printf("\n订单号:%d",p->data.number);
		printf("\n你须支付共%.1lf 元",p->data.total_price + p->data.transport_pay);
		printf("\n其中运费为%.1lf 元",p->data.transport_pay);
		
		/*选择支付方式*/
		printf("\n请选择支付方式");
		printf("\n--------------------");
		printf("\n01 - 微信支付");
		printf("\n02 - 支付宝支付");
		printf("\n03 - 银联支付");
		printf("\n04 - 返回上一级");
		printf("\n--------------------");
		printf("\n请选择(1-4): ");  
		
		int option;/*选项*/
		int i;/*迭代器*/
		
		fflush(stdin);
		scanf("%d",&option);
		
		switch (option)
		{
			case 4:
				return;
			default:
				if (option >3 || option<1)/*若超出选项范围 则退出*/
				{
					return;
				}
				/*进行支付*/
				printf("\n正在跳转");
				
				for (i=0; i<3; i++)
				{
					printf(" .");
					Sleep(700);
				}
				
				printf("\n请稍后");
				
				for (i=0; i<3; i++)
				{
					printf(" .");
					Sleep(800);
				}
				
				Sleep(1500);
				
				printf("\n支付成功！");
				p->data.pay_flag = 1;/*将订单改为已支付*/
		}
	}
}

/*修改顾客信息菜单*/
Customer ChangeCustomerMenu(Customer customer)
{
	while(1)
	{
		/*显示顾客的信息*/
		system("cls");
		printf("\n代码:%d",customer.num);
		printf("\n昵称:%s",customer.id);
		printf("\n姓名:%s",customer.name);
		printf("\n地址:%s",customer.address);
		printf("\n邮编:%s",customer.postcode);
		printf("\n电话:%s",customer.phone);
		/*选择要修改的数据*/
		printf("\n\n请选择你想要修改的数据");
		printf("\n--------------------");
		printf("\n01 - 昵称");
		printf("\n02 - 姓名");
		printf("\n03 - 地址");
		printf("\n04 - 邮编");
		printf("\n05 - 电话");
		printf("\n06 - 返回上一级");
		printf("\n--------------------");
		printf("\n请选择(1-6): ");  
		
		int option;/*选项*/
		int choice;/*决定是否修改*/
		
		fflush(stdin);
		scanf("%d",&option);
		fflush(stdin);
		
		switch (option)
		{
			case 1:
				printf("\n是否进行修改(0-退出 1-确认)");
				fflush(stdin);
				scanf("%d",&choice);/*输入0或1进行最终的决定*/
				
				if (choice == 0)/* 0 返回选择界面*/
				{
					break;
				}
				else
				{
					printf("\n请输入修改后的昵称:");
					/*输入新的信息*/
					gets(customer.id);
				}
		
				break;
			case 2:
				printf("\n是否进行修改(0-退出 1-确认)");
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice == 0)
				{
					break;
				}
				else
				{
					printf("\n请输入修改后的姓名:");
					
					gets(customer.name);
				}
				
				break;
			case 3:
				printf("\n是否进行修改(0-退出 1-确认)");
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice == 0)
				{
					break;
				}
				else
				{
					printf("\n请输入修改后的地址:");
					
					gets(customer.address);
				}
				
				break;
			case 4:
				printf("\n是否进行修改(0-退出 1-确认)");
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice == 0)
				{
					break;
				}
				else
				{
					printf("\n请输入修改后的邮编:");
					
					gets(customer.postcode);
				}
				
				break;
			case 5:
				printf("\n是否进行修改(0-退出 1-确认)");
				fflush(stdin);
				scanf("%d",&choice);
				
				if (choice == 0)
				{
					break;
				}
				else
				{
					printf("\n请输入修改后的电话:");
					
					gets(customer.phone);
				}
				
				break;
			case 6:
				return customer;
			default: continue;
		}
		printf("\n");
		system("pause");
	}
}

/*修改顾客的信息*/
void ChangeCustomer(CustomerNode* CusNodeHead, char name[])
{
	CustomerNode* p = CusNodeHead;
	
	/*根据姓名查找顾客的节点位置*/
	while (p != NULL)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			p->data = ChangeCustomerMenu(p->data);/*修改菜单*/
			return;
		}
		p = p->next;
	}
	
	return;
}