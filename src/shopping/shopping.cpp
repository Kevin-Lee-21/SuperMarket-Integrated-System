#include "shopping.h"
#include "customers.h" // 用于更新顾客积分
#include "products.h"  // 商品模块预留接口
#include <string.h>

// ================= 购物模块实现 =================

// 顾客购物菜单
void shoppingMenu() {
    int choice;
    do {
        printf("\n--- 顾客购物 ---\n");
        printf("1. 查看商品\n");
        printf("2. 购买商品\n");
        printf("0. 返回主菜单\n");
        printf("请选择: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                showProductsForShopping(); // 显示商品
                break;
            case 2:
                buyProduct(); // 购买商品
                break;
            case 0:
                break;
            default:
                printf("无效选择，请重试。\n");
        }
    } while(choice != 0);
}

// 显示商品列表（调用商品模块的接口）
// TODO: 后续在 products.c 中完善
void showProductsForShopping() {
    printf("=== 商品列表 ===\n");
    showProducts(); // 调用 products.h 中预留接口
}

// 顾客购买商品
void buyProduct() {
    char phone[20];
    char productName[50];
    int quantity;

    printf("请输入您的手机号（用于积分统计）: ");
    scanf("%s", phone);

    printf("请输入购买的商品名称: ");
    scanf("%s", productName);

    printf("请输入购买数量: ");
    scanf("%d", &quantity);

    // 调用商品模块接口，减少库存（预留）
    updateStock(productName, quantity);

    // 调用客户管理模块接口，增加积分
    int points = quantity * 10; // 假设每件商品加10积分
    addPoints(phone, points);

    printf("购买成功！已为手机号 %s 增加 %d 积分\n", phone, points);
}

