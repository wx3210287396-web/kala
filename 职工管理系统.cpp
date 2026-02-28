#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{

	////测试代码：
	//Worker * worker = NULL;
	//worker = new Employee(1, "张三", 1);
	//worker->showInfo();
	//delete worker;

	//worker = new Manager(2 ,"李四", 2);
	//worker->showInfo();
	//delete worker;

	//worker = new Boss(3, "王五", 3);
	//worker->showInfo();
	//delete worker;




	//实例化管理者对象
	WorkerManager wm;
	int  choice = 0;

	while (1)
	{
		wm.Show_Menu();

		cout << "请输入您的选择：" << endl;
	cin >> choice;


		switch (choice)
		{
		case 0://退出系统
			wm.ExitSystem();
				break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
		//	//测试
		//{
		//	int ret = wm.IsExist(3);
		//	if (ret != -1)
		//	{
		//		cout << "职工存在" << endl;

		//	}
		//	else
		//	{
		//		cout << "职工不存在" << endl;
		//	}

		//}
			wm.Del_Emp();

			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5://查找职工
			wm.Find_Emp();
			break;
		case 6://职工排序
			wm.Sort_Emp();
			break;
		case 7://清空文档
			wm.Clean_File();
			break;
		default:
			system("cls");//清屏操作
			break;
		}
	}
	wm.Show_Menu();

	system("pause");


	return 0;

}