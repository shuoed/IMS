#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>// ����Ҳ���socket����
#include <mysql.h>   //����ͷ�ļ�
#include <windows.h> //ִ��cmd����

#define SEGMENTATION puts("******************************************\n");
MYSQL *conn_prt;     //����һ��MYSQL���
MYSQL_RES *res;
MYSQL_ROW row;
/*һЩ������������ʼ����*/
char select_head[50] = "select * from ";
char desc_head[50] = "desc ";
char insert_head[200] = "insert into ";
char drop_msg_head[50] = "delete from ";
char change_base_head[50] = "use ";
/*����mysql���ݿ�*/
int mysqlConnect(char *address,char *username,char *password,char *dbname) {
    conn_prt = mysql_init(NULL);
    /*�����Ʒ�����IPΪ192.168.0.1������Ϊ123456,��������ݿ�����Ϊmydb
    if(!mysql_real_connect(conn_prt,"192.168.0.1","root",
                           "123456","mydb",0,NULL,0)) {
        printf("failed to connect:%s\n",mysql_error(conn_prt));
        exit(0) ;
    }
    printf("connect success!\n");
    ����������ԵĻ�����������ɸ�Ϊ*/
    if(!mysql_real_connect(conn_prt,address,username,
                           password,dbname,0,NULL,0)) {
        printf("failed to connect:%s\n",mysql_error(conn_prt));
        return 0;
    }
    printf("���ӱ������ݿ�ɹ���\n");
    mysql_query(conn_prt, "set names gbk");
    return 1;
}

/*��ӡĳ�����ݿ��е�ĳ����*/
int printTable(char *tableName) {
    int t;
    char query[50];
    memset(query,0,50);
    strcpy(query,select_head);
    strcat(query,tableName);
    t = mysql_real_query(conn_prt,query,strlen(query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    //printf("query success!\n");
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
        for(t = 0; t<mysql_num_fields(res); t++) {
            printf("%s\t",row[t]);
        }
        printf("\n");
    }
    getchar();
    return 1;
}

/*��ӡĳ������ֶ�����Щ*/
int descTable(char *tableName) {
    int t;
    char desc_query[50];
    memset(desc_query,0,50);
    strcpy(desc_query,desc_head);
    strcat(desc_query,tableName);
    t = mysql_real_query(conn_prt,desc_query,strlen(desc_query));
    if(t) {
        printf("failed to query(In descTable() function):%s\n",mysql_error(conn_prt));
        return 0;
    }
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
        for(t = 0; t<mysql_num_fields(res); t++) {
            printf("%s\t",row[t]);
        }
        printf("\n");
    }
    getchar();
    return 1;
}

/*��ĳ�����в�������*/
int insertMsg(char *tableName,char *fields,char *values) {
    int t;
    char insert_query[200];
    char left[5]="(";
    char right[5]=") ";
    char value[50]="values";

    strcpy(insert_query,insert_head);   //insert into
    /*�Ѽ��������ַ������ӳ�һ��������mysql����*/
    strcat(insert_query,tableName);
    strcat(insert_query,left);
    strcat(insert_query,fields);
    strcat(insert_query,right);
    strcat(insert_query,value);
    strcat(insert_query,left);
    strcat(insert_query,values);
    strcat(insert_query,right);
    printf("%s\n",insert_query);
    t = mysql_real_query(conn_prt,insert_query,strlen(insert_query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    return t;
}

/*ɾ��ĳ�����е�����*/
int dropMsgTable(char *tableName,char *where) {
    int t;
    char drop_query[200]= {0};
    strcpy(drop_query,drop_msg_head);
    strcat(drop_query,tableName);
    strcat(drop_query," where ");
    strcat(drop_query,where);
    strcat(drop_query,"\"");
    printf("%s\n",drop_query);
    t = mysql_real_query(conn_prt,drop_query,strlen(drop_query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    //printf("OK\n");
    return 1;
}

/*�ı��������ݿ�*/
int changeBase(char *dbname) {
    int t;
    char change_based_query[100]= {0};
    strcpy(change_based_query,change_base_head);
    strcat(change_based_query,dbname);
    t = mysql_real_query(conn_prt,change_based_query,strlen(change_based_query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    printf("change db OK!\n");
    return 1;
}
/*��ӡĳ�����ݿ�������Щ��*/
int showAllTables() {
    int t;
    char query[50] ="show tables";
    t = mysql_real_query(conn_prt,query,strlen(query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
        for(t = 0; t<mysql_num_fields(res); t++) {
            printf("%s\t",row[t]);
        }
        printf("\n");
    }
    return 1;
}
/*��ӡ���ڵ��������ݿ�*/
int showTllBases() {
    int t;
    char query[50] ="show databases";
    t = mysql_real_query(conn_prt,query,strlen(query));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
        for(t = 0; t<mysql_num_fields(res); t++) {
            printf("%s\t",row[t]);
        }
        printf("\n");
    }
    return 1;
}
/*ִ���û������sql���*/
int executeSqlCommand(char *sqlCommand) {
    int t;
  //  mysqlConnect("localhost","root","123456","mydb");
    t = mysql_real_query(conn_prt,sqlCommand,strlen(sqlCommand));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
        for(t = 0; t<mysql_num_fields(res); t++) {
            printf("%s\t",row[t]);
        }
        printf("\n");
    }
    getchar();
    return ;
}
/*ִ���û������sql���*/
int executeSqlCommandNotReturn(char *sqlCommand) {
    int t;
    t = mysql_real_query(conn_prt,sqlCommand,strlen(sqlCommand));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    return t;
}
int returnQueryRows(char *sqlCommand){
    int t,n=0;
    t = mysql_real_query(conn_prt,sqlCommand,strlen(sqlCommand));
    if(t) {
        printf("failed to query:%s\n",mysql_error(conn_prt));
        return 0;
    }
    res = mysql_store_result(conn_prt);
    while(row = mysql_fetch_row(res)) {
       n++;
    }
    return n;
}
void executeCmdCommand() {
    char cmdCommand[200];
    while(1) {
        printf("�س�������������ģʽ��\n");
        getchar();
        gets(cmdCommand);
        system(cmdCommand);
    }
}

