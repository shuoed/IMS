
/*����mysql���ݿ�*/
int mysqlConnect(char *address,char *username,char *password,char *dbname) ;

/*��ӡĳ�����ݿ��е�ĳ����*/
int printTable(char *tableName);

/*��ӡĳ������ֶ�����Щ*/
int descTable(char *tableName) ;

/*��ĳ�����в�������*/
int insertMsg(char *tableName,char *fields,char *values) ;

/*ɾ��ĳ�����е�ĳ�����ݣ�������Ϊ��׼*/
int dropMsgTable(char *tableName,char *where) ;
/*�ı��������ݿ�*/
int changeBase(char *dbname) ;
/*��ӡĳ�����ݿ�������Щ��*/
int showAllTables() ;
/*��ӡ���ڵ��������ݿ�*/
int showTllBases();
/*ִ���û������sql���*/
int executeSqlCommand(char *sqlCommand);
int returnQueryRows(char *sqlCommand);
int executeSqlCommandNotReturn(char *sqlCommand);
void executeCmdCommand() ;
