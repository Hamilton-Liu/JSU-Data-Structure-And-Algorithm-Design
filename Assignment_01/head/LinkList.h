#pragma once
#include "Status.h"
#include "Node.h"
template<class DataType>
class LinkList {
protected:
	Node<DataType> *head;								//单链表头指针
	int length;											//链表长度
public:
	LinkList();											//构造函数，构造空链表
	LinkList(DataType a[], int n);						//构造函数，构造有元素的链表
	virtual ~LinkList();								//析构函数
	void Clear();										//清空单链表
	int GetLength() const;								//求单链表的长度
	bool IsEmpty() const;								//判断单链表是否为空表
	int LocateElem(const DataType &e);					//查找元素
	Status GetElem(int i, DataType &e);					//取元素
	Status SetElem(int i, DataType &e);					//修改元素
	Status InsertElem(int i, DataType &e);				//插入元素
	Status DeleteElem(int i, DataType &e);				//删除元素
	void Traverse(void(*visit)(const DataType &)) const;	//遍历单链表
};

template<class DataType>
LinkList<DataType>::LinkList() {  						//创建一个只含有头节点的空链表
	head = new Node<DataType>;							//创建头节点
	length = 0;											//表长为0
}

template<class DataType>
LinkList<DataType>::LinkList(DataType a[], int n) {  	//构造函数，创建一个非空链表
	Node<DataType> *p;									//指向链表表尾节点的指针变量
	p = head = new Node<DataType>;    					//创建头节点
	for(int i = 0; i < n; i++) {
		p->next = new Node<DataType>(a[i]); 			//创建元素节点，数据域为a[i]，指针域为NULL
		p = p->next; 									//p后移指向当前表尾节点
	}
	length = n;
}

template <class DataType>
LinkList<DataType>::~LinkList() {
	Clear();											//删除所有元素节点
	delete head;										//删除头节点
	head = NULL;
}

template<class DataType>
void LinkList<DataType>::Clear() {						//清空链表
	Node<DataType> *p = head->next;   					//p指向第一个元素节点
	while(p) {  										//循环释放每个节点
		head->next = p->next;    						//修改头节点的后继指针指向待删节点的后继
		delete p;										//释放第一个元素节点
		p = head->next;									//p继续指向链表当前的第一个元素节点
	}
	length = 0;
}

template<class DataType>
int LinkList<DataType>::GetLength() const 				//求单链表的长度
{
	return length;
}

template<class DataType>
bool LinkList<DataType>::IsEmpty() const
{
	return length ? false : true;
}

template <class DataType>
int LinkList<DataType>::LocateElem(const DataType &e) {
	Node<DataType> *p = head->next;  					//p指向第一个元素节点
	int count = 1;
	while(p != NULL && p->data != e) {					//从第一个元素节点开始依次进行比较元素的值
		p = p->next;									//移动指针p使之指向后继节点
		count++;										//计数器累加
	}
	return p ? count : 0;								//找到元素值等于e，返回count的值，否则返回0
}

template<class DataType>
Status LinkList<DataType>::GetElem(int i, DataType &e) {	//取元素
	if(i < 1 || i > length) return INVALID;				//如果位序取值无效，返回无效信息
	Node<DataType> *p = head->next;   					//p指向第一个元素节点
	int count;											//计数器，记录p指向第几个元素节点
	for(count = 1; count < i; count++)   				//后移p使之指向第i个元素节点
		p = p->next;
	e = p->data;										//将数据域的值保存至e中
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::SetElem(int i, DataType &e) {
	if(i < 1 || i > length)	 return INVALID;			//如果位序取值无效，返回无效信息
	Node<DataType> *p = head->next;   					//p指向第一个元素节点
	int count;											//计数器，记录p指向第几个元素节点
	for(count = 1; count < i; count++)   				//后移p使之指向第i个元素节点
		p = p->next;
	p->data = e;										//修改数据域为e
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::InsertElem(int i, DataType &e) {	//插入元素
	if(i < 1 || i > length + 1)   return INVALID;
	Node<DataType> *p = head, *q;						//p初始指向头节点，即第1个元素节点的前驱
	int count;											//计数器，记录p指向第几个元素节点的前驱
	for(count = 1; count < i; count++)					//移动指针p，使得p指向待插位置的前驱
		p = p->next;
	q = new Node<DataType>(e, p->next);					//创建一个新节点，next指向原来的第i个元素节点
	if (!q)   return ALLOCATE_ERROR;					//节点创建失败，返回分配不成功信息；
	p->next = q;										//修改前驱节点的后继指针指向新节点
	length++;
	return SUCCESS;
}

template <class DataType>
Status LinkList<DataType>::DeleteElem(int i, DataType &e) {	//删除第i个元素，通过e反馈给主调函数
	if(i < 1 || i > length)   return INVALID;
	Node<DataType> *p = head, *q;						//p初始指向头节点，即第1个元素节点的前驱
	int count;											//计数器，记录p指向第几个元素节点的前驱
	for(count = 1; count < i; count++)	 				//移动指针p，使其指向待删节点的前驱
		p = p->next;
	q = p->next;	     								//获取待删除节点
	p->next = q->next; 	 								//修改前驱节点的后继指针，指向待删节点的后继
	e = q->data;										//保存被删节点的数据值
	delete q;											//释放节点所占的存储单元
	length--;
	return SUCCESS;
}

template <class DataType>
void LinkList<DataType>::Traverse(void(*visit)(const DataType &)) const {
	Node<DataType> *p = head->next;   					//p指向第一个元素节点
	while(p != NULL) {     								//循环访问每一个元素节点，直到p为空指针
		(*visit)(p->data);  							//通过visit调用函数访问数据元素
		p = p->next;									//后移指针指向后继元素节点
	}
}