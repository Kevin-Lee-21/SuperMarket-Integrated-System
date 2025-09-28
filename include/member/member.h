#ifndef MEMBER_H
#define MEMBER_H

#define MAX_MEMBERS 1000
#define MAX_MEMBER_ID_LENGTH 20
#define MAX_MEMBER_NAME_LENGTH 30
#define MAX_MEMBER_PASSWORD_LENGTH 30

typedef struct {
    char member_id[MAX_MEMBER_ID_LENGTH];    // 会员ID
    char name[MAX_MEMBER_NAME_LENGTH];       // 会员姓名
    char password[MAX_MEMBER_PASSWORD_LENGTH]; // 会员密码
    double points;                          // 积分
    int is_valid;                           // 会员状态
} Member;

// 会员验证函数
int verify_member(const char* member_id, const char* password);
int load_members_from_file(const char* filename); // 从文件加载会员信息

// 会员积分和折扣函数
double calculate_member_discount(const char* member_id);
int add_member_points(const char* member_id, double points);

#endif