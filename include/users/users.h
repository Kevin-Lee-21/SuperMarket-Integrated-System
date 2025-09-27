#ifndef USERS_H
#define USERS_H

#define MAX_USERS 100

// 员工管理系统的数据结构体 
typedef struct {
    char username[20];  // 用户名
    char password[20];  // 密码
    int role;           // 权限：管理员=0 普通员工=1 
} User;

// 全局变量声明
extern User users[MAX_USERS];
extern int usercount;

// 函数声明
void loadusers();
void saveusers();
int login(char *name, char *pwd);
void registeruser();
void changepassword(char *name);

#endif

