#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqQueue
{
	DataType *elems;								//元素存储空间
	int maxSize;									//队列的容量 
	int front, rear;								//队头与队尾指针
public:
	SqQueue(int size = DEFAULT_SIZE);				//构造函数
	virtual ~SqQueue();								//析构函数
	int GetLength() const;							//求队列的长度
	bool IsEmpty() const;							//判断队列是否为空
	void Clear();									//清空队列
	Status EnQueue(const DataType &e);				//入队
	Status DelQueue(DataType &e);					//出队
	Status GetHead(DataType &e) const;				//取队头元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历队列元素
};

template<class DataType>
SqQueue<DataType>::SqQueue(int size)				//构造一个容量为size的空队列
{
	elems = new DataType[size];						
	maxSize = size;
	front = rear = 0;								//队头、队尾指针初始化为0
}

template <class DataType>
SqQueue<DataType>::~SqQueue()						//销毁一个队列
{
	delete []elems;
}

template<class DataType>
int SqQueue<DataType>::GetLength() const			//求队列的长度
{
	return (rear - front + maxSize) % maxSize;		//计算并返回队列中的元素数目
}

template<class DataType>
bool SqQueue<DataType>::IsEmpty() const				//队列为空返回true，否则返回false
{
	return front == rear;
}

template<class DataType>
void SqQueue<DataType>::Clear()						//清空队列
{
	front = rear = 0;
}

template<class DataType>
Status SqQueue<DataType>::EnQueue(const DataType &e)
{
	if((rear + 1) % maxSize == front)					//判断队列是否已满
		return OVER_FLOW;								//队列已满，返回上溢信息
	else {												//队列未满
		elems[rear] = e;								//将e放入队尾指针指示的位置
		rear = (rear + 1) % maxSize;					//队尾指针后移1位
		return SUCCESS;									//返回入队成功信息
	}
}

template<class DataType>
Status SqQueue<DataType>::DelQueue(DataType &e)
{
	if(IsEmpty())										//判断队列是否为空
		return UNDER_FLOW;								//队列为空，返回下溢信息
	else {												//队列不为空
		e = elems[front];								//获取队头元素的值
		front = (front + 1) % maxSize;					//队头指针后移1位即删除队头元素
		return SUCCESS;									//返回出队成功信息
	}	
}

template<class DataType>
Status SqQueue<DataType>::GetHead(DataType &e) const
{
	if(IsEmpty())										//判断队列是否为空
		return UNDER_FLOW;								//队列为空，返回下溢信息
	else {												//队列不为空
		e = elems[front];								//获取队头元素的值
		return SUCCESS;									//返回成功信息
	}
}

template<class DataType>
void SqQueue<DataType>::Traverse(void (*visit)(const DataType &)) const	//遍历队列元素
{
	for (int i = front; i != rear; i = (i + 1) % maxSize)
		(*visit)(elems[i]);
}