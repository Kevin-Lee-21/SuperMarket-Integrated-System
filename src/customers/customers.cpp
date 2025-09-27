#include "customers.h"

Customer customers[MAX_CUSTOMERS]; // 定义客户数组
int customerCount = 0;             // 当前客户数

// 从文件加载客户信息
void loadCustomers(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("客户信息文件未找到，已创建新文件。\n");
        return;
    }
    customerCount = 0;
    while (fscanf(fp, "%s %s %d",
                  customers[customerCount].name,
                  customers[customerCount].phone,
                  &customers[customerCount].points) == 3) {
        customerCount++;
    }
    fclose(fp);
}

// 保存客户信息到文件
void saveCustomers(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("保存失败，无法打开文件！\n");
        return;
    }
    for (int i = 0; i < customerCount; i++) {
        fprintf(fp, "%s %s %d\n",
                customers[i].name,
                customers[i].phone,
                customers[i].points);
    }
    fclose(fp);
}

// 添加客户
void addCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("客户数量已满，无法添加。\n");
        return;
    }
    printf("请输入客户姓名: ");
    scanf("%s", customers[customerCount].name);
    printf("请输入客户电话: ");
    scanf("%s", customers[customerCount].phone);
    customers[customerCount].points = 0; // 默认积分为0
    customerCount++;
    printf("客户添加成功！\n");
}

// 显示客户列表
void showCustomers() {
    printf("\n---- 客户列表 ----\n");
    for (int i = 0; i < customerCount; i++) {
        printf("姓名: %s | 电话: %s | 积分: %d\n",
               customers[i].name,
               customers[i].phone,
               customers[i].points);
    }
    printf("-------------------\n");
}

// 按电话查找客户
int findCustomerByPhone(const char *phone) {
    for (int i = 0; i < customerCount; i++) {
        if (strcmp(customers[i].phone, phone) == 0) {
            return i;
        }
    }
    return -1; // 未找到
}

// 给客户增加积分
void addPoints(const char *phone, int points) {
    int idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printf("未找到该客户，无法加积分。\n");
        return;
    }
    customers[idx].points += points;
    printf("积分添加成功！当前积分: %d\n", customers[idx].points);
}

// 删除客户
void deleteCustomer() {
    char phone[20];
    printf("请输入要删除的客户电话: ");
    scanf("%s", phone);

    int idx = findCustomerByPhone(phone);
    if (idx == -1) {
        printf("未找到该客户。\n");
        return;
    }
    for (int i = idx; i < customerCount - 1; i++) {
        customers[i] = customers[i + 1]; // 前移覆盖
    }
    customerCount--;
    printf("客户删除成功！\n");
}

