#include <iostream>
#include <assert.h>
using namespace std;
#include "Status.h"
#include "Node.h"
#include "LinkList.h"

template <class DataType>
void Display(const DataType & e) 
{    cout << e << "    ";    }

//对于一个不带头节点的单链表，设计递归算法逆置所有节点。
int main(void)
{
	LinkList<int> list;
	int no, data;

	cout << "Please enter 10 integers(21 32 3 11 11 11 41 26 11 5):" << endl;//输入：21 32 3 11 11 11 41 26 11 5
	for(int i=1; i<=10; i++)
	{
		cin >> data;
		list.InsertElem(i, data);
	}
	cout << "The list is:" << endl;
	list.Traverse(Display);
	//----------------以下用于测试不带头结点的单链表的主要操作-------------------------
	cout << "Please enter the serial number of the data to be inserted(1):" << endl;
	cin >> no;//输入：1
	cout << "Please enter the data to be inserted(17):" << endl;
	cin >> data;//输入：17
	list.InsertElem(no, data);
	cout << "After insertion, the list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter the serial number of the data to be deleted(1):" << endl;
	cin >> no;//输入：1
	list.DeleteElem(no, data);
	cout << "After deletion, the list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter the serial number of the data to be modified(1):" << endl;
	cin >> no;//输入：1
	list.GetElem(no, data);
	cout << "The original value of No. " << no << " element is: " << data << endl;
	cout << "Please enter the new value(66):" << endl;
	cin >> data;//输入：66
	list.SetElem(no, data);
	cout << "After modification, the list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	//----------------以下用于测试单链表逆置-------------------------
	list.Reverse();//------------------------------调用单链表逆置函数
	cout << "After inversion, the list is:" << endl;
	list.Traverse(Display);
	cout << endl;

	system("pause");
	return 0;
}