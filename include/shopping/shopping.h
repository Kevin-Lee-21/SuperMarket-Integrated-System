#ifndef SHOPPING_H
#define SHOPPING_H

#include <stdio.h>

// ================= 顾客购物模块函数接口 =================

// 购物模块主入口
// 1. 显示商品
// 2. 选择商品购买
// 3. 结算并更新库存、积分（调用员工/商品模块提供的接口）
void shoppingMenu();

// 显示商品列表（接口调用商品模块的函数即可）
// 这里仅是占位函数，后续在 products.c 实现
void showProductsForShopping();

// 顾客选择商品并购买
void buyProduct();

#endif

