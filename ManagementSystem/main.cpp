#include "administrator.h"
#include "customer.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

struct Customer		//顾客信息
{
	int num; 				//顾客代码
	char id[21]; 			//顾客昵称
	char name[16]; 			//顾客姓名
	char address[26]; 		//地址
	char postcode[11]; 		//邮编
	char phone[12]; 		//电话
};

struct Order		//订单信息
{
	int number; 			//订单号
	char pay_date[30];  	//下单日期
	int customer_num;  		//顾客代码
	int transport_flag; 	// 是否发货标识  1表示已开始配送 0表示未开始
	int pay_flag; 			//是否付款标识  1表示已付款 0表示未付款
	char transport_date[30];//运输日期
	double transport_pay; 	//运费  
	double amount; 			//数量
	double total_price; 	//总金额
	char information[100];  //订单详细信息
};

struct Product		//库存商品信息
{
	int category_num; 		//商品编号
	char factory_num[21]; 	//生产厂家编号
	char information[100]; 	//商品说明
	double price;	 		//单价
	int amount;  			//库存量(份)
};

struct Factory		//生产厂家信息
{
	char num[21]; 			//厂家代码
	char name[36]; 			//厂家名称
};

/*链表节点声明*/
struct CustomerNode			//顾客节点
{
	Customer data;			//数据域
	CustomerNode* next;		//指针
};

struct OrderNode			//订单节点
{
	Order data;
	OrderNode* next;
};

struct ProductNode			//商品节点
{
	Product data;
	ProductNode* next;
};

int main() 
{
	/*在堆区申请空间 分别创建顾客、订单和商品的链表头节点*/
	CustomerNode* CusNodeHead = (CustomerNode*)malloc(sizeof(CustomerNode));
	OrderNode* OrNodeHead = (OrderNode*)malloc(sizeof(OrderNode));
	ProductNode* ProNodeHead = (ProductNode*)malloc(sizeof(ProductNode));
	
	/*头结点指针指向空*/
	CusNodeHead->next = NULL;
	OrNodeHead->next = NULL;
	ProNodeHead->next = NULL;
	
	/*定义商品的生产厂商*/
	Factory factory[3] = {{"180310","杨氏食品集团有限公司"},
						{"203397","国盛食品集团有限公司"},
						{"104534","家百乐食品集团有限公司"}};

	srand(time(NULL));/*设置时间种子*/

	/*对商品链表进行增加及赋值*/
	ProductDefine(ProNodeHead, factory);
	
	/*从文件中读取顾客、订单和商品信息*/
	ReadFile(CusNodeHead, OrNodeHead, ProNodeHead);
	
	/*主菜单  选择管理员界面或顾客界面*/
	while (1) 
	{
		system("cls"); /*清屏*/
		printf("\n欢迎来到杨国福麻辣烫管理系统");
		printf("\n--------------------");
		printf("\n01 - 我是顾客");
		printf("\n02 - 我是管理员");
		printf("\n03 - 退出系统");
		printf("\n--------------------");
		printf("\n   请选择(1-3): ");
		int option;/*选项*/

		fflush(stdin);/*清除输入缓存*/
		scanf("%d",&option);/*输入选择*/

		switch (option) 
		{
			case 1:
				CustomerMenu(CusNodeHead, OrNodeHead, ProNodeHead);  /*顾客菜单*/
				break;
			case 2:
				AdministratorMenu(CusNodeHead, OrNodeHead, ProNodeHead, factory); /*管理员菜单*/
				break;
			case 3:
				WriteFile(CusNodeHead, OrNodeHead, ProNodeHead);/*将顾客、订单和商品信息写入硬盘文件*/
				ReleaseNode(CusNodeHead, OrNodeHead, ProNodeHead);  /*释放堆区节点*/
				return 0;  /*退出系统*/
			default:
				continue;
		}
		system("pause");
	}
}

/*对商品链表进行增加及赋值*/
void ProductDefine(ProductNode* ProNodeHead, Factory* factory)
{
	int i;/*迭代器*/
	ProductNode* p = ProNodeHead;
	
	/*增加商品节点*/
	for (i=0; i<21; i++)
	{
		ProductNode* pnew = (ProductNode*)malloc(sizeof(ProductNode)); /*堆区申请空间*/
		pnew->next = NULL;
		p->next = pnew;			/*节点连接*/
		p = pnew;
	}
	
	p = ProNodeHead->next; /*将指针移到第一个含数据的节点*/
	
	/*21个 商品的价格及商品信息（名称）定义*/
	double price[21] = {3.5, 1.5, 4.0, 2.0, 3.0, 2.5, 4.0,
	 					2.5, 3.0, 3.5, 5.0, 1.5, 4.5, 3.5,
	 					3.5, 3.0, 4.0, 2.5, 3.5, 4.0, 1.5};
	char ProductInformation[22][7] = {"牛肉","生菜","羊肉","豆腐","鱼丸","土豆片","鸭血",
										"冬瓜","金针菇","鹌鹑蛋","方便面","油条","魔芋丝","宽粉",
										"可乐","橙汁","啤酒","花菜","山药","年糕","豆芽"};
								
	/*将商品信息赋值到链表中*/		
	for (i=0; i<21; i++)
	{
		p->data.category_num = i+1;  /*商品编号*/
		p->data.price = price[i];    /*价格*/
		strcpy(p->data.information, ProductInformation[i]);  /*商品信息*/
		p->data.amount = 40;  /*默认初始库存量为40份*/
		
		
		/*生产厂家赋值 1-7为第一家厂家  8-14第二家  15-21第三家*/
		if (i<7 && i>=0)
		{
			strcpy(p->data.factory_num, factory[0].num);
		}
		else if (i>=7 && i<14)
		{
			strcpy(p->data.factory_num, factory[1].num);
		}
		else
		{
			strcpy(p->data.factory_num, factory[2].num);
		}
		
		p = p->next;  /*指针移动*/
	}
	
}

