#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"manager.h"
#include"employee.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile。txt"



class WorkerManager
{
public:

	WorkerManager();

	//展示菜单
	void Show_Menu()
	{
		cout << "****************************************" << endl;
		cout << "********  欢迎使用职工管理系统  ********" << endl;
		cout << "***********  0.退出管理程序  ***********" << endl;
		cout << "***********  1.增加职工信息  ***********" << endl;
		cout << "***********  2.显示所有员工  ***********" << endl;
		cout << "***********  3.删除离职职工  ***********" << endl;
		cout << "***********  4.修改职工信息  ***********" << endl;
		cout << "***********  5.查找职工信息  ***********" << endl;
		cout << "***********  6.按照编号排序  ***********" << endl;
		cout << "***********  7.清空所有文档  ***********" << endl;
		cout << "****************************************" << endl;
		cout << endl;

	}
	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;

	//职工数组执政
	Worker** m_EmpArray;

	//添加职工函数
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空的标志
	bool m_FileIsEmpty;

	//统计文件中人数
	int get_EmpNum();

	//初始化员工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//删除职工
	void Del_Emp();


	//判断职工是否存在，如果存在，返回职工所在数组位置，不存在返回-1
	int IsExist(int id);

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//职工排序
	void Sort_Emp();

	//清空函数
	void Clean_File();


	//析构函数
	~WorkerManager();

};