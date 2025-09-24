// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <time.h> // 用于时间处理

#define MAX_NAME_LENGTH 50     // 商品名称最大长度
#define MAX_CATEGORY_LENGTH 30 // 商品分类最大长度
#define MAX_BARCODE_LENGTH 20  // 条形码最大长度
#define MAX_DESC_LENGTH 100    // 描述最大长度
#define MAX_SUPPLIER_LENGTH 50 // 供应商名称最大长度

// ===== 增强模块：商品状态枚举 =====
typedef enum
{
    PRODUCT_DISCONTINUED = 0, // 已下架停售
    PRODUCT_ACTIVE = 1,       // 上架销售中
    PRODUCT_PROMOTIONAL = 2,  // 促销活动中
    PRODUCT_OUT_OF_STOCK = 3  // 暂时缺货
} ProductStatus;

// 设置商品状态枚举后可以：设置商品状态、检查商品状态以及根据商品状态显示不同信息

typedef struct
{
    // === 商品核心信息 ===
    int id;                           // 商品ID
    char name[MAX_NAME_LENGTH];       // 商品名称
    char barcode[MAX_BARCODE_LENGTH]; // 商品条形码

    // === 商品价格信息 ===
    double purchase_price; // 进货价格（成本）
    double retail_price;   // 零售价格（标价）
    double discount_rate;  // 折扣率(0.0-1.0,默认1.0)
    double member_price;   // 会员价格

    // === 库存信息 ===
    int stock_quantity;  // 当前库存数量
    int min_stock_level; // 最小库存阈值（预警值）
    int max_stock_level; // 最大库存容量

    // === 分类信息 ===
    char category[MAX_CATEGORY_LENGTH]; // 商品分类（如：食品、日用品）

    // === 时间信息 ===
    time_t production_date; // 生产日期
    time_t expiration_date; // 过期日期

    // === 状态标志 ===
    ProductStatus status; // 商品状态（使用枚举更清晰）

    // === 统计信息 ===
    int sales_count;       // 销售数量
    double total_purchase; // 总成本
    double total_sales;    // 总销售额
} Product;

#endif