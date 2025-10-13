#ifndef PAYMENT_H
#define PAYMENT_H

#include "product/Product.h"
#include "member.h"

#define MAX_CART_ITEMS 20
#define MAX_PAYMENT_METHOD_LENGTH 20

typedef struct {
    int product_id;
    char product_name[MAX_NAME_LENGTH];
    double price;
    int quantity;
    double subtotal;
} CartItem;

typedef struct {
    CartItem items[MAX_CART_ITEMS];
    int item_count;
    double total_amount;
    double discount;
    double final_amount;
    char member_id[MAX_MEMBER_ID_LENGTH];
} ShoppingCart;

// 支付相关函数
void init_shopping_cart(ShoppingCart* cart);
int add_to_cart(ShoppingCart* cart, int product_id, int quantity);
int remove_from_cart(ShoppingCart* cart, int product_id);
void display_cart(ShoppingCart* cart);
int process_payment(ShoppingCart* cart, const char* payment_method);
void generate_receipt(ShoppingCart* cart, const char* payment_method);

#endif