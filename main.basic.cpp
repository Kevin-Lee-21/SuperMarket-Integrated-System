#include <stdio.h>
#include "users.h"       // 员工管理模块
#include "customers.h"   // 客户管理模块
#include "shopping.h"    // 顾客购物模块
// #include "products.h" // 商品管理模块（预留接口）

#define USERS_FILE     "include/users/users.txt"
#define CUSTOMERS_FILE "include/customers/customers.txt"
#define PRODUCTS_FILE  "include/products/products.txt" // 预留

// ================= 商品管理模块预留函数 =================
// 后续在 products.c / products.h 实现
void showProducts();             // 展示商品信息
void addProduct();               // 添加商品
void modifyProduct();            // 修改商品信息
void updateStockAndPoints();     // 购买商品后更新库存和积分
void updateStock(char *productName, int quantity); // 购物模块调用

// ================= 主菜单 =================
void menu() {
    printf("\n===== 超市管理系统 =====\n");
    printf("1. 顾客购物\n");
    printf("2. 员工管理\n");
    printf("3. 客户管理\n");
    printf("4. 商品管理\n");
    printf("0. 退出系统\n");
    printf("=======================\n");
    printf("请输入操作: ");
}

// ================= 员工管理子菜单 =================
void userMenu() {
    int choice;
    do {
        printf("\n--- 员工管理 ---\n");
        printf("1. 添加员工\n");
        printf("2. 显示员工\n");
        printf("3. 删除员工\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addUser(); break;
            case 2: showUsers(); break;
            case 3: deleteUser(); break;
            case 0: break;
            default: printf("无效选择，请重试。\n");
        }
    } while(choice != 0);
}

// ================= 客户管理子菜单 =================
void customerMenu() {
    int choice;
    do {
        printf("\n--- 客户管理 ---\n");
        printf("1. 添加客户\n");
        printf("2. 显示客户\n");
        printf("3. 给客户加积分\n");
        printf("4. 删除客户\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        char phone[20];
        int points;

        switch(choice) {
            case 1: addCustomer(); break;
            case 2: showCustomers(); break;
            case 3:
                printf("请输入客户电话: ");
                scanf("%s", phone);
                printf("请输入积分: ");
                scanf("%d", &points);
                addPoints(phone, points);
                break;
            case 4: deleteCustomer(); break;
            case 0: break;
            default: printf("无效选择，请重试。\n");
        }
    } while(choice != 0);
}

// ================= 商品管理子菜单（预留） =================
void productMenu() {
    int choice;
    do {
        printf("\n--- 商品管理 ---\n");
        printf("1. 查看商品\n");
        printf("2. 添加商品（管理层）\n");
        printf("3. 修改商品（管理层）\n");
        printf("4. 更新库存和积分（员工操作）\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: showProducts(); break;
            case 2: addProduct(); break;
            case 3: modifyProduct(); break;
            case 4: updateStockAndPoints(); break;
            case 0: break;
            default: printf("无效选择，请重试。\n");
        }
    } while(choice != 0);
}

// ================= 主函数 =================
int main() {
    int choice;

    // 系统启动时加载数据
    loadUsers(USERS_FILE);
    loadCustomers(CUSTOMERS_FILE);
    // loadProducts(PRODUCTS_FILE); // 预留

    do {
        menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1: shoppingMenu(); break;   // 顾客购物模块放前面
            case 2: userMenu(); break;       // 员工管理
            case 3: customerMenu(); break;   // 客户管理
            case 4: productMenu(); break;    // 商品管理（预留）
            case 0:
                printf("正在保存数据并退出...\n");
                saveUsers(USERS_FILE);
                saveCustomers(CUSTOMERS_FILE);
                // saveProducts(PRODUCTS_FILE); // 预留
                break;
            default: printf("无效选择，请重试。\n");
        }
    } while(choice != 0);

    return 0;
}

