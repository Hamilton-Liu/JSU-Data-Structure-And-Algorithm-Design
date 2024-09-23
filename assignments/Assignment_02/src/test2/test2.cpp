#include <iostream>
using namespace std;
#include "Status.h"
#include "SqStack.h"
#include "Queue.h"

//利用两个栈sl和s2的操作可以模拟一个队列的操作，请写出使用两个栈实现入队、出队和判队列空的函数。


int main(void)
{
	Queue<int> queue;
	int data;

	cout << "Please enter 5 integers(11 12 13 14 15):" << endl;//输入：11 12 13 14 15
	for(int i=1; i<=5; i++)
	{
		cin >> data;
		if(queue.EnQueue(data) == OVER_FLOW)//----------------------------调用入队函数
			cout << "Queue is full!" << endl;
	}
	cout << "Two integers are out of the queue:" << endl;
	for(int i=1; i<=2; i++)
	{
		if(queue.DeQueue(data) != UNDER_FLOW)//----------------------------调用出队函数
			cout << data << "  ";
		else
			cout << endl << "Queue is Empty!" << endl;
	}
	cout << endl;
	cout << "Please enter 4 integers(21 22 23 24):" << endl;//输入：21 22 23 24
	for(int i=1; i<=4; i++)
	{
		cin >> data;
		if(queue.EnQueue(data) == OVER_FLOW)//----------------------------调用入队函数
			cout << "Queue is full!" << endl;
	}
	cout << "All integers are out of the queue:" << endl;
	while(!queue.IsEmpty())//----------------------------调用判队空函数
	{
		queue.DeQueue(data);//----------------------------调用出队函数
		cout << data << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}