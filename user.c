
#include "user.h"
#include "dbop.h"
int login() {
    char userId[10];
    char userPwd[30];
 //   printf("欢迎使用信息管理系统\n");
    printf("账号：");
    scanf("%s",userId);
    printf("\n密码：");
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
    printf("\n请输入用户昵称：");
    scanf("%s",userName);
    printf("\n请输入用户密码：");
    scanf("%s",userPwd);
    printf("\n请再次输入用户密码：");
    scanf("%s",userCPwd);
    printf("\n请输入邮箱(重要):")
    scanf("%s",userMail);
    printf("\n请确认你的邮箱：");
    scanf("%s",userCMail);
}

int changePwd(){

}

