#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqStack
{
	DataType *elems;								//元素存储空间
	int maxSize;									//栈的容量 
	int top1, top2;									//栈顶指针
public:
	SqStack(int size = DEFAULT_SIZE);				//构造函数
	virtual ~SqStack();								//析构函数
	int GetLength(int id) const;							//求栈的长度
	bool IsEmpty(int id) const;						//判断栈是否为空
	void Clear();									//清空栈
	Status Push(int id, const DataType &e);			//入栈
	Status Pop(int id, DataType &e);						//出栈
	Status Top(int id, DataType &e) const;					//取栈顶元素
	void Traverse(int id, void(*visit)(const DataType &)) const;	//遍历栈中元素
};

template<class DataType>
SqStack<DataType>::SqStack(int size)		//构造一个容量为size的共享栈
{	
	elems = new DataType[size];
	maxSize = size;
	top1 = -1;					//构造栈1
	top2 = size;				//构造栈2
}

template<class DataType>
SqStack<DataType>::~SqStack()			//销毁栈
{
	delete[]elems;
}

template <class DataType>
int SqStack<DataType>::GetLength(int id) const		//返回栈中元素个数
{	
	if(id == 1) return (top1 + 1);
	return (maxSize - top2);
}

template<class DataType>
bool SqStack<DataType>::IsEmpty(int id) const		//栈为空返回true，否则返回false
{
	if(id == 1){
		return top1 == -1;
	}
	return top2 == maxSize;
}

template<class DataType>
void SqStack<DataType>::Clear()				//将栈置为空栈
{
	top1 = -1;
	top2 = maxSize;
}

template<class DataType>
Status SqStack<DataType>::Push(int id, const DataType &e)
{
	if(id == 1){
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)			//判断栈1是否已满
			return OVER_FLOW;				//栈已满，返回上溢信息
		else {								//栈未满
			elems[++top1] = e;				//top+1即为新的栈顶位置，将元素e放入该位置
			return SUCCESS; 				//返回成功信息
		}
	}
	else{
		if (top1 + (maxSize - top2 + 1) == maxSize - 1)				//判断栈2是否已满
			return OVER_FLOW;				//栈已满，返回上溢信息
		else {								//栈未满
			elems[--top2] = e;				//top+1即为新的栈顶位置，将元素e放入该位置
			return SUCCESS; 				//返回成功信息
		}
	}
}

template<class DataType>
Status SqStack<DataType>::Pop(int id, DataType &e)	//若出栈成功，用e返回栈顶元素的值
{	
	if (id == 1){
			if (IsEmpty(id))					//判断栈是否为空
			return UNDER_FLOW;				//栈空，返回下溢信息
		else {								//栈不为空
			e = elems[top1--];				//获取当前栈顶元素的值，并删除该元素
			return SUCCESS; 				//返回成功信息
		}
	}
	else{
		if (IsEmpty(id))					//判断栈是否为空
			return UNDER_FLOW;				//栈空，返回下溢信息
		else {								//栈不为空
			e = elems[top2++];				//获取当前栈顶元素的值，并删除该元素
			return SUCCESS; 				//返回成功信息
		}
	}
}

template<class DataType>
Status SqStack<DataType>::Top(int id, DataType &e) const	//若取栈顶元素成功，用e返回栈顶元素的值
{
	if (IsEmpty(id))						//判断栈是否为空
		return UNDER_FLOW;					//栈空，返回下溢信息
	else {
		if(id == 1) e = elems[top1];			//栈不为空
		else e = elems[top2];					//获取当前栈顶元素的值
		return SUCCESS; 					//返回成功信息
	}
}

template <class DataType>
void SqStack<DataType>::Traverse(int id, void(*visit)(const DataType &)) const		//遍历栈中的每个元素
{	
	if(id ==1)
	{
		for (int i = top1; i >= 0; i--)
		(*visit)(elems[i]);
	}
	else
	{
		for (int i = top2; i <= maxSize-1; i++)
		(*visit)(elems[i]);
	}
}