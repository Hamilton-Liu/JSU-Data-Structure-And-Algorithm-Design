#include <iostream>
#include <assert.h>
using namespace std;
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//1-2 从顺序表中删除与给定值e相等的所有元素。
template<class DataType>
Status DelValue(SqList<DataType> &list, int e){
	DataType tmp;
	if (list.LocateElem(e) == 0){
		return UNDER_FLOW;
	} else {
		for(int i=list.GetLength(); i>=1; i--){		//反向遍历顺序表，如果遇到data域数值与目标数相同的元素，则进行删除。反向遍历避免了顺序删除造成的数据遗漏
			list.GetElem(i,tmp);
			if (tmp == e)
			{
				list.DeleteElem(i,tmp);
			}
		}
		return SUCCESS;
	}
}

//测试主函数
int main(void)
{
	SqList<int> list(11);
	int num,min,dx;
	cout << "Please enter 11 integers(6 32 3 11 11 11 41 26 11 5 22):" << endl;//输入：6 32 3 11 11 11 41 26 11 5 22
	for(int i=1; i<=11; i++)
	{
		cin >> num;
		list.InsertElem(i, num);
	}

	//-------以下用于测试第2小题-------------------------
	cout << "Please enter an integer to be deleted(22): " << endl;//输入：22
	cin >> dx;
	if(list.LocateElem(dx))
	{
		DelValue(list,dx);//------对第2小题函数的调用
		cout << "The deleted list is:" << endl;
		list.Traverse(Display);
		cout << endl << endl;
	}
	else
		cout << "Not found!" << endl;
	cout << "Please enter an integer to be deleted(26): " << endl;//输入：26
	cin >> dx;
	if (list.LocateElem(dx))
	{
		DelValue(list, dx);//------对第2小题函数的调用
		cout << "The deleted list is:" << endl;
		list.Traverse(Display);
		cout << endl << endl;
	}
	else
		cout << "Not found!" << endl;
	cout << "Please enter an integer to be deleted(11): " << endl;//输入：11
	cin >> dx;
	if(list.LocateElem(dx))
	{
		DelValue(list,dx);//------对第2小题函数的调用
		cout << "The deleted list is:" << endl;
		list.Traverse(Display);
		cout << endl << endl;
	}
	else
		cout << "Not found!" << endl << endl;

	system("pause");
	return 0;
}