
#include "user.h"
#include "dbop.h"
int login() {
    char userId[10];
    char userPwd[30];
 //   printf("��ӭʹ����Ϣ����ϵͳ\n");
    printf("�˺ţ�");
    scanf("%s",userId);
    printf("\n���룺");
    scanf("%s",userPwd);
    if(verify(userId,userPwd)) {
        return 1;
    }
    return 0;
}
int verify(char *username,char *password) {
    char sql[150]="select * from user where username= '";
    strcat(sql,username);
    strcat(sql,"' and userpassword= '");
    strcat(sql,password);
    strcat(sql,"';");
    mysqlConnect("127.0.0.1","root","123456","mydb");
    if(returnQueryRows(sql)) {
        return 1;
    }
    return 0;
}
int registerUser()
{
    char userId[10];
    char userPwd[50];
    char userCPwd[50];
    char userName[50];
    char userMail[50];
    char userCMail[50];
    printf("\n�������û��ǳƣ�");
    scanf("%s",userName);
    printf("\n�������û����룺");
    scanf("%s",userPwd);
    printf("\n���ٴ������û����룺");
    scanf("%s",userCPwd);
    printf("\n����������(��Ҫ):")
    scanf("%s",userMail);
    printf("\n��ȷ��������䣺");
    scanf("%s",userCMail);
}

int changePwd(){

}

