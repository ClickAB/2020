
#include <stdio.h> 
#include<iostream>
#include <stdlib.h> 
#include<Windows.h>
#include<mysql.h>
#include<iomanip>
#pragma comment(lib, "libmysql.lib")
using namespace std;


	MYSQL mysql, * sock; //声明mysql的句柄 
	const char* host = "localhost"; //本机连接
	const char* user = "root"; //mysql用户名 
	char passwd[100] = {}; //用户密码 
	const char* db = "teacher"; //老师信息数据库
	unsigned int port = 3306; //mysql服务器端口设置在3306
	const char* unix_socket = NULL; //unix_socket
	unsigned long client_flag = 0; //参数一般为0 
	const char* i_query = "select * from teacherinformation "; //查询语句，从那个表中查询,这里后面没有;
	MYSQL_RES* result; //保存结果集
	MYSQL_ROW row; //代表的是结果集中的一行 
	unsigned int	num_fields;//结果集某行的列数
void init() //初始化系统
{
	mysql_init(&mysql); //连接之前必须使用这个函数来初始化 
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	cout << "连接教师工作量系统，请输入密码" << endl;
	cin.get(passwd, 100); 
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
	cout << "成功退出系统" << endl;
	exit(0);

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
			cout << "教师号   姓名    性别    职称    任教课  班级          班级数   理论课时 实验课时" << endl;
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
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
		cout << "修改信息失败" << endl;
	}
	else
	{

		cout << "修改信息成功" << endl;

	}

	
}
void delete_teacher()
{
	cout << "请输入要删除的教师号" << endl;
	cin >> number;
	sprintf_s(query_sql,
		"DELETE FROM teacherinformation WHERE 教师号 = %d", number);
	if (mysql_query(&mysql, query_sql) != 0) //mysql_query函数运行SQL语句,成功返回0
	{
		cout << "sql语句出现错误" << endl;
		cout << mysql_error(&mysql) << endl;//sql语句错误信息
		cout << "删除失败" << endl;
	}
	else
	{

		cout << "删除成功"<<endl;

	}

}
void Totalhours_singelTask()
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
void teacherTask_out()
{
	sprintf_s(query_sql, "SELECT *  FROM teacher ");
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
			cout << "教师号 单任务量 总任务量" << endl;
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
void search_teacher()
{
	cout << "请输入要查询的教师号" << endl;
	cin >> number;
	sprintf_s(query_sql, "SELECT * FROM teacherinformation a left join teacher b using(`教师号`)where a.`教师号`=%d", number);
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
			cout << "教师号   姓名    性别    职称    任教课  班级         班级数   理论课时 实验课时 单任务 总任务" << endl;
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
void menu()
{
	cout  << "进入教师工作量管理系统" << endl << endl;
	cout  << "教师工作量管理系统" << endl;
	cout  << "1.输入教师授课教学信息" << endl;
	cout  << "2.修改教师授课教学信息" << endl;
	cout  << "3.删除教师授课教学信息" << endl;
	cout  << "4.浏览教师授课教学信息" << endl;
	cout  << "5.浏览教师教学的工作量" << endl;
	cout  << "6.查询某教师的所有信息" << endl;
	cout  << "7.退出系统" << endl;

}
int main()
{
	init();
	int menu_ch;
	char if_ch;
	menu();
	while (1)
	{
		cout << endl;
		cout  << "请输入你要进行的操作" << endl;
		cin >> menu_ch;
		while (menu_ch > 7 || menu_ch < 1)
		{
			cout <<"输入错误，请重新输入" << endl;
			cin >> menu_ch;
		}
		switch (menu_ch)
		{
		case 1:insert_teacher(); break;
		case 2:update_teacher(); break;
		case 3:delete_teacher(); break;
		case 4:browse_teacher(); break;
		case 5:Totalhours_singelTask(); teacherTask_out(); break;
		case 6:Totalhours_singelTask(); search_teacher(); break;
		case 7:exit(); 
		}
		cout << endl << "如果你想继续,请输入Y,否则退出系统" << endl;
		cin >> if_ch;
		if (if_ch != 'Y')
			break;

	}
	cout << "成功退出系统" << endl;
	exit(0);
}
