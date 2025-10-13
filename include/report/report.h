#ifndef REPORT_H
#define REPORT_H

#include <time.h>   // 用于日期处理
#include <string.h> // 用于字符串处理

#define MAX_NAME_LENGTH 50 // 商品名称最大长度
#define MAX_DATE_LENGTH 20 // 日期字符串最大长度 (YYYY-MM-DD)

// ===== 销售记录结构体 =====
typedef struct
{
    int id;                        // 商品编号
    char name[MAX_NAME_LENGTH];    // 商品名称
    double price;                  // 单价
    int quantity;                  // 销售数量
    char date[MAX_DATE_LENGTH];    // 销售日期（格式：YYYY-MM-DD）
} SaleRecord;

// ===== 报表模块核心结构体 =====
typedef struct
{
    SaleRecord sales[100]; // 存储销售记录（这里设定最多 100 条，可扩展）
    int count;             // 当前销售记录数量
} Report;

// ===== 报表模块函数声明 =====
void initReport(Report *report);                              // 初始化报表
void addSaleRecord(Report *report, SaleRecord record);        // 添加销售记录
void generateDailyReport(Report *report, const char *date);   // 生成日报表
void generateMonthlyReport(Report *report, const char *month);// 生成月报表
void generateYearlyReport(Report *report, const char *year);  // 生成年报表

#endif // REPORT_H
