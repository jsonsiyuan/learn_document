# SQLite - C/C++ #

	sqlite3_open(const char *filename, sqlite3 **ppDb)
	sqlite3_exec(sqlite3*, const char*sql,sqlite_callback, 	void *data, char **errmsg)
	sqlite3_close(sqlite3*)

demo:

## 连接数据库 ##

	#include <stdio.h>
	#include <sqlite3.h>
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int rc;
	
	   rc = sqlite3_open("test.db", &db);
	
	   if( rc ){
	  fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	  exit(0);
	   }else{
	  fprintf(stderr, "Opened database successfully\n");
	   }
	   sqlite3_close(db);
	}

## 创建表 ##

	#include <stdio.h>
	#include <stdlib.h>
	#include <sqlite3.h> 

	static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	   int i;
	   for(i=0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
	   printf("\n");
	   return 0;
	}
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int  rc;
	   char *sql;
	
	   /* Open database */
	   rc = sqlite3_open("test.db", &db);
	   if( rc ){
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      exit(0);
	   }else{
	      fprintf(stdout, "Opened database successfully\n");
	   }
	
	   /* Create SQL statement */
	   sql = "CREATE TABLE COMPANY("  \
	         "ID INT PRIMARY KEY     NOT NULL," \
	         "NAME           TEXT    NOT NULL," \
	         "AGE            INT     NOT NULL," \
	         "ADDRESS        CHAR(50)," \
	         "SALARY         REAL );";
	
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	   fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Table created successfully\n");
	   }
	   sqlite3_close(db);
	   return 0;
	}

## INSERT 操作 ##

	#include <stdio.h>
	#include <stdlib.h>
	#include <sqlite3.h>
	
	static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	   int i;
	   for(i=0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
	   printf("\n");
	   return 0;
	}
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int rc;
	   char *sql;
	
	   /* Open database */
	   rc = sqlite3_open("test.db", &db);
	   if( rc ){
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      exit(0);
	   }else{
	      fprintf(stderr, "Opened database successfully\n");
	   }
	
	   /* Create SQL statement */
	   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
	         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
	         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
	         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
	         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
	         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
	         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
	         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
	
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Records created successfully\n");
	   }
	   sqlite3_close(db);
	   return 0;
	}

## SELECT 操作 ##

	#include <stdio.h>
	#include <stdlib.h>
	#include <sqlite3.h>
	
	static int callback(void *data, int argc, char **argv, char **azColName){
	   int i;
	   fprintf(stderr, "%s: ", (const char*)data);
	   for(i=0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
	   printf("\n");
	   return 0;
	}
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int rc;
	   char *sql;
	   const char* data = "Callback function called";
	
	   /* Open database */
	   rc = sqlite3_open("test.db", &db);
	   if( rc ){
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      exit(0);
	   }else{
	      fprintf(stderr, "Opened database successfully\n");
	   }
	
	   /* Create SQL statement */
	   sql = "SELECT * from COMPANY";
	
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Operation done successfully\n");
	   }
	   sqlite3_close(db);
	   return 0;
	}

## UPDATE 操作 ##

	#include <stdio.h>
	#include <stdlib.h>
	#include <sqlite3.h> 
	
	static int callback(void *data, int argc, char **argv, char **azColName){
	   int i;
	   fprintf(stderr, "%s: ", (const char*)data);
	   for(i=0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
	   printf("\n");
	   return 0;
	}
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int rc;
	   char *sql;
	   const char* data = "Callback function called";
	
	   /* Open database */
	   rc = sqlite3_open("test.db", &db);
	   if( rc ){
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      exit(0);
	   }else{
	      fprintf(stderr, "Opened database successfully\n");
	   }
	
	   /* Create merged SQL statement */
	   sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
	         "SELECT * from COMPANY";
	
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Operation done successfully\n");
	   }
	   sqlite3_close(db);
	   return 0;
	}

## 使用没有回调的select ##

**API介绍：**

	int sqlite3_get_table(
	sqlite3 *db,          /* An open database */
	const char *zSql,     /* SQL to be evaluated */
	char ***pazResult,    /* Results of the query */
	int *pnRow,           /* Number of result rows written here */
	int *pnColumn,        /* Number of result columns written here */
	char **pzErrmsg       /* Error msg written here */
	);
	void sqlite3_free_table(char **result);

	第1个参数不再多说，看前面的例子。
	第2个参数是sql 语句，跟sqlite3_exec 里的sql 是一样的。是一个很普通的以\0结尾的char*字符串。
	第3个参数是查询结果，它依然一维数组（不要以为是二维数组，更不要以为是三维数组）。它内存布局是：字段名称，后面是紧接着是每个字段的值。下面用例子来说事。
	第4个参数是查询出多少条记录（即查出多少行，不包括字段名那行）。
	第5个参数是多少个字段（多少列）。
	第6个参数是错误信息，跟前面一样，这里不多说了


	#include <sqlite3.h>
	#include <stdio.h>
	#include <stdlib.h>
	/*
	使用sqlite3_get_table获取数据
	 
	*/
	 
	int main(void)
	{
	    sqlite3 *conn;/*句柄*/
	    if(sqlite3_open("ku1.db",&conn)!=SQLITE_OK)
	    {
	        printf("打开失败%s\n",sqlite3_errmsg(conn));
	    }    
	 
	 
	    char **dbresult;
	   
	      
	    int rows,cols;
	    sqlite3_get_table(conn,"select * from t1",&dbresult,&rows,&cols,NULL);
	    //这里会把列头一起打印出来,全部保存在dbresult数组里
	    for(int i=0;i<rows+1;i++)//行
	    {
	        for(int j=0;j<cols;j++)//列
	        {
	            printf("%s\t",dbresult[i*cols+j]);
	        }
	        printf("\n");
	    }
	    sqlite3_free_table(dbresult);
	    sqlite3_close(conn);
	}


## DELETE 操作 ##

	#include <stdio.h>
	#include <stdlib.h>
	#include <sqlite3.h> 
	
	static int callback(void *data, int argc, char **argv, char **azColName){
	   int i;
	   fprintf(stderr, "%s: ", (const char*)data);
	   for(i=0; i<argc; i++){
	      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	   }
	   printf("\n");
	   return 0;
	}
	
	int main(int argc, char* argv[])
	{
	   sqlite3 *db;
	   char *zErrMsg = 0;
	   int rc;
	   char *sql;
	   const char* data = "Callback function called";
	
	   /* Open database */
	   rc = sqlite3_open("test.db", &db);
	   if( rc ){
	      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	      exit(0);
	   }else{
	      fprintf(stderr, "Opened database successfully\n");
	   }
	
	   /* Create merged SQL statement */
	   sql = "DELETE from COMPANY where ID=2; " \
	         "SELECT * from COMPANY";
	
	   /* Execute SQL statement */
	   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	   if( rc != SQLITE_OK ){
	      fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      sqlite3_free(zErrMsg);
	   }else{
	      fprintf(stdout, "Operation done successfully\n");
	   }
	   sqlite3_close(db);
	   return 0;
	}



# 注意事项 #

编译缺少头文件：

>     sudo apt-get install libsqlite3-dev