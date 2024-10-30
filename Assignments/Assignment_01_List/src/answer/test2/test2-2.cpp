#include <iostream>
using namespace std;
#include <assert.h>
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//2-2 删除值为e的所有数据元素。
template <class DataType>
Status OrdListDeleteElem(SqList<DataType> &list, int e){
    DataType tmp;
    for (int i = list.GetLength(); i >= 1; i--){
        list.GetElem(i,tmp);
        if(tmp == e) list.DeleteElem(i,tmp);
    }
    return SUCCESS;
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
	
	//------------以下用于测试第2小题---------------------------------
	cout << "Please enter an integer to be deleted(3):" << endl;
	cin >> data;//输入：3
	OrdListDeleteElem(list1,data);//----------调用第2小题函数
	cout << "After deletion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be deleted(27):" << endl;
	cin >> data;//输入：27
	OrdListDeleteElem(list1,data);//----------调用第2小题函数
	cout << "After deletion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be deleted(77):" << endl;
	cin >> data;//输入：77
	OrdListDeleteElem(list1,data);//----------调用第2小题函数
	cout << "After deletion, list1 is:" << endl;
	list1.Traverse(Display);
	cout << endl << endl;

	system("pause");
	return 0;
}