#include "Report.h"
#include <stdio.h>
#include <string.h>

// ��ʼ������
void initReport(Report *report)
{
    report->count = 0;
}

// ������ۼ�¼
void addSaleRecord(Report *report, SaleRecord record)
{
    if (report->count < 100) // ������
    {
        report->sales[report->count++] = record;
    }
}

// �����ձ���
void generateDailyReport(Report *report, const char *date)
{
    printf("==== �ձ��� (%s) ====\n", date);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strcmp(report->sales[i].date, date) == 0)
        {
            double subtotal = report->sales[i].price * report->sales[i].quantity;
            printf("��Ʒ: %s ����: %d ����: %.2f С��: %.2f\n",
                   report->sales[i].name,
                   report->sales[i].quantity,
                   report->sales[i].price,
                   subtotal);
            total += subtotal;
        }
    }
    printf("���������۶�: %.2f\n", total);
}

// �����±���
void generateMonthlyReport(Report *report, const char *month)
{
    printf("==== �±��� (%s) ====\n", month);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strncmp(report->sales[i].date, month, 7) == 0) // ǰ7λ��YYYY-MM
        {
            total += report->sales[i].price * report->sales[i].quantity;
        }
    }
    printf("���������۶�: %.2f\n", total);
}

// �����걨��
void generateYearlyReport(Report *report, const char *year)
{
    printf("==== �걨�� (%s) ====\n", year);
    double total = 0;
    for (int i = 0; i < report->count; i++)
    {
        if (strncmp(report->sales[i].date, year, 4) == 0) // ǰ4λ�����
        {
            total += report->sales[i].price * report->sales[i].quantity;
        }
    }
    printf("���������۶�: %.2f\n", total);
}
