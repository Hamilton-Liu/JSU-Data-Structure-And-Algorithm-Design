#include <iostream>
#include <assert.h>
using namespace std;
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//1-3 在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，并删除其他所有重复的元素，使表中所有元素的值均不相同。
template <class DataType>
Status DelRepElem(SqList<DataType> &list){
	if (list.GetLength() == 0) return UNDER_FLOW;
	else {
		for (int i = 1; i <= list.GetLength()-1; i++){		//顺序遍历
			int tmp,opn = 0;
			list.GetElem(i,opn);
			for (int j = list.GetLength(); j >= i+1; j--){	//反向遍历
				list.GetElem(j,tmp);
				if (tmp == opn) {
					list.DeleteElem(j,tmp);
				}
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

	//--------------以下用于测试第3小题--------------------------------------------
	list.GetElem(1,num);	list.InsertElem(list.GetLength() + 1, num);	list.InsertElem(list.GetLength() + 1, num);
	list.GetElem(2,num);	list.InsertElem(list.GetLength() + 1, num);
	list.GetElem(3,num);	list.InsertElem(2,num);	list.InsertElem(list.GetLength() + 1, num);
	cout << "The current list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	DelRepElem(list);//------对第3小题函数的调用
	cout << "After deleting duplicate elements, the list is:" << endl;
	list.Traverse(Display);
	cout << endl << endl;

	system("pause");
	return 0;
}