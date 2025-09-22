#include<stdio.h>
#include<math.h>
#include<string.h>

#define MAX_USERS 100

//Ա������ϵͳ�����ݽṹ�� 
typedef struct{
	char username[20];//�û��� 
	char password[20];//���� 
	int role;//Ȩ�ޣ�����Ա=0 ��ͨԱ��=1 
}User;

User users[MAX_USERS];
int usercount = 0;
//��ȡ�û���Ϣ������ʱ�ã� 
void loadusers(){
	FILE *fp=fopen("users.txt","r");
	if(fp==NULL){
		printf("�û��ļ������ڣ����������ļ�.\n");
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

//�����û���Ϣ���˳�/ע��/�޸�����ʱ�ã�
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

//��¼
int login(char *name,char *pwd){
	for(int i=0;i<usercount;i++){
		if(strcmp(users[i].username,name)==0&&
		   strcmp(users[i].password,pwd)==0){
		   return users[i].role;   	
		}
	}
	return -1;
} 

//ע��
void registeruser()
{
	if(usercount>=MAX_USERS)
	{
		printf("�û�����������\n");
		return;
	}
	char name[20],pwd[20];
	int role;
	
	printf("���������û�����");
	scanf("%s",name);
	
	//�������
	for(int i=0;i<usercount;i++){
		if(strcmp(users[i].username,name)==0){
			printf("�û����Ѵ��ڣ�\n");
			return;
		}
	}

	printf("���������룺");
	scanf("%s",pwd);
	printf("�������ɫ��0=����Ա 1=��ͨԱ������");
	scanf("%d",&role); 
	
	strcpy(users[usercount].username,name);
	strcpy(users[usercount].password,pwd);
	users[usercount].role=role;
	usercount++;
	
	saveusers();//���³�Ա��Ϣ¼���ļ� 
	printf("ע��ɹ���\n");
} 

//�޸�����
void changepassword(char *name)
{
	char oldpwd[20],newpwd[20];
	printf("����������룺");
	scanf("%s",oldpwd);
	
	for(int i=0;i<usercount;i++)
	{
		if(strcmp(users[i].username,name)==0&&
		   strcmp(users[i].password,oldpwd)==0)
		{
			printf("������������");
			scanf("%s",newpwd);
			strcpy(users[i].password,newpwd);
			saveusers();
			printf("�����޸ĳɹ���\n");
			return; 
		}   
	}
	printf("�����޸�ʧ��");
} 

int main()
{
	loadusers();
	
	int choice;
	while(1){
		printf("\n=== ���й���ϵͳ ��¼���� ===\n");
		printf("1.��¼\n");
		printf("2.ע��\n");
		printf("3.�˳�\n");
		printf("��ѡ��\n");
		scanf("%d",&choice);
		
		if(choice==1){
			char name[20],pwd[20];
			printf("�û���: ");
            scanf("%s", name);
            printf("����: ");
            scanf("%s", pwd);
            int role=login(name,pwd);
            if (role == 0) {
            printf("��ӭ����Ա %s ��¼��\n", name);
                // adminMenu();  // ����Ա�˵�
                changepassword(name); // ʾ��
            } else if (role == 1) {
                printf("��ӭԱ�� %s ��¼��\n", name);
                // staffMenu();  // Ա���˵�
            } else {
                printf("��¼ʧ�ܣ�\n");
            } 
		}	 	 else if (choice == 2) {
            registeruser();
        } 
        else if (choice == 3) {
            saveusers();
            break;
        } 
        else {
            printf("������Ч��\n");
		}
	}
	return 0;
}
