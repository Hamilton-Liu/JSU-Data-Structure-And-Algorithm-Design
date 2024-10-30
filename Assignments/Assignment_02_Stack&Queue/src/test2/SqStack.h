#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqStack
{
	DataType *elems;								//元素存储空间
public:
	int maxSize;									//栈的容量 
	int top;										//栈顶指针
	SqStack(int size = DEFAULT_SIZE);				//构造函数
	virtual ~SqStack();								//析构函数
	int GetLength() const;							//求栈的长度
	bool IsEmpty() const;							//判断栈是否为空
	void Clear();									//清空栈
	Status Push(const DataType &e);					//入栈
	Status Pop(DataType &e);						//出栈
	Status Top(DataType &e) const;					//取栈顶元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历栈中元素
};

template<class DataType>
SqStack<DataType>::SqStack(int size)		//构造一个容量为size的空栈
{
	elems = new DataType[size];
	maxSize = size;
	top = -1;
}

template<class DataType>
SqStack<DataType>::~SqStack()			//销毁栈
{
	delete[]elems;
}

template <class DataType>
int SqStack<DataType>::GetLength() const		//返回栈中元素个数
{
	return top + 1;
}

template<class DataType>
bool SqStack<DataType>::IsEmpty() const		//栈为空返回true，否则返回false
{
	return top == -1;
}

template<class DataType>
void SqStack<DataType>::Clear()				//将栈置为空栈
{
	top = -1;
}

template<class DataType>
Status SqStack<DataType>::Push(const DataType &e)
{
	if (top == maxSize - 1)				//判断栈是否已满
		return OVER_FLOW;				//栈已满，返回上溢信息
	else {								//栈未满
		elems[++top] = e;				//top+1即为新的栈顶位置，将元素e放入该位置
		return SUCCESS; 				//返回成功信息
	}
}

template<class DataType>
Status SqStack<DataType>::Pop(DataType &e)	//若出栈成功，用e返回栈顶元素的值
{
	if (IsEmpty())						//判断栈是否为空
		return UNDER_FLOW;				//栈空，返回下溢信息
	else {								//栈不为空
		e = elems[top--];				//获取当前栈顶元素的值，并删除该元素
		return SUCCESS; 				//返回成功信息
	}
}

template<class DataType>
Status SqStack<DataType>::Top(DataType &e) const	//若取栈顶元素成功，用e返回栈顶元素的值
{
	if (IsEmpty())							//判断栈是否为空
		return UNDER_FLOW;				//栈空，返回下溢信息
	else {									//栈不为空
		e = elems[top];						//获取当前栈顶元素的值
		return SUCCESS; 					//返回成功信息
	}
}

template <class DataType>
void SqStack<DataType>::Traverse(void(*visit)(const DataType &)) const		//遍历栈中的每个元素
{
	for (int i = top; i >= 0; i--)
		(*visit)(elems[i]);
}

