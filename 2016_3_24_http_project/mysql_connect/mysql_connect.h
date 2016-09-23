#pragma once

#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
#include"mysql.h"

#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_USER "root"
#define DEFAULT_PWD "213"
#define DEFAULT_DB "6_students"
class sql_connect
{
public:
	sql_connect(const string &host = DEFAULT_HOST,\
			const string &user = DEFAULT_USER,\
			const string &passwd = DEFAULT_PWD,\
			const string &db = DEFAULT_DB);
	~sql_connect();
	//connect mysql
	bool connect_mysql();

	bool insert_info(const string &_info);
	bool select_info();
	//bool delete_info(const string &_info);
	bool update_info(const string &_info);
	void show_info();
	void close_mysql();
private:
	MYSQL_RES *_res;
	MYSQL *_mysql_base;//mysql handle
	string _host;
	string _user;
	string _passwd;
	string _db;
};
