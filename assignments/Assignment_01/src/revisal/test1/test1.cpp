#include <iostream>
#include <assert.h>
using namespace std;
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//1-1 从顺序表中删除具有最小值的元素（假设顺序表中元素都不相同），并由函数返回被删元素的值，空出的位置由最后一个元素填补。
template <class DataType>
DataType DelMinElem(SqList<DataType> &list){
    DataType min,tmp;
    if (list.GetLength() == 0) return UNDER_FLOW;						//如果是空表，返回下溢信息
	list.GetElem(1, min);										    	//初始化最小值
	int flag = 1;											        	//定义标记变量来标记最小值的下标
	for (int i = 2 ; i <= list.GetLength(); i++){                       //遍历顺序表，如果有更小值，则替换，并记录下标
        list.GetElem(i,tmp);
		if (tmp < min){
			min=tmp;
			flag = i;
		}
	}
	if (flag != list.GetLength()){
		list.GetElem(list.GetLength(),tmp);
		list.SetElem(flag,tmp);
	}
	list.DeleteElem(list.GetLength(),tmp);
    return min;
}

//1-2 从顺序表中删除与给定值e相等的所有元素。
/*template<class DataType>
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
}*/

//订正
template<class DataType>
Status DelValue(SqList<DataType> &list, DataType e){
	DataType tmp;
	int pos = 1;
	while (pos <= list.GetLength())
	{
		list.GetElem(pos,tmp);
		if (tmp == e) list.DeleteElem(pos,tmp);
		else pos ++;
	}
}

//1-3 在一个顺序表中如果一个数据值有重复出现，则留下第一个这样的数据值，并删除其他所有重复的元素，使表中所有元素的值均不相同。
template <class DataType>
Status DelRepElem(SqList<DataType> &list){
	int i = 1;
	DataType tmp,opn = 0;
	while (i <= list.GetLength()-1)
	{
		int j = i+1;
		list.GetElem(i,opn);
		while(j <= list.GetLength())
		{
			list.GetElem(j,tmp);
			if (tmp == opn) 
			list.DeleteElem(j,tmp);
			else j++;
		}
		i++;
	}
	return SUCCESS;
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

	//-------以下用于测试第1小题-------------------------
	min = DelMinElem(list);//------对第1小题函数的调用
	cout << "The current min value is: " << min << endl;
	cout << "After deleting the min value, the list is: " << endl;
	list.Traverse(Display);
	cout << endl;
	min = DelMinElem(list);//------对第1小题函数的调用
	cout << "The current min value is: " << min << endl;
	cout << "After deleting the min value, the list is:" << endl;
	list.Traverse(Display);
	cout << endl;
	min = DelMinElem(list);//------对第1小题函数的调用
	cout << "The current min value is: " << min << endl;
	cout << "After deleting the min value, the list is:" << endl;
	list.Traverse(Display);
	cout << endl << endl;

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

	//--------------以下用于测试第3小题--------------------------------------------
	list.GetElem(1,num);	list.InsertElem(list.GetLength() + 1,num);	list.InsertElem(list.GetLength() + 1, num);
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