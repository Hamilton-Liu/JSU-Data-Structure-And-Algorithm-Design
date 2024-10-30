#pragma once
#include "Status.h"
using namespace std;
const int DEFAULT_SIZE = 100;
template <class DataType>
class Stack {
protected:
    DataType *elems;                    //指向动态分配的数组
    int maxSize;                        //栈的容量
    int length;                         //栈的长度
public:
    Stack(int size = DEFAULT_SIZE);     //构造函数
    virtual ~Stack();                   //析构函数
    Status EnElem(DataType &e);         //元素入栈
    Status OutElem(DataType &e);        //元素出栈
    Status GetElem(DataType &e);        //取元素
};

template <class DataType>
Stack<DataType>::Stack(int size){
    
}