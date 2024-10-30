#include <iostream>
#include <assert.h>
using namespace std;
#include "Status.h"
#include "Node.h"
#include "LinkList.h"

template <class DataType>
void Display(const DataType & e) 
{    cout << e << "    ";    }

//4-1 插入函数：把元素值e作为数据元素插入表中，使得插入后的表仍然有序。
template <class DataType>
Status OrdListInsertElem(LinkList<DataType> &list,DataType e){
	if(list.IsEmpty()) list.InsertElem(1,e);
    else{
		DataType tmp;
		int pos = 1;
		while(pos <= list.GetLength()){
			list.GetElem(pos,tmp);
			if(e < tmp) break;
			else pos++;
		}
		list.InsertElem(pos,e);
  		for(int i = 1; i <= list.GetLength(); i++){
        list.GetElem(i,tmp);
        if(e <= tmp){
            list.InsertElem(i,e);
            return SUCCESS;
        	}
    	}
		list.InsertElem(list.GetLength()+1,e);
	}
}

//4-2 删除数据元素等于e的节点。
template <class DataType>
Status OrdListDeleteElem(LinkList<DataType> &list, DataType e){
    DataType tmp;
	int pos = 1, count = 0;
	while(pos <= list.GetLength()){
		list.GetElem(i,tmp);
		if(tmp > e) break;
		if(tmp == e) {
			list.DeleteElem(i,tmp);
			count ++;
		}
		else pos ++;
	}
    return count ? SUCCESS : FAILED;
}

int main(void)
{
	LinkList<int> list;
	int data;

	cout << "Please enter 11 ordered integers(5 10 11 22 27 33 44 44 55 56 60):" << endl;//输入：5 10 11 22 27 33 44 44 55 56 60
	for(int i=1; i<=11; i++)
	{
		cin >> data;
		list.InsertElem(i, data);
	}
	
	//------------以下用于测试第1小题---------------------------------
	cout << "Please enter an integer to be inserted(3):" << endl;
	cin >> data;//输入：3
	OrdListInsertElem(list,data);//----------调用第1小题函数
	cout << "After insertion, list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be inserted(27):" << endl;
	cin >> data;//输入：27
	OrdListInsertElem(list,data);//----------调用第1小题函数
	cout << "After insertion, list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be inserted(77):" << endl;
	cin >> data;//输入：77
	OrdListInsertElem(list,data);//----------调用第1小题函数
	cout << "After insertion, list is:" << endl;
	list.Traverse(Display);
	cout << endl << endl;
	
	//------------以下用于测试第2小题---------------------------------
	cout << "Please enter an integer to be deleted(3):" << endl;
	cin >> data;//输入：3
	OrdListDeleteElem(list, data);//----------调用第2小题函数
	cout << "After deletion, list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be deleted(27):" << endl;
	cin >> data;//输入：27
	OrdListDeleteElem(list,data);//----------调用第2小题函数
	cout << "After deletion, list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	cout << "Please enter an integer to be deleted(77):" << endl;
	cin >> data;//输入：77
	OrdListDeleteElem(list,data);//----------调用第2小题函数
	cout << "After deletion, list is:" << endl;
	list.Traverse(Display);
	cout << endl << endl;

	system("pause");
	return 0;
}