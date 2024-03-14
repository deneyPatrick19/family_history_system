#ifndef __HEADER_H__
#define __HEADER_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

/*结构声明*/
typedef struct Customer //顾客信息
{
	int num; //顾客代码
	char id[21]; //顾客昵称
	char name[16]; //顾客姓名
	char address[26]; //地址
	char postcode[11]; //邮编
	char phone[12]; //电话
}Customer;

typedef struct Order	//订单信息
{
	int number; //订单号
	char pay_date[30];  //下单日期
	int customer_num;  //顾客代码
	int transport_flag; // 是否发货标识  1表示已开始配送 0表示未开始
	int pay_flag; //是否付款标识  1表示已付款 0表示未付款
	char transport_date[30]; //运输日期
	double transport_pay; //运费  
	double amount; //数量
	double total_price; //总金额
	char information[100];
}Order;

typedef struct Product	//库存商品信息
{
	int category_num; //商品编号
	char factory_num[21]; //生产厂家编号
	char information[100]; //商品说明
	double price;	 //单价
	int amount;  //库存量(份)
}Product;

typedef struct Factory	//生产厂家信息
{
	char num[21]; //厂家代码
	char name[36]; //厂家名称
}Factory;

//函数定义

void DefineProduct(Product product[], Factory factory[]);
void WriteFile(Customer customer[], Order order[], Product product[], int customer_orderNum[]);
void ReadFile(Customer customer[], Order order[], Product product[], int customer_orderNum[]);
/*顾客菜单函数定义*/
void CustomerMenu(Customer customer[], Order order[], Product product[], int customer_orderNum[]);

void PurchaseMenu(Customer customer[], Order order[], int customer_orderNum[], Product product[], char name[]);
Customer InputCustomer(Customer c, int customer_orderNum[], char name[]);
void AddCustomer(Customer customer[],int customer_orderNum[], char name[]);
int SearchCustomer(Customer customer[],int customer_orderNum[],char var_name[]);
char* AssignItems(Product product[], int PurchaseItems[],char* information);
void AddOrder(Order order[], Customer customer[], char name[], int customer_orderNum[], int PurchaseItems[]);
void TraversalCustomer(Customer customer[], int customer_orderNum[]);
void TraversalOrder(Order order[], int customer_orderNum[]);
char* GetTime(char* str_time);
int FindOrder(Order order[], int customer_orderNum[], int var_number);
int FindCustomer(Customer customer[], int customer_orderNum[], int var_customernum);
void ShowReceipt(Customer customer[], Order order[], int order_number, int customer_orderNum[]);
void Pay(Order order[], int customer_orderNum[], int order_number);
void ChangeCustomerInfor(Customer customer[], int flag);

/*管理员菜单函数定义*/
void AdministratorMenu(Customer customer[], Order order[], Product product[], Factory factory[], int customer_orderNum[]);
int EnterPassword(char password[]);
void CheckTransportInfor(Order order[], Customer customer[], int customer_orderNum[]);
int DeleteOrder(Order order[], int customer_orderNum[], int var_number);
void ShowProduct(Product product[]);
void ConnectFactory(Factory factory[], Product product[]);
void ShowCompleteOrder(Order order[], int customer_orderNum[]);
void ShowNotPay(Order order[], int customer_orderNum[]);
void ShowNotTransport(Order order[], Customer customer[], int customer_orderNum[]);

#endif
