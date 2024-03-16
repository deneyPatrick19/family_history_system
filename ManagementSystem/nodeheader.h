#ifndef __NODEHEADER_H__
#define __NODEHEADER_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

/*结构声明*/
typedef struct Customer		//顾客信息
{
	int num; 				//顾客代码
	char id[21]; 			//顾客昵称
	char name[16]; 			//顾客姓名
	char address[26]; 		//地址
	char postcode[11]; 		//邮编
	char phone[12]; 		//电话
}Customer;

typedef struct Order		//订单信息
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
}Order;

typedef struct Product		//库存商品信息
{
	int category_num; 		//商品编号
	char factory_num[21]; 	//生产厂家编号
	char information[100]; 	//商品说明
	double price;	 		//单价
	int amount;  			//库存量(份)
}Product;

typedef struct Factory		//生产厂家信息
{
	char num[21]; 			//厂家代码
	char name[36]; 			//厂家名称
}Factory;

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

struct Node					//总结点 分别指向顾客、订单和商品节点
{
	CustomerNode* customerHead;
	OrderNode* orderHead; 
	ProductNode* productHead;
};

/*函数定义*/

char* GetTime(char* str_time);
void ProductDefine(ProductNode* ProNodeHead, Factory* factory);
void ReleaseNode(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead);
void WriteFile(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead);
void ReadFile(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead);

/*顾客菜单函数定义*/
void CustomerMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead);

void PurchaseMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead, char *name);
char* AssignItems(ProductNode* ProNodeHead, int* PurchaseItems, char* information);

int	SearchCustomer(CustomerNode* CusNodeHead, char name[]);

Customer InputCustomer(char* name);
CustomerNode* AddCustomer(CustomerNode* CusNodeHead, char* name);
Order InputOrder(CustomerNode* CusNodeHead, char* name);
OrderNode* AddOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead, char* name);

CustomerNode* FindCustomer(CustomerNode* CusNodeHead, int number);
OrderNode* FindOrder(OrderNode* OrNodeHead, int number);
ProductNode* FindProduct(ProductNode* ProNodeHead, int option);

void ShowReceipt(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, int number);

int DeleteOrderByCustomer(OrderNode* OrNodeHead, ProductNode* ProNodeHead, int number);
void ResumeCustomerAmount(char* information, ProductNode* ProNodeHead);

int TraversalCustomerOrders(OrderNode* OrNodeHead, CustomerNode* CusNodeHead, char* name);

void Pay(OrderNode* OrNodeHead, int number);

Customer ChangeCustomerMenu(Customer customer);
void ChangeCustomer(CustomerNode* CusNodeHead, char name[]);


/*管理员菜单函数定义*/
void AdministratorMenu(CustomerNode* CusNodeHead, OrderNode* OrNodeHead, ProductNode* ProNodeHead, Factory* factory);

int EnterPassword(char* password);

int TraversalOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead);

int CheckTransportInformation(OrderNode* OrNodeHead, CustomerNode* CusNodeHead);

int DeleteOrderByAdministrator(OrderNode* OrNodeHead, ProductNode* ProNodeHead, int number);

void ShowProduct(ProductNode* ProNodeHead);

void ConnectFactory(ProductNode* ProNodeHead, Factory* factory);

int ShowCompleteOrder(OrderNode* OrNodeHead, CustomerNode* CusNodeHead);
int ShowNotPay(OrderNode* OrNodeHead, CustomerNode* CusNodeHead);
int ShowNotTransport(OrderNode* OrNodeHead, CustomerNode* CusNodeHead);

#endif