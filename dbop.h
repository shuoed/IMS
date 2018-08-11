
/*连接mysql数据库*/
int mysqlConnect(char *address,char *username,char *password,char *dbname) ;

/*打印某个数据库中的某个表*/
int printTable(char *tableName);

/*打印某个表的字段有哪些*/
int descTable(char *tableName) ;

/*往某个表中插入数据*/
int insertMsg(char *tableName,char *fields,char *values) ;

/*删除某个表中的某个数据，以名字为基准*/
int dropMsgTable(char *tableName,char *where) ;
/*改变身处的数据库*/
int changeBase(char *dbname) ;
/*打印某个数据库中有哪些表*/
int showAllTables() ;
/*打印存在的所有数据库*/
int showTllBases();
/*执行用户输入的sql语句*/
int executeSqlCommand(char *sqlCommand);
int returnQueryRows(char *sqlCommand);
int executeSqlCommandNotReturn(char *sqlCommand);
void executeCmdCommand() ;
