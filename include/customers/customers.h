#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdio.h>
#include <string.h>

#define MAX_CUSTOMERS 100   // 最大客户数

// 客户数据结构
typedef struct {
    char name[50];     // 客户姓名
    char phone[20];    // 客户电话
    int points;        // 客户积分
} Customer;

// 全局客户数组与计数
extern Customer customers[MAX_CUSTOMERS];
extern int customerCount;

// 客户管理模块函数声明
void loadCustomers(const char *filename);     // 从文件读取客户信息
void saveCustomers(const char *filename);     // 保存客户信息到文件
void addCustomer();                           // 添加客户
void showCustomers();                         // 显示所有客户
int findCustomerByPhone(const char *phone);   // 按电话查找客户
void addPoints(const char *phone, int points);// 给客户加积分
void deleteCustomer();                        // 删除客户

#endif

