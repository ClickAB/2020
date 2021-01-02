
#include <stdio.h> 
#include<iostream>
#include <stdlib.h> 
#include<Windows.h>
#include<mysql.h>
#include<iomanip>
#include<map>
#pragma comment(lib, "libmysql.lib")
using namespace std;


class sys {
public:
	void init();
	void exitsys();
	void browse_teacher();
	void insert_teacher();
	void delete_teacher();
	void update_teacher();
	void Totalhours_singelTask();
	void search_teacher();
	void teacherTask_out();
	void menu();

private:
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
	char query_sql[500] = {};//存放sql语句
	int number;//教师号
	char name[20] = {};//姓名
	char sex[20] = {};//性别
	char title[20] = {};//职称
	char teaching_courses[20] = {};//教课科目
	char class_number[20] = {};//班级
	int class_sum ;//班级数目
	float tclass_hour;//理论课时
	float eclass_hour;//实验课时
};
void sys::init() //初始化系统
{
	mysql_init(&mysql); //连接之前必须使用这个函数来初始化 
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	cout << "连接教师工作量系统，请输入密码" << endl;
	cin.get(passwd, 100); 
	if ((sock = mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag)) == NULL) //连接MySQL 
	{
		cout << "未能成功与mysql建立连接" << endl;//输出连接错误
		cout << mysql_error(&mysql) << endl;//输出错误信息
		exit(1);
	}
	else
	{
		cout << "与Mysql服务器建立连接"<<endl;//输出即为连接成功
	}
}
void sys::exitsys()//退出系统
{
	cout << "成功退出系统" << endl;
	exit(0);

}


void sys::browse_teacher()//浏览教师信息
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

void sys::insert_teacher()//插入教师信息
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
void sys::update_teacher()//修改教师信息
{
	cout << "请输入要修改的教师号" << endl;
	cin >> number;
	map<string, int> mymap = {
		   { "姓名", 0 },
		   { "性别", 1},
		   { "职称", 2 },
		   { "任教课程", 3 },
		   { "班级", 4 },
		   { "班级数目", 5},
		   { "理论课时", 6 },
		   { "实验课时", 7 }};
	string tableupdate;
	cout << "请输入要修改的教师信息类型" << endl;
	cin >> tableupdate;
	while (mymap[tableupdate] > 7 || mymap[tableupdate] < 1)
	{
		cout << "输入错误，请重新输入" << endl;
		cin >> tableupdate;
	}
	switch (mymap[tableupdate])
	{
	case 0:
		cout << "请输入修改后的姓名" << endl;
		cin >> name;
		sprintf_s(query_sql, "update teacherinformation set 姓名='%s'where 教师号=%d", name, number);
		break;
	case 1:
		cout << "请输入修改后的性别" << endl;
		cin >> sex;
		sprintf_s(query_sql, "update teacherinformation set 性别='%s'where 教师号=%d", sex, number);
		break;
	case 2:
		cout << "请输入修改后的职称" << endl;
		cin >> title;
		sprintf_s(query_sql, "update teacherinformation set 职称='%s'where 教师号=%d", title, number);
		break;
	case 3:
		cout << "请输入修改后的任教课程" << endl;
		cin >> teaching_courses;
		sprintf_s(query_sql, "update teacherinformation set 任教课程='%s'where 教师号=%d", teaching_courses, number);
		break;
	case 4:
		cout << "请输入修改后的班级" << endl;
		cin >> class_number;
		sprintf_s(query_sql, "update teacherinformation set 班级='%s'where 教师号=%d", class_number, number);
		break;
	case 5:
		cout << "请输入修改后的班级数目" << endl;
		cin >> class_sum;
		sprintf_s(query_sql, "update teacherinformation set 班级数目='%d'where 教师号=%d", class_sum, number);
		break;
	case 6:
		cout << "请输入修改后的理论课时" << endl;
		cin >> tclass_hour;
		sprintf_s(query_sql, "update teacherinformation set 理论课时='%f'where 教师号=%d", tclass_hour, number);
		break;
	case 7:
		cout << "请输入修改后的实验课时" << endl;
		cin >> eclass_hour;
		sprintf_s(query_sql, "update teacherinformation set 实验课时='%f'where 教师号=%d", eclass_hour, number);
		break;
	}
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
void sys::delete_teacher()//删除教师信息
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
void sys::Totalhours_singelTask()//教师工作量计算
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
void sys::teacherTask_out()//查询教师工作量信息
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
void sys::search_teacher()//查询教师所有信息
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
void sys::menu()//显示菜单
{
	cout  << "教师工作量管理系统" << endl;
	cout  << "1.输入教师授课教学信息" << endl;
	cout  << "2.修改教师授课教学信息" << endl;
	cout  << "3.删除教师授课教学信息" << endl;
	cout  << "4.浏览教师授课教学信息" << endl;
	cout  << "5.浏览教师教学的工作量" << endl;
	cout  << "6.查询某教师的所有信息" << endl;
	cout  << "7.显示菜单" << endl;
	cout  << "8.退出系统" << endl;

}
int main()
{
	int menu_ch;//菜单选项
	char if_ch;//继续选项
	sys teachersys;
	teachersys.init();
	cout << "进入教师工作量管理系统" << endl << endl;
	teachersys.menu();
	while (1)
	{
		cout << endl;
		cout  << "请输入你要进行的操作" << endl;
		cin >> menu_ch;
		while (menu_ch > 8 || menu_ch < 1)
		{
			cout <<"输入错误，请重新输入" << endl;
			cin >> menu_ch;
		}
		switch (menu_ch)
		{
		case 1:teachersys.insert_teacher(); 
			   break;
		case 2:teachersys.update_teacher(); 
			   break;
		case 3:teachersys.delete_teacher(); 
			   break;
		case 4:teachersys.browse_teacher();
			   break;
		case 5:teachersys.Totalhours_singelTask(); 
			   teachersys.teacherTask_out();
			   break;
		case 6:teachersys.Totalhours_singelTask(); 
			   teachersys.search_teacher(); 
			   break;
		case 7:teachersys.menu(); 
			   break;
		case 8:teachersys.exitsys();
			   break;
		}
		cout << endl << "如果你想继续,请输入Y,否则退出系统" << endl;
		cin >> if_ch;
		if (if_ch != 'Y')
			break;
	}
	cout << "成功退出系统" << endl;
	exit(0);
}
