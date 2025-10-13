#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"

// 全局员工数组
Staff staffs[MAX_STAFF];
int staff_count = 0;

// 从文件加载员工信息
int load_staff_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("错误：无法打开员工文件 %s\n", filename);
        return 0;
    }
    
    char line[100];
    staff_count = 0;
    
    while (fgets(line, sizeof(line), file) && staff_count < MAX_STAFF) {
        // 解析每行数据，格式：ID,姓名,密码
        char* token = strtok(line, ",");
        if (token) {
            strncpy(staffs[staff_count].staff_id, token, MAX_STAFF_ID_LENGTH);
            
            token = strtok(NULL, ",");
            if (token) {
                strncpy(staffs[staff_count].name, token, MAX_STAFF_NAME_LENGTH);
                
                token = strtok(NULL, ",\n");
                if (token) {
                    strncpy(staffs[staff_count].password, token, MAX_STAFF_PASSWORD_LENGTH);
                    staffs[staff_count].is_logged_in = 0;
                    staff_count++;
                }
            }
        }
    }
    
    fclose(file);
    return 1;
}

// 验证员工身份
int verify_staff(const char* staff_id, const char* password) {
    for (int i = 0; i < staff_count; i++) {
        if (strcmp(staffs[i].staff_id, staff_id) == 0 && 
            strcmp(staffs[i].password, password) == 0) {
            staffs[i].is_logged_in = 1;
            return 1;
        }
    }
    return 0;
}