#include<stdio.h>
#include<math.h>
#include<string.h>

#define MAX_USERS 100

//员工管理系统的数据结构体 
typedef struct{
	char username[20];//用户名 
	char password[20];//密码 
	int role;//权限：管理员=0 普通员工=1 
}User;

User users[MAX_USERS];
int usercount = 0;
//读取用户信息（启动时用） 
void loadusers(){
	FILE *fp=fopen("users.txt","r");
	if(fp==NULL){
		printf("用户文件不存在，将创建新文件.\n");
		return;
	}
	while(fscanf(fp,"%s %s %d",
				 users[usercount].username,
				 users[usercount].password,
				 &users[usercount].role)!=EOF){
				 	usercount++;
	}
	fclose(fp);			 
}

//保存用户信息（退出/注册/修改密码时用）
void saveusers(){
	FILE *fp = fopen("users.txt","w");
	for(int i=0;i<usercount;i++)
	{
		fprintf(fp,"%s %s %d\n",
				users[i].username,
				users[i].password,
				users[i].role);
	}
	fclose(fp);
} 

//登录
int login(char *name,char *pwd){
	for(int i=0;i<usercount;i++){
		if(strcmp(users[i].username,name)==0&&
		   strcmp(users[i].password,pwd)==0){
		   return users[i].role;   	
		}
	}
	return -1;
} 

//注册
void registeruser()
{
	if(usercount>=MAX_USERS)
	{
		printf("用户数量已满！\n");
		return;
	}
	char name[20],pwd[20];
	int role;
	
	printf("请输入新用户名：");
	scanf("%s",name);
	
	//检察重名
	for(int i=0;i<usercount;i++){
		if(strcmp(users[i].username,name)==0){
			printf("用户名已存在！\n");
			return;
		}
	}

	printf("请输入密码：");
	scanf("%s",pwd);
	printf("请输入角色（0=管理员 1=普通员工）：");
	scanf("%d",&role); 
	
	strcpy(users[usercount].username,name);
	strcpy(users[usercount].password,pwd);
	users[usercount].role=role;
	usercount++;
	
	saveusers();//将新成员信息录入文件 
	printf("注册成功！\n");
} 

//修改密码
void changepassword(char *name)
{
	char oldpwd[20],newpwd[20];
	printf("请输入旧密码：");
	scanf("%s",oldpwd);
	
	for(int i=0;i<usercount;i++)
	{
		if(strcmp(users[i].username,name)==0&&
		   strcmp(users[i].password,oldpwd)==0)
		{
			printf("请输入新密码");
			scanf("%s",newpwd);
			strcpy(users[i].password,newpwd);
			saveusers();
			printf("密码修改成功！\n");
			return; 
		}   
	}
	printf("密码修改失败");
} 

int main()
{
	loadusers();
	
	int choice;
	while(1){
		printf("\n=== 超市管理系统 登录界面 ===\n");
		printf("1.登录\n");
		printf("2.注册\n");
		printf("3.退出\n");
		printf("请选择：\n");
		scanf("%d",&choice);
		
		if(choice==1){
			char name[20],pwd[20];
			printf("用户名: ");
            scanf("%s", name);
            printf("密码: ");
            scanf("%s", pwd);
            int role=login(name,pwd);
            if (role == 0) {
            printf("欢迎管理员 %s 登录！\n", name);
                // adminMenu();  // 管理员菜单
                changepassword(name); // 示例
            } else if (role == 1) {
                printf("欢迎员工 %s 登录！\n", name);
                // staffMenu();  // 员工菜单
            } else {
                printf("登录失败！\n");
            } 
		}	 	 else if (choice == 2) {
            registeruser();
        } 
        else if (choice == 3) {
            saveusers();
            break;
        } 
        else {
            printf("输入无效！\n");
		}
	}
	return 0;
}
