#include <stdio.h>
#include "photograph.h"
#include "dbop.h"
#define WELCOME "欢迎使用信息存储系统"
#define WEBSITE "网址"
#define ADDRESSLIST "通讯录"
#define SETSYSTEM "系统设置"
#define EXITSYSTEM "退出"
#define INPUTORDER "请输入操作命令"
#define INPUTCONTENT "请输入要添加的内容:"
#define DBEXCEPTION "数据库异常！"

#define WIDTH 50 //图形的宽度

/*数据库连接用宏*/
#define HOST "localhost"//本地
#define USERNAME "root"//dbms user name
#define PASSWORD "123456"//password
#define DATABASE "mydb"//database name
int showHomePage() {
    int i;
    system("cls");
    p01();
    //显示菜单
    printf("\n\t%s\n    \
           \t1. %s\n    \
           \t2. %s\n    \
           \t3. %s\n    \
           \t4. %s\n",WELCOME,WEBSITE,ADDRESSLIST,SETSYSTEM,EXITSYSTEM);
    for(i=0; i<WIDTH; i++)
        putchar('*');
    putchar('\n');

    while(1) {
        //获取用户的输入，    mysqlConnect("localhost","root","123456","mydb");
//执行相应的功能
        switch(getFunNum(1,4)) {
        case 1:
            showFunPage(WEBSITE,1);
            break;
        case 2:
            showFunPage(ADDRESSLIST,2);
            break;
        case 3:
            setSystemFun();
            break;
        case 4:
            return 1;
            break;
        }
    }
}
int getFunNum(int start,int end) {
    char c[20]= {'\0'};
    int i;
    while(1) {
        printf("%s（%d to %d):",INPUTORDER,start,end);
        gets(c);
        getchar();
        for(i=start; i<=end&&strlen(c)<2; i++)
            if((c[0]==i+'0')&&c[1]=='\0')
                return c[0]-'0';
        printf("\n输入有误，请重新输入:");
    }
}

void showData(int code) {
    mysqlConnect("localhost","root","123456","mydb");
    if(code == 1) {
        printTable("website");
    } else if(code == 2) {
        printTable("addresslist");
    }
}
void addData(int code) {

    int n;
    printf("%s\n",INPUTCONTENT);
    char s1[50],s2[50],s3[50],s[150]= {'\0'};
    mysqlConnect("localhost","root","123456","mydb");
    if(code == 1) {
        printf("标签：");
        scanf("%s",s1);
        printf("网址：");
        scanf("%s",s2);
        printf("备注：");
        scanf("%s",s3);
    } else if(code ==2) {
        printf("姓名：");
        scanf("%s",s1);
        printf("手机号：");
        scanf("%s",s2);
        printf("备注：");
        scanf("%s",s3);
    }
    strcat(s,"'");
    strcat(s,s1);
    strcat(s,"','");
    strcat(s,s2);
    strcat(s,"','");
    strcat(s,s3);
    strcat(s,"'");
    printf("%s",s);
    if(code==1) {
        n = insertMsg("website","title,address,commentsoaf",s);
    } else if(code==2) {
        n = insertMsg("addresslist","name,pn1,commentsoaf",s);
    }
    // printf("写入了%d个字节\n",n);
    return 0;
}

