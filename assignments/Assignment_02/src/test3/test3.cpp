#include <iostream>
using namespace std;
#include "Status.h"
#include "SqQueue.h"

//修改有关循环队列的设计，取消队尾指针rear，
//以front和length分别表示循环队列中的队头位置和队列中所含元素的个数。
//试完成循环队列判断队空、入队和出队函数的实现。

int main(void)
{
	SqQueue<int> queue(5);
	int data;

	cout << "Please enter 5 integers(11 12 13 14 15):" << endl;//输入：11 12 13 14 15
	for(int i=1; i<=5; i++)
	{
		cin >> data;
		if(queue.EnQueue(data) == OVER_FLOW)//-----------------------调用入队函数
			cout << "Queue is full!" << endl;
	}
	cout << "Two integers are out of the queue:" << endl;
	for(int i=1; i<=2; i++)
	{
		if(queue.DelQueue(data) != UNDER_FLOW)//-----------------------调用出队函数
			cout << data << "  ";
		else
			cout << endl << "Queue is Empty!" << endl;
	}
	cout << endl;
	cout << "Please enter 4 integers(21 22 23 24):" << endl;//输入：21 22 23 24
	for(int i=1; i<=4; i++)
	{
		cin >> data;
		if(queue.EnQueue(data) == OVER_FLOW)//-----------------------调用入队函数
			cout << "Queue is full!" << endl;
	}
	cout << "All integers are out of the queue:" << endl;
	while(!queue.IsEmpty())//-----------------------调用判队空函数
	{
		queue.DelQueue(data);//-----------------------调用出队函数
		cout << data << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}