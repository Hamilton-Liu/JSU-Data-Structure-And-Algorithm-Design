#pragma once
#include "Status.h"
#include "Node.h"			//包含单链表节点类的头文件
template<class DataType>
class LinkQueue
{
	Node<DataType> *front, *rear;					//队头与队尾指针
public:
	LinkQueue();									//构造函数
	virtual ~LinkQueue();							//析构函数
	int GetLength() const;							//求队列的长度
	bool IsEmpty() const;							//判断队列是否为空
	void Clear();									//清空队列
	Status EnQueue(const DataType &e);				//入队
	Status DelQueue(DataType &e);					//出队
	Status GetHead(DataType &e) const;				//取队头元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历队列元素
};

template<class DataType>
LinkQueue<DataType>::LinkQueue()					//构造一个空的链队列
{
	rear = front = new Node<DataType>;
}

template <class DataType>
LinkQueue<DataType>::~LinkQueue()					//销毁一个链队列
{
	Clear();										//释放所有元素节点
	delete front;									//释放头节点
}

template<class DataType>
int LinkQueue<DataType>::GetLength() const			//求链队列的长度
{
	int count = 0;									//计数器，记录元素节点的数目
	Node<DataType> *p = front->next;				//定义辅助指针指向队头节点
	while (p)										//遍历链表，统计节点数目
	{
		count++;	p = p->next;
	}
	return count;									//返回节点数目（元素个数）
}

template<class DataType>
bool LinkQueue<DataType>::IsEmpty() const			//链队列为空返回true，否则返回false
{
	return front == rear;
}

template<class DataType>
void LinkQueue<DataType>::Clear()					//清空链队列
{
	Node<DataType> *p = front->next;				//定义辅助指针指向第一个元素节点
	while (p) {										//从链表头部开始依次删除节点
		front->next = p->next;						//修改头节点的后继指针指向第一个元素节点的后继节点
		delete p;									//删除第一个元素节点
		p = front->next;							//辅助指针指向当前的第一个元素节点
	}
	rear = front;									//修改队尾指针指向头节点
}

template<class DataType>
Status LinkQueue<DataType>::EnQueue(const DataType &e)
{
	//申请分配一个新节点存储元素e 
	Node<DataType> *pNew = new Node<DataType>(e);
	if (!pNew)										//判断节点是否分配失败
		return OVER_FLOW;							//节点分配失败，返回上溢信息
	else {											//节点分配成功
		rear->next = pNew;							//将节点插入队尾指针所指节点之后
		rear = rear->next;							//移动队尾指针指向新节点
		return SUCCESS; 							//返回成功信息
	}
}

template<class DataType>
Status LinkQueue<DataType>::DelQueue(DataType &e)	//若出队成功，用e返回队头元素的值
{
	if (IsEmpty())									//判断队列是否为空
		return UNDER_FLOW;							//队列为空，返回下溢信息
	else {											//队列不为空
		Node<DataType> *p = front->next;			//定义辅助指针指向当前队头节点
		e = p->data;								//获取当前队头元素的值
		front->next = p->next;						//修改头节点中的后继指针
		if (rear == p)								//判断队列是否只有一个元素
			rear = front;							//只有一个元素，修改队尾指针指向头节点
		delete p;									//删除原队头节点
		return SUCCESS; 							//返回成功信息
	}
}

template<class DataType>
Status LinkQueue<DataType>::GetHead(DataType &e) const	//若取队头元素成功，用e返回队头元素的值
{
	if (IsEmpty())									//判断队列是否为空
		return UNDER_FLOW;							//队列为空，返回下溢信息
	else {											//队列不为空
		e = front->next->data;						//获取第一个元素节点中数据元素的值
		return SUCCESS; 							//返回成功信息
	}
}

template<class DataType>
void LinkQueue<DataType>::Traverse(void(*visit)(const DataType &)) const	//遍历链队列元素
{
	for (Node<DataType> *p = front->next; p; p = p->next)
		(*visit)(p->data);
}
