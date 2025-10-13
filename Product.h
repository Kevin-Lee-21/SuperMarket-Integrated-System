#pragma once

#include <time.h> // 用于时间处理
#define MAX_NAME_LENGTH 50     // 商品名称最大长度
#define MAX_CATEGORY_LENGTH 30 // 商品分类最大长度
#define MAX_DESC_LENGTH 100    // 描述最大长度
#define MAX_SUPPLIER_LENGTH 50 // 供应商名称最大长度
#define MAX_PRODUCTS 1000
#define MAXSIZE 1000


typedef struct {
    int id;                  // 商品id
    char name[MAX_NAME_LENGTH];            // 商品名称
    char category[MAX_CATEGORY_LENGTH];        // 商品分类
    char cost_price[20];         // 成本价格
    char selling_price[20];      // 销售价格
    char stock[20];                // 当前库存数量
    char min_stock[20];            // 最小库存预警值
    char max_stock[20];            // 最大库存容量
    char supplier[MAX_SUPPLIER_LENGTH];        // 供应商信息
    char production_date[11]; // 生产日期，格式为 "YYYY-MM-DD"
    int expiry_days;          //保质期     
    
} Product;

extern Product items[MAXSIZE];
extern int length;
extern char* categories[];

void MainMenu();
void AdMenu();
void save_data();
void load_data();
void Show();
void Show_category_AD();
void Show_category_CU();
void Append();
void Delete();
void Modify();
void Find();
void Find_by_name();
Product* Find_by_id(int id);