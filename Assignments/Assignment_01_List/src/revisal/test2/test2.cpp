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
Status OrdListInsertElem(SqList<DataType> &list,DataType e){
    DataType big;
	int i = 1;
    while(i <= list.GetLength())
	{
        list.GetElem(i,big);
        if(big < e){
            i++;
    	} else break;
	}
	list.InsertElem(i,e);
	return SUCCESS;
}

//2-2 删除值为e的所有数据元素。
template <class DataType>
Status OrdListDeleteElem(SqList<DataType> &list, DataType e)
{
    DataType tmp;
	int i = 1;
	while(i <= list.GetElem())
	{
		list.GetElem(i,tmp);
		if(tmp > e) break;
		if (tmp == e) list.DeleteElem(i,e);
		else i++;
	}
	return SUCCESS;
}

//2-3 合并两个有序表，得到一个新的有序表。
template <class DataType>
Status OrdListMerge(SqList<DataType> &list1, SqList<DataType> &list2, SqList<DataType> &list3){
    for(int i = 1; i <= list2.GetLength(); i++){				//将list2中的元素按顺序一一复制到list3中
        DataType tmp;
        list2.GetElem(i,tmp);
        list3.InsertElem(i,tmp);
    }
    for(int j = 1; j <= list1.GetLength(); j++){				//遍历list1，对其中每一个元素进行顺序插入，插入到list3中
        DataType big,tmp;
        list1.GetElem(j,tmp);
        for(int i = 1; i <= list3.GetLength(); i++){			//遍历list3，将其中元素与list1中的tmp进行比较
            list3.GetElem(i,big);
            if(big >= tmp){										//如果在遍历过程中出现更大的元素，则在此处插入tmp元素，并跳出循环
                list3.InsertElem(i,tmp);
				break;
            } else if(i == list3.GetLength()) {					//如果在遍历完后仍未出现更大元素，则在list3的最后一位后插入tmp元素
				list3.InsertElem(list3.GetLength()+1,tmp);
				}
        }
    }
    return SUCCESS;												//返回成功信息
}
//2-3 订正: 合并两个有序表，得到一个新的有序表。
template <class DataType>
Status OrdListMerge(SqList<DataType> &list1, SqList<DataType> &list2, SqList<DataType> &list3){

}

//2-4 从有序顺序表中删除其值在给定值s与t之间（s＜t）的所有元素，即删除取值在[s,t]之间的所有元素；如果s≥t或顺序表为空，则显示出错信息，并退出运行。
template <class DataType>
Status OrdListIntervalDelete(SqList<DataType> &list,int s,int t){
    if(s >= t || list.IsEmpty()) return FAILED;
    else{
		DataType tmp;
		int i=1;
		while(i < list.GetLength()){
			list.GetElem(i,tmp);
			if(tmp > t) break;
			if(tmp >= s) list.DeleteElem(i,tmp);
			else i++;
		}
        return SUCCESS;
    }
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

	//------------以下用于测试第3小题---------------------------------
	cout << "Please enter 5 integers(5 27 30 36 77):" << endl;//输入：5 27 30 36 77
	for(int i=1; i<=5; i++)
	{
		cin >> num;
		list2.InsertElem(i, num);
	}
	if(OrdListMerge(list1,list2,list3) == SUCCESS)//---------调用第3小题函数
	{
		cout << "The merged list3 is:" << endl;
		list3.Traverse(Display);
	}
	else
		cout << "The space of list3 is insufficient!";
	cout << endl << endl;

	//------------以下用于测试第4小题---------------------------------
	int s,t;
	cout << "Please enter the lower bound of the deleted integer(0):" << endl;
	cin >> s;//输入：0
	cout << "Please enter the upper bound of the deleted integer(11):" << endl;
	cin >> t;//输入：11
	if(OrdListIntervalDelete(list3,s,t) == SUCCESS)//---------调用第4小题函数
	{
		cout << "After deletion, list3 is:" << endl;
		list3.Traverse(Display);
		cout << endl;
	}
	cout << "Please enter the lower bound of the deleted integer(30):" << endl;
	cin >> s;//输入：30
	cout << "Please enter the upper bound of the deleted integer(50):" << endl;
	cin >> t;//输入：50
	if(OrdListIntervalDelete(list3,s,t) == SUCCESS)//---------调用第4小题函数
	{
		cout << "After deletion, list3 is:" << endl;
		list3.Traverse(Display);
		cout << endl;
	}
	cout << "Please enter the lower bound of the deleted integer(58):" << endl;
	cin >> s;//输入：58
	cout << "Please enter the upper bound of the deleted integer(100):" << endl;
	cin >> t;//输入：100
	if(OrdListIntervalDelete(list3,s,t) == SUCCESS)//---------调用第4小题函数
	{
		cout << "After deletion, list3 is:" << endl;
		list3.Traverse(Display);
		cout << endl;
	}
	cout << endl;

	system("pause");
	return 0;
}