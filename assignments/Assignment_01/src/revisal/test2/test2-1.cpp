#include <iostream>
using namespace std;
#include <assert.h>
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//2.1 把给定值e插入有序表中，使得插入后的表仍然有序。
template <class DataType>
Status OrdListInsertElem(SqList<DataType> &list,int e){
    DataType big;
    for(int i = 1; i <= list.GetLength(); i++){
        list.GetElem(i,big);
        if(big >= e){
            list.InsertElem(i,e);
            return SUCCESS;
    	}
	}list.InsertElem(list.GetLength()+1,e);
}

//测试主函数
int main(void)
{
	SqList<int> list1(50),list2(50),list3(50);
	int num,data;

	cout << "Please enter 11 ordered integers(5 10 11 22 27 33 44 44 55 56 60):" << endl;//输入：5 10 11 22 27 33 44 44 55 56 60
	for(int i=1; i<=11; i++)
	{
		cin >> num;
		list1.InsertElem(i, num);
	}

	//------------以下用于测试第1小题---------------------------------
	cout << "Please enter an integer to be inserted(3):" << endl;
	cin >> data;//输入：3
	OrdListInsertElem(list1,data);//----------调用第1小题函数
	cout << "After insertion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be inserted(27):" << endl;
	cin >> data;//输入：27
	OrdListInsertElem(list1,data);//----------调用第1小题函数
	cout << "After insertion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be inserted(77):" << endl;
	cin >> data;//输入：77
	OrdListInsertElem(list1,data);//----------调用第1小题函数
	cout << "After insertion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl << endl;

	system("pause");
	return 0;
}