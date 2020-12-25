
#include <stdio.h> 
#include<iostream>
#include <stdlib.h> 
#include<Windows.h>
#include<mysql.h>
#pragma comment(lib, "libmysql.lib")
using namespace std;


	MYSQL mysql, * sock; //声明mysql的句柄 
	const char* host = "localhost"; //本机连接
	const char* user = "root"; //mysql用户名 
	const char* passwd = "2020";//char passwd[100] = {}; //用户密码 
	const char* db = "teacher"; //老师信息数据库
	unsigned int port = 3306; //mysql服务器端口设置在3306
	const char* unix_socket = NULL; //unix_socket这是unix下的，我在Windows下，所以就把它设置为NULL 
	unsigned long client_flag = 0; //这个参数一般为0 
	const char* i_query = "select * from teacherinformation "; //查询语句，从那个表中查询,这里后面没有;
	MYSQL_RES* result; //保存结果集
	MYSQL_ROW row; //代表的是结果集中的一行 
	unsigned int	num_fields;//结果集某行的列数
void init() //初始化系统
{
	mysql_init(&mysql); //连接之前必须使用这个函数来初始化 
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	/* cout << "         连接教师工作量系统，请输入密码" << endl;
	cin.get(passwd, 100); */
	if ((sock = mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag)) == NULL) //连接MySQL 
	{
		cout << "未能成功与mysql建立连接" << endl;//输出连接错误
		cout << mysql_error(&mysql) << endl;//输出错误信息
		exit(1);//程序正常退出
	}
	else
	{
		cout << "与Mysql服务器建立连接"<<endl;//输出即为连接成功
	}

	
}
void exit()//退出系统
{
	mysql_free_result(result); //释放结果集 
	mysql_close(sock); //关闭连接 
	system("pause");
	exit(EXIT_SUCCESS);

}

char query_sql[500] = {};
int number ;
char name[20] = {};
char sex[20] = {};
char title[20] = {};
char teaching_courses[20] = {};
char class_number[20] = {};
int class_sum = {};
float tclass_hour;
float eclass_hour;
void browse_teacher()
{
	sprintf_s(query_sql,"select * from teacherinformation");
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
	}
	else
	{

		result = mysql_store_result(&mysql);
		if (result == NULL) //保存查询的结果 
		{
			if (mysql_field_count(&mysql) == 0)
			{
				cout << "没有返回结果" << endl;
			}

		}
		else
		{
			while ((row = mysql_fetch_row(result)) != NULL) //读取结果集中的数据
			{
				num_fields = mysql_num_fields(result);
				for (unsigned i = 0; i < num_fields; i++)
				{
					printf(" %s\t", row[i]);
				}//打印当前行的数据 
				printf("\n");
			}
		}

	}
	mysql_free_result(result); //释放结果集 
}

void insert_teacher()
{
	
	cout << "请分别输入教师号，姓名，性别，职称，任教课程，班级，班级数目，理论课时，实验课时" << endl;
	cin >> number >> name>>sex>>title>>teaching_courses>>class_number>>class_sum>>tclass_hour>>eclass_hour;
	sprintf_s(query_sql,
		"insert into teacherinformation(教师号,姓名,性别,职称,任教课程,班级,班级数目,理论课时,实验课时) values(%d,'%s','%s','%s','%s','%s',%d,%f,%f)"
		, number,name,sex,title,teaching_courses,class_number,class_sum,tclass_hour,eclass_hour);
	cout << query_sql << endl;
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
		cout << "插入信息失败" << endl;
	}
	else
	{

		cout << "插入信息成功";

	}

	
}
void update_teacher()
{
	cout << "请输入要修改的教师号" << endl;
	cin >> number;
	cout << "请分别输入要修改的姓名，性别，职称，任教课程，班级，班级数目，理论课时，实验课时" << endl;
	cin >> name >> sex >> title >> teaching_courses >> class_number >> class_sum >> tclass_hour >> eclass_hour;
	sprintf_s(query_sql,
		"update teacherinformation set 姓名='%s',性别='%s',职称='%s',任教课程='%s',班级='%s',班级数目=%d,理论课时=%f,实验课时=%f where 教师号=%d"
		,name,sex,title,teaching_courses,class_number,class_sum,tclass_hour,eclass_hour,number);
	cout << query_sql << endl;
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
		cout << "修改信息失败" << endl;
	}
	else
	{

		cout << "修改信息成功";

	}

	
}
void delete_teacher()
{
	cout << "请输入要删除的教师号" << endl;
	cin >> number;
	sprintf_s(query_sql,
		"DELETE FROM teacherinformation WHERE 教师号 = %d", number);
	cout << query_sql << endl;
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
		cout << "删除失败" << endl;
	}
	else
	{

		cout << "删除成功";

	}

}
void Totalhouts_singelTask()
{
	sprintf_s(query_sql, "delete  from teacher;");
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
	}
	else
	{
		;
	}
	sprintf_s(query_sql, "insert into teacher(教师号,单,总) select 教师号,1.5*(实验课时+理论课时),班级数目*1.5*(实验课时+理论课时) from teacherinformation where  班级数目=2;");
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << mysql_error(&mysql) << endl;//sql语句出现错误
	}
	else
	{
		;
	}
	sprintf_s(query_sql, "insert into teacher(教师号,单,总) select 教师号,2*(实验课时+理论课时),班级数目*2*(实验课时+理论课时) from teacherinformation where  班级数目=3;");
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << mysql_error(&mysql) << endl;//sql语句出现错误
	}
	else
	{
		;
	}
	sprintf_s(query_sql, "insert into teacher(教师号,单,总) select 教师号,2.5*(实验课时+理论课时),班级数目*2.5*(实验课时+理论课时) from teacherinformation where  班级数目>=4;");
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << mysql_error(&mysql) << endl;//sql语句出现错误
	}
	else
	{
		;
	}
}
void search_teacher()
{
	cout << "请输入要查询的教师号" << endl;
	cin >> number;
	sprintf_s(query_sql, "SELECT *  FROM teacherinformation LEFT OUTER JOIN teacher ON teacherinformation.`教师号`=teacher.`教师号` where teacherinformation.`教师号`='%d';", number);
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
	}
	else
	{

		result = mysql_store_result(&mysql);
		if (result == NULL) //保存查询的结果 
		{
			if (mysql_field_count(&mysql) == 0)
			{
				cout << "没有返回结果" << endl;
			}

		}
		else
		{
			while ((row = mysql_fetch_row(result)) != NULL) //读取结果集中的数据
			{
				num_fields = mysql_num_fields(result);
				for (unsigned i = 0; i < num_fields; i++)
				{
					printf(" %s\t", row[i]);
				}//打印当前行的数据 
				printf("\n");
			}
		}

	}
	mysql_free_result(result); //释放结果集 
}


int main()
{
	init();
	search_teacher();
	exit();
}
