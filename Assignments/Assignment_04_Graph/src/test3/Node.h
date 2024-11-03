#pragma once
template <class DataType>
class Node {
public:
	DataType data;									//数据域
	Node< DataType> *next;							//指针域
	Node() { next = NULL; }							//无参构造函数，可用于构造头节点
	Node(DataType e, Node< DataType> *link = NULL) 	//有参构造函数，构造数据元素节点
	{
		data = e;	next = link;
	}
};