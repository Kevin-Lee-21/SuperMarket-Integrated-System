#ifndef STAFF_H
#define STAFF_H

#include "product/Product.h"

#define MAX_STAFF 50
#define MAX_STAFF_ID_LENGTH 20
#define MAX_STAFF_NAME_LENGTH 30
#define MAX_STAFF_PASSWORD_LENGTH 30

typedef struct {
    char staff_id[MAX_STAFF_ID_LENGTH];      // 员工ID
    char name[MAX_STAFF_NAME_LENGTH];        // 员工姓名
    char password[MAX_STAFF_PASSWORD_LENGTH];// 密码
    int is_logged_in;                       // 登录状态
} Staff;

// 员工验证函数
int verify_staff(const char* staff_id, const char* password);
int load_staff_from_file(const char* filename); // 从文件加载员工信息

#endif