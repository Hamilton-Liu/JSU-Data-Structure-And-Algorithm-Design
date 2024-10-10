#include <iostream>
using namespace std;
#include <assert.h>
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

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

	system("pause");
	return 0;
}