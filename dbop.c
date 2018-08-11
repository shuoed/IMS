#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>// 解决找不到socket问题
#include <mysql.h>   //所需头文件
#include <windows.h> //执行cmd命令

#define SEGMENTATION puts("******************************************\n");
MYSQL *conn_prt;     //创造一个MYSQL句柄
MYSQL_RES *res;
MYSQL_ROW row;
/*一些操作的命令起始部分*/
char select_head[50] = "select * from ";
char desc_head[50] = "desc ";
char insert_head[200] = "insert into ";
char drop_msg_head[50] = "delete from ";
char change_base_head[50] = "use ";
/*连接mysql数据库*/
int mysqlConnect(char *address,char *username,char *password,char *dbname) {
    conn_prt = mysql_init(NULL);
    /*假设云服务器IP为192.168.0.1，密码为123456,进入的数据库名字为mydb
    if(!mysql_real_connect(conn_prt,"192.168.0.1","root",
                           "123456","mydb",0,NULL,0)) {
        printf("failed to connect:%s\n",mysql_error(conn_prt));
        exit(0) ;
    }
    printf("connect success!\n");
    如果本机测试的话，上面的语句可改为*/
    if(!mysql_real_connect(conn_prt,address,username,
                           password,dbname,0,NULL,0)) {
        printf("failed to connect:%s\n",mysql_error(conn_prt));
        return 0;
    }
    printf("连接本地数据库成功！\n");
    mysql_query(conn_prt, "set names gbk");
    return 1;
}

/*打印某个数据库中的某个表*/
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

/*打印某个表的字段有哪些*/
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

/*往某个表中插入数据*/
int insertMsg(char *tableName,char *fields,char *values) {
    int t;
    char insert_query[200];
    char left[5]="(";
    char right[5]=") ";
    char value[50]="values";

    strcpy(insert_query,insert_head);   //insert into
    /*把几个变量字符串连接成一个完整的mysql命令*/
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

/*删除某个表中的数据*/
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

/*改变身处的数据库*/
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
/*打印某个数据库中有哪些表*/
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
/*打印存在的所有数据库*/
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
/*执行用户输入的sql语句*/
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
/*执行用户输入的sql语句*/
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
        printf("回车，进入命令行模式！\n");
        getchar();
        gets(cmdCommand);
        system(cmdCommand);
    }
}