/*获取现在的时间*/
char* GetTime(char* str_time)
{
	int sec = 0;
	time_t* clock;
	
	//获取时间，保存到time_t结构体中。在time的返回值(sec)里面有全部秒数
    sec = time(clock);
    strcpy(str_time, ctime(clock)); //将time_t类型的结构体中的时间，按照一定格式保存成字符串，
	
	return str_time; /*返回时间字符串*/
}

/*将顾客、订单和商品信息写入硬盘文件*/
void WriteFile(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead)
{
	FILE* fp = NULL; /*文件指针*/
	
	CustomerNode* p_customer = CusNodeHead->next;
	OrderNode* p_order = OrNodeHead->next;
	ProductNode* p_product = ProNodeHead->next;
	
	/*顾客*/
	/*打开文件*/
	fp = fopen("customer.txt", "wb"); 
	while (p_customer != NULL)
	{
		fwrite(&(p_customer->data), sizeof(Customer), 1, fp); /*写入文件*/
		p_customer = p_customer->next; 
	}
	fclose(fp); /*关闭文件*/
	
	/*订单*/
	fp = fopen("order.txt", "wb");
	while (p_order != NULL)
	{
		fwrite(&(p_order->data), sizeof(Order), 1, fp);
		p_order = p_order->next;
	}
	fclose(fp);
	
	/*商品*/
	fp = fopen("product.txt", "wb");
	while (p_product != NULL)
	{
		fwrite(&(p_product->data), sizeof(Product), 1 , fp);
		p_product = p_product->next;
	}
	fclose(fp);
	
}

/*从文件中读取顾客、订单和商品信息*/
void ReadFile(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead)
{
	FILE* fp = NULL; /*文件指针*/
	
	CustomerNode* p_customer = CusNodeHead;
	OrderNode* p_order = OrNodeHead;
	ProductNode* p_product = ProNodeHead;
	
	/*顾客*/
	fp = fopen("customer.txt", "rb");/*打开文件*/
	
	if (fp == NULL)/*若返回值为NULL 则文件不存在*/
	{
		printf("\n文件不存在");
	}
	else
	{
		while (1)
		{
			Customer customer;
			
			/*fread返回值不为0则文件未读完  为0则读取完毕退出循环*/
			int count = fread(&customer, sizeof(Customer), 1, fp);
			if (count == 0)
			{
				break;
			}
			
			/*建立节点 存储读取来的数据*/
			CustomerNode* pnew_customer = (CustomerNode*)malloc(sizeof(CustomerNode));
			pnew_customer->next = NULL;
			pnew_customer->data = customer;
			p_customer->next = pnew_customer;
			p_customer = pnew_customer;
		}
	}
	fclose(fp);/*关闭文件*/
	
	/*订单*/
	fp = fopen("order.txt", "rb");
	
	if (fp == NULL)
	{
		printf("\n文件不存在");
	}
	else
	{
		while (1)
		{
			Order order;
			
			int count = fread(&order, sizeof(Order), 1, fp);
			if (count == 0)
			{
				break;
			}
			
			OrderNode* pnew_order = (OrderNode*)malloc(sizeof(OrderNode));
			pnew_order->next = NULL;
			pnew_order->data = order;
			p_order->next = pnew_order;
			p_order = pnew_order;
		}
	}
	fclose(fp);
	
	/*商品*/
	fp = fopen("product.txt", "rb");
	
	if (fp == NULL)
	{
		printf("\n文件不存在");
	}
	else
	{
		while (1)
		{
			Product product;
			
			int count = fread(&product, sizeof(Product), 1, fp);
			if (count == 0)
			{
				break;
			}
			
			ProductNode* pnew_product = (ProductNode*)malloc(sizeof(ProductNode));
			pnew_product->next = NULL;
			pnew_product->data = product;
			p_product->next = pnew_product;
			p_product = pnew_product;
		}
	}
	fclose(fp);
	
}

/*释放节点*/
void ReleaseNode(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead)
{
	/*顾客*/
	/*代指针指向头结点*/
	CustomerNode *p_customer = CusNodeHead;
	while (p_customer != NULL)
	{
		CusNodeHead = CusNodeHead->next; /*头指针向链表尾移动*/
		free(p_customer);/*代指针所指空间释放*/
		p_customer = CusNodeHead;   /*代指针指向头指针 不断移动*/
	}
	
	/*订单*/
	OrderNode* p_order = OrNodeHead;
	while (p_order != NULL)
	{
		OrNodeHead = OrNodeHead->next;
		free(p_order);
		p_order = OrNodeHead;
	}
	
	/*商品*/
	ProductNode* p_product = ProNodeHead;
	while (p_product != NULL)
	{
		ProNodeHead = ProNodeHead->next;
		free(p_product);
		p_product = ProNodeHead;
	}
}