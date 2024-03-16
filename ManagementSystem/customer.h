#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

/*结构声明*/
struct Customer;		//顾客信息
struct Order;		//订单信息
struct Product;		//库存商品信息
struct Factory;		//生产厂家信息
/*链表节点声明*/
struct CustomerNode;			//顾客节点
struct OrderNode;			//订单节点
struct ProductNode;			//商品节点


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
void ChangeCustomer(CustomerNode* CusNodeHead, char* name);

#endif