int stringCompare(char *s,char *c) {//模糊匹配
    int sl=0,cl=0,i=0,j=0;
    while(s[sl++]!='\0');
    while(c[cl++]!='\0');
    if(sl>cl)return 0;
    for(i=0,j=0; i<cl; i++) {
        if(s[j]==c[i])j++;
        else if(j>=sl-1)return 1;
        else j=0;
    }
    if(j>=sl-1)return 1;
    return 0;
}
/*
void getDataId(int code,char *title,char *where)
{
    char sql[200]="select * from ";
    if(code == 1) {
      strcat(sql,"website");
    } else if(code ==2) {
     strcat(sql,"addresslist");
    }
    strcat(sql," where ");
    strcat(sql,title);
    strcat(sql," like ");
    strcat(sql,where);
    mysqlConnect("localhost","root","123456","mydb");
    executeSqlCommand(sql);

}
*/
void searchData(char *s,int code) {

    int order;
    char d[20];//用户输入
    char s1[50],s2[50],s3[50];
    char ss[150]= {'\0'};
    if(code == 1) {
        printf("1. 网站名称\t2. 网址\t3. 返回菜单\n");
    } else if(code ==2) {
        printf("1. 姓名\t2. 手机号\t3.返回菜单");
    }
    order = getFunNum(1,3);

    if(order==3)
        showFunPage(s,code);
    printf("请输入要匹配的数据：");
    scanf("%s",d);
    mysqlConnect("localhost","root","123456","mydb");
    if(code == 1) {
        if(order==1) {
            strcat(ss,"select * from website where title like '%");
            strcat(ss,d);
            strcat(ss,"%';");
            printf("%s\n",ss);
        } else if(order==2) {
            strcat(ss,"select * from website where address like '%");
            strcat(ss,d);
            strcat(ss,"%';");
            printf("%s\n",ss);
        }
    } else if(code==2) {
        if(order==1) {
            strcat(ss,"select * from addresslist where name like '%");
            strcat(ss,d);
            strcat(ss,"%';");
            printf("%s\n",ss);
        } else if(order==2) {
            strcat(ss,"select * from addresslist where pn1 like '%");
            strcat(ss,d);
            strcat(ss,"%';");
            printf("%s\n",ss);
        }
    }
    executeSqlCommand(ss);
    return ;
}
void upData(char *s,int code) {
    char sql[150]= {'\0'};
    char nd[50]= {'\0'};
    int t;
    char id[10];
    printf("请先根据条件找到要更新的数据！\t请记住该数据ID!!\n");
    searchData(s,code);
    printf("请输入要修改信息的ID：");
    scanf("%s",id);

    printf("请选择要更新的字段：\n");
    if(code==1) {
        printf("1.网站名称\t2.网址\t3.备注");
        scanf("%d",&t);
        printf("请输入新的数据：");
        scanf("%s",nd);
        switch(t) {
        case 1:
            strcat(sql,"update website set title ='");
            break;
        case 2:
            strcat(sql,"update website set address ='");
            break;
        case 3:
            strcat(sql,"update website set commentsoaf ='");
            break;
        }
        strcat(sql,nd);
        strcat(sql,"' where id='");
        strcat(sql,id);
        strcat(sql,"';");
        printf("%s\n",sql);
    } else if(code==2) {

    }
    executeSqlCommandNotReturn(sql);
    return ;
}
void deleteData(char *s,int code) {
    char sql[150]= {'\0'};
    char nd[50]= {'\0'};
    int t;
    char id[10];
    printf("请先根据条件找到要更新的数据！\t请记住该数据ID!!\n");
    searchData(s,code);
    printf("请输入要修改信息的ID：");
    scanf("%s",id);
    if(code == 1) {
        strcat(sql,"delete from website where id='");
    } else if(code==2) {
        strcat(sql,"delete from addresslist where id='");
    }
    strcat(sql,id);
    strcat(sql,"';");
    executeSqlCommandNotReturn(sql);
    return 0;
}
void showFunPage(char *s,int func) {
    int f = func;
    system("cls");
    printf("\n欢迎进入 %s管理系统\n\n",s);
    printf("1. 查看\t\n");
    printf("2. 添加\t\n");
    printf("3. 查找\t\n");
    printf("4. 修改\t\n");
    printf("5. 删除\t\n");
    printf("6. 返回主菜单\n");
    while(1) {
        switch(getFunNum(1,6)) {
        case 1:
            showData(f);
            break;
        case 2:  //  executeSqlCommand(sql);
            addData(f);
            break;
        case 3:
            searchData(s,f);
            break;
        case 4:
            upData(s,f);
            break;
        case 5:
            deleteData(s,f);
            break;
        case 6:
            showHomePage();
            break;
        }
    }
}
void setSystemFun() {
    printf("系统功能待完善！\n");
}
