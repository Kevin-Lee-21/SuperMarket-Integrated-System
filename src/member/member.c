#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"

// 全局会员数组
Member members[MAX_MEMBERS];
int member_count = 0;

// 从文件加载会员信息
int load_members_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("错误：无法打开会员文件 %s\n", filename);
        return 0;
    }
    
    char line[200];
    member_count = 0;
    
    while (fgets(line, sizeof(line), file) && member_count < MAX_MEMBERS) {
        // 解析每行数据，格式：会员ID,姓名,密码,积分,状态
        char* token = strtok(line, ",");
        if (token) {
            strncpy(members[member_count].member_id, token, MAX_MEMBER_ID_LENGTH);
            
            token = strtok(NULL, ",");
            if (token) {
                strncpy(members[member_count].name, token, MAX_MEMBER_NAME_LENGTH);
                
                token = strtok(NULL, ",");
                if (token) {
                    strncpy(members[member_count].password, token, MAX_MEMBER_PASSWORD_LENGTH);
                    
                    token = strtok(NULL, ",");
                    if (token) {
                        members[member_count].points = atof(token);
                        
                        token = strtok(NULL, ",\n");
                        if (token) {
                            members[member_count].is_valid = atoi(token);
                            member_count++;
                        }
                    }
                }
            }
        }
    }
    
    fclose(file);
    printf("已从 %s 加载 %d 名会员信息\n", filename, member_count);
    return 1;
}

// 验证会员身份
int verify_member(const char* member_id, const char* password) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].member_id, member_id) == 0 && 
            strcmp(members[i].password, password) == 0 && 
            members[i].is_valid) {
            return 1;
        }
    }
    return 0;
}

// 计算会员折扣
double calculate_member_discount(const char* member_id) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].member_id, member_id) == 0) {
            // 根据积分计算折扣
            if (members[i].points >= 1000) return 0.15; // 15%折扣
            if (members[i].points >= 500) return 0.10;  // 10%折扣
            if (members[i].points >= 100) return 0.05;  // 5%折扣
            return 0.02; // 默认2%折扣
        }
    }
    return 0.0; // 非会员无折扣
}

// 添加会员积分
int add_member_points(const char* member_id, double points) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(members[i].member_id, member_id) == 0) {
            members[i].points += points;
            printf("会员 %s 获得 %.1f 积分，当前积分: %.1f\n", 
                   members[i].name, points, members[i].points);
            return 1;
        }
    }
    printf("错误：未找到会员ID: %s\n", member_id);
    return 0;
}