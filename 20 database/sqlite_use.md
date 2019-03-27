# sqlite3 #
## 1 base  ##
`RDBMS`--->关系型数据库管理系统

linux add sqlite3

	sudo apt-get insatll sqlite3
	sudo apt-get install sqliteman

----------
### 1.1 数据查询 ###
	SELECT
### 1.2 表的操作 ###
**DDL(Data Definition Language 数据定义语言)用于操作对象和对象的属性**

	CREATE
	DROP
	ALTER

### 1.3 数据操作 ###
**DML(Data Manipulation Language 数据操控语言)用于操作数据库对象中包含的数据**

	INSERT
	UPDATE
	DELETE

### 1.4 权限操作 ###
**DCL(Data Control Language 数据控制语句)的操作是数据库对象的权限**

	GRANT
	REVORK
## 2 sqlite3 data class  ##
|类型|解释|
|::|::|
|NULL|一个 NULL 值|
|INTEGER|一个带符号的整数，根据值的大小存储在 1、2、3、4、6 或 8 字节中|
|REAL|一个浮点值，存储为 8 字节的 IEEE 浮点数字|
|TEXT|一个文本字符串，使用数据库编码（UTF-8、UTF-16BE 或 UTF-16LE）存储|
|BLOB|一个 blob 数据，完全根据它的输入存储|
## 3 key cmd  ##

	.help
	.databases
	.schema
	.header on
	.mode column
	.width 10, 20, 10

## 4 sqlite3 script  ##

**创建数据库**

	sqlite3 DatabaseName.db
demo：

	sqlite3 testDB.db

**创建表**

	CREATE TABLE database_name.table_name(
	column1 datatype  PRIMARY KEY(one or more columns),
	column2 datatype,
	column3 datatype,
	.....
	columnN datatype,
	);
demo：

	CREATE TABLE COMPANY(
		ID INT PRIMARY KEY     NOT NULL,
		NAME           TEXT    NOT NULL,
		AGE            INT     NOT NULL,
		ADDRESS        CHAR(50),
		SALARY         REAL
		);

**修改表**

	ALTER TABLE database_name.table_name ADD COLUMN column_def...;

demo：

	ALTER TABLE OLD_COMPANY ADD COLUMN SEX char(1);

**删除列**

1.创建一个新表

	create table stu1 as select id,name ,score from stu;

2.删除原来的表

	drop table stu;

3.改名字

	alter table stu1 rename to stu;

**删除表**

	DROP TABLE database_name.table_name;

demo：
	
	DROP TABLE COMPANY;


**插入数据**

	INSERT INTO TABLE_NAME [(column1,column2,column3,...columnN)]  
	VALUES (value1, value2, value3,...valueN);

	INSERT INTO TABLE_NAME VALUES (value1,value2,value3,...valueN);

demo：

	INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)
	VALUES (1, 'Paul', 32, 'California', 20000.00 );

	INSERT INTO COMPANY VALUES (7, 'James', 24, 'Houston', 10000.00 );


**获取数据**

	SELECT column1, column2, columnN FROM table_name;
	SELECT * FROM table_name;

demo：

	SELECT * FROM COMPANY;
	SELECT ID, NAME, SALARY FROM COMPANY;

*WHERE use*

	SELECT column1, column2, columnN 
	FROM table_name
	WHERE [condition]

**更新数据**

	UPDATE table_name
	SET column1 = value1, column2 = value2...., columnN = valueN
	WHERE [condition];

demo：

	UPDATE COMPANY SET ADDRESS = 'Texas' WHERE ID = 6;

**删除数据**

	DELETE FROM table_name
	WHERE [condition];

demo：
	
	DELETE FROM COMPANY WHERE ID = 7;


**高级应用**

1. index
2. join
3. view
4. Autoincrement