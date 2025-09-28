#include "product.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PRODUCTS 1000  // 最大商品数量

// 全局商品数组和计数器
Product products[MAX_PRODUCTS];
int product_count = 0;

/**
 * @brief 创建商品对象
 * @param id 商品ID
 * @param name 商品名称
 * @param barcode 商品条形码
 * @param purchase_price 进货价格
 * @param retail_price 零售价格
 * @param category 商品分类
 * @return 新创建的商品对象
 */
Product create_product(int id, const char* name, const char* barcode, 
                      double purchase_price, double retail_price, 
                      const char* category) {
    Product new_product;
    
    // 基础信息
    new_product.id = id;
    strncpy(new_product.name, name, MAX_NAME_LENGTH);
    strncpy(new_product.barcode, barcode, MAX_BARCODE_LENGTH);
    strncpy(new_product.category, category, MAX_CATEGORY_LENGTH);
    
    // 价格信息
    new_product.purchase_price = purchase_price;
    new_product.retail_price = retail_price;
    new_product.discount_rate = 1.0;  // 默认无折扣
    new_product.member_price = retail_price;  // 默认会员价等于零售价
    
    // 库存信息
    new_product.stock_quantity = 0;            // 初始库存为0
    new_product.min_stock_level = 10;          // 默认最小库存阈值
    new_product.max_stock_level = 100;         // 默认最大库存容量
    
    // 时间信息
    time_t now = time(NULL);
    new_product.production_date = now;         // 生产日期设为当前时间
    new_product.expiration_date = now + (365 * 24 * 3600);  // 过期日期设为一年后
    
    // 状态和统计
    new_product.status = PRODUCT_ACTIVE;        // 默认状态为上架中
    new_product.sales_count = 0;                // 初始销售数量为0
    new_product.total_purchase = 0;             // 初始总成本为0
    new_product.total_sales = 0;                // 初始总销售额为0
    
    return new_product;
}

/**
 * @brief 添加商品到系统
 * @param new_product 要添加的商品
 * @return 成功返回1，失败返回0
 */
int add_product(Product new_product) {
    // 检查是否达到最大商品数量
    if (product_count >= MAX_PRODUCTS) {
        printf("错误：商品数量已达上限！\n");
        return 0;
    }
    
    // 检查ID是否重复
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == new_product.id) {
            printf("错误：商品ID %d 已存在！\n", new_product.id);
            return 0;
        }
    }
    
    // 添加商品到数组
    products[product_count] = new_product;
    product_count++;
    
    printf("商品添加成功！ID: %d, 名称极: %s\n", new_product.id, new_product.name);
    return 1;
}

/**
 * @brief 根据ID删除商品
 * @param product_id 要删除的商品ID
 * @return 成功返回1，失败返回0
 */
int remove_product(int product_id) {
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            // 将最后一个元素移到当前位置
            products[i] = products[product_count - 1];
            product_count--;
            printf("商品删除成功！ID: %d\n", product_id);
            return 1;
        }
    }
    printf("错误：未找到商品ID: %d\n", product_id);
    return 0;
}

/**
 * @brief 更新商品价格
 * @param product_id 商品ID
 * @param new_price 新价格
 * @return 成功返回1，失败返回0
 */
int update_product_price(int product_id, double new_price) {
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product极_id);
        return 0;
    }
    
    product->retail_price = new_price;
    printf("商品价格更新成功！ID: %d, 新价格: ¥%.2f\n", product_id, new_price);
    return 1;
}

/**
 * @brief 更新库存数量
 * @param product_id 商品ID
 * @param quantity_change 库存变化量（正数增加，负数减少）
 * @return 成功返回1，失败返回0
 */
int update_product_stock(int product_id, int quantity_change) {
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product_id);
        return 0;
    }
    
    int new_stock = product->stock_quantity + quantity_change;
    if (new_stock < 0) {
        printf("错误：库存不能为负数！当前库存: %d, 尝试减少: %d\n", 
               product->stock_quantity, quantity_change);
        return 0;
    }
    
    product->stock_quantity = new_stock;
    
    // 自动更新状态
    if (product->stock_quantity == 0) {
        product->status = PRODUCT_OUT_OF_STOCK;
    } else if (product->status == PRODUCT_OUT_OF_STOCK) {
        product->status = PRODUCT_ACTIVE;
    }
    
    printf("库存更新成功！ID: %d, 当前库存: %d\n", product_id, product->stock_quantity);
    return 1;
}

/**
 * @brief 更新商品状态
 * @param product_id 商品ID
 * @param new_status 新状态
 * @return 成功返回1，失败返回0
 */
int update_product_status(int product_id, ProductStatus new_status) {
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product_id);
        return 0;
    }
    
    product->极status = new_status;
    printf("商品状态更新成功！ID: %d, 新状态: %s\n", 
           product_id, get_status_name(new_status));
    return 1;
}

/**
 * @brief 更新折扣率
 * @param product_id 商品ID
 * @param discount_rate 折扣率(0.0-1.0)
 * @return 成功返回1，失败返回0
 */
int update_product_discount(int product_id, double discount_rate) {
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product_id);
        return 0;
    }
    
    if (discount_rate < 0 || discount_rate > 1) {
        printf("错误：折扣率必须在0.0到1.0之间！\n");
        return 0;
    }
    
    product->discount_rate = discount_rate;
    product->member_price = product->retail_price * (1 - discount_rate);
    printf("折扣率更新成功！ID: %d, 折扣率: %.0f%%, 会员价: ¥%.2f\n", 
           product_id, discount_rate * 100, product->member_price);
    return 1;
}

