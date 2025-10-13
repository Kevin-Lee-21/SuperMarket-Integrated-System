#include "Report.h"
#include <stdio.h>
#include <string.h>

// 初始化报表
void initReport(Report *report)
{
    report->count = 0;
}

// 添加销售记录
void addSaleRecord(Report *report, SaleRecord record)
{
    if (report->count < 100) // 简单限制
    {
        report->sales[report->count++] = record;
    }
}

// 生成日报表
void generateDailyReport(Report *report, const char *date)
{
    printf("==== 日报表 (%s) ====\n", date);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strcmp(report->sales[i].date, date) == 0)
        {
            double subtotal = report->sales[i].price * report->sales[i].quantity;
            printf("商品: %s 数量: %d 单价: %.2f 小计: %.2f\n",
                   report->sales[i].name,
                   report->sales[i].quantity,
                   report->sales[i].price,
                   subtotal);
            total += subtotal;
        }
    }
    printf("当天总销售额: %.2f\n", total);
}

// 生成月报表
void generateMonthlyReport(Report *report, const char *month)
{
    printf("==== 月报表 (%s) ====\n", month);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strncmp(report->sales[i].date, month, 7) == 0) // 前7位是YYYY-MM
        {
            total += report->sales[i].price * report->sales[i].quantity;
        }
    }
    printf("本月总销售额: %.2f\n", total);
}

// 生成年报表
void generateYearlyReport(Report *report, const char *year)
{
    printf("==== 年报表 (%s) ====\n", year);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strncmp(report->sales[i].date, year, 4) == 0) // 前4位是年份
        {
            total += report->sales[i].price * report->sales[i].quantity;
        }
    }
    printf("本年总销售额: %.2f\n", total);
}
