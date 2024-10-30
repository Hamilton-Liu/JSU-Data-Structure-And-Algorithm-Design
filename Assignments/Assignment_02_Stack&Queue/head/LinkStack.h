#pragma once
#include "Status.h"
#include  "Node.h"			//包含单链表节点类的头文件
template<class DataType>
class LinkStack
{
	Node<DataType> *top;							//栈顶指针
public:
	LinkStack();									//构造函数
	virtual ~LinkStack();							//析构函数
	int GetLength() const;							//求栈的长度
	bool IsEmpty() const;							//判断栈是否为空
	void Clear();									//清空栈
	Status Push(const DataType &e);					//入栈
	Status Pop(DataType &e);						//出栈
	Status Top(DataType &e) const;					//取栈顶元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历栈中元素
};

template<class DataType>
LinkStack<DataType>::LinkStack()		//建立一个空栈
{
	top = NULL;
}

template<class DataType>
LinkStack<DataType>::~LinkStack()		//销毁栈
{
	Clear();							//通过调用清空栈操作达到删除链表的目的
}					

template <class DataType>
int LinkStack<DataType>::GetLength() const	//返回栈中元素个数
{
	int count = 0；						//计数器，记录元素节点的数目
		Node<DataType> *p = top;		//定义辅助指针指向栈顶节点
	while (p)							//遍历链表，统计节点数目
	{
		count++;	p = p->next;
	}
	return count;						//返回节点数目（元素个数）
}

template<class DataType>
bool LinkStack<DataType>::IsEmpty() const	//栈为空返回true，否则返回false
{
	return top == NULL;
}

template<class DataType>
void LinkStack<DataType>::Clear()		//将栈置为空栈
{
	Node<DataType> *p = top;			//定义辅助指针用于删除链表中的节点
	while (p) {							//从链表头部开始依次删除节点
		top = top->next;				//栈顶指针指向后续节点，使后续节点成为新栈顶
		delete p;						//删除原栈顶节点
		p = top;						//辅助指针指向新栈顶节点
	}
}

template<class DataType>
Status LinkStack<DataType>::Push(const DataType &e)
{
	//申请分配一个新节点存储元素e，并插入链表头部
	Node<DataType> *pNew = new Node<DataType>(e, top);
	if (!pNew)								//判断节点是否分配失败
		return OVER_FLOW;					//节点分配失败，返回上溢信息
	else {									//节点分配成功
		top = pNew;							//栈顶指针指向新节点 
		return SUCCESS; 					//返回成功信息
	}
}

template<class DataType>
Status LinkStack<DataType>::Pop(DataType &e)	//若出栈成功，用e返回栈顶元素的值
{
	if (IsEmpty())						//判断栈是否为空
		return UNDER_FLOW;				//栈空，返回下溢信息
	else {								//栈不为空
		Node<DataType> *p = top;		//定义辅助指针指向当前栈顶节点
		e = top->data;					//获取当前栈顶元素的值
		top = top->next;	delete p;	//top指向新栈顶节点，删除旧栈顶节点
		return SUCCESS; 				//返回成功信息
	}
}

template<class DataType>
Status LinkStack<DataType>::Top(DataType &e) const	//若取栈顶元素成功，用e返回栈顶元素的值
{
	if (IsEmpty())							//判断栈是否为空
		return UNDER_FLOW;					//栈空，返回下溢信息
	else {									//栈不为空
		e = top->data;						//获取当前栈顶元素的值
		return SUCCESS; 					//返回成功信息
	}
}

template <class DataType>
void LinkStack<DataType>::Traverse(void(*visit)(const DataType &)) const		//遍历栈中的每个元素
{
	Node<DataType> *p = top;				//定义辅助指针指向栈顶节点
	while (p) {								//从栈顶节点开始依次访问节点
		(*visit)(p->data);					//访问节点元素
		p = p->next;						//指向后续节点
	}
}