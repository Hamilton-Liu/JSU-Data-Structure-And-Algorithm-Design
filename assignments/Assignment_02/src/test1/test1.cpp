#include <iostream>
using namespace std;
#include "Status.h"
#include "SqStack.h"

//1.为了减少顺序栈溢出情况的发生，可以让两个顺序栈共用一个数组存储数据元素，被称为共享栈。
//此时，两个栈的栈底分别设置在数组的两端，入栈时栈顶向数组中间移动，如下图所示.
//当两个栈的栈顶位置相遇时才是栈满状态。请设计共享栈的类定义，实现判断栈空、入栈和出栈的函数。

//用于元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e << "  ";    }

int main(void)
{
	SqStack<int> stack(10);
	int data;

	cout << "Please enter 5 integers(11 12 13 14 15):" << endl;//输入：11 12 13 14 15
	for(int i=1; i<=5; i++)
	{
		cin >> data;
		if(stack.Push(1,data) == OVER_FLOW)//-------------调用共享栈入栈函数
		{	cout << "Stack is full!" << endl;	exit(0);	}
	}
	cout << "Please enter 4 integers(21 22 23 24):" << endl;//输入：21 22 23 24
	for(int i=1; i<=4; i++)
	{
		cin >> data;
		if(stack.Push(2,data) == OVER_FLOW)//------------调用共享栈入栈函数
		{	cout << "Stack is full!" << endl;	exit(0);	}
	}

	cout << "Stack-1 has " << stack.GetLength(1) << " elements:" << endl;//------------调用共享栈求栈长函数
	stack.Traverse(1,Display);//------------调用共享栈遍历函数
	cout << endl;
	cout << "Stack-2 has " << stack.GetLength(2) << " elements:" << endl;//------------调用共享栈求栈长函数
	stack.Traverse(2,Display);//------------调用共享栈遍历函数
	cout << endl;

	cout << "The elements in stack-1 are out of the stack:" << endl;
	while(stack.GetLength(1))
	{
		stack.Pop(1,data);//------------调用共享栈出栈函数
		cout << data << "  "; 
	}
	cout << endl;
	cout << "The elements in stack-2 are out of the stack:" << endl;
	while(stack.GetLength(2))
	{
		stack.Pop(2,data);//------------调用共享栈出栈函数
		cout << data << "  "; 
	}
	cout << endl;

	if(stack.IsEmpty(1) && stack.IsEmpty(2))//------------调用共享栈判栈空函数
		cout << "Stack is empty!" << endl;

	system("pause");
	return 0;
}