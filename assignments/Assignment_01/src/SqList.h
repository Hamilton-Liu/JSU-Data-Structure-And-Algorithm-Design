#pragma once
#include "Status.h"
const int DEFAULT_SIZE = 100;
template<class DataType>
class SqList {
protected:
	DataType *elems;										//指向动态分配的数组
	int maxSize;											//顺序表的容量 
	int length;												//顺序表的长度
public:
	SqList(int size = DEFAULT_SIZE);						//构造函数
	virtual ~SqList();										//析构函数
	int GetLength() const;									//求顺序表的长度
	int GetMaxSize() const;									//求顺序表的容量
	bool IsEmpty() const;									//判断顺序表是否空表
	void Clear();											//清空顺序表
	int LocateElem(DataType &e);							//查找元素
	Status GetElem(int i, DataType &e);						//取元素
	Status SetElem(int i, DataType &e);						//修改元素
	Status InsertElem(int i, DataType &e);					//插入元素
	Status DeleteElem(int i, DataType &e);					//删除元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历顺序表
	SqList(const SqList<DataType> &sa);						//拷贝构造函数
	SqList<DataType> &operator =(const SqList<DataType> &sa);//赋值运算符重载
	//实验-1.1
	Status DelMinElem(DataType &e);							//删除最小元素
};

template<class DataType>
SqList<DataType>::SqList(int size) {   //创建一个容量为size的顺序表
	elems = new DataType[size];
	maxSize = size;
	length = 0;
}

template<class DataType>
SqList<DataType>::~SqList() 	   //销毁顺序表
{
	delete[]elems;
}

template<class DataType>
int SqList<DataType>::GetLength() const
{
	return length;
}

template<class DataType>
int SqList<DataType>::GetMaxSize() const	//求顺序表的容量
{
	return maxSize;
}

template<class DataType>
bool SqList<DataType>::IsEmpty() const
{
	return length ? false : true;
}

template<class DataType>
void SqList<DataType>::Clear()
{
	length = 0;
}

template<class DataType>
int SqList<DataType>::LocateElem(DataType &e) {
	int i = 0;
	while (i < length) {
		if (elems[i] == e) return i + 1;		//元素值相等，则返回位序，即当前下标+1
		else i++;								//若不相等，则继续向后寻找
	}
	return 0;									//顺序表没有与e相等的数据元素，返回0
}

template<class DataType>
Status SqList<DataType>::GetElem(int i, DataType &e) {
	if (i <1 || i > length) return INVALID;					//如果位序超出范围，返回无效信息
	e = elems[i - 1];										//将要数据元素保存在e中
	return SUCCESS;
}

template<class DataType>
Status SqList<DataType>::SetElem(int i, DataType &e) {
	if (i <1 || i > length) return INVALID;					//如果位序超出范围，返回无效信息
	elems[i - 1] = e;										//修改数据元素的值等于给定值e
	return SUCCESS;
}

template<class DataType>
Status SqList<DataType>::InsertElem(int i, DataType &e) {
	if (length == maxSize)  return OVER_FLOW;					//如果表已满，返回溢出信息
	if (i <1 || i > length + 1)  return INVALID;				//如果位序超出范围，返回无效信息
	for (int j = length - 1; j >= i - 1; j--)					//移动元素
		elems[j + 1] = elems[j];
	elems[i - 1] = e;											//将e存入当前位置
	length++;													//表长加1
	return SUCCESS;												//返回插入成功信息
}

template<class DataType>
Status SqList<DataType>::DeleteElem(int i, DataType &e) {
	if (length == 0) return UNDER_FLOW;							//如果是空表，返回下溢信息
	if (i <1 || i > length) return INVALID;						//如果位序超出范围，返回无效信息
	e = elems[i - 1];											//将要删除的数据元素保存在e中
	for (int j = i; j <= length - 1; j++)						//移动元素
		elems[j - 1] = elems[j];
	length--;													//表长减1
	return SUCCESS;
}

template<class DataType>
void SqList<DataType>::Traverse(void(*visit)(const DataType &)) const {  //遍历顺序表中的每个元素
	for (int i = 1; i <= length; i++)
		(*visit)(elems[i - 1]);									//调用visit指向的函数，依次访问数据元素
}

template <class DataType>
SqList<DataType>::SqList(const SqList<DataType> & sa) {
	elems = new DataType[sa.maxSize];
	maxSize = sa.maxSize;
	length = sa.length;
	for (int i = 0; i < length; i++)
		elems[i] = sa.elems[i];
}

template <class DataType>
SqList<DataType>&  SqList<DataType>::operator=(const SqList<DataType> & sa) {
	if(this == &sa)	return *this;
	if(elems)	delete[]elems;
	elems = new DataType[sa.maxSize];
	maxSize = sa.maxSize;    length = sa.length;
	for (int i = 0; i < length; i++)    elems[i] = sa.elems[i];
	return *this;
}

//实验-1.1
template <class DataType>
Status SqList<DataType>::DelMinElem(DataType &e) {
	if (length == 0) return UNDER_FLOW;							//如果是空表，返回下溢信息
	e = elems[0];												//将需要删除的数据信息存放在e中
	int flag = 0;												//定义标记变量来标记最小值的下标
	for (int i = 1 ; i <= length; i++){
		if (elems[i] < elems[i-1]){
			e = elems[i];
			flag = i;
		}
	}
	elems[flag] = elems[length];
	length--;
}