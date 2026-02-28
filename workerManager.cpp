#include "workerManager.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"


WorkerManager::WorkerManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//出书画数组指针为
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.文件存在，并且没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout<<"文件为空"<<endl;
		this->m_EmpNum = 0;
		//出书画数组指针为
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.文件存在，并且记录了数据
	//读取文件中有多少人
	int num = this->get_EmpNum();
	//cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;
	
	this->m_EmpArray = new Worker * [this->m_EmpNum];//将文件中的数据存到数组中，开辟空间
	//将文件中的数据存到数组中
	this->init_Emp();


	////测试代码
	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "职工编号： " << this->m_EmpArray[i]->m_Id<<" "
	//		<< "姓名： " << this->m_EmpArray[i]->m_Name<<" "
	//		<< "部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;

	//}
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量： " << endl;
	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数=原来记录人数+新增人数
		//开辟新空间
		Worker ** newSpace = new Worker* [newSize ];
		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];

			}
		}
		//批量添加新数据
		for(int i=0;i<addNum;i++)
		{
			int id;
			string name;
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;
			cout << "请选择该职工的岗位" << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}
		//释放原有空间
		delete[] this->m_EmpArray;

		//更新新空间指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;


		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

		//保存数据到文件中
		this->save();

	}

	else
	{
		cout << "输入数据有误" << endl;
	}
	//按任意键清屏，回到上级目录
	system("pause");
	system("cls");

}

//成功添加后，保存到文件中
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件  --写文件
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name<<" "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();




}
int  WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return num;
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;


	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else //老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();

}


//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();

		}
		//按任意键清屏
		system("pause");
		system("cls");
	}
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空!" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);
		if (index != -1)//说明职工存在,并且要删除掉index位置上的职工
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				//数据前移
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组中记录的人员个数
			//数据同步更新到文件中
			this->save();
			cout << "删除成功" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}

		//按任意键清屏
		system("pause");
		system("cls");

	}

}

	//判断职工是否存在，如果存在，返回职工所在数组位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;//最开始认定不存在状况

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			  //找到职工
			index = i;

			break;
		}
	}
	return index;
}


//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入修改的职工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到职工编号
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = " ";
			int dSelect = 0;

			cout << "查到： " << id << "号职工，请输入新的职工号: " << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入新岗位： " << endl;
			cout << "1.普通职工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;

			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
				case 1:
					worker = new Employee(newId, newName, dSelect);
					break;
				case 2:
					worker = new Manager(newId, newName, dSelect);
					break;
				case 3:
					worker = new Boss(newId, newName, dSelect);
					break;
				default:
					break;
			}
			//更新数据到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;

			//保存到文件中
			this->save();
		}

		else//未查找到职工
		{
			cout << "未查找到职工,修改失败" << endl;

		}
		//按任意键清屏
		system("pause");
		system("cls");

	}
}



//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;

	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1.按照职工编号查找" << endl;
		cout << "2.按照职工姓名查找" << endl;
		int select = 0;
		cin>> select;

		if (select==1)
		{
			//按照编号查
			int id;
			cout << "请输入查找的职工的编号为：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工的信息如下： " << endl;
				this->m_EmpArray[ret]->showInfo();

			}
			else
			{
				cout << "查找失败，查无此人" << endl;  
			}
		}
		else if(select ==2)
		{
			//按照姓名查
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			//加入一个是否查到的标志
			bool flag = false;//默认未找到员工

			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,职工编号为：" << this->m_EmpArray[i]->m_Id <<
						"号职工信息如下：" << endl;

					flag = true;
					this->m_EmpArray[i]->showInfo();//显示信息的接口

				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}
			
		}
		else
		{
			cout << "输入的选项有误" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");



}


//按照编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		//按任意键清屏
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式" << endl;
		cout << "1.按照职工号进行升序" << endl;
		cout << "2.按照职工号进行降序" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < m_EmpNum; i++)
		{
			int minOrMax = i;//声明一个最小值或者最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//判断一开始认定的最小值或者最大值 是不是 计算的最小值或最大值 ，若不是，交换数据
			if (i != minOrMax)
			{
				Worker * temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}

		}

		cout << "排序成功！排序后的结果为:" << endl;
		this->save();
		this->Show_Emp();
	}
}


void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "清空成功" << endl;
	}
	//按任意键清屏
	system("pause");
	system("cls");
}


void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum ;i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;

	}
}