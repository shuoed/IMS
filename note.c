#include <stdio.h>
#include "photograph.h"
#include "dbop.h"
#define WELCOME "��ӭʹ����Ϣ�洢ϵͳ"
#define WEBSITE "��ַ"
#define ADDRESSLIST "ͨѶ¼"
#define SETSYSTEM "ϵͳ����"
#define EXITSYSTEM "�˳�"
#define INPUTORDER "�������������"
#define INPUTCONTENT "������Ҫ��ӵ�����:"
#define DBEXCEPTION "���ݿ��쳣��"

#define WIDTH 50 //ͼ�εĿ��

/*���ݿ������ú�*/
#define HOST "localhost"//����
#define USERNAME "root"//dbms user name
#define PASSWORD "123456"//password
#define DATABASE "mydb"//database name
int showHomePage() {
    int i;
    system("cls");
    p01();
    //��ʾ�˵�
    printf("\n\t%s\n    \
           \t1. %s\n    \
           \t2. %s\n    \
           \t3. %s\n    \
           \t4. %s\n",WELCOME,WEBSITE,ADDRESSLIST,SETSYSTEM,EXITSYSTEM);
    for(i=0; i<WIDTH; i++)
        putchar('*');
    putchar('\n');

    while(1) {
        //��ȡ�û������룬    mysqlConnect("localhost","root","123456","mydb");
//ִ����Ӧ�Ĺ���
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
        printf("%s��%d to %d):",INPUTORDER,start,end);
        gets(c);
        getchar();
        for(i=start; i<=end&&strlen(c)<2; i++)
            if((c[0]==i+'0')&&c[1]=='\0')
                return c[0]-'0';
        printf("\n������������������:");
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
        printf("��ǩ��");
        scanf("%s",s1);
        printf("��ַ��");
        scanf("%s",s2);
        printf("��ע��");
        scanf("%s",s3);
    } else if(code ==2) {
        printf("������");
        scanf("%s",s1);
        printf("�ֻ��ţ�");
        scanf("%s",s2);
        printf("��ע��");
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
    // printf("д����%d���ֽ�\n",n);
    return 0;
}

int stringCompare(char *s,char *c) {//ģ��ƥ��
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
    char d[20];//�û�����
    char s1[50],s2[50],s3[50];
    char ss[150]= {'\0'};
    if(code == 1) {
        printf("1. ��վ����\t2. ��ַ\t3. ���ز˵�\n");
    } else if(code ==2) {
        printf("1. ����\t2. �ֻ���\t3.���ز˵�");
    }
    order = getFunNum(1,3);

    if(order==3)
        showFunPage(s,code);
    printf("������Ҫƥ������ݣ�");
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
    printf("���ȸ��������ҵ�Ҫ���µ����ݣ�\t���ס������ID!!\n");
    searchData(s,code);
    printf("������Ҫ�޸���Ϣ��ID��");
    scanf("%s",id);

    printf("��ѡ��Ҫ���µ��ֶΣ�\n");
    if(code==1) {
        printf("1.��վ����\t2.��ַ\t3.��ע");
        scanf("%d",&t);
        printf("�������µ����ݣ�");
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
    printf("���ȸ��������ҵ�Ҫ���µ����ݣ�\t���ס������ID!!\n");
    searchData(s,code);
    printf("������Ҫ�޸���Ϣ��ID��");
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
    printf("\n��ӭ���� %s����ϵͳ\n\n",s);
    printf("1. �鿴\t\n");
    printf("2. ���\t\n");
    printf("3. ����\t\n");
    printf("4. �޸�\t\n");
    printf("5. ɾ��\t\n");
    printf("6. �������˵�\n");
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
    printf("ϵͳ���ܴ����ƣ�\n");
}
