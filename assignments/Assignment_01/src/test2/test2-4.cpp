#include <iostream>
using namespace std;
#include <assert.h>
#include "Status.h"
#include "SqList.h"

//用于顺序表元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

//2-4 从有序顺序表中删除其值在给定值s与t之间（s＜t）的所有元素，即删除取值在[s,t]之间的所有元素；如果s≥t或顺序表为空，则显示出错信息，并退出运行。
template <class DataType>
Status OrdListIntervalDelete(SqList<DataType> &list,int s,int t){
    DataType tmp;
    if(s >= t || list.GetLength() == 0) return FAILED;
    else{
        for (int i = list.GetLength(); i >= 1; i--){
            list.GetElem(i,tmp);
            if(tmp >=s && tmp <= t){
                list.DeleteElem(i,tmp);
            }
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
		list3.InsertElem(i, num);
	}

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