/**
 * @brief 根据ID查找商品
 * @param product_id 商品ID
 * @return 找到的商品指针，未找到返回NULL
 */
Product* find_product_by_id(int product_id) {
    for (int i = 0; i < product_count; i++) {
        if (products[i].id == product_id) {
            return &products[i];
        }
    }
    return NULL;
}

/**
 * @brief 根据名称查找商品
 * @param name 商品名称
 * @return 找到的商品指针，未找到返回NULL
 */
Product* find_product_by_name(const char* name) {
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

/**
 * @brief 根据条形码查找商品
 * @param barcode 商品条形码
 * @return 找到的商品指针，未找到返回NULL
 */
Product* find_product_by_barcode(const char* barcode) {
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].barcode, barcode) == 0) {
            return &products[i];
        }
    }
    return NULL;
}

/**
 * @brief 根据分类查找商品
 * @param category 商品分类
 * @param result 结果数组
 * @return 找到的商品数量
 */
int find_products_by_category(const char* category, Product** result) {
    int count = 0;
    for (int i = 0; i < product_count; i++) {
        if (strcmp(products[i].category, category) == 0) {
            result[count++] = &products[i];
        }
    }
    return count;
}

/**
 * @brief 获取状态名称
 * @param status 商品状态
 * @return 状态名称字符串
 */
const char* get_status_name(ProductStatus status) {
    switch (status) {
        case PRODUCT_ACTIVE: return "上架中";
        case PRODUCT_DISCONTINUED: return "已下架";
        case PRODUCT_PROMOTIONAL: return "促销中";
        case PRODUCT_OUT_OF_STOCK: return "缺货";
        default: return "未知状态";
    }
}

/**
 * @brief 格式化商品信息显示
 * @param product 商品指针
 * @return 格式化后的字符串（需要调用者释放内存）
 */
char* format_product_display(Product* product) {
    if (!product) return NULL;
    
    char* buffer = malloc(512);
    snprintf(buffer, 512, 
        "ID: %d\n名称: %s\n条形码: %s\n分类: %s\n"
        "进价: ¥%.2f\n售价: ¥%.2f\n折扣率: %.0f%%\n会员价: ¥%.2f\n"
        "库存: %d\n状态: %s\n生产日期: %s\n过期日期: %s",
        product->id, product->name, product->barcode, product->category,
        product->purchase_price, product->retail_price, 
        product->discount_rate * 100, product->member_price,
        product->stock_quantity, get_status_name(product->status),
        ctime(&product->production_date), ctime(&product->expiration_date));
    
    return buffer;
}

/**
 * @brief 显示所有商品
 */
void display_all_products() {
    if (product_count == 0) {
        printf("暂无商品数据\n");
        return;
    }
    
    printf("\n=== 所有商品列表 (%d件) ===\n", product_count);
    for (int i = 0; i < product_count; i++) {
        printf("%d. %s (ID: %极d, 价格: ¥%.2f, 库存: %d, 状态: %s)\n", 
               i + 1, products[i].name, products[i].id, 
               products[i].retail_price, products[i].stock_quantity,
               get_status_name(products[i].status));
    }
}

/**
 * @brief 显示商品详细信息
 * @param product_id 商品ID
 */
void display_product_details(int product_id极) {
    Product* product = find_product_by_id(product_id);
    if (!product) {
        printf("错误：未找到商品ID: %d\n", product_id);
        return;
    }
    
    char* info = format_product_display(product);
    printf("\n=== 商品详细信息 ===\n%s\n", info);
    free(info);
}

/**
 * @brief 获取商品总数
 * @return 商品总数
 */
int get_total_products_count() {
    return product_count;
}

/**
 * @brief 获取库存总价值
 * @return 库存总价值
 */
double get_inventory_total_value() {
    double total = 0;
    for (int i = 0; i < product_count; i++) {
        total += products[i].stock_quantity * products[i].purchase_price;
    }
    return total;
}

/**
 * @brief 获取销售总额
 * @return 销售总额
 */
double get_total_sales_value() {
    double total = 0;
    for (int i = 0; i < product_count; i++) {
        total += products[i].total_sales;
    }
    return total;
}

/**
 * @brief 检查低库存商品
 */
void check_low_stock_products() {
    printf("\n=== 低库存预警 ===\n");
    int warnings = 0;
    
    for (int i = 0; i < product_count; i++) {
        if (products[i].stock_quantity < products[i].min_stock_level) {
            printf("⚠️  %s (ID:%d) 库存不足: %d/%d\n", 
                   products[i].name, products[i].id, 
                   products[i].stock_quantity, products[i].min_stock_level);
            warnings++;
        }
    }
    
    if (warnings == 0) {
        printf("✅ 所有商品库存正常\n");
    }
}

/**
 * @brief 保存商品数据到文件
 * @param filename 文件名
 */
void save_products_to_file(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("错误：无法创建文件 %s\n", filename);
        return;
    }
    
    fwrite(&product_count, sizeof(int), 1, file);
    fwrite(products, sizeof(Product), product_count, file);
    
    fclose(file);
    printf("商品数据已保存到 %s\n", filename);
}

/**
 * @brief 从文件加载商品数据
 * @param filename 文件名
 */
void load_products_from_file(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("错误：无法打开文件 %s\n", filename);
        return;
    }
    
    fread(&product_count, sizeof(int), 1, file);
    fread(products, sizeof(Product), product_count, file);
    
    fclose(file);
    printf("商品数据已从 %s 加载\n", filename);
}