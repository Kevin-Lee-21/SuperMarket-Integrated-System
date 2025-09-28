#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "payment.h"
#include "product/Product.h"
#include "member.h"
#include "Report.h"

// 全局变量声明
extern Product products[MAX_PRODUCTS];
extern int product_count;
extern Report sales_report;
extern Member members[MAX_MEMBERS];
extern int member_count;

// 初始化购物车
void init_shopping_cart(ShoppingCart* cart) {
    cart->item_count = 0;
    cart->total_amount = 0;
    cart->discount = 0;
    cart->final_amount = 0;
    memset(cart->member_id, 0, MAX_MEMBER_ID_LENGTH);
}

// 添加商品到购物车
int add_to_cart(ShoppingCart* cart, int product_id, int quantity) {
    if (cart->item_count >= MAX_CART_ITEMS) {
        printf("错误：购物车已满！\n");
        return 0;
    }
    
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product_id);
        return 0;
    }
    
    if (product->stock_quantity < quantity) {
        printf("错误：库存不足！当前库存: %d，需要: %d\n", 
               product->stock_quantity, quantity);
        return 0;
    }
    
    // 添加到购物车
    CartItem new_item;
    new_item.product_id = product_id;
    strncpy(new_item.product_name, product->name, MAX_NAME_LENGTH);
    new_item.price = product->retail_price;
    new_item.quantity = quantity;
    new_item.subtotal = product->retail_price * quantity;
    
    cart->items[cart->item_count++] = new_item;
    cart->total_amount += new_item.subtotal;
    
    return 1;
}

// 从购物车移除商品
int remove_from_cart(ShoppingCart* cart, int product_id) {
    for (int i = 0; i < cart->item_count; i++) {
        if (cart->items[i].product_id == product_id) {
            // 从总金额中减去
            cart->total_amount -= cart->items[i].subtotal;
            
            // 将最后一个元素移到当前位置
            cart->items[i] = cart->items[cart->item_count - 1];
            cart->item_count--;
            
            printf("商品已从购物车移除！\n");
            return 1;
        }
    }
    printf("错误：未找到商品ID: %d\n", product_id);
    return 0;
}

// 显示购物车内容
void display_cart(ShoppingCart* cart) {
    printf("\n=== 购物车内容 ===\n");
    for (int i = 0; i < cart->item_count; i++) {
        printf("%d. %s x%d ¥%.2f = ¥%.2f\n", 
               i + 1, cart->items[i].product_name, cart->items[i].quantity,
               cart->items[i].price, cart->items[i].subtotal);
    }
    printf("总计: ¥%.2f\n", cart->total_amount);
    
    // 如果是会员，显示折扣信息
    if (strlen(cart->member_id) > 0) {
        double discount_rate = calculate_member_discount(cart->member_id);
        double discount_amount = cart->total_amount * discount_rate;
        printf("会员折扣: -¥%.2f (%.0f%%)\n", discount_amount, discount_rate * 100);
        printf("最终金额: ¥%.2f\n", cart->total_amount - discount_amount);
    }
}

// 处理支付
int process_payment(ShoppingCart* cart, const char* payment_method) {
    // 计算最终金额（考虑会员折扣）
    if (strlen(cart->member_id) > 0) {
        double discount_rate = calculate_member_discount(cart->member_id);
        cart->discount = cart->total_amount * discount_rate;
        cart->final_amount = cart->total_amount - cart->discount;
    } else {
        cart->final_amount = cart->total_amount;
    }
    
    // 更新库存和销售数据
    for (int i = 0; i < cart->item_count; i++) {
        Product* product = find_product_by_id(cart->items[i].product_id);
        if (product) {
            // 更新库存
            update_product_stock(product->id, -cart->items[i].quantity);
            
            // 更新销售统计
            product->sales_count += cart->items[i].quantity;
            product->total_sales += cart->items[i].subtotal;
            
            // 添加到销售报告
            SaleRecord record;
            record.id = product->id;
            strncpy(record.name, product->name, MAX_NAME_LENGTH);
            record.price = product->retail_price;
            record.quantity = cart->items[i].quantity;
            
            // 获取当前日期
            time_t now = time(NULL);
            struct tm* t = localtime(&now);
            snprintf(record.date, MAX_DATE_LENGTH, "%04d-%02d-%02d", 
                    t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
            
            addSaleRecord(&sales_report, record);
        }
    }
    
    // 如果是会员，更新积分
    if (strlen(cart->member_id) > 0) {
        // 每消费1元获得1积分
        double points_earned = cart->final_amount;
        add_member_points(cart->member_id, points_earned);
    }
    
    printf("支付成功！支付方式: %s, 支付金额: ¥%.2f\n", 
           payment_method, cart->final_amount);
    return 1;
}

// 生成收据
void generate_receipt(ShoppingCart* cart, const char* payment_method) {
    printf("\n========== 收据 ==========\n");
    printf("交易时间: %s", ctime(&time(NULL)));
    
    for (int i = 0; i < cart->item_count; i++) {
        printf("%s x%d ¥%.2f = ¥%.2f\n", 
               cart->items[i].product_name, cart->items[i].quantity,
               cart->items[i].price, cart->items[i].subtotal);
    }
    
    printf("--------------------------\n");
    printf("商品总额: ¥%.2f\n", cart->total_amount);
    
    if (cart->discount > 0) {
        printf("会员折扣: -¥%.2f\n", cart->discount);
    }
    
    printf("应付金额: ¥%.2f\n", cart->final_amount);
    printf("支付方式: %s\n", payment_method);
    
    if (strlen(cart->member_id) > 0) {
        printf("会员ID: %s\n", cart->member_id);
        
        // 显示获得的积分
        double points_earned = cart->final_amount;
        printf("获得积分: %.1f\n", points_earned);
    }
    
    printf("==========================\n");
    printf("感谢您的光临！\n");
}