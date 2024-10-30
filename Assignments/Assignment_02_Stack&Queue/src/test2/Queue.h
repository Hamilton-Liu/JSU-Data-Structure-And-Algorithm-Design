#pragma once
#include "SqStack.h"

//利用两个栈sl和s2的操作可以模拟一个队列的操作，请写出使用两个栈实现入队、出队和判队列空的函数。

//用于元素的输出
template <class DataType>
void Display(const DataType & e) 
{    cout << e ;    }

template <class DataType>
class Queue
{
    SqStack<DataType> *stk1, *stk2;         //两个构成队列的内部栈
    DataType tmp;                           //缓存变量
public:
    Queue(int size = DEFAULT_SIZE);         //构造函数
    virtual ~Queue();                       //构造函数
    bool IsEmpty() const;                   //判断队空
    Status EnQueue(const DataType &e);      //入队
    Status DeQueue(DataType &e);            //出队
};

template<class DataType>
Queue<DataType>::Queue(int size)            //构造容量为size的队列
{
    stk1 = new SqStack<DataType>(size/2);
    stk2 = new SqStack<DataType>(size/2);
}

template<class DataType>
bool Queue<DataType>::IsEmpty() const       //判断队列是否为空
{
    return (stk1->IsEmpty() && stk2->IsEmpty());
}

template<class DataType>
Status Queue<DataType>::EnQueue(const DataType &e)  //入队
{
    for (int i = stk2->top; i >= 0 ; i--)
    {
        stk2->Pop(tmp);
        stk1->Push(tmp);
    }
    stk1->Push(e);
    return SUCCESS;
}

template<class DataType>
Status Queue<DataType>::DeQueue(DataType &e)  //出队
{
    for (int i = stk1->top; i >= 0 ; i--)
    {
        stk1->Pop(tmp);
        stk2->Push(tmp);
    }
    stk2->Pop(e);
    return SUCCESS;
}

template <class DataType>
Queue<DataType>::~Queue()						//销毁一个队列
{
	delete stk1, stk2;
}