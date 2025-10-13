#define _CRT_SECURE_NO_WARNINGS
#include "Report.h"
#include "Product.h"

#include "D:\desk top\Sepermarket\Sepermarket\payment.h"
#include <stdio.h>
#include <string.h>
#include <time.h>


Report report;

int saveReportToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s 进行写入\n", filename);
        return -1;
    }

    // 写入记录数量
    fprintf(file, "%d\n", report.count);

    // 写入每条销售记录
    for (int i = 0; i < report.count; i++) {
        fprintf(file, "%d,%s,%s,%s,%s\n",
            report.sales[i].id,
            report.sales[i].name,
            report.sales[i].price,
            report.sales[i].quantity,
            report.sales[i].date);
    }

    fclose(file);
    return 0;
}

// 从文件读取报表数据
int loadReportFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s 进行读取\n", filename);
        return -1;
    }

    // 读取记录数量
    if (fscanf(file, "%d\n", &report.count) != 1) {
        printf("文件格式错误\n");
        fclose(file);
        return -1;
    }

    // 检查记录数量是否超出限制
    if (report.count > 100) {
        printf("记录数量超出限制\n");
        fclose(file);
        return -1;
    }

    // 读取每条销售记录
    for (int i = 0; i < report.count; i++) {
        int id;
        char name[MAX_NAME_LENGTH];
        char price[20];
        char quantity[20];
        char date[MAX_DATE_LENGTH];

        if (fscanf(file, "%d,%[^,],%[^,],%[^,],%s\n",
            &id, name, price, quantity, date) != 5) {
            printf("读取第 %d 条记录时出错\n", i + 1);
            fclose(file);
            return -1;
        }

        report.sales[i].id = id;
        strcpy(report.sales[i].name, name);
        strcpy(report.sales[i].price, price);
        strcpy(report.sales[i].quantity, quantity);
        strcpy(report.sales[i].date, date);
    }

    fclose(file);
    return 0;
}

void init_record(SaleRecord* record, CartItem* item) {
    record->id = item->product_id;
    strcpy(record->name, item->product_name);
    strcpy(record->price, item->price);
    strcpy(record->quantity, item->quantity);
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[11]; // 10个字符 + 结束符

    // 获取当前时间
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // 格式化为 xxxx-xx-xx
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    strcpy(record->date, buffer);

}

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
            double subtotal = extractDouble(report->sales[i].price) * extractDouble(report->sales[i].quantity);
            printf("商品: %s 数量: %s 单价: %s 小计: %.2f元\n",
                   report->sales[i].name,
                   report->sales[i].quantity,
                   report->sales[i].price,
                   subtotal);
            total += subtotal;
        }
    }
    printf("当天总销售额: %.2f元\n", total);
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
            total += extractDouble(report->sales[i].price) * extractDouble(report->sales[i].quantity);
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
            total += extractDouble(report->sales[i].price) * extractDouble(report->sales[i].quantity);
        }
    }
    printf("本年总销售额: %.2f\n", total);
}
