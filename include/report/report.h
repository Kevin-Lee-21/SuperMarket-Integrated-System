#ifndef REPORT_H
#define REPORT_H

#include <time.h>   // �������ڴ���
#include <string.h> // �����ַ�������

#define MAX_NAME_LENGTH 50 // ��Ʒ������󳤶�
#define MAX_DATE_LENGTH 20 // �����ַ�����󳤶� (YYYY-MM-DD)

// ===== ���ۼ�¼�ṹ�� =====
typedef struct
{
    int id;                        // ��Ʒ���
    char name[MAX_NAME_LENGTH];    // ��Ʒ����
    double price;                  // ����
    int quantity;                  // ��������
    char date[MAX_DATE_LENGTH];    // �������ڣ���ʽ��YYYY-MM-DD��
} SaleRecord;

// ===== ����ģ����Ľṹ�� =====
typedef struct
{
    SaleRecord sales[100]; // �洢���ۼ�¼�������趨��� 100 ��������չ��
    int count;             // ��ǰ���ۼ�¼����
} Report;

// ===== ����ģ�麯������ =====
void initReport(Report *report);                              // ��ʼ������
void addSaleRecord(Report *report, SaleRecord record);        // ������ۼ�¼
void generateDailyReport(Report *report, const char *date);   // �����ձ���
void generateMonthlyReport(Report *report, const char *month);// �����±���
void generateYearlyReport(Report *report, const char *year);  // �����걨��

#endif // REPORT_H
