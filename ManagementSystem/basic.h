#ifndef __BASIC_H__
#define __BASIC_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

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
#endif