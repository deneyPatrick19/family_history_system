#ifndef __ADMINISTRATOR_H__
#define __ADMINISTRATOR_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>

/*结构声明*/
struct Customer;	//顾客信息
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
CustomerNode* FindCustomer(CustomerNode* CusNodeHead, int number);
OrderNode* FindOrder(OrderNode* OrNodeHead, int number);
ProductNode* FindProduct(ProductNode* ProNodeHead, int option);

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