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
    list.GetElem(list.GetLength(),tmp);
	list.SetElem(flag,tmp);
	list.DeleteElem(list.GetLength(),tmp);
    return min;
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

    system("pause");
    return 0;
}
