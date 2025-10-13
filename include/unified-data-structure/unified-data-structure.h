// include/core/CommonTypes.h
#ifndef CORE_COMMON_TYPES_H
#define CORE_COMMON_TYPES_H

#include <time.h>

#define MAX_NAME_LENGTH 50
#define MAX_CATEGORY_LENGTH 30
#define MAX_BARCODE_LENGTH 20
#define MAX_DATE_LENGTH 20

// 统一商品结构（核心字段）
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char barcode[MAX_BARCODE_LENGTH];
    double purchase_price; // 成本价（用于利润计算）
    double retail_price;   // 零售价
    int stock;             // 当前库存
} UnifiedProduct;

// 统一销售记录
typedef struct {
    int product_id;
    double unit_price;    // 销售时价格
    double cost_price;    // 成本价
    int quantity;
    time_t sale_time;      // 使用time_t保证兼容性
} UnifiedSaleRecord;

#endif